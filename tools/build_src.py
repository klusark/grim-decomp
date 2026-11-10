"""Turn raw/<prog>/functions/*.c into an organized source tree under src/<prog>/.

Module assignment: every function Ghidra has a real name for (Actor_*, Lua_*, ...)
belongs to the module named by its prefix. Unnamed FUN_* functions inherit the module
of the nearest preceding named function (code from one compilation unit is contiguous
in the image), except that a long run of unnamed functions becomes its own
region_<addr> module so we do not pretend to know what it is."""
import sys
import bisect, glob, json, os, re, sys
from collections import Counter, OrderedDict, defaultdict
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import frame_locals
import ftol_fold

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
RAW = os.path.join(ROOT, "raw")
SRC = os.environ.get("GRIM_SRC_DIR") or os.path.join(ROOT, "src")  # override for experiments
LONG_RUN = 30  # unnamed functions in a row before we split off a region_ module

# prefix -> module (lower-case prefix otherwise)
PREFIX_MAP = {
    "Vec3": "math3d", "Frustum": "math3d", "Polygon": "math3d", "Angles": "math3d",
    "Matrix": "math3d", "Camera": "math3d", "Math": "math",
    "PositionedSounds": "sound", "PositionedSound": "sound", "Sound": "sound",
    "SectorList": "sector", "Sector": "sector", "SectorVertexPool": "sector",
    "SetFile": "sector", "Set": "set", "Walker": "walker", "Planner": "walker",
    "Collision": "collision", "Cos": "costume", "Im": "imuse", "Sounds": "imuse",
    "iMUSE": "imuse", "grimSound": "imuse", "Chore": "chore", "Win": "window",
    "Engine": "engine", "Profile": "engine", "Timer": "timer", "Movie": "movie",
    "Renderer": "renderer", "String": "string", "lua": "lapi", "luaS": "lstring",
    "luaY": "lparser", "luaU": "lundump", "luaZ": "lzio", "hmiFX": "hmi",
    "luaL": "lauxlib", "luaB": "lbuiltin", "luaD": "ldo", "luaF": "lfunc", "luaX": "llex",
    "luaM": "lmem", "luaO": "lobject", "luaT": "ltm", "luaH": "ltable", "luaV": "lvm",
    "luaY_parse": "lparser", "luaC": "lgc", "luaA": "lapi", "luaI": "ltm",
    # MSVC C runtime internals with CamelCase or lowercase_prefix names
    "FindHandler": "crt", "CatchIt": "crt", "CallCatchBlock": "crt", "BuildCatchObject": "crt",
    "FrameUnwindToState": "crt", "Eh": "crt", "write": "crt", "get": "crt", "shortsort": "crt",
    "qsort": "crt", "doexit": "crt", "siglookup": "crt", "copy": "crt", "findenv": "crt",
    "terminate": "crt", "strtoxl": "crt", "wcstoxl": "crt", "wcsncnt": "crt", "iswctype": "crt",
    # grimjedi RDroid / Std libraries
    "rdRaster": "rdraster", "rdCache": "rdcache", "rdClip": "rdclip", "rdPuppet": "rdpuppet",
    "rdKeyframe": "rdpuppet", "rdThing": "rdthing", "rdSprite": "rdprimitive",
    "rdPolyline": "rdprimitive", "rdPrimit3": "rdprimit3", "rdCanvas": "rdcanvas",
    "rdMaterial": "rdmaterial", "rdCamera": "rdcamera", "rdModel": "rdmodel", "rdLight": "rdlight",
    "rdColormap": "rdcolormap", "rdroid": "rdroid",
    "Input": "stdinput", "D3D": "std3d", "Texture": "std3d",
    "DDraw": "stddisplay", "DIB": "stddisplay", "Display": "stddisplay", "Surface": "stddisplay",
    "Palette": "stddisplay", "Pixel": "stddisplay", "stdDisplay": "stddisplay",
    "stdBitmap": "stdbitmap", "stdBmp": "stdbmp", "stdGif": "stdgif", "stdPcx": "stdpcx",
    "stdLbm": "stdlbm", "stdFile": "stdfileutil", "stdCompress": "stdfileutil", "Std": "std",
    "stdMemory": "stdmemory", "Mem": "memory", "Str": "string", "Font": "text", "Text": "text",
    "TextObject": "textobject", "ObjectState": "objstate", "StateImage": "objstate",
    "Services": "services", "Svc": "services", "Res": "res", "Pool": "memory",
    "Mixer": "mixer", "DSound": "mixer", "Insane": "insane", "LightEd": "lighted",
    "LecShare": "lecshare", "Actor": "actor", "Costume": "costume", "Room": "room",
    "Walk": "walkplane", "WalkPlane": "walkplane", "Primitive": "primitives",
    "Matrix34": "math3d",
    # costume tag handlers with their original names (exact-name entries): keep them with their components
    "BitmapRequester": "bitmapcomponent", "ColormapRequester": "cmapcomponent", "ThingRequester": "modelcomponent",
    "KeyframeRequester": "keyframecomponent", "KeyframeAdjuster": "keyframecomponent",
}
# zlib 1.1.3 functions have no module prefix
ZLIB_NAMES = {"zlibVersion", "inflate", "deflate", "zcalloc", "zcfree", "crc32", "adler32",
              "inflateInit2_", "inflateEnd", "inflateReset", "deflateInit2_", "deflateReset",
              "deflateEnd", "putShortMSB", "flush_pending", "lm_init", "huft_build", "bi_flush",
              "bi_windup", "copy_block", "init_block", "fle_zfilio_config"}
ZLIB_PREFIXES = ("gz", "inflate_", "deflate_", "_tr_", "longest_match", "fill_window", "send_")
# address-range overrides for *unnamed* functions (start, end, module)
RANGES = {
    "GRIMFANDANGO.EXE": [(0x004AC540, 0x004D61FF, "crt")],
    "LUA.DLL": [(0x1001B000, 0x10021FFF, "crt")],
    "IMUSE.DLL": [(0x1000FA30, 0x10012FFF, "crt")],
}
IMPORT_NAMES = set()
# imports that are not Win32 stdcall: the game's own DLLs (cdecl) and the varargs ones
CDECL_IMPORTS = {"wsprintfA", "wsprintfW"}
# (hmiFX*: the HMI sound library's exports are __stdcall too, see the stdcall branch in the functions.h writer)
CDECL_IMPORT_PREFIXES = ("lua_", "Im", "Sounds", "Cos", "grimSound_", "iMUSE_", "hmiFX")
# decorated stdcall names from the mingw import libraries (build/gen_stdcall_names.py)
try:
    STDCALL_NAMES = json.load(open(os.path.join(ROOT, "build", "stdcall_names.json")))
except (OSError, ValueError):
    STDCALL_NAMES = {}


sys.path.insert(0, os.path.join(ROOT, "build"))
import dllnames
DLL_STDCALL = dllnames.load()  # EXE imports that are callee-pop exports of the rebuilt DLLs


# original names from the remaster (round orig-names, tools/orig_batch.py): {program: {name: module}} for the renamed
# functions whose new name would put them in another module (or crt.c); exact-name entries like PREFIX_MAP's, per
# program since the three DLLs share names such as `next`
try:
    ORIG_MODULES = json.load(open(os.path.join(ROOT, "names", "orig_modules.json")))
except (OSError, ValueError):
    ORIG_MODULES = {}


def module_for(name):
    if name.startswith("FUN_") or name.startswith("thunk_"):
        return None
    pinned = ORIG_MODULES.get(CUR_PROG, {}).get(name)
    if pinned:
        return pinned
    if name in IMPORT_NAMES or re.match(r"^(switchD|LAB|DAT)_", name):
        return None
    if name.startswith("lua_"):
        return "lapi"
    if name in ZLIB_NAMES or name.startswith(ZLIB_PREFIXES):
        return "zlib"
    if name.startswith("_"):  # _stricmp, _ftol, _findfirst, _setjmp3 ... (MSVC CRT)
        return "crt"
    if "__" in name:  # <module>__<addr> names from gen_dll_module_names.py
        return name.split("__", 1)[0].lower()
    if re.match(r"^(Im[A-Z]|Sounds[A-Z]|Sounds_)", name):
        return "imuse_api"
    if name in PREFIX_MAP:  # luaY_parse and other exact-name entries
        return PREFIX_MAP[name]
    if "_" not in name and name == name.lower():  # CRT names: atof, fopen, exit ...
        return "crt"
    p = name.split("_", 1)[0] if "_" in name else name
    return PREFIX_MAP.get(p, p.lower())


CUR_PROG = None


def read_text(path):
    with open(path, encoding="utf-8", errors="replace") as f:
        text = f.read()
    if text.startswith('{"error"'):
        # the decompiler gave up on this one (e.g. "Overlapping input varnodes"); keep a
        # trap body so the module still builds and the failure is visible in the source
        addr = os.path.basename(path)[:-2]
        reason = text.replace("\n", " ").replace("*/", "* /")[:200]
        return (f"/* Ghidra could not decompile this function: {reason} */\n"
                f"void FUN_{addr}(void)\n\n{{\n  __builtin_trap();\n}}\n")
    return text


# A function returning bool/char/short leaves only AL/AX defined in EAX when gcc compiles it; the original (MSVC) code that
# calls it, and assembled callers in general, test the whole of EAX.  Return types narrower than int are therefore widened.
RET_NARROW_RE = re.compile(r"\A((?:\s*/\*.*?\*/)*\s*)(bool|char|byte|undefined1|uchar|short|ushort|undefined2)(\s+(?:__\w+\s+)?[A-Za-z_]\w*\s*\()", re.S)
RET_WIDE = {"bool": "int", "char": "int", "short": "int", "byte": "uint", "undefined1": "uint", "uchar": "uint",
            "ushort": "uint", "undefined2": "uint"}


def widen_return_type(code):
    m = RET_NARROW_RE.match(code)
    if not m:
        return code
    return m.group(1) + RET_WIDE[m.group(2)] + code[m.end(2):]


def signature_of(code):
    s = _signature_of_raw(code)
    return ARRAY_RET_RE.sub(r"\1 *\3", s) if s else s


def _signature_of_raw(code):
    """Everything between the leading comment block(s) and the first `{` line,
    joined into one line: `type name(args)`."""
    body = re.sub(r"/\*.*?\*/", "", code, flags=re.S)
    head = body.split("\n{", 1)[0] if "\n{" in body else ""
    sig = " ".join(head.split())
    if sig and "(" in sig and sig.endswith(")"):
        return sig
    return None


GLOBAL_RE = re.compile(r"\b((?:_?DAT|PTR|PTR_s|s|u|LAB|FLOAT|DOUBLE|BYTE|WORD|DWORD|UNK)_[A-Za-z0-9_]*?_?[0-9a-f]{8})\b")


# ---------------------------------------------------------------------------
# Compilability fix-ups.
#
# Ghidra's C is a description of machine code, not a program: it reinterprets
# registers between pointer/float/int, reads sub-pieces of variables
# (`x._1_2_`), calls functions with a different argument count than their
# prototype, jumps to labels in other functions, and names globals without
# types. The passes below rewrite exactly those spots, with small macros
# from ghidra_types.h (PIECE, PUN, STACK0X, JUMPOUT), so that gcc -m32 accepts
# the result (see build/Makefile and build/BUILD_NOTES.md). Code that is
# already valid C is left as it is.
# ---------------------------------------------------------------------------

FLOAT_TYPES = {"float", "double", "float4", "float8", "float10", "unkbyte10", "long double"}
PRIM_TYPES = {
    "undefined", "undefined1", "undefined2", "undefined3", "undefined4", "undefined5",
    "undefined6", "undefined7", "undefined8", "byte", "word", "dword", "qword", "sbyte",
    "uchar", "ushort", "uint", "ulong", "longlong", "ulonglong", "float4", "float8", "float10",
    "code", "wchar16", "wchar_t", "int3", "uint3", "int5", "uint5", "int6", "uint6", "int7",
    "uint7", "unkbyte10", "unkuint10", "unkint10", "char", "short", "int", "long", "float",
    "double", "void", "bool", "unsigned", "signed", "size_t", "HANDLE", "HWND", "LPVOID",
    "DWORD", "BOOL", "BYTE", "WORD", "LPSTR", "LPCSTR", "string", "pointer", "dword",
}
CTRL_WORDS = {"if", "while", "for", "switch", "return", "sizeof", "else", "do", "case", "goto"}


def match_paren(s, i):
    """s[i] is an opening bracket; return the index of its partner (or len(s))."""
    opn = s[i]
    cls = {"(": ")", "[": "]", "{": "}"}[opn]
    depth = 0
    j = i
    n = len(s)
    while j < n:
        c = s[j]
        if c == "/" and s.startswith("/*", j):
            k = s.find("*/", j + 2)
            j = n if k < 0 else k + 2
            continue
        if c in "\"'":
            k = j + 1
            while k < n and s[k] != c:
                k += 2 if s[k] == "\\" else 1
            j = k + 1
            continue
        if c == opn:
            depth += 1
        elif c == cls:
            depth -= 1
            if depth == 0:
                return j
        j += 1
    return n


