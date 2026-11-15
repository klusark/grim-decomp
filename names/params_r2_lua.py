# Parameter names of LUA.DLL functions (tools/names_batch.py), round 2 (Lua 3.1's names where it has the function)
N = {
 'lua_updatetasks': ['loop'],
 'lua_getlocal': ['funcObj', None, None],
 'lua_setlocal': ['funcObj', None],
 'luaD_protectedrun': ['nResults'],
 'protectedparser': ['z', 'bin'],
 'fillvalids': [None, 'func'],
 'LoadHeader': ['zio'],
 'ExecutionState_CrunchOpcodes': ['state'],
}
