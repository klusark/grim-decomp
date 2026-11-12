# Types, round 8 (2026-11-12): Lua 3.1's objects in LUA.DLL

LUA.DLL had no structure typed. Its code is Lua 3.1 with the original names, so its object model is known in
outline; the layouts here are the ones Grim's build has, each checked against the code that builds or reads it.
Batches: `names/types_lua.json` (8 structures, 50 prototypes), `names/lua_lfunc_fix.json` (two names).

## The structures

Every collectable object starts with Lua's `GCnode {next, marked}`, written into each structure as `pNext` (typed as
the structure's own list) and `nMarked`.

| structure | size | fields | checked against |
|---|---|---|---|
| `TObject` | 8 | `int nTtype`, `uint dwValue` | everything below; the value is a union (float or pointer), kept as its bits since `ghidra_types.h` holds structures only |
| `TaggedString` | 0x1c | `pNext`, `nMarked`, `int nConstIndex` (+8), `uint dwHash` (+0xc), `TObject globalval` (+0x10), `char aStr[]` (+0x18) | `newone` / `insert` (lstring.c): Grim has constindex **before** the hash, the other way from Lua 3.1; constindex -1 marks a userdata, whose tag and pointer sit in `globalval` |
| `StringTable` | 0xc | `int nSize`, `int nUse`, `TaggedString **ppHash` | `insert`, `grow` (61 of them at the state's `string_root`) |
| `Node` | 0x10 | `TObject ref`, `TObject val` | `luaH_get` / `luaH_set`: a nil key is an empty slot |
| `Hash` | 0x18 | `pNext`, `nMarked`, `Node *pNode`, `int nNhash`, `int nNuse`, `int nHtag` | `luaH_new` (tag -3), `luaH_set` (rehash at 70 % use), `freeHash` |
| `LocVar` | 8 | `TaggedString *pVarname`, `int nLine` | `luaF_getlocalname`, `luaC_protomark`: line -1 ends the list |
| `TProtoFunc` | 0x20 | `pNext`, `nMarked`, `TObject *pConsts` (+8), `int nNconsts`, `byte *pCode` (+0x10), `int nLineDefined`, `TaggedString *pFileName` (+0x18), `LocVar *pLocvars` | `luaF_newproto` (zeroes the six), `freefunc` (frees +0x10, +0x1c, +8), `luaC_protomark` (marks +0x18 as a string, +8 as nconsts objects): Grim puts the constants first |
| `Closure` | 0x14 + 8n | `pNext`, `nMarked`, `int nNelems`, `TObject aConsts[1]` | `luaF_newclosure` (0x14 + 8 * nelems), `closuremark` (nelems + 1 values) |

The bridge named the string table's slots `ppHash` (its policy for a pointer to pointers).

## Two constructors swapped

The function named `luaF_newproto` (0x10004ba0) takes `nelems`, allocates `0x14 + 8 * nelems` bytes and links the
block into `rootcl`: Lua 3.1's `luaF_newclosure`. The one named `luaF_newclosure` (0x10004bf0) takes nothing,
allocates 0x20 bytes, zeroes six fields and links into `rootproto`: `luaF_newproto`. The callers agree (the parser
and lundump's `LoadFunction` make prototypes; `luaV_closure` makes closures), and so do the list globals, which were
named right. The names are swapped back (`names/lua_lfunc_fix.json`).

## The prototypes

lfunc.c (`luaF_newclosure`, `luaF_newproto`, `luaF_freeproto`, `freefunc`, `luaF_freeclosure`,
`luaF_getlocalname`), lgc.c (`strmark`, `luaC_protomark`, `closuremark`, `hashmark`, `markobject`, `ismarked`,
`luaC_getref`, `luaC_hashcallIM`, `luaC_strcallIM`), lobject.c (`luaO_equalObj`), lstring.c (`luaS_new`,
`luaS_free`, `luaS_createudata`, `newone`, `insert`, `grow`, `luaS_rawsetglobal`, `luaS_globaldefined`), ltable.c
(`luaH_new`, `luaH_free`, `freeHash`, `luaH_get`, `luaH_set`, `present`, `hashindex`, `rehash`, `luaH_next`,
`hashnext`, `luaH_hashnodecreate`, `emptyslots`, `luaH_forcerehash`), ldo.c (`luaD_gcIM`, which gets a TObject the
GC builds on its stack), lapi.c (`luaA_pushobject`, `put_luaObject`, `set_normalized`, `normalized_type`,
`luaA_protovalue`, `checkfunc`), lvm.c (`luaV_settable`, `luaV_getglobal`, `luaV_setglobal`, `luaV_pack`), ltm.c
(`luaT_efectivetag`) and ldo.c's `luaD_callTM`. The public `lua_*` API passes `lua_Object` handles (ints) and keeps them.

The decompiler carried the types into the callers: ltable.c now reads `t->pNode + iVar1`,
`(pNVar3->ref).nTtype == -7`, `return &pNVar3->val;`; lgc.c `markobject(f->pConsts + uVar3)`; lfunc.c
`pLVar4->pVarname->aStr`.

Four of the functions are hand-written (build/overrides.c): `luaO_equalObj`, `hashindex`, `luaH_new` and
`luaV_pack` take and return the types now; their bodies still work on the words (`int *a = (int *)ta`), unchanged.
The overrides' calls of the retyped functions (`luaH_set`, `luaS_new`, `luaA_pushobject`, `luaT_efectivetag`,
`luaD_callTM`) pass the types too (the overrides compile with `-w`: a mismatch would not be reported).

## Checks

* All four programs compile and link; no new stub.
* `datacmp.py` against round 7's build: 0 differences, 0 moved, 0 missing in all four, every unused span zero.
* Sections: the EXE (but its build-time string), CHORE.DLL and IMUSE.DLL identical; LUA.DLL's code changes in the
  typed functions and their callers.
* A full export of LUA.DLL (a new structure's fields are a structure change: 3.5 minutes).
* Clean-room against grim_tools' knowngood (5167 tests, no install file in the run folder), on the build with the
  first 44 prototypes: all 5167 the same as the reference and as round 7; on the final one (50): only the three lab
  tests differ from round 7's log, which this run failed and round 7's passed (not deterministic, data_unused.md);
  every other test the same.

## Next

The stack and the rest of the state: `g_pLuaState` points at a record whose +0x1c is the stack top and +0x20 its
base (TObject *); the lists and tables of the state are separate globals (`g_dwLState_*`). A `lua_State` structure
for that record, and the stack's users in lvm.c / ldo.c, are the next step for LUA.DLL.