def split_top(s, sep=","):
    out, depth, cur = [], 0, []
    i = 0
    while i < len(s):
        c = s[i]
        if c in "([{":
            depth += 1
        elif c in ")]}":
            depth -= 1
        if c == sep and depth == 0:
            out.append("".join(cur))
            cur = []
        else:
            cur.append(c)
        i += 1
    out.append("".join(cur))
    return out


def base_type(t):
    t = re.sub(r"\b(const|volatile|struct|enum|union)\b", "", t)
    return " ".join(t.replace("*", " ").split())


def is_type(s, known):
    s = s.strip()
    if not s or not re.fullmatch(r"(?:(?:const|unsigned|signed|struct|enum|union)\s+)*[A-Za-z_]\w*(?:\s+\w+)*\s*(?:\*\s*)*(?:\[\s*\d*\s*\])?", s):
        return False
    b = base_type(s).split()
    if not b:
        return False
    if "*" in s:
        return True
    return all(w in known for w in b)


def type_kind(t):
    if t is None:
        return None
    if "*" in t or "[" in t:
        return "ptr"
    if base_type(t) in FLOAT_TYPES:
        return "float"
    return "int"


def deref(t):
    if t is None:
        return None
    if "[" in t:
        return re.sub(r"\s*\[[^\]]*\]\s*$", "", t)
    i = t.rfind("*")
    if i < 0:
        return None
    return t[:i].rstrip()


def parse_params(sig):
    """`ret cc name(params)` -> (ret, name, [(type, name)], variadic) or None."""
    m = re.match(r"^(.*?)\b([A-Za-z_]\w*)\s*\((.*)\)$", sig)
    if not m:
        return None
    ret, name, ps = m.group(1).strip(), m.group(2), m.group(3).strip()
    ret = re.sub(r"\b__\w+\b", "", ret).strip()
    params, variadic = [], False
    if ps and ps != "void":
        for p in split_top(ps):
            p = p.strip()
            if p == "...":
                variadic = True
                continue
            pm = re.match(r"^(.*?)([A-Za-z_]\w*)\s*(\[[^\]]*\])?$", p)
            if pm and pm.group(1).strip():
                params.append((pm.group(1).strip() + (" *" if pm.group(3) else ""), pm.group(2)))
            else:
                params.append((p, None))
    return ret, name, params, variadic


DECL_RE = re.compile(r"^\s+((?:const\s+|unsigned\s+|struct\s+)*[A-Za-z_]\w*(?:\s*\*)*)\s*(\**)\s*([A-Za-z_]\w*)\s*(\[[^\]]*\])?\s*;\s*$")


def split_function(code):
    """-> (head, body) where body starts at the opening brace line."""
    i = code.find("\n{")
    if i < 0:
        return code, ""
    return code[:i + 1], code[i + 1:]


def local_types(body):
    vt = {}
    for line in body.split("\n")[1:]:
        if not line.strip():
            break
        m = DECL_RE.match(line)
        if not m:
            break
        t = (m.group(1) + " " + m.group(2)).strip()
        if m.group(4):
            t += " " + m.group(4)
        vt[m.group(3)] = t
    return vt


class Ctx:
    """Per-program knowledge the rewrites need."""

    def __init__(self):
        self.protos = {}      # name -> (ret, params, variadic)
        self.cc = {}          # name -> __thiscall / __fastcall / __stdcall
        self.gtypes = {}      # global name -> declared C type (named globals)
        self.known_types = set(PRIM_TYPES)
        self.import_ints = set()   # names of the PE imports


# -- expression typing (best effort; None = unknown) -------------------------

NUM_RE = re.compile(r"(?:0x[0-9a-fA-F]+|\d+(?:\.\d*)?(?:[eE][-+]?\d+)?)[uUlLfF]*")
IDENT_RE = re.compile(r"[A-Za-z_]\w*")
BIN_OPS = ["||", "&&", "==", "!=", "<=", ">=", "<<", ">>", "|", "^", "&", "<", ">", "+", "-", "*", "/", "%"]


def unary_end(s, i, ctx):
    """End index of the unary expression that starts at s[i] (cast operand)."""
    n = len(s)
    while i < n and s[i] == " ":
        i += 1
    if i >= n:
        return i
    c = s[i]
    if c == "(":
        j = match_paren(s, i)
        if is_type(s[i + 1:j], ctx.known_types):
            return unary_end(s, j + 1, ctx)
        i = j + 1
    elif c in "*&-+!~":
        return unary_end(s, i + 1, ctx)
    else:
        m = NUM_RE.match(s, i) if c.isdigit() else IDENT_RE.match(s, i)
        if not m:
            return i
        i = m.end()
    while i < n:
        k = i
        while k < n and s[k] in " \n\t":
            k += 1  # Ghidra wraps long calls: `F\n      (args)`
        if k < n and s[k] in "[(":
            i = match_paren(s, k) + 1
        elif s.startswith("->", i) or (s[i] == "." and i + 1 < n and not s[i + 1].isdigit()):
            m = IDENT_RE.match(s, i + (2 if s[i] == "-" else 1))
            if not m:
                break
            i = m.end()
        else:
            break
    return i


def strip_parens(e):
    e = e.strip()
    while e.startswith("(") and match_paren(e, 0) == len(e) - 1:
        e = e[1:-1].strip()
    return e


def type_of(e, vt, ctx, depth=0):
    if depth > 30:
        return None
    e = strip_parens(e)
    if not e:
        return None
    # top-level binary operators
    operands, ops = [], []
    i, start, n, prev_operand = 0, 0, len(e), False
    while i < n:
        c = e[i]
        if c in "([":
            i = match_paren(e, i) + 1
            prev_operand = True
            continue
        if c in "?":
            return None
        if c.isalnum() or c in "_.":
            i += 1
            prev_operand = True
            continue
        if c == " ":
            i += 1
            continue
        op = next((o for o in BIN_OPS if e.startswith(o, i)), None)
        if op and prev_operand and not e.startswith("->", i):
            operands.append(e[start:i])
            ops.append(op)
            i += len(op)
            start = i
            prev_operand = False
            continue
        if e.startswith("->", i):
            i += 2
            continue
        i += 1
        prev_operand = False
    if ops:
        operands.append(e[start:])
        if any(o in ("||", "&&", "==", "!=", "<=", ">=", "<", ">") for o in ops):
            return "int"
        if any(o in ("<<", ">>", "|", "^", "&", "%") for o in ops):
            return "int"
        kinds = [type_of(x, vt, ctx, depth + 1) for x in operands]
        ks = [type_kind(k) for k in kinds]
        if "float" in ks:
            return "float10" if any(base_type(k or "") == "float10" for k in kinds) else "float"
        if "ptr" in ks:
            if "-" in ops and ks.count("ptr") > 1:
                return "int"
            return next(k for k in kinds if type_kind(k) == "ptr")
        if None in ks:
            return None
        return "int"
    # unary
    if e[0] == "(":
        j = match_paren(e, 0)
        inner = e[1:j]
        if is_type(inner, ctx.known_types):
            return " ".join(inner.split())
        # `(&local_1e0)[i]`: an element of a local used as the start of an array
        m = re.fullmatch(r"&\s*([A-Za-z_]\w*)", inner.strip())
        if m and e[j + 1:].lstrip().startswith("[") and m.group(1) in vt:
            return vt[m.group(1)]
        return None
    if e[0] == "*":
        return deref(type_of(e[1:], vt, ctx, depth + 1))
    if e[0] == "&":
        return "void *"
    if e[0] in "-+":
        return type_of(e[1:], vt, ctx, depth + 1)
    if e[0] in "!~":
        return "int"
    if e[0].isdigit():
        m = NUM_RE.match(e)
        if m and m.end() == len(e):
            return "double" if re.search(r"[.eE]", m.group(0)) and not m.group(0).startswith("0x") else "int"
        return None
    m = IDENT_RE.match(e)
    if not m:
        return None
    name = m.group(0)
    rest = e[m.end():]
    if name == "PUN":
        return " ".join(split_top(e[m.end() + 1:-1])[0].split())
    if name in ("ROUND", "SQRT"):
        return "float10"
    t = vt.get(name) or ctx.gtypes.get(name)
    is_func = False
    if t is None and name in ctx.protos:
        t, is_func = ctx.protos[name][0], True
    elif t is None and name in ctx.import_ints:
        t, is_func = "int", True  # (an imported function without a prototype is declared `extern int f();` in imports.h)
    i = 0
    while i < len(rest):
        if rest[i] == "[":
            j = match_paren(rest, i)
            t = deref(t)
            i = j + 1
        elif rest[i] == "(":
            j = match_paren(rest, i)
            if not is_func:
                t = None
            is_func = False
            i = j + 1
        else:
            return None
    if is_func:
        return "code *"
    return t


# -- the rewrites -----------------------------------------------------------

CAST_AT_RE = re.compile(r"\(([A-Za-z_][\w ]*?(?:\s*\*)*)\)")


_DISASM = {}
CUR_FN_ADDR = None


def int_float_conversions(addr):
    """-> (has FILD-like int->float conversion, has FIST-like float->int conversion) from the original code.
    Without them every `(float)intvar` / `(uint)(floatexpr)` in Ghidra's text is a bit reinterpretation of a
    stack slot or struct field that holds the other type (no value conversion exists in the machine code)."""
    if CUR_PROG not in _DISASM:
        try:
            _DISASM[CUR_PROG] = json.load(open(os.path.join(RAW, CUR_PROG, "disasm.json")))
        except (OSError, ValueError):
            _DISASM[CUR_PROG] = {}
    text = _DISASM[CUR_PROG].get(addr)
    if text is None:
        return True, True  # unknown: assume conversions exist (no rewrite)
    return bool(re.search(r"\bFI(?:LD|ADD|SUB|MUL|DIV|COM)", text)) or " CVTSI2S" in text, \
        bool(re.search(r"\bFIST", text)) or " CVTT" in text


def fix_casts(body, vt, ctx):
    """Ghidra reuses one register for a pointer and a float (`(float)param_2` with
    `float *param_2`, `(float *)((float)x * -1.0)`): C forbids those conversions,
    Ghidra means a bit-for-bit reinterpretation, i.e. PUN()."""
    casts = [m for m in CAST_AT_RE.finditer(body) if is_type(m.group(1), ctx.known_types)]
    has_fild, has_fist = int_float_conversions(CUR_FN_ADDR)
    # an int variable that gets a float's bits (`v = (uint)(float)x;` -> PUN below) holds a float: `(float)v` reads those
    # bits back, also in a function that has FILD for other conversions (`local_4 = (uint)(float)(int)i;
    # lua_pushnumber((float)local_4);` in sputLua_SubmitSaveGameData pushed 1065353216 for index 1, found by grim_tools/cleanroom)
    float_slots = set() if has_fist else set(re.findall(
        r"\b(\w+)\s*=\s*\(\s*(?:u?int|undefined4|ulong|long|dword)\s*\)\s*\(\s*float\s*\)", body))

    for m in reversed(casts):
        T = " ".join(m.group(1).split())
        tk = type_kind(T)
        if tk not in ("float", "ptr") and not (tk == "int" and not has_fist):
            continue
        # skip things that are not casts: `sizeof(int *)`, declarations, prototypes
        pre = body[:m.start()].rstrip()
        if pre.endswith("sizeof"):
            continue
        s = m.end()
        e = unary_end(body, s, ctx)
        if e <= s:
            continue
        operand = body[s:e]
        ok = type_kind(type_of(operand, vt, ctx))
        if tk == "float" and ok == "int" and (not has_fild or operand.strip() in float_slots) \
                and not NUM_RE.fullmatch(operand.strip()) \
                and CAST_AT_RE.sub("", operand.strip()) != "" and not operand.lstrip().startswith("ROUND"):
            new = f"PUN({T},{operand.strip()})"  # int slot read as float
        elif tk == "int" and ok == "float" and not has_fist and re.fullmatch(r"(?:u?int|undefined4|uint|ulong|long|dword)", T) \
                and "ROUND" not in operand:
            new = f"PUN({T},(float){operand.strip()})"  # float stored through an int slot
        elif tk == "float" and ok == "ptr":
            new = f"PUN(float,{operand.strip()})"
            if base_type(T) != "float":
                new = f"({T}){new}"
        elif tk == "ptr" and ok == "float":
            new = f"PUN({T},(float){operand.strip()})"
        else:
            continue
        body = body[:m.start()] + new + body[e:]
    return body


def fix_pieces(body):
    """`x._1_2_` (bytes 1..2 of x) -> PIECE(x,1,2), an lvalue of that width."""
    prev = None
    while prev != body:
        prev = body
        body = re.sub(r"\b([A-Za-z_]\w*)\._(\d+)_(\d+)_\b", r"PIECE(\1,\2,\3)", body)
        body = re.sub(r"(PIECE\([^()]*\))\._(\d+)_(\d+)_\b", r"PIECE(\1,\2,\3)", body)
    return body


def fix_views(body, vt):
    """`_local_4` is Ghidra's other-width view of local_4 (like `_DAT_x` for globals)."""
    def rep(m):
        n = m.group(1)
        return f"PIECE({n},0,4)" if n in vt and "_" + n not in vt else m.group(0)
    body = re.sub(r"\b_([A-Za-z]\w*)\b", rep, body)
    # NAN(x) is Ghidra's "unordered" test; a bare NAN is the constant
    return re.sub(r"\bNAN\s*\(", "ISNAN(", body)


