"""Tiny client for the ghidra-mcp HTTP bridge (same endpoints/params as the MCP tools).
Reads are GET with query params, writes are POST with a JSON body."""
import json, time, urllib.request, urllib.parse

BASE = "http://127.0.0.1:8089"
EXE = "/v101/GRIMFANDANGO.EXE"
LUA = "/LUA.DLL"
IMUSE = "/v101/IMUSE.DLL"
CHORE = "/CHORE.DLL"


def get(path, **params):
    url = f"{BASE}/{path.lstrip('/')}"
    if params:
        url += "?" + urllib.parse.urlencode(params)
    for attempt in range(4):
        try:
            with urllib.request.urlopen(url, timeout=180) as r:
                return r.read().decode("utf-8", "replace")
        except Exception as e:
            err = e
            time.sleep(1.5 * (attempt + 1))
    raise RuntimeError(f"GET {url}: {err}")


def get_json(path, **params):
    txt = get(path, **params)
    try:
        return json.loads(txt)
    except Exception:
        return {"_raw": txt}


# ---- change journal -----------------------------------------------------
# Every write that can change a decompilation is recorded in raw/touched.json
# ({program: [address, ...]}) so `export_raw.py --changed` can re-export only
# the touched functions and their callers instead of the whole program.
import atexit, os
_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
TOUCHED_PATH = os.path.join(_ROOT, "raw", "touched.json")
MUTATING = {"rename_function_by_address", "rename_function", "create_function", "set_function_prototype",
            "set_plate_comment", "rename_data", "rename_or_label", "set_global", "create_label",
            "apply_data_type", "set_function_no_return", "delete_function", "rename_variable",
            "rename_variables", "set_decompiler_comment", "set_comment", "set_parameter_type",
            "set_local_variable_type", "batch_rename_function_components", "batch_create_labels",
            "rename_label", "delete_label", "set_function_this_type"}
_touched = {}


def _record(path, body):
    name = path.strip("/")
    if name not in MUTATING:
        if name.startswith(("modify_struct", "add_struct", "create_struct", "resize_struct", "remove_struct")):
            _touched.setdefault(body.get("program", "?"), set()).add("*struct*")
        return
    prog = body.get("program", "?")
    for key in ("function_address", "address", "function"):
        if key in body:
            _touched.setdefault(prog, set()).add(str(body[key]))
            break


def _flush_touched():
    if not _touched:
        return
    try:
        cur = json.load(open(TOUCHED_PATH)) if os.path.exists(TOUCHED_PATH) else {}
    except ValueError:
        cur = {}
    for prog, addrs in _touched.items():
        cur[prog] = sorted(set(cur.get(prog, [])) | addrs)
    os.makedirs(os.path.dirname(TOUCHED_PATH), exist_ok=True)
    json.dump(cur, open(TOUCHED_PATH, "w"), indent=1)


atexit.register(_flush_touched)


def post(path, **body):
    _record(path, body)
    url = f"{BASE}/{path.lstrip('/')}"
    if body.get("program"):
        # the bridge takes the program of a write from the query string (a `program` in the JSON body is ignored and
        # the write goes to its current program, which switch_program does not always change)
        q = {"program": body["program"]}
        if body.get("strict_mode"):   # (like program, read from the query string)
            q["strict_mode"] = body["strict_mode"]
        url += "?" + urllib.parse.urlencode(q)
    data = json.dumps(body).encode()
    req = urllib.request.Request(url, data=data, headers={"Content-Type": "application/json"})
    for attempt in range(4):
        try:
            with urllib.request.urlopen(req, timeout=180) as r:
                txt = r.read().decode("utf-8", "replace")
            try:
                return json.loads(txt)
            except Exception:
                return {"_raw": txt}
        except urllib.error.HTTPError as e:
            return {"error": f"HTTP {e.code}", "body": e.read().decode("utf-8", "replace")}
        except Exception as e:
            err = e
            time.sleep(1.5 * (attempt + 1))
    raise RuntimeError(f"POST {url}: {err}")


def ok(resp):
    if isinstance(resp, dict) and str(resp.get("_raw", "")).lstrip().startswith(("Failed", "Error")):
        return False   # some endpoints answer with plain text ("Failed to set function prototype: ...")
    return isinstance(resp, dict) and ("error" not in resp or resp.get("status") == "success")


def ensure_current(program):
    """POST (write) endpoints act on the bridge's *current* program and ignore the program
    argument, so make sure it is the one we mean before any batch of writes."""
    r = get("switch_program", program=program)
    if '"success":true' not in r:
        raise RuntimeError(f"could not switch program: {r}")


# ---- convenience wrappers -------------------------------------------------
def rename_function(program, address, new_name):
    return post("rename_function_by_address", program=program, function_address=address, new_name=new_name)


def create_function(program, address, name=""):
    body = dict(program=program, address=address)
    if name:
        body["name"] = name
    return post("create_function", **body)


def set_prototype(program, address, prototype, calling_convention=""):
    body = dict(program=program, function_address=address, prototype=prototype)
    if calling_convention:
        body["calling_convention"] = calling_convention
    return post("set_function_prototype", **body)


def set_plate_comment(program, address, comment):
    return post("set_plate_comment", program=program, address=address, comment=comment)


def rename_data(program, address, new_name):
    return post("rename_data", program=program, address=address, new_name=new_name)


def rename_or_label(program, address, name):
    return post("rename_or_label", program=program, address=address, name=name)


def set_global(program, address, name, type_name, plate_comment="", array_length=0):
    return post("set_global", program=program, address=address, name=name, type_name=type_name,
                plate_comment=plate_comment, array_length=array_length)


def add_tag(program, address, tags):
    """tags: comma-separated string."""
    return post("add_function_tag", program=program, function=address, tags=tags)


def batch_tags(program, assignments):
    """assignments: [{"function": addr, "tags": "a,b"}, ...]"""
    return post("batch_add_function_tags", program=program, assignments=assignments)


def decompile(program, address):
    return get("decompile_function", program=program, address=address)


def xrefs_to(program, address, limit=2000):
    return get("get_xrefs_to", program=program, address=address, limit=limit)
