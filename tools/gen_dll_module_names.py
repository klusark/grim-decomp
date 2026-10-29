"""Module-level names for the unnamed functions of LUA.DLL and IMUSE.DLL.

The module boundaries come from the __FILE__ strings each DLL passes to its
allocator / assert service (see raw/<dll>/functions).  Functions whose exact
identity is known get a real name; the rest get `<module>__<addr>` so the
organised source tree groups them by original file.  Output goes to
names/lua_modules.json and names/imuse_modules.json.
"""
import json, os
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

LUA_RANGES = [  # (start, module, note)
    (0x1000, 'lapi', 'lapi.c (Lua 3.1 C API)'),
    (0x2960, 'lauxlib', 'lauxlib.c (argument checking helpers)'),
    (0x2c20, 'lbuffer', 'lbuffer.c (string buffer)'),
    (0x2cf0, 'lbuiltin', 'lbuiltin.c (built-in functions)'),
    (0x3e40, 'ldo', 'ldo.c (stack and call machinery, Grim task marks)'),
    (0x4ba0, 'lfunc', 'lfunc.c (prototypes and closures)'),
    (0x4e70, 'lgc', 'lgc.c (garbage collector)'),
    (0x53d0, 'liolib', 'liolib.c (file/system library)'),
    (0x5c00, 'llex', 'llex.c (lexer)'),
    (0x73b0, 'lmem', 'lmem.c (memory through the service table)'),
    (0x74b0, 'lobject', 'lobject.c'),
    (0x75e0, 'lstate', 'lstate.c (Grim execution states / tasks)'),
    (0x8d40, 'lstring', 'lstring.c (string table)'),
    (0x95b0, 'lstrlib', 'lstrlib.c (string library)'),
    (0xa6f0, 'lparser', 'lua.stx (yacc parser) and code generation'),
    (0xc190, 'ltable', 'ltable.c (hash tables, with Grim save support)'),
    (0xc850, 'ltm', 'ltm.c (tag methods)'),
    (0xcea0, 'lundump', 'lundump.c (precompiled chunk loader)'),
    (0xd6d0, 'lvm', 'lvm.c (virtual machine)'),
    (0xee30, 'lzio', 'lzio.c (input streams)'),
    (0xef80, None, 'MSVC C runtime'),
]
LUA_KNOWN = {
    0x29d0: ('luaL_argerror', "bad argument #%d to function '%s'"),
    0x2a30: ('luaL_check_string', ''), 0x2a70: ('luaL_opt_string', ''),
    0x2aa0: ('luaL_check_number', ''), 0x2ae0: ('luaL_opt_number', ''),
    0x2b10: ('luaL_tablearg', ''), 0x2b50: ('luaL_functionarg', ''), 0x2b90: ('luaL_nonnullarg', ''),
    0x2bc0: ('luaL_openlib', ''), 0x2be0: ('luaL_verror', 'formats the message then lua_error'),
    0x2c50: ('luaL_growbuffer', 'doubles the shared string buffer through the realloc service'),
    0x3170: ('luaB_tostring', 'userdata: %p / task: %d / table: %p formatting'),
    0x3cc0: ('luaB_rawsettable', ''),
    0x3df0: ('luaB_predefine', 'registers the built-in functions and the setfallback compatibility entry'),
    0x3e40: ('luaD_checkstack', 'Lua2C - C2Lua overflow / stack size overflow'),
    0x4a50: ('luaD_protectedparser', 'runs luaU_undump1 or luaY_parser on the open ZIO'),
    0x4ba0: ('luaF_newproto', ''), 0x4bf0: ('luaF_newclosure', ''),
    0x5c00: ('luaX_init', 'interns the reserved words'),
    0x5d00: ('luaX_lex', 'main tokenizer; numbers are returned through the float out-parameter'),
    0x6890: ('luaX_pragma', "handles the $debug / $nodebug / $if pragmas"),
    0x73b0: ('luaM_free', ''), 0x73f0: ('luaM_growaux', ''),
    0x7450: ('luaO_redimension', 'next prime size for a hash; table overflow past the last prime'),
    0x8d40: ('luaS_init', ''), 0x9000: ('luaS_newlstr', ''), 0x9110: ('luaS_newfixedstring', ''),
    0xa7d0: ('luaY_code_byte', 'code size overflow'), 0xaa40: ('luaY_syntaxerror', 'lua.stx error reporting'),
    0xabd0: ('yyparse', 'generated LALR parser from lua.stx'), 0xb860: ('luaY_next_constant', 'constant table overflow'),
    0xc200: ('luaH_save', 'Grim save-game table writer (asserts writtenItems == numItems)'),
    0xc850: ('luaT_init', ''), 0xc920: ('luaT_checktag', "not result of `newtag'"),
    0xc9f0: ('luaT_realtag', '%d is not a valid tag'), 0xcab0: ('luaI_checkevent', 'not a valid event name'),
    0xd420: ('luaU_loadheader', 'binary file %s too new/old version'), 0xd5c0: ('luaU_str2number', 'parses %lf %c'),
    0xdf40: ('luaV_execute', 'opcode interpreter loop'), 0xebc0: ('luaV_strconc', 'string concatenation'),
    0xec50: ('luaV_gettable', ''),
}

IMUSE_RANGES = [
    (0x1000, 'iMUSE_Codec', 'compressed audio decoding (VIMA/ADPCM style tables) - module name inferred'),
    (0x1f10, 'iMUSE_Dispatch', 'iMUSE_Dispatch.c (command dispatch, fades, triggers)'),
    (0x36b0, 'iMUSE_dsound', 'iMUSE_dsound.c (DirectSound output)'),
    (0x4aa0, 'iMUSE_api', 'exported Im* entry points'),
    (0x5360, 'iMUSE_Mixer', 'iMUSE_Mixer.c (software mixing / resampling)'),
    (0x7410, 'iMUSE_sounds', 'iMUSE_sounds.c (sound resource slots)'),
    (0xa1e0, 'iMUSE_stream', 'stream tracks (Im_RefillStreamTrack and friends) - module name inferred'),
    (0xb870, 'hmi', 'HMI SOS FX hooks and helpers - module name inferred'),
    (0xd210, None, 'MSVC C runtime'),
]
IMUSE_KNOWN = {}


def gen(prog, raw, ranges, known, out):
    fs = json.load(open(os.path.join(ROOT, 'raw', raw, 'functions.json')))
    base = 0x10000000
    entries = []
    for f in fs:
        if not f['name'].startswith('FUN_'):
            continue
        a = int(f['address'], 16) - base
        mod = note = None
        for s, m, n in ranges:
            if a >= s:
                mod, note = m, n
        if mod is None:
            continue
        if a in known:
            name, cm = known[a]
            comment = '%s: %s' % (note.split(' (')[0], cm) if cm else note
        else:
            name = '%s__%04x' % (mod, a)
            comment = 'Unidentified function of %s' % note
        entries.append({'addr': f['address'], 'name': name, 'comment': comment, 'tags': mod.lower(), 'program': prog})
    json.dump(entries, open(os.path.join(ROOT, 'names', out), 'w'), indent=0)
    print(out, len(entries))


gen('/LUA.DLL', 'LUA.DLL', LUA_RANGES, LUA_KNOWN, 'lua_modules.json')
gen('/v101/IMUSE.DLL', 'IMUSE.DLL', IMUSE_RANGES, IMUSE_KNOWN, 'imuse_modules.json')