def fix_pseudo_regs(body):
    body = re.sub(r"\bstack0x([0-9a-f]+)\b", r"STACK0X(0x\1)", body)
    body = re.sub(r"\bregister0x([0-9a-f]+)\b", r"REGISTER0X(0x\1)", body)
    # `unaff_FS_OFFSET` is the SEH chain head FS:[0]; Ghidra leaves it as an
    # uninitialised local. Point it at the TEB, whose first dword is FS:[0].
    body = re.sub(r"^(\s*)([\w ]+?\s*\*+)\s*unaff_FS_OFFSET;", r"\1\2unaff_FS_OFFSET = (\2)TEB_BASE();", body, flags=re.M)
    return body


def fix_jumps(body):
    """`goto LAB_x;` where LAB_x is not in this function (Ghidra split a function or
    jumps into a tail of another one) -> JUMPOUT(LAB_x), which traps."""
    labels = set(re.findall(r"^\s*([A-Za-z_]\w*):", body, flags=re.M))
    def rep(m):
        return m.group(0) if m.group(1) in labels else f"JUMPOUT({m.group(1)});"
    return re.sub(r"\bgoto\s+([A-Za-z_]\w*)\s*;", rep, body)


def fix_switch(body, vt, ctx):
    """`switch(ptr)` / `case (byte *)0x1:` -> integer switch."""
    body = re.sub(r"\bcase\s+\([\w ]+\*+\)\s*", "case ", body)
    out, pos = [], 0
    for m in re.finditer(r"\bswitch\s*\(", body):
        if m.start() < pos:
            continue
        j = match_paren(body, m.end() - 1)
        expr = body[m.end():j]
        if type_kind(type_of(expr, vt, ctx)) in ("ptr", "float"):
            out.append(body[pos:m.end()] + f"(int)({expr})")
            pos = j
    out.append(body[pos:])
    return "".join(out)


def call_is_statement(s, start, end):
    k = end
    while k < len(s) and s[k] in " \t":
        k += 1
    if k >= len(s) or s[k] != ";":
        return False
    k = start - 1
    while k >= 0 and s[k] in " \t\n":
        k -= 1
    if k < 0 or s[k] in ";{}:":
        return True
    if s[k] == ")":
        # find the matching "(" and look at the keyword before it
        depth = 0
        while k >= 0:
            if s[k] == ")":
                depth += 1
            elif s[k] == "(":
                depth -= 1
                if depth == 0:
                    break
            k -= 1
        w = re.search(r"(\w+)\s*$", s[:k])
        return bool(w and w.group(1) in ("if", "while", "for"))
    return bool(re.search(r"\belse$", s[:k + 1]))


def fix_calls(body, vt, ctx, stats):
    """Calls that disagree with the callee's prototype (argument count, or the result
    of a `void` function used as a value - both are prototype errors in Ghidra)
    go through an unprototyped pointer: ((code *)F)(args). Same machine code
    for cdecl, and the compiler stops second-guessing the decompiler. When the
    callee is __thiscall/__fastcall, or a float is passed (an unprototyped call
    would promote it to double), the cast spells out the call Ghidra saw:
    ((void (__thiscall *)(float))F)(x)."""
    out, pos = [], 0
    for m in re.finditer(r"(?<![\w.>])([A-Za-z_]\w*)\s*\(", body):
        name = m.group(1)
        if m.start() < pos or name not in ctx.protos or name in CTRL_WORDS:
            continue
        ret, params, variadic = ctx.protos[name]
        j = match_paren(body, m.end() - 1)
        args = body[m.end():j]
        nargs = 0 if not args.strip() else len(split_top(args))
        bad = nargs < len(params) or (nargs > len(params) and not variadic)
        if not bad and ret == "void" and not call_is_statement(body, m.start(), j + 1):
            # `x = F()` / `(float10)F()` with F declared void
            bad = not body[:m.start()].rstrip().endswith("return")
        if bad:
            stats["calls"] += 1
            argl = split_top(args) if args.strip() else []
            types = []
            for i, a in enumerate(argl):
                if i < len(params) and len(argl) >= len(params):
                    t = params[i][0]  # surplus arguments: the first ones match
                else:
                    k = type_kind(type_of(a, vt, ctx))
                    t = "float" if k == "float" else ("void *" if k == "ptr" else "int")
                types.append(" ".join(t.split()))
            cc = ctx.cc.get(name, "")
            if cc or any(type_kind(t) == "float" for t in types):
                r = ret if ret != "void" or call_is_statement(body, m.start(), j + 1) else "int"
                fn = f"(({r} ({cc + ' ' if cc else ''}*)({', '.join(types) or 'void'})){name})("
            else:
                fn = f"((code *){name})("
            out.append(body[pos:m.start()] + fn)
            pos = m.end()
    out.append(body[pos:])
    return "".join(out)


ODD_SYM_RE = re.compile(r"\b((?:PTR_)?[su]_[^\s,;]*?_[0-9a-f]{8})\b")
RAM_TYPES = {"i": "int", "u": "uint", "f": "float", "c": "char", "b": "byte", "s": "short",
             "us": "ushort", "d": "double", "pc": "code *", "p": "void *", "pp": "void **",
             "pi": "int *", "pu": "uint *", "pf": "float *", "pb": "byte *", "pv": "void *"}


ARRAY_RET_RE = re.compile(r"^(\w[\w ]*?)\s*\[(\d+)\]\s+(\w+\()", re.M)


IMG_SECTIONS = []  # [(name, start, size)] of the program being built (raw/<prog>/sections.json)
FUNC_AT = {}       # address int -> C name of every function of the program being built
ASM_ADDRS = set()  # functions replaced by src/<prog>/asm_funcs.s (tools/gen_asm.py)
LIB_REPL = {}      # address -> category of the functions taken out of the build (names/lib_replace.json)
DATA_ELT = {}   # address -> C type for a Ghidra data item of 2 or 4 bytes (raw/<prog>/data_items.txt)
ELT_TYPES = {"undefined4": "undefined4", "dword": "undefined4", "int": "undefined4", "uint": "undefined4",
             "undefined2": "undefined2", "word": "undefined2", "short": "undefined2", "ushort": "undefined2",
             "undefined1": "undefined", "byte": "undefined", "char": "undefined"}
ACCESS_ELT = {}  # address -> C type of the narrowest direct access (raw/<prog>/access_sizes.json)
PTR_TYPES = {}  # PTR_<addr> -> pointee type applied in Ghidra (raw/<prog>/ptr_types.json)
STDCALL_FUNCS = set()  # C names of callee-pop functions (raw/<prog>/stdcall_funcs.json)


def load_lib_replace(prog):
    """{address: category} of the functions names/lib_replace.json takes out of the build: "dead" (original C runtime
    / zlib code that nothing live can reach, see tools/lib_audit.py), "host" / "zlib" (replaced by the system
    library; the symbol resolves to msvcrt.dll / libz.a or to a generated alias)."""
    path = os.path.join(ROOT, "names", "lib_replace.json")
    out = {}
    if os.path.exists(path):
        for cat, addrs in json.load(open(path)).get(prog, {}).items():
            if cat == "zlib" and os.environ.get("GRIM_BUNDLED_ZLIB"):
                continue   # build the game's own zlib 1.1.3 again (needs src/ + asm regenerated with the variable set)
            for a in addrs:
                out[a] = cat
    return out


GUARD_PROG = {"GRIM_EXE": "GRIMFANDANGO.EXE", "GRIM_LUA": "LUA.DLL", "GRIM_IMUSE": "IMUSE.DLL", "GRIM_CHORE": "CHORE.DLL"}
ALL_PROGS = frozenset(GUARD_PROG.values())
_GUARD = r"\bGRIM_(?:EXE|LUA|IMUSE|CHORE)\b"


def _guard_set(cond, parent):
    """Programs for which an #if condition holds; None when it is not a program guard (the block then inherits its
    parent).  `0` is no program, `defined(GRIM_X) || defined(GRIM_Y)` (or a bare name) the listed ones."""
    cond = cond.strip()
    if re.fullmatch(r"0\b.*", cond):
        return frozenset()
    names = re.findall(_GUARD, cond)
    rest = re.sub(r"defined\s*\(\s*GRIM_(?:EXE|LUA|IMUSE|CHORE)\s*\)|" + _GUARD + r"|\|\||[\s()]", "", cond)
    if not names or rest:
        return None
    return frozenset(GUARD_PROG[n] for n in names) & parent


def load_overrides():
    """Names of the functions build/overrides.c, build/fastpaths.c and build/overrides_*.c define by hand, per program.
    Each file is compiled for every program (build/link.py) and guards its code with #ifdef GRIM_EXE / GRIM_LUA /
    GRIM_IMUSE / GRIM_CHORE, so a name only counts for the programs whose guard encloses its definition: the three DLLs
    share the image base 0x10000000, so a FUN_1000xxxx name of one DLL is often an unrelated function of another
    (CHORE.DLL's hand-written FUN_10004970 used to turn IMUSE.DLL's own FUN_10004970, called at shutdown, into a trap
    stub).  Returns {program: set of names}."""
    by_prog = {p: set() for p in ALL_PROGS}
    defn = re.compile(r"^[A-Za-z_][\w *]*?\b(\w+)\s*\([^;{]*\)\s*\{", re.M)
    for fname in ["overrides.c", "fastpaths.c"] + sorted(os.path.basename(x) for x in glob.glob(os.path.join(ROOT, "build", "overrides_*.c"))):
        path = os.path.join(ROOT, "build", fname)
        if not os.path.exists(path):
            continue
        text = open(path, encoding="utf-8").read()
        lines = text.split("\n")
        # programs in force on each line: a stack of (this branch, parent, programs of the branches before an #else)
        progs_at = []
        stack = [(ALL_PROGS, ALL_PROGS, frozenset())]
        for line in lines:
            m = re.match(r"\s*#\s*(ifdef|ifndef|if|elif|else|endif)\b(.*)", line)
            if m:
                kind, cond = m.group(1), m.group(2)
                cur, parent, taken = stack[-1]
                if kind in ("ifdef", "ifndef", "if"):
                    g = (_guard_set("defined(%s)" % cond.strip(), cur) if kind == "ifdef" else
                         _guard_set(cond, cur) if kind == "if" else None)
                    stack.append((cur if g is None else g, cur, frozenset() if g is None else g))
                elif len(stack) > 1 and kind == "elif":
                    g = _guard_set(cond, parent)
                    stack[-1] = (parent if g is None else g - taken, parent, taken | (g or frozenset()))
                elif len(stack) > 1 and kind == "else":
                    stack[-1] = (parent - taken if taken else parent, parent, taken)
                elif len(stack) > 1 and kind == "endif":
                    stack.pop()
            progs_at.append(stack[-1][0])
        starts = [0]
        for line in lines:
            starts.append(starts[-1] + len(line) + 1)

        def progs_of(pos):
            return progs_at[bisect.bisect_right(starts, pos) - 1]

        for m in defn.finditer(text):
            for p in progs_of(m.start()):
                by_prog[p].add(m.group(1))
        # functions written in top-level asm() blocks are declared by a `/* OVERRIDES: a b c */` line
        for m in re.finditer(r"^/\* OVERRIDES: ([^*]*?)\s*\*/", text, re.M):
            for p in progs_of(m.start()):
                by_prog[p] |= set(m.group(1).split())
    return by_prog


OVERRIDES_BY_PROG = load_overrides()
OVERRIDES = set().union(*OVERRIDES_BY_PROG.values())   # any program (for tools that do not know the program)
FLOAT_RETURNERS_NOW = ftol_fold.float_returners()   # float/double-returning functions (previous functions.h)
# modules that call DirectX COM objects: every `(**(code **)(` / `(*(code *)**` in them is a vtable
# method call (the cdecl service-table calls live in other modules)
COM_MODULES = {"std3d", "stddisplay", "stdinput", "mixer", "rdmaterial"}
COM_VTBL_RE = re.compile(r"(\(\*\*\()code( \*\*\)\(\*)")
COM_CALL_RE = re.compile(r"(\(\*\*?\()code( \*\*?\))")
IMG_LIT_RE = re.compile(r"\b0x([0-9a-f]{6,8})\b")
# `(int)puVar3 <` / `ppvVar8 <=` / `(uint)param_1 ==` just before a literal, and
# `< (int)piVar3` just after it: Ghidra's pointer temporaries and parameters
PTR_OPERAND = r"(?:\((?:u?int)\)\s*)?(?:p[a-zA-Z]*Var\d+|param_\d+)"
CMP_BEFORE_RE = re.compile(PTR_OPERAND + r"\s*(?:<=|>=|==|!=|<|>)$")
CMP_AFTER_RE = re.compile(r"^(?:<=|>=|==|!=|<|>)\s*" + PTR_OPERAND + r"\b")


def fix_image_addrs(code):
    """A literal such as 0x4ed080 that falls inside a dumped data section is an
    address Ghidra printed as a number (typically an argument to an import with
    an integer prototype): make it IMG_ADDR(0x4ed080), which relocates it into
    the rebuilt section.  Only in pointer-like positions (argument, assignment,
    cast operand, return value): a literal next to an arithmetic or bitwise
    operator, or in a case label, is a constant and stays as it is."""
    if not IMG_SECTIONS:
        return code

    def rep(m):
        v = int(m.group(1), 16)
        if v in FUNC_AT:  # a code address: a callback or function-pointer argument
            before = code[:m.start()].rstrip()
            if before[-1:] in "(,=" or before.endswith("return"):
                return "((unsigned)(uintptr_t)%s)" % FUNC_AT[v]
            return m.group(0)
        if not any(start <= v <= start + size for _, start, size in IMG_SECTIONS):
            return m.group(0)
        before = code[:m.start()].rstrip()
        after = code[m.end():].lstrip()
        # a pointer compared with an address: `(int)puVar3 < 0x8dacf0` is a loop
        # bound at the end of a table (sometimes end + 1), `0x8da86b < (int)piVar3`
        # the same the other way round. The literal relocates with the table.
        if CMP_BEFORE_RE.search(before) or CMP_AFTER_RE.match(after):
            return "IMG_ADDR(0x%08x)" % v
        if before.endswith(("&", "|", "^", "+", "-", "*", "/", "%", "<<", ">>", "~", "<", ">")) \
                or before.endswith("case") or (before[-1:] not in "(,=)" and not before.endswith("return")):
            return m.group(0)
        if after[:1] in ("&", "|", "^", "*", "/", "%", "<", ">", "+", "-", ":"):
            if not after.startswith("->"):
                return m.group(0)
        return "IMG_ADDR(0x%08x)" % v
    code = IMG_LIT_RE.sub(rep, code)
    code = PTRDIFF_RE.sub(ptrdiff, code)
    return fix_indexed_addrs(code)


PTRDIFF_RE = re.compile(r"\b([A-Za-z_]\w*) \+ -0x([0-9a-f]{6})\b")


def ptrdiff(m):
    """`(int)(PTR + -0x2355bf) / 0xc`: PTR is an int * and the constant is an address divided by 4
    (0x8d56fc), so this is `(PTR - table) / 12` with the table at its original address. Written as
    a byte offset from the relocated section address."""
    k = int(m.group(2), 16) * 4
    if not any(start <= k <= start + size for _, start, size in IMG_SECTIONS):
        v = int(m.group(2), 16)
        if any(start <= v <= start + size for _, start, size in IMG_SECTIONS):
            # `iVar + -0x8cb0b0 >> 4`: an int minus the byte address of a table (an index into it): the
            # address relocates with the table, a bare literal would be off by the section shift
            return "%s - (int)IMG_ADDR(0x%08x)" % (m.group(1), v)
        return m.group(0)
    return "(int *)((char *)%s - IMG_ADDR(0x%08x))" % (m.group(1), k)


DEREF_OPEN_RE = re.compile(r"\(\s*[A-Za-z_][\w ]*?\s*\*+\s*\)\(")  # `*(T *)(` and `(T *)(`: a pointer cast of a sum
ADD_LIT_RE = re.compile(r"(?<![\w*&<>])((?:[+]\s*)0x([0-9a-f]{6,8})\b|\b0x([0-9a-f]{6,8})\s*[+])")


def fix_indexed_addrs(code):
    """`*(int *)(iVar5 * 4 + 0x8db0a8)` is `array[i]` for a global array: the literal is the
    array's address and has to move with the rebuilt section. Inside the group that follows a
    pointer-dereferencing cast `*(T *)(`, a literal added to something and falling in a dumped
    section becomes IMG_ADDR(...). (A literal elsewhere next to `+` may be a plain constant.)"""
    if not IMG_SECTIONS:
        return code

    def in_image(v):
        return any(start <= v <= start + size for _, start, size in IMG_SECTIONS)

    out = []
    pos = 0
    for m in DEREF_OPEN_RE.finditer(code):
        if m.start() < pos:
            continue  # inside a group already handled
        depth, i = 1, m.end()
        while i < len(code) and depth:
            depth += {"(": 1, ")": -1}.get(code[i], 0)
            i += 1
        group = code[m.end():i - 1]

        def lit(mm):
            v = int(mm.group(2) or mm.group(3), 16)
            if not in_image(v):
                return mm.group(0)
            if mm.group(2):
                return "+ IMG_ADDR(0x%08x)" % v
            return "IMG_ADDR(0x%08x) +" % v

        new_group = ADD_LIT_RE.sub(lit, group)
        out.append(code[pos:m.end()])
        out.append(new_group)
        pos = i - 1
    out.append(code[pos:])
    return "".join(out)


def fix_symbols(code):
    """Ghidra string labels keep punctuation from the string (`s_Resource_<__12s>_00..`,
    `s_threeDNum_>__0__(i_004dd7a4`); make them identifiers. `iRam00000002` is
    an absolute address read: `(*(int *)0x00000002)`."""
    def odd(m):
        t = m.group(1)
        return re.sub(r"\W", "_", t) if re.search(r"\W", t) else t
    code = ODD_SYM_RE.sub(odd, code)
    # `undefined1 [10] f(void)`: an array cannot be returned in C, use a pointer
    code = ARRAY_RET_RE.sub(r"\1 *\3", code)
    def ram(m):
        t = RAM_TYPES.get(m.group(1), "undefined4")
        return f"(*({t} *)0x{m.group(2)})"
    return re.sub(r"\b([a-z]*)Ram([0-9a-f]{8})\b", ram, code)


def fix_fnptr_calls(body, vt, ctx):
    """`(*fn)(x)` with `void *fn` (Ghidra's type for most callbacks) -> `(*(code *)fn)(x)`."""
    def rep(m):
        inner = m.group(1)
        t = type_of(inner, vt, ctx)
        if t is not None and base_type(t) == "void" and t.count("*") == 1:
            return f"(*(code *){inner})("
        return m.group(0)
    return re.sub(r"\(\*(\**\s*[A-Za-z_]\w*(?:->\w+)?)\)\s*\(", rep, body)


DWORD_DEREF_RE = re.compile(r"\s*\*\s*\(\s*(?:undefined4|uint|int|dword|ulong|long)\s*\*\s*\)\s*\(")


DWORD_TYPES = ("undefined4", "uint", "int", "dword", "ulong", "long")


def is_dword_type(t):
    t = " ".join((t or "").replace("unsigned int", "uint").replace("unsigned long", "ulong").split())
    return t in DWORD_TYPES


def is_dword_lvalue(a, ctx=None):
    """`v`, `v[i]`, `(&v)[i]` or `*(undefined4 *)(...)`: a dword read as it is, no arithmetic on it."""
    if re.fullmatch(r"\s*[A-Za-z_]\w*(?:\s*\[[^\]]*\])?\s*", a):
        return True
    if re.fullmatch(r"\s*\(\s*&\s*[A-Za-z_]\w*\s*\)\s*\[.*\]\s*", a) and match_paren(a, a.index("[")) == len(a.rstrip()) - 1:
        return True
    m = DWORD_DEREF_RE.match(a)
    if not m:
        return False
    j = match_paren(a, m.end() - 1)
    return j is not None and j >= 0 and a[j + 1:].strip() == ""


ASSIGN_RE = re.compile(r"(?m)^([ \t]*)([^;=\n{}]*?[\w\])])\s*=\s*([^;=\n][^;\n]*);[ \t]*$")


def fix_assign_bits(body, vt, ctx, stats):
    """`dword = float-expression;` stores the float's bits in the machine code (FSTP to the dword); C would convert the
    value. Ghidra writes a real conversion as ROUND()/(int)(...), so an implicit one is a bit copy:
    `_DAT_008ca320 = fVar7;` -> PUN(undefined4,(float)(fVar7)). (Collision_*, rdModel3, rdPrimitive and std3d stored
    floats this way, found by grim_tools/cleanroom with gcc -Wfloat-conversion.)"""
    def repl(m):
        ind, lhs, rhs = m.groups()
        if "==" in rhs or lhs.rstrip().endswith(("!", "<", ">", "+", "-", "*", "/", "|", "&", "^", "%")):
            return m.group(0)
        rk = "float" if re.fullmatch(r"\s*\*\(float \*\)&DAT_[0-9a-f]{8}\s*", rhs) else type_kind(type_of(rhs.strip(), vt, ctx))
        if rk != "float" or NUM_RE.fullmatch(rhs.strip()) or rhs.lstrip().startswith("PUN("):
            return m.group(0)
        g = re.fullmatch(r"\s*_?(DAT_[0-9a-f]{8})\s*", lhs)
        if g and type_of(lhs.strip(), vt, ctx) is None:
            # an unnamed global gets its C type later (from all its uses), as a dword when it is also used as one:
            # store the float through a float view of its address, which is right whatever that type is
            stats["args"] += 1
            return f"{ind}*(float *)&{g.group(1)} = {rhs.strip()};"
        lt = type_of(lhs.strip(), vt, ctx)
        if not is_dword_type(lt):
            return m.group(0)
        stats["args"] += 1
        return f"{ind}{lhs} = PUN({' '.join(lt.split())},(float)({rhs.strip()}));"
    for _ in range(8):   # (until nothing changes: a value copied from one such global to another)
        before = body
        body = ASSIGN_RE.sub(repl, body)
        # the other uses of a global stored as a float above are floats too (`fVar5 = _DAT_008ca320;`, `_DAT_x - v`)
        for g in sorted(set(re.findall(r"\*\(float \*\)&(DAT_[0-9a-f]{8}) = ", body))):
            body = re.sub(r"(?<![\w&])_?" + g + r"\b", "*(float *)&" + g, body)
            body = body.replace("*(float *)&*(float *)&" + g, "*(float *)&" + g)
            # (a store that was given the dword's bits before the global became a float view takes the float itself)
            body = re.sub(r"(?m)^([ \t]*\*\(float \*\)&" + g + r" = )PUN\([\w ]+,\(float\)\((.*)\)\);[ \t]*$", r"\1\2;", body)
        if body == before:
            break
    return body


def fix_call_args(body, vt, ctx, stats):
    """A float parameter given a pointer-typed variable (or the reverse) is again one
    register reused by Ghidra: PUN the argument."""
    starts = [m for m in re.finditer(r"(?<![\w.>)])([A-Za-z_]\w*)\s*\(", body)
              if m.group(1) in ctx.protos and m.group(1) not in CTRL_WORDS]
    for m in reversed(starts):
        ret, params, variadic = ctx.protos[m.group(1)]
        open_i = body.index("(", m.start())
        j = match_paren(body, open_i)
        args = split_top(body[open_i + 1:j]) if body[open_i + 1:j].strip() else []
        if len(args) < len(params) or (len(args) > len(params) and not variadic):
            continue  # went through ((code *)F) already
        changed = False
        for i, (pt, _) in enumerate(params):
            a = args[i]
            pk, ak = type_kind(pt), type_kind(type_of(a, vt, ctx))
            if pk == "float" and ak == "ptr":
                args[i] = f"PUN(float,{a.strip()})"
            elif pk == "ptr" and ak == "float":
                args[i] = f"PUN({pt},(float){a.strip()})"
            elif pk == "float" and re.fullmatch(r"\s*0x[0-9a-f]{6,8}\s*", a) and int(a, 16) >= 0x00800000:
                # a float constant the decompiler printed as the hex of its bits (callee's float parameter)
                args[i] = f"FBITS({a.strip()})"
            elif pk == "float" and is_dword_lvalue(a, ctx) and (
                    (ak == "int" and is_dword_type(type_of(a, vt, ctx))) or
                    (ak is None and re.match(r"\s*\(?\s*&?\s*(?:UINT|INT|DAT|_DAT)_[0-9a-f]{8}\b", a))):
                # a dword variable (or a dword read through a pointer) for a float parameter: the machine code pushes
                # its bits (Ghidra writes (float) for a FILD conversion). rdMatrix_LookAt passed the roll (undefined4)
                # to rdMatrix_BuildFromVectorAngle34's float angle, and C converted 5.0's bits to 1084227584.0; rdThing_Draw passed the
                # model radius `*(undefined4 *)(model + 0x5c)` to rdClip_SphereInFrustrum (found by grim_tools/cleanroom)
                args[i] = f"PUN(float,{a.strip()})"
            elif pk == "int" and ak == "float" and is_dword_type(pt) and not NUM_RE.fullmatch(a.strip()):
                # the reverse: a float for a dword parameter is pushed as its bits (Ghidra writes the conversion as
                # ROUND()/(int) otherwise); the sprite component's rdSprite_New got the width truncated to an int
                args[i] = f"PUN({' '.join(pt.split())},(float)({a.strip()}))"
            else:
                continue
            changed = True
            stats["args"] += 1
        if changed:
            body = body[:open_i + 1] + ",".join(args) + body[j:]
    return body


def fix_stdcall(code):
    """Add __stdcall to the definition of a callee-pop function (see STDCALL_FUNCS)."""
    head, body = split_function(code)
    if not body or not STDCALL_FUNCS:
        return code
    # the signature follows the plate comment, which may itself contain `Name (` text
    cut = head.rfind("*/") + 2 if "*/" in head else 0
    plate, sig = head[:cut], head[cut:]
    names = re.findall(r"\b([A-Za-z_]\w*)\s*\((?!\*)", sig)
    name = names[-1] if names else None
    if name in STDCALL_FUNCS and "__stdcall" not in sig and "__fastcall" not in sig and "__thiscall" not in sig:
        sig = re.sub(r"\b" + re.escape(name) + r"\s*\(", "__stdcall " + name + "(", sig, count=1)
    return plate + sig + body


# ---- x87 return values feeding _ftol (Ghidra cannot pass ST0 to `_ftol`) ------------------------------------
# The game converts Lua numbers with `lua_getnumber(obj); _ftol();`: the float comes back in ST0 and _ftol
# consumes it.  Ghidra prints the call as a statement and the _ftol argument as stack garbage
#     lua_getnumber(iVar1);
#     lVar5 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
# so the statement before a garbage `_ftol` call, when it is a call of a function that returns in ST0, is the value.
_X87_NAMES = {}


def x87_float_names():
    if CUR_PROG not in _X87_NAMES:
        names = set()
        rawdir = os.path.join(RAW, CUR_PROG)
        try:
            found = json.load(open(os.path.join(rawdir, "x87_returns.json")))
            byaddr = {f["address"]: f["name"] for f in json.load(open(os.path.join(rawdir, "functions.json")))}
            for k in found:
                names.add(byaddr.get(k, k))
        except OSError:
            pass
        names.discard("_ftol")
        _X87_NAMES[CUR_PROG] = names
    return _X87_NAMES[CUR_PROG]


FTOL_GARBAGE_RE = re.compile(r"^(?P<ind>[ \t]*)(?:(?P<lhs>[A-Za-z_]\w*) = )?_ftol\((?:\(double\)CONCAT44\([^;]*\))?\);[ \t]*$")
PREV_CALL_RE = re.compile(r"^(?P<ind>[ \t]*)(?:(?P<v>[A-Za-z_]\w*) = )?(?P<f>[A-Za-z_]\w*)\((?P<a>.*)\);[ \t]*$")


def seh_strip_allowed():
    """names/seh_strip*.json {prog: [addresses]}: functions whose C++ exception frame may be dropped (see strip_seh_frames)"""
    global _SEH_OK
    if _SEH_OK is None:
        _SEH_OK = set()
        for path in glob.glob(os.path.join(ROOT, "names", "seh_strip*.json")):
            for prog, addrs in json.load(open(path)).items():
                if prog != "_comment":
                    _SEH_OK |= {(prog, a) for a in addrs}
    return (CUR_PROG, CUR_FN_ADDR) in _SEH_OK


_SEH_OK = None


def fix_ftol(body, seh=True):
    if seh and seh_strip_allowed():
        body = strip_seh_frames(body)
    lines = body.split("\n")
    names = x87_float_names()
    out = []
    for ln in lines:
        m = FTOL_GARBAGE_RE.match(ln)
        if m and m.group("lhs") and out:  # a bare `_ftol();` hides a use of EAX that Ghidra dropped: stays assembly
            pm = PREV_CALL_RE.match(out[-1])
            if pm and pm.group("f") in names:
                lhs = "%s = " % m.group("lhs")
                if pm.group("v"):  # `fVar = f(..);` already named
                    out.append("%s%sFTOL(%s);" % (m.group("ind"), lhs, pm.group("v")))
                else:
                    out[-1] = "%s%sFTOL(%s(%s));" % (m.group("ind"), lhs, pm.group("f"), pm.group("a"))
                continue
        out.append(ln)
    return drop_unused_artifacts("\n".join(out))



# ---- C++ exception frames (SEH registration) ----------------------------------------------------------------
# MSVC registers an exception frame in every function that constructs/destroys C++ objects:
#     uStack_4 = 0xffffffff;  pcStack_8 = FUN_10021fe6;  uStack_c = *unaff_FS_OFFSET;  *unaff_FS_OFFSET = &uStack_c;
#     ... uStack_4 = 0; ...        *unaff_FS_OFFSET = uStack_c;       (state changes, unlink before returning)
# The frame only matters when a C++ exception unwinds through the function (it runs the destructors listed in the
# handler's table).  The game never throws; the only thing that unwinds is longjmp, which does not run them either way.
# The frame is removed when its three variables are used for nothing else.
SEH_PREV_RE = re.compile(r"^[ \t]*(\w+) = \*unaff_FS_OFFSET;[ \t]*$", re.M)


def strip_seh_frames(body):
    if "unaff_FS_OFFSET" not in body or "unaff_EBP" in body:
        return body
    prevs = SEH_PREV_RE.findall(body)
    if len(prevs) != 1:
        return body
    prev = prevs[0]
    lines = body.split("\n")
    # the registration statements sit together at the start of the body: `prev = *fs:[0]`, the handler, the state
    # (-1 in a constructor, 0 in a destructor) and `*fs:[0] = &prev`, in any order
    first = next((i for i, l in enumerate(lines) if re.match(r"^[ \t]*%s = \*unaff_FS_OFFSET;" % prev, l)), None)
    reg = next((i for i, l in enumerate(lines) if re.match(r"^[ \t]*\*unaff_FS_OFFSET = (?:\(\w+\))?&%s;" % prev, l)), None)
    if first is None or reg is None:
        return body
    lo, hi = max(0, min(first, reg) - 4), max(first, reg) + 1
    state = handler = None
    for i in range(lo, min(hi + 1, len(lines))):
        l = lines[i]
        m = re.match(r"^[ 	]*(\w+) = 0xffffffff;[ 	]*$", l)
        if m:
            state = m.group(1)
        m = re.match(r"^[ 	]*(\w+_4) = (?:0x)?[0-9a-fA-F]+;[ 	]*$", l)  # the state slot [EBP-4] (local_4 / uStack_4)
        if m and not state and i > min(first, reg):
            state = m.group(1)
        m = re.match(r"^[ 	]*(\w+) = (?:\(code \*\))?[A-Za-z_]\w*;[ 	]*$", l)
        if m and re.search(r"^[ 	]+code \*%s;" % m.group(1), body, re.M):
            handler = m.group(1)
    keep, dropped = [], 0
    for i, l in enumerate(lines):
        if re.match(r"^[ \t]*%s = \*unaff_FS_OFFSET;" % prev, l) or re.match(r"^[ \t]*\*unaff_FS_OFFSET = (?:\(\w+\))?&%s;" % prev, l) \
                or re.match(r"^[ \t]*\*unaff_FS_OFFSET = %s;" % prev, l):
            dropped += 1
            continue
        # state changes: the whole slot, or only its low byte (`local_4._0_1_ = 1;`, `local_4 = CONCAT31(local_4._1_3_,1);`)
        if state and (re.match(r"^[ \t]*%s(?:\._0_1_)? = (?:0x)?[0-9a-fA-F]+;[ \t]*$" % state, l)
                      or re.match(r"^[ \t]*%s = CONCAT31\(%s\._1_3_,(?:0x)?[0-9a-fA-F]+\);[ \t]*$" % (state, state), l)):
            continue
        if handler and lo <= i <= hi and re.match(r"^[ \t]*%s = " % handler, l):
            continue
        keep.append(l)
    if dropped < 2:
        return body
    out = "\n".join(keep)
    names = [n for n in (prev, state, handler, "unaff_FS_OFFSET") if n]
    for n in names:
        # the variable must be dead now (only its declaration is left)
        if len(re.findall(r"\b%s\b" % n, out)) != 1:
            return body
    out = "\n".join(l for l in out.split("\n") if not any(re.match(r"^[ \t]+[\w ]+?[ \t]+\**%s;[ \t]*$" % n, l) for n in names))
    return out


ARTIFACT_DECL_RE = re.compile(r"^[ \t]+[A-Za-z_][\w ]*?[ \t]+\**(unaff_\w+|in_\w+|extraout_\w+);[ \t]*$")


def drop_unused_artifacts(body):
    """Declarations of unaff_*/in_*/extraout_* locals that no statement uses any more (the garbage
    operand of a `_ftol` call that fix_ftol replaced)."""
    lines = body.split("\n")
    keep = []
    for ln in lines:
        m = ARTIFACT_DECL_RE.match(ln)
        if m and sum(len(re.findall(r"\b%s\b" % m.group(1), x)) for x in lines) == 1:
            continue
        keep.append(ln)
    return "\n".join(keep)


def fix_function(code, ctx, stats):
    code = ftol_fold.fold(code, FLOAT_RETURNERS_NOW)
    code = fix_symbols(code)
    code = fix_stdcall(code)
    code = fix_image_addrs(code)
    head, body = split_function(code)
    if not body:
        return code
    sig = signature_of(code)
    vt = {}
    if sig:
        pp = parse_params(sig)
        if pp:
            for t, n in pp[2]:
                if n:
                    vt[n] = t
    vt.update(local_types(body))
    body = fix_ftol(body)
    body = fix_pieces(body)
    body = fix_views(body, vt)
    body = fix_pseudo_regs(body)
    body = fix_jumps(body)
    body = fix_calls(body, vt, ctx, stats)
    body = fix_fnptr_calls(body, vt, ctx)
    body = fix_call_args(body, vt, ctx, stats)
    body = fix_assign_bits(body, vt, ctx, stats)
    body = fix_switch(body, vt, ctx)
    body = fix_casts(body, vt, ctx)
    body = fix_negative_stack(body)
    body = EXTRAOUT_RE.sub(lambda m: "((uint)(" + m.group(1) + "))", body)
    body = FLOAT_BITS_RE.sub(lambda m: m.group(1) + "FBITS(" + m.group(2) + ")", body)
    # last: offset-named locals become views into one frame array (keeps Ghidra's layout)
    body, trailer = frame_locals.rewrite(body)
    body = float_frame_locals(body)
    # STACK0X(0x..) is __builtin_frame_address(0) + offset: an aligned local makes gcc realign the
    # stack and move the frame pointer away from the argument area, so those functions get no alignment
    if re.search(r"STACK0X\(0x0", body):
        body = body.replace(" __attribute__((aligned(16)))", "")
    # test knob (build/overrides.c, GRIM_lua_cmd_poll): with GRIM_ACTIVE set the window procedure ignores
    # WM_ACTIVATEAPP, so a run behind other windows is not paused and its display is not shut down
    body = body.replace("      if (param_2 == 0x1c) {\n", "      if (param_2 == 0x1c && GRIM_getenv(\"GRIM_ACTIVE\") == 0) {\n")
    return head + body + trailer


NEG_STACK_RE = re.compile(r"(&?)STACK0X\((0xffff[0-9a-f]{4})\)")


def float_frame_locals(body):
    """Frame-array locals Ghidra left as undefined4 but the code uses as float
    (assigned a number-returning call, compared with a float literal, pushed as a number)."""
    for m in re.finditer(r"#define (\w+) \(\*\(undefined4 \*\)\(_frame", body):
        n = m.group(1)
        if re.search(r"%s\s*=\s*(?:luaL_\w*number|lua_getnumber)\(|%s\s*[<>]=?\s*-?\d+\.\d+|lua_pushnumber\(%s\)" % (n, n, n), body):
            body = body.replace("#define %s (*(undefined4 *)" % n, "#define %s (*(float *)" % n, 1)
    return body


# lua_pushnumber takes a float; Ghidra prints constant arguments as raw bit patterns
FLOAT_BITS_RE = re.compile(r"(lua_pushnumber\()(0x[0-9a-fA-F]{6,8})(?=\))")
FLOAT_ARG_IMPORTS = {"lua_pushnumber"}

# CONCAT31(extraout_var, bVarN): the decompiler widens a bool result with the (undefined) upper bytes
# of EAX; the callee returned a clean 0/1, so the widened value is just the zero-extended byte
EXTRAOUT_RE = re.compile(r"CONCAT31\(extraout_var\w*,([^()]+)\)")


def fix_negative_stack(body):
    """`&STACK0X(0xffffffa8)` is an address below the return address of the original frame (a
    jmp_buf for setjmp, an output structure, a scratch buffer). With our compiler that spot is
    inside its own locals, or below the stack pointer. The function gets a byte array standing
    for the original region and every negative offset maps into it, keeping the relative layout."""
    offs = {m.group(2) for m in NEG_STACK_RE.finditer(body)}
    if not offs:
        return body
    kmax = max(0x100000000 - int(o, 16) for o in offs)
    n = (kmax + 16 + 15) // 16 * 16

    def rep(m):
        addr = "(_stkneg + %d)" % (n - (0x100000000 - int(m.group(2), 16)))
        return addr if m.group(1) else "(*(undefined *)%s)" % addr

    body = NEG_STACK_RE.sub(rep, body)
    decl = "  unsigned char _stkneg[%d] __attribute__((aligned(16)));  /* the original frame below the return address */\n" % n
    return re.sub(r"^\{\n", "{\n" + decl, body, count=1, flags=re.M)


# -- globals: infer a C type for each Ghidra data symbol ----------------------

NAMED_TYPE_MAP = {"string": "char", "TerminatedCString": "char", "unicode": "wchar16",
                  "TerminatedUnicode": "wchar16", "pointer": "void *", "pointer32": "void *",
                  "ImageBaseOffset32": "undefined4"}


def c_decl(t, name):
    """Ghidra type string + name -> C declarator (`char[128]` -> `char name[128]`)."""
    t = NAMED_TYPE_MAP.get(t, t)
    arr = ""
    m = re.match(r"^(.*?)((?:\[\d*\])+)$", t)
    if m:
        t, arr = m.group(1), m.group(2)
    t = re.sub(r"\s+\*", "*", t).replace("*", " *").replace("* *", "**")
    return f"{t.strip()} {name}{arr}"


SYM_RE = re.compile(r"\b(_?[A-Za-z][A-Za-z0-9_]*?_[0-9a-f]{8})\b")


def infer_global_types(bodies, ctx, sym_re):
    """Usage-based type for every DAT_/PTR_/s_/... symbol (Ghidra only exported names).

    Ghidra prints a plain `DAT_x` value only when the access width matches the data
    defined there, `_DAT_x` when it does not, and `&DAT_x + n` scaled by DAT_x's
    type - so a DAT_x that is only ever address-taken is a byte (`undefined`), and
    one used as a value gets the type of the locals it is copied to/from."""
    uses = defaultdict(Counter)
    for body, vt in bodies:
        for m in sym_re.finditer(body):
            g = m.group(1)
            a, b = m.start(), m.end()
            if g in vt or re.search(r"(?:goto|JUMPOUT\()\s*$", body[max(0, a - 10):a]) \
                    or (body[b:b + 1] == ":" and re.search(r"\n\s*$", body[max(0, a - 10):a])):
                continue
            pre = body[max(0, a - 3):a]
            post = body[b:b + 3]
            if pre.endswith("(*") and post.startswith(")("):
                uses[g]["call"] += 1
            elif pre.rstrip().endswith("&") and not pre.rstrip().endswith("&&"):
                uses[g]["addr"] += 1
            elif post.startswith("[") or re.search(r"\b(?:return|else|case)\s*\*$", body[max(0, a - 12):a]) or (pre.endswith("*") and (
                    not re.search(r"[\w)\]]\s*\*$", body[max(0, a - 20):a])
                    or re.search(r"\((?:\w+\s*)+\**\)\s*\*$", body[max(0, a - 40):a]))):
                uses[g]["deref"] += 1
            elif post.startswith("->"):
                uses[g]["member"] += 1
            else:
                uses[g]["value"] += 1
                # copied to/from a typed local?
                line_s = body.rfind("\n", 0, a) + 1
                line_e = body.find("\n", b)
                line = body[line_s:line_e].strip()
                mm = re.fullmatch(r"(\w+) = " + re.escape(g) + r";", line) or \
                    re.fullmatch(re.escape(g) + r" = (\w+);", line)
                if mm and mm.group(1) in vt:
                    uses[g]["T:" + vt[mm.group(1)]] += 1
                elif re.search(re.escape(g) + r"\s*[-+*/]\s*-?\d+\.\d|\d\.\d+\s*[-+*/<>]=?\s*" + re.escape(g) + r"\b", line) \
                        or re.fullmatch(re.escape(g) + r" = -?\d+\.\d+;", line):
                    uses[g]["T:float"] += 1
                else:
                    # `DAT_x = (T *)alloc(...)` and `p = DAT_x + 1` (p a pointer local): Ghidra scaled
                    # the arithmetic by T, so DAT_x is a T pointer (an int-typed DAT_x would step by bytes)
                    am2 = re.fullmatch(r"(\w+) = " + re.escape(g) + r" [-+] -?\w+;", line)
                    if am2 and CUR_PROG == "LUA.DLL" and g.startswith("DAT_"):
                        lt = ""
                        if True:   # (a real pointer local is not enough evidence: Ghidra casts there)
                            # a frame-local view (`#define puStack_24 (*(undefined4 **)(_frame + ...))`)
                            dm = re.search(r"#define " + re.escape(am2.group(1)) + r" \(\*\(([\w ]+\*+)\)", body)
                            lt = dm.group(1)[:-1].replace(" *", "*").replace("*", " *").strip() if dm else ""   # (the cast is a pointer to the local)
                        if "*" in lt:
                            uses[g]["P:" + lt] += 1
    return uses


def global_decl(g, u, ctx):
    """-> (kind, text) where kind is 'decl' or 'macro'."""
    if g.startswith("s_"):
        return f"extern char {g}[];"
    if g.startswith("u_"):
        return f"extern wchar16 {g}[];"
    if g.startswith("LAB_"):
        return f"extern code {g};  /* code label (address only) */"
    if g.startswith("PTR_"):
        # a global tools/type_pointer_globals.py typed in Ghidra: Ghidra scales its
        # arithmetic by that pointee, so the C declaration must match
        t = PTR_TYPES.get(g[4:])
        if t:
            return f"extern {c_decl(t, g)};"
        return f"extern undefined *{g};"
    if g.startswith("FLOAT_"):
        return f"extern float {g};"
    if g.startswith("DOUBLE_"):
        return f"extern double {g};"
    for pfx, t in (("BYTE_", "byte"), ("WORD_", "word"), ("DWORD_", "dword")):
        if g.startswith(pfx):
            return f"extern {t} {g};"
    if u["call"]:
        return f"extern code *{g};"
    if u["deref"] or u["member"]:
        ptrs = Counter({k[2:]: v for k, v in u.items()
                        if k.startswith("T:") and "*" in k and base_type(k[2:]) != "void"})
        t = ptrs.most_common(1)[0][0] if ptrs else "undefined4 *"
        return f"extern {c_decl(t, g)};"
    if u["value"]:
        ts = Counter({k[2:]: v for k, v in u.items() if k.startswith("T:")})
        if not ts:
            # weaker evidence (see infer_global_types): only when nothing else says what it is
            ts = Counter({k[2:]: v for k, v in u.items() if k.startswith("P:")})
        am = re.search(r"_([0-9a-f]{8})$", g)
        # no better evidence: the width of Ghidra's data item (a 1-byte item indexed as
        # `(&DAT_x)[i]` is a byte table, not 4-byte elements)
        t = DATA_ELT.get(am.group(1)) or ACCESS_ELT.get(am.group(1), "undefined4") if am else "undefined4"
        if ts:
            t = ts.most_common(1)[0][0]
            if "[" in t:
                t = "undefined4"
        return f"extern {c_decl(t, g)};"
    # touched only by address: Ghidra prints `(&DAT_x)[i]` / `&DAT_x + n` scaled by the data item's own
    # size, so a 2- or 4-byte item must not be declared as a byte
    am = re.search(r"_([0-9a-f]{8})$", g)
    if am and am.group(1) in DATA_ELT:
        return f"extern {DATA_ELT[am.group(1)]} {g};"
    return f"extern undefined {g};"


def load_global_aliases(prog, rawdir):
    """Globals renamed by names-only batches (tools/orig_gbatch.py: "global" + "old" + "oldtype"), new -> old name.

    While a renamed global keeps the Ghidra type it had at the rename, the build treats it as its old name: the
    raw text is read with the old name and the old name is replaced by the new one in the written files. So the
    declarations (DAT_ globals get a type inferred from use, named ones their Ghidra type) and every fix-up that
    looks at the name stay as they were, and the generated C only changes in the name. A global retyped in Ghidra
    later (its type no longer the "oldtype") is taken as named, with its new type."""
    path = PROG_PATHS.get(prog)
    m = {}
    for f in sorted(glob.glob(os.path.join(ROOT, "names", "*.json"))):
        try:
            data = json.load(open(f, encoding="utf-8"))
        except ValueError:
            continue
        if not isinstance(data, list):
            continue
        for e in data:
            if isinstance(e, dict) and e.get("names_only") and e.get("program") == path and e.get("old") \
                    and e.get("global") and e["old"] != e["global"]:
                m[e["global"]] = (e["old"], e.get("oldtype", ""))
    cur = {}
    try:
        for line in read_text(os.path.join(rawdir, "globals.json")).splitlines():
            gm = re.match(r"^(\S+) @ ([0-9a-f]+) \[\w+\] \((.*)\) xrefs=\d+$", line.strip())
            if gm:
                cur.setdefault(gm.group(1), gm.group(3))
    except FileNotFoundError:
        pass
    out = {}
    for new, (old, t) in m.items():
        seen = {new}
        while old in m and old not in seen:   # chains: a -> b in one batch, b -> c in a later one
            seen.add(old)
            old, t = m[old]
        if new in cur and (cur[new] or "") == (t or ""):
            out[new] = old
    return out


def alias_re(names):
    # NAME, Ghidra's other-width view _NAME and its piece NAME_2 (DAT_x_2)
    return re.compile(r"\b(_?)(" + "|".join(map(re.escape, sorted(names, key=len, reverse=True))) + r")(_\d+)?\b") \
        if names else None


GLOBAL_ALIAS = {}
PROG_PATHS = {"GRIMFANDANGO.EXE": "/v101/GRIMFANDANGO.EXE", "LUA.DLL": "/LUA.DLL", "IMUSE.DLL": "/v101/IMUSE.DLL",
              "CHORE.DLL": "/CHORE.DLL"}


def build(prog):
    prog_ov = OVERRIDES_BY_PROG.get(prog, OVERRIDES)   # hand-written functions of this program
    rawdir = os.path.join(RAW, prog)
    global IMG_SECTIONS
    IMG_SECTIONS = []
    if os.path.exists(os.path.join(rawdir, "sections.json")):
        # (name, start, initialised bytes): only literals inside the file-backed part of a
        # section are addresses; masks such as 0x7fff00 fall in the zero tail of .data
        IMG_SECTIONS = [(s["name"], int(s["start"], 16), s["size"]) for s in json.load(open(os.path.join(rawdir, "sections.json")))]
    global CUR_PROG
    funcs = json.load(open(os.path.join(rawdir, "functions.json")))
    CUR_PROG = prog
    global ASM_ADDRS
    ASM_ADDRS = set()
    ap = os.path.join(ROOT, "names", "asm_funcs.json")
    if os.path.exists(ap):
        ASM_ADDRS = set(json.load(open(ap)).get(prog, []))
    global LIB_REPL
    LIB_REPL = load_lib_replace(prog)
    global DATA_ELT
    DATA_ELT = {}
    di_path = os.path.join(rawdir, "data_items.txt")
    if os.path.exists(di_path):
        for line in open(di_path, encoding="utf-8", errors="replace"):
            m = re.match(r"^\S+ @ ([0-9a-f]{8}) \[([^\]]*)\] \((\d+) bytes?\)", line)
            if m and m.group(2) in ELT_TYPES:
                DATA_ELT[m.group(1)] = ELT_TYPES[m.group(2)]
    global ACCESS_ELT
    ACCESS_ELT = {}
    ac_path = os.path.join(rawdir, "access_sizes.json")
    if os.path.exists(ac_path):
        for k, v in json.load(open(ac_path)).items():
            if v == 1:
                ACCESS_ELT[k] = "undefined"
            elif v == 2:
                ACCESS_ELT[k] = "undefined2"
    global PTR_TYPES
    PTR_TYPES = {}
    pt_path = os.path.join(rawdir, "ptr_types.json")
    if os.path.exists(pt_path):
        PTR_TYPES = json.load(open(pt_path))
    global STDCALL_FUNCS
    STDCALL_FUNCS = set()
    sc_path = os.path.join(rawdir, "stdcall_funcs.json")
    if os.path.exists(sc_path):
        sc = json.load(open(sc_path))
        by_addr = {f["address"]: f["name"] for f in funcs}
        STDCALL_FUNCS = {by_addr.get(a, v["name"]) for a, v in sc.items()}
    global FUNC_AT
    FUNC_AT = {int(f["address"], 16): f["name"] for f in funcs
               if not f.get("isThunk") and not f.get("isExternal") and not f["name"].startswith("FUN_")}
    FUNC_AT.update({int(f["address"], 16): f["name"] for f in funcs
                    if not f.get("isThunk") and not f.get("isExternal") and f["name"].startswith("FUN_")})
    funcs.sort(key=lambda f: int(f["address"], 16))
    # per program: LUA.DLL's own lua_* functions are *imports* of the EXE; a set
    # shared across programs filed them under _thunks when LUA.DLL ran after the EXE
    IMPORT_NAMES.clear()
    try:
        imports = json.loads(read_text(os.path.join(rawdir, "imports.json")))
        for imp in imports:
            IMPORT_NAMES.add(imp["name"])
    except Exception:
        imports = []
    ranges = RANGES.get(prog, [])

    # pass 1: module per function
    assigned = []
    state = {"current": "startup", "run": []}

    def flush_run():
        run = state["run"]
        if not run:
            return
        mod = f"region_{run[0]['address']}" if len(run) >= LONG_RUN else state["current"]
        for f in run:
            a = int(f["address"], 16)
            m = mod
            for lo, hi, rm in ranges:
                if lo <= a <= hi:
                    m = rm
            if m == "crt":
                # crt.c is left out of the link (the host runtime replaces it); an
                # unnamed function in the CRT region still has to be defined, since
                # tables in .data may point at it (FUN_004bdf70, LecShare's module list)
                m = "crt_unnamed"
            assigned.append((f, m))
        state["run"] = []

    for f in funcs:
        name = f["name"]
        if f.get("isThunk") or f.get("isExternal") or name in IMPORT_NAMES:
            assigned.append((f, "_thunks"))
            continue
        m = module_for(name)
        if m is None:
            state["run"].append(f)
        else:
            flush_run()
            state["current"] = m
            assigned.append((f, m))
    flush_run()

    # pass 2: read every body, collect prototypes, apply the compilability fix-ups
    out = os.path.join(SRC, prog)
    os.makedirs(out, exist_ok=True)
    for old in os.listdir(out):
        if old.endswith((".c", ".h", ".md")):
            os.remove(os.path.join(out, old))
    by_mod = OrderedDict()
    for f, m in sorted(assigned, key=lambda t: int(t[0]["address"], 16)):
        by_mod.setdefault(m, []).append(f)

    global GLOBAL_ALIAS
    GLOBAL_ALIAS = load_global_aliases(prog, rawdir)
    alias_in = alias_re(GLOBAL_ALIAS)
    ctx = Ctx()
    ctx.import_ints = {i["name"] for i in imports}
    named_globals = {}
    try:
        for line in read_text(os.path.join(rawdir, "globals.json")).splitlines():
            gm = re.match(r"^(\S+) @ ([0-9a-f]+) \[\w+\] \((.*)\) xrefs=\d+$", line.strip())
            if gm:
                gname = GLOBAL_ALIAS.get(gm.group(1), gm.group(1))
                if gname != gm.group(1) and SYM_RE.fullmatch(gname):
                    continue   # renamed DAT_/PTR_/UINT_ global: unnamed data, as before the rename
                named_globals.setdefault(gname, (gm.group(2), gm.group(3)))
    except FileNotFoundError:
        pass
    for g, (_, t) in named_globals.items():
        ctx.gtypes[g] = NAMED_TYPE_MAP.get(t, t)
        bt = base_type(re.sub(r"\[.*", "", t))
        if bt and bt not in PRIM_TYPES:
            ctx.known_types.add(bt)

    codes = {}      # address -> raw code
    sigs = {}       # address -> signature
    seen_names = Counter()
    renamed = {}
    missing = []
    for mod, fl in by_mod.items():
        if mod == "_thunks":
            continue
        for f in fl:
            path = os.path.join(rawdir, "functions", f["address"] + ".c")
            if not os.path.exists(path):
                missing.append(f["address"])
                continue
            code = read_text(path).strip("\n")
            if alias_in:
                code = alias_in.sub(lambda m: m.group(1) + GLOBAL_ALIAS[m.group(2)] + (m.group(3) or ""), code)
            name = f["name"]
            seen_names[name] += 1
            if seen_names[name] > 1:
                # Ghidra allows two functions with one name; C does not. Calls keep
                # resolving to the first definition.
                new = f"{name}_{f['address']}"
                code = re.sub(r"\b" + re.escape(name) + r"(\s*\()", new + r"\1", code, count=1)
                renamed[f["address"]] = new
            code = widen_return_type(code)
            codes[f["address"]] = code
            sig = signature_of(code)
            if sig:
                sigs[f["address"]] = sig
                pp = parse_params(sig)
                if pp and pp[1] not in ctx.protos:
                    ctx.protos[pp[1]] = (pp[0], pp[2], pp[3])
                    ccm = re.search(r"(__thiscall|__fastcall|__stdcall)", sig.split('(')[0])
                    if ccm:
                        ctx.cc[pp[1]] = ccm.group(1)
                    for t, _ in pp[2]:
                        bt = base_type(t)
                        if bt and re.fullmatch(r"\w+", bt):
                            ctx.known_types.add(bt)
                    bt = base_type(pp[0])
                    if bt and re.fullmatch(r"\w+", bt):
                        ctx.known_types.add(bt)

    if missing:
        print(prog, f"WARNING: {len(missing)} function(s) in functions.json have no "
              "raw/<prog>/functions/<addr>.c (export incomplete?) - skipped")
        for mod in list(by_mod):
            by_mod[mod] = [f for f in by_mod[mod] if f["address"] in codes or mod == "_thunks"]
            if not by_mod[mod]:
                del by_mod[mod]
    stats = Counter()
    fixed = {}
    for a, code in codes.items():
        global CUR_FN_ADDR
        CUR_FN_ADDR = a
        fixed[a] = fix_function(code, ctx, stats) if FIXUPS else code

    protos = OrderedDict()
    globals_seen = defaultdict(set)
    idents_seen = set()
    index_rows = []
    bodies = []
    for mod, fl in by_mod.items():
        if mod == "_thunks":
            continue
        lo, hi = fl[0]["address"], fl[-1]["address"]
        lines = [f"/* {prog} :: {mod}.c", f" * functions 0x{lo} .. 0x{hi} ({len(fl)} functions)",
                 " * Decompiled from the shipped binaries with Ghidra; see ../../README.md */",
                 '#include "ghidra_types.h"', '#include "globals.h"', '#include "functions.h"', ""]
        protos[mod] = []
        for f in fl:
            code = fixed[f["address"]]
            if mod in COM_MODULES:
                code = COM_CALL_RE.sub(r"\1code_std\2", code)
            else:
                # `(**(code **)(*obj + off))`: a vtable slot (the object's first dword + offset) is a
                # COM method; service-table calls read `(**(code **)(table + off))` and stay cdecl
                code = COM_VTBL_RE.sub(r"\1code_std\2", code)
            sig = sigs.get(f["address"])
            if sig:
                protos[mod].append((f["address"], signature_of(code)))
            _, body = split_function(code)
            body = re.sub(r"/\*.*?\*/", "", body, flags=re.S)
            idents_seen.update(re.findall(r"\b[A-Za-z_]\w*\b", body))
            vt = local_types(body)
            pp = parse_params(sig) if sig else None
            if pp:
                vt.update({n: t for t, n in pp[2] if n})
            bodies.append((body, vt))
            for g in SYM_RE.findall(body):
                if g not in vt:
                    globals_seen[g].add(f["address"])
            title = f["name"] + (f"  (renamed {renamed[f['address']]}: duplicate name)" if f["address"] in renamed else "")
            lines.append(f"/* ---- 0x{f['address']}  {title} ---- */")
            if f["address"] in LIB_REPL and f["name"] not in prog_ov:
                lines.append("/* NOT COMPILED: names/lib_replace.json (%s): the system C runtime / zlib (or nothing, for dead "
                             "code) is used instead; this C text is only for reading */" % LIB_REPL[f["address"]])
                lines.append("#if 0")
                lines.append(code)
                lines.append("#endif")
                code = ""
            elif f["name"] in prog_ov or f["address"] in ASM_ADDRS:
                if f["name"] in prog_ov:
                    lines.append("/* replaced by the hand-written version in build/overrides.c */")
                else:
                    lines.append("/* NOT COMPILED: the build uses the original machine code of this function (src/%s/asm_funcs.s, "
                                 "tools/gen_asm.py); this C text is only for reading */" % prog)
                lines.append("#if 0")
                lines.append(code)
                lines.append("#endif")
                code = ""
            lines.append(code)
            lines.append("")
            index_rows.append((f["address"], f["name"], mod, code.count("\n") + 1))
        with open(os.path.join(out, mod + ".c"), "w", newline="\n") as w:
            w.write("\n".join(lines))

    # one-instruction `JMP target` wrappers Ghidra marks as thunks (sputLua_Display ->
    # Render_Present, ImTerminate -> TrTerminate ...). They have no C body;
    # a jump in inline asm defines the symbol so callers and function-pointer
    # tables (data.s) resolve. Thunks that share their target's name are the same
    # symbol already; import thunks (`JMP [IAT]`) resolve to the import library.
    jumps = []
    fmap = {f["address"]: f for f in funcs}
    for f in by_mod.get("_thunks", []):
        path = os.path.join(rawdir, "functions", f["address"] + ".c")
        if not os.path.exists(path):
            continue
        tm = re.search(r"/\* thunk: \S+ @ [0-9a-f]+ -> ([0-9a-f]{8}) \*/", read_text(path))
        if not tm:
            continue
        tf = fmap.get(tm.group(1))
        if tf is None or tf.get("isExternal"):
            continue
        target = renamed.get(tm.group(1), tf["name"])
        if target == f["name"]:
            continue
        jumps.append((f["address"], f["name"], target))
    if jumps:
        with open(os.path.join(out, "thunks.c"), "w", newline="\n") as w:
            w.write(f"/* {prog}: jump thunks. Each is a single `JMP target` instruction in the\n"
                    f"   original; Ghidra marks them as thunks and decompiles no body. */\n\n")
            for addr, name, target in jumps:
                w.write(f'/* {name} @ 0x{addr} */\n'
                        f'__asm__(".text\\n.globl _{name}\\n_{name}:\\n\\tjmp _{target}\\n");\n')
    defined = {pp_name for pp_name in ctx.protos}
    with open(os.path.join(out, "functions.h"), "w", newline="\n") as w:
        w.write(f"/* {prog}: prototypes of every decompiled function, by module */\n#pragma once\n#include \"ghidra_types.h\"\n\n")
        for mod, pl in protos.items():
            w.write(f"/* ===== {mod}.c ===== */\n")
            for addr, sig in pl:
                w.write(f"{sig}; /* 0x{addr} */\n")
            w.write("\n")
        # imports that return in ST(0) (raw/<prog>/x87_returns.json, tools/find_x87_returns.py)
        x87 = {}
        xp = os.path.join(rawdir, "x87_returns.json")
        if os.path.exists(xp):
            x87 = {k: v["type"] for k, v in json.load(open(xp)).items() if not re.fullmatch(r"[0-9a-f]{8}", k)}

        def x87_ret(name):
            return x87.get(name, "int")

        # functions the code refers to but that are not decompiled here: thunks,
        # imports, and FUN_ addresses Ghidra has no function for
        thunk_names = {f["name"] for f, m in assigned if m == "_thunks"}
        imp_names = {i["name"] for i in imports}
        extra = sorted(n for n in idents_seen
                       if n not in defined and (n in thunk_names or n in imp_names or re.fullmatch(r"(?:thunk_)?FUN_[0-9a-f]{8}", n)))
        exrefs = sorted(n for n in idents_seen if n.endswith("_exref"))
        if extra or exrefs:
            w.write("/* ===== referenced, not decompiled here (thunks, imports, unknown FUN_) ===== */\n")
            for n in extra:
                why = "import" if n in imp_names else ("thunk" if n in thunk_names else "no function at this address")
                if n in imp_names and (n in DLL_STDCALL or n.startswith("hmiFX") or (not n.startswith(CDECL_IMPORT_PREFIXES) and n not in CDECL_IMPORTS)):
                    # Win32/DirectX: stdcall, callee pops. Unprototyped on purpose: the
                    # decompiled call sites carry Ghidra's argument lists.
                    # the asm label keeps the symbol undecorated (`_f`, not `_f@0`) so the
                    # linker's --enable-stdcall-fixup can bind it to the import library's `_f@N`
                    asm_name = DLL_STDCALL.get(n) or STDCALL_NAMES.get(n, "_" + n)
                    w.write(f'{x87_ret(n)} STDCALL {n}() __asm__("{asm_name}"); /* {why} */\n')
                elif n in FLOAT_ARG_IMPORTS:
                    w.write(f"void {n}(float); /* {why} */\n")
                else:
                    w.write(f"{x87_ret(n)} {n}(); /* {why} */\n")
            for n in exrefs:
                w.write(f"extern int (STDCALL *{n})(); /* import address table slot */\n")
        defined.update(extra)
    # data symbols: everything address-named that is not a function or a local,
    # plus `_name` (Ghidra's other-width view) of named globals
    for g in list(globals_seen):
        if g in defined or re.match(r"(?:thunk_)?FUN_", g) or g.endswith("_exref"):
            del globals_seen[g]
    under_named = sorted(g for g in named_globals if "_" + g in idents_seen)
    untyped_named = sorted(g for g in named_globals if re.fullmatch(r"undefined\d?", named_globals[g][1]))
    sym_re = re.compile(SYM_RE.pattern[:-3] + "".join("|_" + re.escape(g) for g in under_named)
                        + "".join("|" + re.escape(g) for g in untyped_named) + r")\b")
    uses = infer_global_types(bodies, ctx, sym_re)
    for g in under_named:
        globals_seen["_" + g].add("?")
    with open(os.path.join(out, "globals.h"), "w", newline="\n") as w:
        w.write(f"/* {prog}: every global / string symbol referenced by the decompiled code.\n"
                " * Named globals carry their Ghidra type. For DAT_/PTR_/s_ symbols Ghidra exported\n"
                " * no type; the type below is inferred from how the code uses the symbol\n"
                " * (see infer_global_types in tools/build_src.py) - fix it in Ghidra, not here. */\n"
                "#pragma once\n#include \"ghidra_types.h\"\n\n")
        named_used = sorted((g for g in named_globals if (g in idents_seen or g in under_named) and g not in defined),
                            key=lambda g: named_globals[g][0])
        if named_used:
            w.write("/* ---- named globals (type from Ghidra) ---- */\n")
            for g in named_used:
                if g in untyped_named:  # Ghidra only says "undefinedN": infer like DAT_
                    d = global_decl(g, uses[g], ctx)
                    if d == f"extern undefined {g};":
                        d = f"extern {c_decl(named_globals[g][1], g)};"
                    w.write(f"{d} /* 0x{named_globals[g][0]}, {named_globals[g][1]} in Ghidra */\n")
                    continue
                w.write(f"extern {c_decl(named_globals[g][1], g)}; /* 0x{named_globals[g][0]} */\n")
            w.write("\n/* ---- unnamed data (type inferred from use) ---- */\n")
        macros = []
        plain = set(globals_seen)
        for g in sorted(globals_seen, key=lambda s: s[-8:]):
            if not sum(uses[g].values()):
                continue  # only a goto target / label
            users = sorted(globals_seen[g])
            note = f"/* used by {len(users)} fn(s), first 0x{users[0]} */"
            if g.startswith("_"):
                base = g[1:]
                t = re.sub(r"\s+", " ", global_decl(base, uses[g], ctx)[len("extern "):].split(";")[0])
                t = t.replace(base, "").replace("[]", "*").strip() or "undefined4"
                if base not in plain and base not in named_globals:
                    w.write(f"extern undefined {base}; {note}\n")
                    plain.add(base)
                macros.append(f"#define {g} (*({t} *)&{base}) /* same address as {base}, other width */")
                continue
            w.write(f"{global_decl(g, uses[g], ctx)} {note}\n")
        # `DAT_x_2`: Ghidra's name for the piece at DAT_x + 2
        pieces = sorted(set(re.findall(r"\b((DAT_[0-9a-f]{8})_(\d+))\b", "\n".join(b for b, _ in bodies))))
        for full, base, off in pieces:
            off = int(off)
            t = "undefined1" if off % 2 else ("undefined2" if off % 4 else "undefined4")
            if base not in plain:
                w.write(f"extern undefined {base};\n")
                plain.add(base)
            macros.append(f"#define {full} (*({t} *)((undefined *)&{base} + {off}))")
        if macros:
            w.write("\n/* ---- re-typed views of the symbols above ---- */\n" + "\n".join(macros) + "\n")
    with open(os.path.join(out, "ghidra_types.h"), "w", newline="\n") as w:
        w.write(GHIDRA_TYPES)
        if IMG_SECTIONS:
            w.write("\n/* The original data sections, rebuilt from the Ghidra memory dump by build/gendata.py.\n"
                    " * IMG_ADDR() relocates an address literal Ghidra printed as a number. */\n")
            for name, start, size in IMG_SECTIONS:
                w.write(f"extern unsigned char sect_{name.strip('.')}[];  /* {name}: 0x{start:08x}, {size} bytes */\n")
            w.write("#define IMG_ADDR(a) ((unsigned)(uintptr_t)img_addr_(a))  /* integer, like the literal it replaces */\n")
            w.write("static inline void *img_addr_(unsigned a) {\n")
            for name, start, size in IMG_SECTIONS:
                w.write(f"    if (a >= 0x{start:08x}u && a <= 0x{start + size:08x}u) return sect_{name.strip('.')} + (a - 0x{start:08x}u);\n")
            w.write("    return (void *)(uintptr_t)a;\n}\n")
        unknown = sorted(t for t in ctx.known_types - PRIM_TYPES if re.fullmatch(r"[A-Za-z_]\w*", t))
        if unknown:
            w.write("\n/* Ghidra structure types used in prototypes/globals; layouts are not exported,\n"
                    " * so they are incomplete here unless a compat header defines them. */\n")
            for t in unknown:
                w.write(f"typedef struct {t} {t};\n")
    with open(os.path.join(out, "imports.h"), "w", newline="\n") as w:
        w.write(f"/* {prog}: imported symbols (from the PE import table) */\n#pragma once\n")
        for imp in imports:
            if imp["name"] in FLOAT_ARG_IMPORTS:
                w.write(f"/* {imp.get('address', '')} */ extern void {imp['name']}(float);\n")
            else:
                w.write(f"/* {imp.get('address', '')} */ extern int {imp['name']}();\n")
    with open(os.path.join(out, "FUNCTIONS.md"), "w", newline="\n") as w:
        named = sum(1 for r in index_rows if not r[1].startswith("FUN_"))
        w.write(f"# {prog} function index\n\n{len(index_rows)} functions, {named} with real names.\n\n")
        w.write("| address | name | module | lines |\n|---|---|---|---|\n")
        for a, n, m, l in index_rows:
            w.write(f"| {a} | {n} | {m}.c | {l} |\n")
    if GLOBAL_ALIAS:
        back = {o: n for n, o in GLOBAL_ALIAS.items()}
        alias_out = alias_re(back)
        for fn in os.listdir(out):
            if fn.endswith((".c", ".h")):
                fp = os.path.join(out, fn)
                t = open(fp, encoding="utf-8", newline="").read()
                t2 = alias_out.sub(lambda m: m.group(1) + back[m.group(2)] + (m.group(3) or ""), t)
                if t2 != t:
                    open(fp, "w", encoding="utf-8", newline="").write(t2)
        print(prog, "renamed globals (built under their old names):", len(GLOBAL_ALIAS))
    print(prog, "modules:", {m: len(v) for m, v in by_mod.items()})
    if FIXUPS:
        print(prog, "fix-ups:", dict(stats))
    if renamed:
        print(prog, "duplicate function names renamed:", renamed)
    return by_mod, index_rows


FIXUPS = True  # `--raw` on the command line writes Ghidra's text untouched


def _ghidra_helpers():
    """SUBnm / CONCATnm / ZEXTnm / SEXTnm / CARRYn / SCARRYn / SBORROWn for every width."""
    ut = {1: "uint8_t", 2: "uint16_t", 3: "uint32_t", 4: "uint32_t", 5: "uint64_t", 6: "uint64_t",
          7: "uint64_t", 8: "uint64_t"}
    st = {1: "int8_t", 2: "int16_t", 4: "int32_t", 8: "int64_t"}
    out = []
    for n in range(1, 9):
        for m in range(1, 9):
            if m < n:
                mask = "" if m in (1, 2, 4, 8) else f" & 0x{(1 << 8 * m) - 1:x}ULL"
                out.append(f"#define SUB{n}{m}(x,off) (({ut[m]})((GHIDRA_U64(x) >> (8*(off))){mask}))")
            if n + m <= 8:
                lmask = f"(GHIDRA_U64(l) & 0x{(1 << 8 * m) - 1:x}ULL)"
                out.append(f"#define CONCAT{n}{m}(h,l) (({ut[n + m]})((GHIDRA_U64(h) << {8 * m}) | {lmask}))")
            if m > n:
                out.append(f"#define ZEXT{n}{m}(x) (({ut[m]})(x))")
                if n in st and m in st:
                    out.append(f"#define SEXT{n}{m}(x) (({st[m]})({st[n]})(x))")
    for n, t in ut.items():
        if n in st:
            s = st[n]
            out.append(f"#define CARRY{n}(a,b) (({t})(a) > ({t})~({t})(b))")
            out.append(f"#define SCARRY{n}(a,b) ((({s})(({t})(a) + ({t})(b)) < 0) != ((({s})(a) < 0) && (({s})(b) < 0)) && ((({s})(a) < 0) == (({s})(b) < 0)))")
            out.append(f"#define SBORROW{n}(a,b) (((({s})(a) ^ ({s})(b)) & (({s})(a) ^ ({s})(({t})(a) - ({t})(b)))) < 0)")
    return "\n".join(out) + "\n"


GHIDRA_TYPES = """/* Ghidra decompiler primitive types and pseudo-operations, so the exported code
 * compiles. Generated by tools/build_src.py - do not edit.
 *
 * Everything follows Ghidra's x86-32 model: 4-byte pointers, int and long. Build
 * with a 32-bit target (gcc -m32, see build/Makefile); on a 64-bit target the
 * `(int)ptr + 0x10` arithmetic all over the decompilation truncates pointers.
 * Define GHIDRA_ALLOW_64BIT to compile (not run) on a 64-bit target anyway. */
#pragma once
#include <stdint.h>
#include <stdbool.h>
#ifndef GHIDRA_ALLOW_64BIT
_Static_assert(sizeof(void *) == 4, "Ghidra x86 output assumes 4-byte pointers: compile with -m32");
#endif

typedef uint8_t  undefined;
typedef uint8_t  undefined1;
typedef uint16_t undefined2;
typedef uint32_t undefined3;  /* 3-byte value, widened: use PIECE() for exact 3-byte stores */
typedef uint32_t undefined4;
typedef uint64_t undefined5;
typedef uint64_t undefined6;
typedef uint64_t undefined7;
typedef uint64_t undefined8;
typedef uint8_t  byte;
typedef uint16_t word;
typedef uint32_t dword;
typedef uint64_t qword;
typedef int8_t   sbyte;
typedef uint8_t  uchar;
typedef uint16_t ushort;
typedef uint32_t uint;
typedef uint32_t ulong;       /* Win32 long is 32 bits */
typedef int64_t  longlong;
typedef uint64_t ulonglong;
typedef int32_t  int3;        /* Ghidra's odd-width integers, widened */
typedef uint32_t uint3;
typedef int64_t  int5, int6, int7;
typedef uint64_t uint5, uint6, uint7;
typedef float    float4;
typedef double   float8;
typedef long double float10;  /* x87 extended */
typedef long double unkbyte10;
typedef uint16_t wchar16;
/* `code` is "some function": an unprototyped function type, so `(*(code *)p)(a, b)`
 * calls with whatever arguments Ghidra saw. */
typedef int code();

/* x87 / Ghidra pseudo-ops */
#define ROUND(x)   ((float10)__builtin_rintl((float10)(x)))   /* FRNDINT */
#define ABS(x)     (((x) < 0) ? -(x) : (x))
#define SQRT(x)    ((float10)__builtin_sqrtl((float10)(x)))   /* FSQRT */
#define FTOL(x)    ((long long)(x))                /* x87 _ftol: truncate toward zero (the value Ghidra loses in ST0) */
#define ISNAN(x)   ((x) != (x))                    /* Ghidra NAN(x): unordered compare */
#define NAN        (__builtin_nanf(""))
#define f2xm1(x)   ((float10)__builtin_exp2l((float10)(x)) - 1)             /* F2XM1 */
#define fscale(a,b) ((float10)__builtin_ldexpl((float10)(a), (int)(b)))     /* FSCALE */
#define fsin(x)    ((float10)__builtin_sinl((float10)(x)))                   /* FSIN */
#define fcos(x)    ((float10)__builtin_cosl((float10)(x)))                   /* FCOS */
#define LOCK()     ((void)0)                                  /* x86 LOCK prefix */
#define UNLOCK()   ((void)0)

/* integer view of any scalar (pointer or integer) for SUB/CONCAT */
#define GHIDRA_U64(x) ((uint64_t)(x))

/* Bit-for-bit reinterpretation: Ghidra keeps one register for a pointer and a float
 * and casts between them (`(float)ptr_var`). PUN(T, x) gives x's bits as a T. */
#ifndef PUN
#define PUN(T, x) (__extension__({ union { __typeof__((x) + 0) a; T b; } _pun_u = {0}; \\
                                  _pun_u.a = (x); _pun_u.b; }))
#endif

/* `x._1_2_`: bytes 1..2 of x, as an lvalue of that width */
typedef struct __attribute__((packed)) { uint32_t v : 24; } ghidra_piece3;
typedef struct __attribute__((packed)) { uint64_t v : 40; } ghidra_piece5;
typedef struct __attribute__((packed)) { uint64_t v : 48; } ghidra_piece6;
typedef struct __attribute__((packed)) { uint64_t v : 56; } ghidra_piece7;
typedef struct __attribute__((packed)) { uint8_t  v; } ghidra_piece1;
typedef struct __attribute__((packed)) { uint16_t v; } ghidra_piece2;
typedef struct __attribute__((packed)) { uint32_t v; } ghidra_piece4;
typedef struct __attribute__((packed)) { uint64_t v; } ghidra_piece8;
#define PIECE(var, off, size) (((ghidra_piece##size *)((uint8_t *)&(var) + (off)))->v)

/* stack0xNNNN: the stack slot at entry-ESP + 0xNNNN (positive: arguments).
 * With a frame pointer, entry ESP = EBP + 4. */
#define STACK0X(off) (*(undefined *)((char *)__builtin_frame_address(0) + 4 + (int32_t)(off)))
/* register0x00000010 is ESP in Ghidra's x86 register space */
#define REGISTER0X(off) ((undefined4)(uintptr_t)__builtin_frame_address(0))
/* linear address of the TEB: FS:[0], the SEH chain head, is its first dword */
#define TEB_BASE() ({ unsigned __teb; __asm__ volatile("movl %%fs:0x18, %0" : "=r"(__teb)); (void *)__teb; })
/* goto into another function: unrepresentable in C */
#define JUMPOUT(label) __builtin_trap()

""" + _ghidra_helpers()

if __name__ == "__main__":
    args = sys.argv[1:]
    if "--raw" in args:
        args.remove("--raw")
        FIXUPS = False
    progs = args or [d for d in os.listdir(RAW) if os.path.isdir(os.path.join(RAW, d))]
    for p in progs:
        build(p)
