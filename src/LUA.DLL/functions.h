/* LUA.DLL: prototypes of every decompiled function, by module */
#pragma once
#include "ghidra_types.h"

/* ===== lapi.c ===== */
int * __cdecl lua_recognizelib(int param_1,int param_2); /* 0x10001000 */
undefined4 __cdecl lua_openlib(undefined4 *param_1,int param_2); /* 0x10001060 */
uint __cdecl lua_FuncPtrToID(int param_1); /* 0x100010d0 */
undefined4 __cdecl lua_IDToFuncPtr(uint param_1); /* 0x10001120 */
undefined4 __cdecl lua_closelibs(void); /* 0x10001160 */
undefined4 __cdecl lua_Initialize(undefined4 param_1,undefined4 *param_2); /* 0x10001190 */
int __cdecl luaA_Address(int param_1); /* 0x100011e0 */
void luaA_packresults(void); /* 0x10001200 */
int luaA_passresults(void); /* 0x10001240 */
undefined4 lua_pop(void); /* 0x100012a0 */
void __cdecl checkCparams(int param_1); /* 0x100012b0 */
int put_luaObjectonTop(void); /* 0x100012e0 */
int __cdecl lua_lua2C(int param_1); /* 0x10001340 */
undefined4 __cdecl lua_callfunction(int param_1); /* 0x10001360 */
void __cdecl set_normalized(TObject *d,TObject *s); /* 0x100013c0 */
int __cdecl normalized_type(TObject *o); /* 0x100013e0 */
int __cdecl lua_gettagmethod(int param_1,byte *param_2); /* 0x10001410 */
int __cdecl put_luaObject(TObject *o); /* 0x10001430 */
undefined4 __cdecl lua_settagmethod(int param_1,byte *param_2); /* 0x10001490 */
int __cdecl lua_seterrormethod(void); /* 0x100014c0 */
undefined4 __cdecl lua_gettable(void); /* 0x10001520 */
undefined4 lua_rawgettable(void); /* 0x10001540 */
undefined4 __cdecl lua_settable(void); /* 0x100015b0 */
undefined4 __cdecl lua_rawsettable(void); /* 0x100015e0 */
int __cdecl lua_createtable(void); /* 0x10001610 */
undefined4 __cdecl lua_getglobal(byte *param_1); /* 0x10001640 */
int __cdecl lua_rawgetglobal(byte *param_1); /* 0x10001670 */
undefined4 __cdecl lua_setglobal(byte *param_1); /* 0x10001690 */
undefined4 __cdecl lua_rawsetglobal(byte *param_1); /* 0x100016c0 */
undefined4 __cdecl lua_isnil(int param_1); /* 0x10001700 */
undefined4 __cdecl lua_istable(int param_1); /* 0x10001730 */
undefined4 __cdecl lua_isuserdata(int param_1); /* 0x10001760 */
int __cdecl lua_iscfunction(int param_1); /* 0x10001790 */
undefined4 __cdecl lua_isnumber(int param_1); /* 0x100017b0 */
undefined4 __cdecl lua_isstring(int param_1); /* 0x100017f0 */
undefined4 __cdecl lua_isfunction(int param_1); /* 0x10001810 */
undefined4 __cdecl lua_istask(int param_1); /* 0x10001830 */
float __cdecl lua_getnumber(int param_1); /* 0x10001860 */
int __cdecl lua_getstring(int param_1); /* 0x100018c0 */
undefined4 __cdecl lua_getuserdata(int param_1); /* 0x10001910 */
int __cdecl lua_getcfunction(int param_1); /* 0x10001940 */
TObject * __cdecl luaA_protovalue(TObject *o); /* 0x10001970 */
int __cdecl lua_gettask(int obj); /* 0x10001990 */
undefined4 __cdecl lua_pushtask(int param_1); /* 0x100019c0 */
undefined4 __cdecl lua_pushnil(void); /* 0x10001a10 */
void __cdecl lua_pushnumber(float n); /* 0x10001a50 */
undefined4 __cdecl lua_pushstring(byte *param_1); /* 0x10001aa0 */
undefined4 __cdecl lua_pushCclosure(int param_1,uint param_2); /* 0x10001b10 */
undefined4 __cdecl lua_pushusertag(byte *param_1,uint param_2); /* 0x10001b90 */
void __cdecl luaA_pushobject(TObject *o); /* 0x10001c00 */
undefined4 __cdecl lua_pushobject(int param_1); /* 0x10001c40 */
undefined4 __cdecl lua_tag(int param_1); /* 0x10001ca0 */
int * __cdecl lua_settag(int param_1); /* 0x10001d30 */
undefined4 __cdecl lua_pausetasks(void); /* 0x10001db0 */
undefined4 __cdecl lua_unpausetasks(void); /* 0x10001de0 */
int __cdecl lua_updatetasks(int param_1); /* 0x10001e10 */
int __cdecl lua_stackedfunction(int param_1); /* 0x10002090 */
undefined4 __cdecl lua_printstack(int param_1); /* 0x100020f0 */
undefined4 __cdecl lua_currentline(int param_1); /* 0x10002280 */
int lua_currenttask(void); /* 0x100022b0 */
int __cdecl lua_getlocal(int param_1,int param_2,int *param_3); /* 0x100022c0 */
undefined4 __cdecl lua_setlocal(int param_1,int param_2); /* 0x10002330 */
undefined4 __cdecl lua_funcinfo(int param_1,int *param_2,undefined4 *param_3); /* 0x100023c0 */
char * __cdecl lua_getobjname(int param_1,undefined4 *param_2); /* 0x10002440 */
void __cdecl checkfunc(TObject *o); /* 0x100024a0 */
int * __cdecl lua_beginblock(void); /* 0x100024c0 */
undefined4 __cdecl lua_endblock(void); /* 0x10002510 */
uint __cdecl lua_ref(int param_1); /* 0x10002560 */
int __cdecl lua_getref(uint param_1); /* 0x10002590 */
undefined4 __cdecl lua_setfallback(byte *name,int fallback); /* 0x100025b0 */
void __cdecl do_unprotectedrun(undefined4 param_1,int param_2,void *param_3); /* 0x100025f0 */
void luaA_ResetSaveCount(void); /* 0x10002660 */
undefined4 __cdecl lua_Save(undefined *param_1); /* 0x10002670 */
void __cdecl LuaSaveWriter(undefined4 param_1,int param_2); /* 0x10002730 */
undefined4 lua_Restore(code *param_1); /* 0x10002760 */
void Lua_Terminate(void); /* 0x10002900 */
undefined4 Lua_Startup(void); /* 0x10002920 */
void Lua_Shutdown(void); /* 0x10002940 */
undefined4 __cdecl lua_error(byte *param_1); /* 0x10004650 */
int __cdecl lua_dofile(char *param_1); /* 0x10004890 */
int __cdecl lua_dostring(char *param_1); /* 0x10004b20 */
uint __cdecl lua_unref(uint param_1); /* 0x10004e00 */
int __cdecl lua_collectgarbage(int param_1); /* 0x10004ee0 */
undefined4 __cdecl lua_iolibopen(void); /* 0x10005ae0 */
void openwithtags(void); /* 0x10005b20 */
undefined4 __cdecl lua_mathlibopen(void); /* 0x10007320 */
void LState_initglobals(void); /* 0x10008a00 */
int * __cdecl lua_open(void); /* 0x10008b40 */
undefined4 __cdecl lua_close(void); /* 0x10008c30 */
undefined4 __cdecl lua_strlibopen(void); /* 0x1000a6e0 */
int lua_newtag(void); /* 0x1000c8d0 */
int __cdecl lua_copytagmethods(int param_1,int param_2); /* 0x1000c950 */

/* ===== lauxlib.c ===== */
int __cdecl luaFGetc(undefined4 param_1); /* 0x10002960 */
int __cdecl luaFUngetc(int param_1,undefined4 param_2); /* 0x10002990 */
void __cdecl luaL_argerror(undefined4 param_1,int param_2); /* 0x100029d0 */
int __cdecl luaL_check_string(int param_1); /* 0x10002a30 */
undefined4 __cdecl luaL_opt_string(int param_1,undefined4 param_2); /* 0x10002a70 */
float __cdecl luaL_check_number(int param_1); /* 0x10002aa0 */
float __cdecl luaL_opt_number(int param_1,float param_2); /* 0x10002ae0 */
int __cdecl luaL_tablearg(int param_1); /* 0x10002b10 */
int __cdecl luaL_functionarg(int param_1); /* 0x10002b50 */
int __cdecl luaL_nonnullarg(int param_1); /* 0x10002b90 */
void __cdecl luaL_openlib(undefined4 *param_1,int param_2); /* 0x10002bc0 */
void __cdecl luaL_verror(char *fmt,...); /* 0x10002be0 */
int __cdecl luaL_openspace(int param_1); /* 0x10002c20 */
void __cdecl Lbuffer_Openspace(int param_1); /* 0x10002c50 */
void __cdecl luaL_addchar(undefined1 param_1); /* 0x10002cb0 */
void luaL_resetbuffer(void); /* 0x10002cf0 */

/* ===== lbuiltin.c ===== */
void __cdecl luaL_addsize(int param_1); /* 0x10002d10 */
int __cdecl luaL_newbuffer(int param_1); /* 0x10002d30 */
void __cdecl luaL_oldbuffer(int param_1); /* 0x10002d80 */
undefined4 luaL_buffer(void); /* 0x10002da0 */
void nextvar(void); /* 0x10002db0 */
void __cdecl pushstring(uint param_1); /* 0x10002e40 */
void foreachvar(void); /* 0x10002e70 */
void next(void); /* 0x10002f80 */
void foreach(void); /* 0x10002fd0 */
void internaldostring(void); /* 0x100030d0 */
void internaldofile(void); /* 0x10003120 */
void bi_tostring(void); /* 0x10003150 */
undefined1 * __cdecl to_string(int param_1); /* 0x10003170 */
void luaI_startscript(void); /* 0x10003260 */
void luaI_stopscript(void); /* 0x10003370 */
void luaI_findscript(void); /* 0x100034c0 */
void luaI_identifyscript(void); /* 0x10003610 */
void luaI_nextscript(void); /* 0x100036a0 */
void luaI_breakhere(void); /* 0x10003770 */
void luaI_print(void); /* 0x10003780 */
void luaI_type(void); /* 0x100037d0 */
void tonumber(void); /* 0x10003820 */
void luaI_error(void); /* 0x10003910 */
void luaI_assert(void); /* 0x10003930 */
void setglobal(void); /* 0x10003970 */
void rawsetglobal(void); /* 0x100039b0 */
void getglobal(void); /* 0x100039f0 */
void rawgetglobal(void); /* 0x10003a10 */
void luatag(void); /* 0x10003a30 */
void luaI_call(void); /* 0x10003a60 */
int __cdecl getnarg(int param_1); /* 0x10003ba0 */
void settag(void); /* 0x10003bf0 */
void newtag(void); /* 0x10003c20 */
void copytagmethods(void); /* 0x10003c40 */
void rawgettable(void); /* 0x10003c80 */
void rawsettable(void); /* 0x10003cc0 */
void settagmethod(void); /* 0x10003d10 */
void gettagmethod(void); /* 0x10003d50 */
void seterrormethod(void); /* 0x10003d80 */
void luaI_collectgarbage(void); /* 0x10003db0 */
void luaB_predefine(void); /* 0x10003df0 */

/* ===== ldo.c ===== */
void __cdecl luaD_checkstack(int param_1); /* 0x10003e40 */
void __cdecl luaD_adjusttop(int param_1); /* 0x10003ee0 */
void __cdecl luaD_openstack(int param_1); /* 0x10003f40 */
void __cdecl luaD_lineHook(undefined4 param_1); /* 0x10003f90 */
void __cdecl luaD_callHook(int param_1,int param_2,int param_3); /* 0x10004000 */
void __cdecl luaD_taskHook(undefined4 param_1,undefined4 param_2); /* 0x100040c0 */
void __cdecl luaD_callTM(TObject *f,int nParams,int nResults); /* 0x100040e0 */
void __cdecl luaD_deletestates(int param_1); /* 0x10004160 */
undefined4 luaD_call(code *param_1,void *param_2); /* 0x10004180 */
int __cdecl callC(undefined *param_1,int param_2); /* 0x100044e0 */
int __cdecl callCclosure(int param_1,undefined *param_2,int param_3); /* 0x10004580 */
void __cdecl luaD_travallstacks(undefined *param_1); /* 0x10004600 */
void __cdecl message(byte *param_1); /* 0x100046a0 */
undefined4 __cdecl luaD_protectedrun(void *param_1); /* 0x100046e0 */
void __cdecl do_callinc(void *param_1); /* 0x100047c0 */
void __cdecl luaD_gcIM(TObject *o); /* 0x10004810 */
int __cdecl do_main(int *param_1,int param_2); /* 0x100049b0 */
undefined4 __cdecl protectedparser(int *param_1,int param_2); /* 0x10004a50 */

/* ===== lfunc.c ===== */
Closure * __cdecl luaF_newclosure(int nelems); /* 0x10004ba0 */
TProtoFunc * __cdecl luaF_newproto(void); /* 0x10004bf0 */
void __cdecl luaF_freeproto(TProtoFunc *l); /* 0x10004c40 */
void __cdecl freefunc(TProtoFunc *f); /* 0x10004c70 */
void __cdecl luaF_freeclosure(Closure *l); /* 0x10004cc0 */
char * __cdecl luaF_getlocalname(TProtoFunc *func,int local_number,int line); /* 0x10004cf0 */
uint __cdecl luaC_ref(int *param_1,int param_2); /* 0x10004d40 */
TObject * __cdecl luaC_getref(int ref); /* 0x10004e30 */

/* ===== lgc.c ===== */
void __cdecl luaC_hashcallIM(Hash *l); /* 0x10004e70 */
void __cdecl luaC_strcallIM(TaggedString *l); /* 0x10004ea0 */
void invalidaterefs(void); /* 0x10004fc0 */
int __cdecl ismarked(TObject *o); /* 0x10005010 */
int __cdecl listcollect(undefined4 *param_1); /* 0x10005070 */
void markall(void); /* 0x100050b0 */
void travlock(void); /* 0x100050e0 */
void globalmark(void); /* 0x10005120 */
void __cdecl strmark(TaggedString *s); /* 0x10005150 */
int __cdecl markobject(TObject *o); /* 0x10005170 */
void __cdecl luaC_protomark(TProtoFunc *f); /* 0x100051f0 */
void __cdecl closuremark(Closure *f); /* 0x10005270 */
void __cdecl hashmark(Hash *h); /* 0x100052b0 */
void luaC_checkGC(void); /* 0x10005300 */
void io_readfrom(void); /* 0x10005320 */

/* ===== io.c ===== */
longlong __cdecl gettag(int param_1); /* 0x100053d0 */
void __cdecl pushresult(int param_1); /* 0x100053f0 */
void __cdecl closefile(byte *param_1); /* 0x10005430 */
int __cdecl getfile(byte *param_1); /* 0x10005480 */
int __cdecl ishandler(int param_1); /* 0x100054c0 */
void __cdecl setreturn(byte *param_1,byte *param_2); /* 0x10005520 */
void __cdecl setfile(byte *param_1,byte *param_2,uint param_3); /* 0x10005550 */
void io_writeto(void); /* 0x10005570 */
void io_appendto(void); /* 0x10005620 */
void io_read(void); /* 0x10005660 */
int __cdecl getfileparam(byte *param_1,int *param_2); /* 0x10005780 */
void io_write(void); /* 0x100057d0 */
void io_execute(void); /* 0x10005870 */
void io_remove(void); /* 0x100058a0 */
void io_rename(void); /* 0x100058d0 */
void io_tmpname(void); /* 0x10005900 */
void io_getenv(void); /* 0x10005920 */
void io_date(void); /* 0x10005940 */
void setloc(void); /* 0x100059c0 */
void io_exit(void); /* 0x10005a20 */
void io_debug(void); /* 0x10005a50 */
void errorfb(void); /* 0x10005ad0 */

/* ===== llex.c ===== */
void luaX_init(void); /* 0x10005c00 */
void __cdecl luaX_setinput(undefined4 param_1); /* 0x10005c30 */
void __cdecl firstline(int param_1); /* 0x10005c70 */
int luaX_lasttoken(void); /* 0x10005cf0 */
uint __cdecl luaY_lex(float *param_1); /* 0x10005d00 */
void __cdecl inclinenumber(uint *param_1); /* 0x10006890 */
void __cdecl skipspace(uint *param_1); /* 0x10006b10 */
uint __cdecl checkcond(byte *param_1); /* 0x10006b60 */
void __cdecl readname(uint *param_1,int param_2); /* 0x10006bb0 */
void __cdecl ifskip(uint *param_1); /* 0x10006c30 */
undefined4 __cdecl read_long_string(uint *param_1,undefined4 *param_2); /* 0x10006cb0 */

/* ===== math.c ===== */
void math_abs(void); /* 0x10006ea0 */
void math_sin(void); /* 0x10006ee0 */
void math_cos(void); /* 0x10006f00 */
void math_tan(void); /* 0x10006f20 */
void math_asin(void); /* 0x10006f50 */
void math_acos(void); /* 0x10006f80 */
void math_atan(void); /* 0x10006fb0 */
void math_atan2(void); /* 0x10006fe0 */
void math_ceil(void); /* 0x10007020 */
void math_floor(void); /* 0x10007050 */
void math_mod(void); /* 0x10007080 */
void math_sqrt(void); /* 0x100070c0 */
void math_pow(void); /* 0x100070e0 */
void math_log(void); /* 0x10007120 */
void math_log10(void); /* 0x10007140 */
void math_exp(void); /* 0x10007160 */
void math_deg(void); /* 0x10007190 */
void math_rad(void); /* 0x100071b0 */
void math_min(void); /* 0x100071d0 */
void math_max(void); /* 0x10007230 */
void math_random(void); /* 0x10007290 */
void math_randomseed(void); /* 0x10007300 */

/* ===== lmem.c ===== */
void * __cdecl luaM_malloc(uint size); /* 0x100073b0 */
void __cdecl luaM_free(void *block); /* 0x100073d0 */
uint __cdecl luaM_growaux(undefined4 *param_1,uint param_2,int param_3,byte *param_4,uint param_5); /* 0x100073f0 */

/* ===== lobject.c ===== */
undefined4 __cdecl luaO_redimension(int param_1); /* 0x10007450 */
int __cdecl luaO_equalObj(TObject *t1,TObject *t2); /* 0x100074b0 */
int __cdecl luaO_findstring(byte *param_1,undefined4 *param_2); /* 0x10007550 */
void __cdecl luaO_insertlist(undefined4 *param_1,undefined4 *param_2); /* 0x100075c0 */

/* ===== lstate.c ===== */
undefined4 * __fastcall LState_Construct(undefined4 *param_1); /* 0x100075e0 */
undefined4 __stdcall LState_SerialToPtr(int a1); /* 0x10007660 */
uint __cdecl comparePtrIDs(int param_1,int param_2); /* 0x10007810 */
undefined4 __stdcall LState_SaveObject(int a1,int a2); /* 0x10007830 */
undefined4 __stdcall LState_LoadObject(int a1,int a2); /* 0x10007880 */
int __stdcall LState_ResolveObject(int a1); /* 0x100078b0 */
undefined4 __stdcall LState_LoadResolvedObject(int a1,int a2); /* 0x10007910 */
undefined4 __stdcall LState_GlobalEndRestore(int a1); /* 0x10007930 */
undefined4 __stdcall LState_GlobalBeginRestore(int a1); /* 0x100079d0 */
undefined4 __stdcall LState_SaveGlobals(int a1); /* 0x100081c0 */
byte * __cdecl lstate__85e0(int param_1); /* 0x100085e0 */
undefined4 __thiscall LState_Save(void *this,int a1); /* 0x10008640 */
undefined4 __thiscall LState_Restore(void *this,int a1); /* 0x100087f0 */
undefined4 * lua_newstate(void); /* 0x10008ad0 */
int __thiscall LState_attach(void *this,int a1); /* 0x10008b70 */
void __fastcall LState_detach(int param_1); /* 0x10008bb0 */
undefined4 __fastcall LState_next(int param_1); /* 0x10008bf0 */
void __fastcall LState_Destruct(int *param_1); /* 0x10008c00 */

/* ===== lstring.c ===== */
void luaS_init(void); /* 0x10008d40 */
TaggedString * __cdecl luaS_createudata(void *udata,int tag); /* 0x10008d90 */
TaggedString * __cdecl insert(char *buff,int tag,StringTable *tb); /* 0x10008dc0 */
byte * __cdecl hash(byte *param_1,int param_2); /* 0x10008f10 */
void __cdecl grow(StringTable *tb); /* 0x10008f50 */
TaggedString * __cdecl newone(char *buff,int tag,uint h); /* 0x10009000 */
TaggedString * __cdecl luaS_new(char *str); /* 0x100090e0 */
void __cdecl luaS_newfixedstring(byte *param_1); /* 0x10009110 */
void __cdecl luaS_free(TaggedString *l); /* 0x10009130 */
void __cdecl luaS_writestrings(undefined *param_1,int *param_2); /* 0x10009180 */
void __cdecl luaS_resolvestrings(int *param_1); /* 0x10009290 */
int __cdecl luaS_count(int *param_1,uint *param_2); /* 0x100092e0 */
int luaS_collector(void); /* 0x10009370 */
void __cdecl remove_from_list(undefined4 *param_1); /* 0x100093e0 */
uint * luaS_collectudata(void); /* 0x10009410 */
void luaS_freeall(void); /* 0x10009470 */
void __cdecl luaS_rawsetglobal(TaggedString *ts,TObject *newval); /* 0x100094e0 */
int * __cdecl luaS_travsymbol(undefined *param_1); /* 0x10009510 */
int __cdecl luaS_globaldefined(char *name); /* 0x10009550 */
void str_len(void); /* 0x10009570 */

/* ===== str.c ===== */
void str_sub(void); /* 0x100095b0 */
void __cdecl addnchar(uint *param_1,uint param_2); /* 0x10009650 */
void closeandpush(void); /* 0x10009680 */
void str_lower(void); /* 0x100096a0 */
void str_upper(void); /* 0x100096e0 */
void str_rep(void); /* 0x10009720 */
void __cdecl addstr(uint *param_1); /* 0x10009760 */
void str_ascii(void); /* 0x10009780 */
uint __cdecl luaI_singlematch(uint param_1,char *param_2,int *param_3); /* 0x100097f0 */
uint * __cdecl bracket_end(char *param_1); /* 0x100099e0 */
uint __cdecl matchclass(uint param_1,uint param_2); /* 0x10009a10 */
void str_find(void); /* 0x10009cb0 */
void __cdecl push_captures(int *ms); /* 0x10009e40 */
char * __cdecl match(char *param_1,int *param_2,int *param_3); /* 0x10009ea0 */
int __cdecl capture_to_close(int *param_1); /* 0x1000a030 */
char * __cdecl matchitem(char *param_1,char *param_2,int *param_3,int *param_4); /* 0x1000a060 */
int __cdecl check_cap(int param_1,int *param_2); /* 0x1000a150 */
char * __cdecl matchbalance(char *param_1,int param_2,int param_3); /* 0x1000a180 */
void str_gsub(void); /* 0x1000a1d0 */
void __cdecl add_s(int param_1,int *param_2); /* 0x1000a2e0 */
void str_format(void); /* 0x1000a440 */
void __cdecl luaI_addquoted(char *param_1); /* 0x1000a680 */

/* ===== lparser.c ===== */
void __cdecl luaY_syntaxerror(char *msg,char *token); /* 0x1000a6f0 */
void __cdecl luaY_error(char *msg); /* 0x1000a730 */
void __cdecl luaY_codedebugline(uint param_1); /* 0x1000a750 */
void __cdecl code_oparg(char param_1,int param_2,uint param_3,int param_4); /* 0x1000a790 */
void __cdecl check_pc(int param_1); /* 0x1000a7d0 */
undefined4 __cdecl code_oparg_at(int param_1,char param_2,int param_3,uint param_4,int param_5); /* 0x1000a810 */
void __cdecl deltastack(int param_1); /* 0x1000a8b0 */
int __cdecl luaY_parser(int param_1); /* 0x1000a900 */
void __cdecl init_state(TaggedString *param_1); /* 0x1000a980 */
void __cdecl code_byte(undefined1 param_1); /* 0x1000aa10 */
int close_func(void); /* 0x1000aa40 */
void __cdecl code_neutralop(undefined1 param_1); /* 0x1000ab20 */
void __cdecl code_opcode(undefined1 param_1,int param_2); /* 0x1000ab30 */
void __cdecl luaI_registerlocalvar(undefined4 param_1,undefined4 param_2); /* 0x1000ab50 */
undefined4 luaY_parse(void); /* 0x1000abd0 */
int __cdecl fix_opcode(int param_1,char param_2,int param_3,uint param_4); /* 0x1000b770 */
void __cdecl code_pop(undefined1 param_1); /* 0x1000b800 */
uint __cdecl string_constant(int param_1,int *param_2); /* 0x1000b810 */
int __cdecl next_constant(int *param_1); /* 0x1000b860 */
void __cdecl code_string(int param_1); /* 0x1000b8a0 */
void __cdecl code_constant(uint param_1); /* 0x1000b8c0 */
void __cdecl code_number(float param_1); /* 0x1000b8e0 */
int __cdecl real_constant(float param_1); /* 0x1000b950 */
void __cdecl flush_record(int param_1); /* 0x1000b9c0 */
void __cdecl flush_list(uint param_1,int param_2); /* 0x1000b9e0 */
void __cdecl luaI_unregisterlocalvar(undefined4 param_1); /* 0x1000ba10 */
void __cdecl store_localvar(undefined4 param_1,int param_2); /* 0x1000ba20 */
void __cdecl add_localvar(undefined4 param_1); /* 0x1000ba70 */
void __cdecl add_varbuffer(int param_1,int param_2); /* 0x1000ba90 */
int __cdecl var2store(int param_1); /* 0x1000bad0 */
int __cdecl singlevar(int param_1,int *param_2); /* 0x1000baf0 */
int __cdecl aux_localname(int param_1,int param_2); /* 0x1000bba0 */
void __cdecl pushupvalue(int param_1); /* 0x1000bbd0 */
int __cdecl indexupvalue(int param_1); /* 0x1000bc40 */
void __cdecl adjuststack(int param_1); /* 0x1000bcc0 */
int __cdecl adjust_functioncall(int param_1,uint param_2); /* 0x1000bd00 */
void __cdecl adjust_mult_assign(int param_1,int param_2); /* 0x1000bd80 */
void __cdecl code_args(int param_1,int param_2); /* 0x1000bde0 */
void __cdecl lua_pushvar(int param_1); /* 0x1000be60 */
void __cdecl storevar(int param_1); /* 0x1000bec0 */
int __cdecl lua_codestore(int param_1,int param_2); /* 0x1000bf00 */
int __cdecl fix_jump(int param_1,char param_2,int param_3); /* 0x1000bf50 */
void __cdecl fix_upjmp(char param_1,int param_2); /* 0x1000bf70 */
void __cdecl codeIf(int param_1,int param_2); /* 0x1000bfa0 */
void __cdecl code_shortcircuit(int param_1,char param_2); /* 0x1000c000 */
void codereturn(void); /* 0x1000c020 */
void func_onstack(void); /* 0x1000c060 */
void init_func(void); /* 0x1000c100 */

/* ===== ltable.c ===== */
void __cdecl luaH_free(Hash *frees); /* 0x1000c190 */
void __cdecl freeHash(Hash *t); /* 0x1000c1d0 */
void __cdecl luaH_save(undefined *param_1,int param_2); /* 0x1000c200 */
undefined4 * __cdecl luaH_load(undefined *param_1); /* 0x1000c2e0 */
Node * __cdecl luaH_hashnodecreate(int nhash); /* 0x1000c390 */
Hash * __cdecl luaH_new(int nhash); /* 0x1000c3d0 */
void __cdecl luaH_forcerehash(Hash *t); /* 0x1000c450 */
int __cdecl present(Hash *t,TObject *key); /* 0x1000c4d0 */
int __cdecl hashindex(TObject *ref); /* 0x1000c580 */
TObject * __cdecl luaH_get(Hash *t,TObject *ref); /* 0x1000c5f0 */
TObject * __cdecl luaH_set(Hash *t,TObject *ref); /* 0x1000c620 */
void __cdecl rehash(Hash *t); /* 0x1000c6b0 */
int __cdecl emptyslots(Hash *t); /* 0x1000c770 */
Node * __cdecl luaH_next(TObject *o,TObject *r); /* 0x1000c7b0 */
Node * __cdecl hashnext(Hash *t,int i); /* 0x1000c810 */

/* ===== ltm.c ===== */
void luaT_init(void); /* 0x1000c850 */
void __cdecl init_entry(int param_1); /* 0x1000c8a0 */
void __cdecl luaT_realtag(int param_1); /* 0x1000c920 */
int __cdecl validevent(int param_1,int param_2); /* 0x1000c9c0 */
void __cdecl luaT_checktag(int param_1); /* 0x1000c9f0 */
int __cdecl luaT_efectivetag(TObject *o); /* 0x1000ca20 */
undefined * __cdecl luaT_gettagmethod(int param_1,byte *param_2); /* 0x1000ca60 */
int __cdecl luaI_checkevent(byte *param_1,undefined4 *param_2); /* 0x1000cab0 */
void __cdecl luaT_settagmethod(int param_1,byte *param_2,undefined4 *param_3); /* 0x1000cae0 */
char * __cdecl luaT_travtagmethods(undefined *param_1); /* 0x1000cb80 */
void errorFB(void); /* 0x1000cbf0 */
void nilFB(void); /* 0x1000cc10 */
void typeFB(void); /* 0x1000cc20 */
void luaT_setfallback(void); /* 0x1000cc30 */
void __cdecl fillvalids(int param_1,undefined4 *param_2); /* 0x1000ce50 */

/* ===== lundump.c ===== */
undefined4 __cdecl luaU_undump1(int *param_1); /* 0x1000cea0 */
undefined4 * __cdecl LoadChunk(int *param_1); /* 0x1000cf10 */
undefined4 * __cdecl LoadFunction(int *param_1); /* 0x1000cf30 */
uint __cdecl LoadWord(int *param_1); /* 0x1000cfa0 */
uint __cdecl ezgetc(int *param_1); /* 0x1000cfd0 */
void __cdecl unexpectedEOZ(int param_1); /* 0x1000d010 */
undefined4 * __cdecl lundump__d030(uint param_1,uint *param_2); /* 0x1000d030 */
uint __cdecl ezread(uint *param_1,undefined4 *param_2,uint param_3); /* 0x1000d060 */
uint __cdecl LoadSize(int *param_1); /* 0x1000d090 */
undefined4 __cdecl LoadTString(uint *param_1); /* 0x1000d0d0 */
uint * __cdecl Undump_LoadString(uint *param_1); /* 0x1000d0f0 */
void __cdecl lundump__d130(uint *param_1,uint param_2); /* 0x1000d130 */
void __cdecl LoadLocals(int param_1,uint *param_2); /* 0x1000d1a0 */
void __cdecl LoadConstants(int param_1,undefined4 *param_2); /* 0x1000d230 */
float __cdecl luaU_LoadNumber(undefined4 *param_1); /* 0x1000d2f0 */
int __cdecl lundump__d360(undefined1 *param_1); /* 0x1000d360 */
int __cdecl lundump__d380(undefined1 *param_1); /* 0x1000d380 */
void __cdecl lundump__d3c0(int param_1,int *param_2); /* 0x1000d3c0 */
void __cdecl LoadHeader(undefined4 *param_1); /* 0x1000d420 */
void __cdecl LoadSignature(int *param_1); /* 0x1000d570 */
undefined4 __cdecl luaV_tonumber(int *param_1); /* 0x1000d5c0 */
undefined4 __cdecl luaV_tostring(int *param_1); /* 0x1000d620 */

/* ===== lvm.c ===== */
void __cdecl luaV_closure(uint param_1); /* 0x1000d6d0 */
void luaV_gettable(void); /* 0x1000d740 */
void __cdecl luaV_settable(TObject *t,int mode); /* 0x1000d810 */
void __cdecl luaV_getglobal(TaggedString *ts); /* 0x1000d900 */
void __cdecl luaV_setglobal(TaggedString *ts); /* 0x1000d990 */
void __cdecl luaV_pack(int firstel,int nvararg,TObject *tab); /* 0x1000da30 */
void ExecutionState_CleanUp(void); /* 0x1000db10 */
undefined4 __thiscall ExecutionState_Save(void *this,int a1); /* 0x1000db40 */
undefined4 __thiscall ExecutionState_Restore(void *this,int a1,int a2,int a3); /* 0x1000dbd0 */
void * __cdecl ExecutionState_New(int size); /* 0x1000dd10 */
void __cdecl ExecutionState_Delete(int param_1); /* 0x1000dd90 */
int __thiscall ExecutionState_Construct(void *this,int a1,int a2,int a3); /* 0x1000ddb0 */
undefined4 __fastcall ExecutionState_getaux(int param_1); /* 0x1000dde0 */
int __thiscall ExecutionState_setvalues(void *this,int a1,int a2,int a3); /* 0x1000ddf0 */
void __fastcall ExecutionState_resetcounter(int param_1); /* 0x1000de20 */
int __fastcall ExecutionState_execute(int *param_1); /* 0x1000de30 */
void __cdecl adjust_varargs(int param_1); /* 0x1000dee0 */
int __fastcall ExecutionState_CrunchOpcodes(int *param_1); /* 0x1000df40 */
TaggedString * __cdecl strconc(char *param_1,char *param_2); /* 0x1000ebc0 */
void __cdecl call_binTM(int param_1,byte *param_2); /* 0x1000ec50 */
void __cdecl call_arith(int param_1); /* 0x1000ecf0 */
void __cdecl comparison(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4); /* 0x1000ed10 */

/* ===== lzio.c ===== */
undefined4 * __cdecl luaZ_mopen(undefined4 *param_1,int param_2,undefined4 param_3,undefined4 param_4); /* 0x1000edc0 */
undefined4 zmfilbuf(void); /* 0x1000edf0 */
undefined4 * __cdecl luaZ_sopen(undefined4 *param_1,char *param_2,undefined4 param_3); /* 0x1000ee00 */
undefined4 * __cdecl luaZ_Fopen(undefined4 *param_1,int param_2,undefined4 param_3); /* 0x1000ee30 */
uint __cdecl zffilbuf(int *param_1); /* 0x1000ee60 */
uint __cdecl luaZ_read(uint *param_1,undefined4 *param_2,uint param_3); /* 0x1000eea0 */
void lzio__ef20(void); /* 0x1000ef20 */
void lzio__ef40(void); /* 0x1000ef40 */

/* ===== crt.c ===== */
longlong _ftol(void); /* 0x1000ef80 */
undefined4 __cdecl _setjmp3(undefined4 *param_1,int param_2,int param_3,undefined4 param_4); /* 0x1000efa8 */
void _CallSettingFrame(undefined *UNRECOVERED_JUMPTABLE); /* 0x1000f030 */
undefined4 __stdcall _UnwindNestedFrames(int a1,int a2); /* 0x1000f080 */
void __cdecl __CxxFrameHandler(int *param_1,int param_2,int param_3); /* 0x1000f180 */
void __cdecl _global_unwind2(int param_1); /* 0x1000f390 */
void __cdecl _local_unwind2(int param_1,int param_2); /* 0x1000f3d2 */
undefined4 _unwind_handler(void); /* 0x1000f43a */
undefined4 __stdcall _NLG_Notify(int a1); /* 0x1000f466 */
int __cdecl vsprintf(char *buf,char *fmt,void *args); /* 0x1000f480 */
int __cdecl sprintf(char *buf,char *fmt,...); /* 0x1000f4f0 */
int __cdecl printf(char *fmt,...); /* 0x1000f560 */
void __cdecl strtol(byte *param_1,undefined4 *param_2,uint param_3); /* 0x1000f680 */
uint __cdecl strtoxl(byte *param_1,undefined4 *param_2,uint param_3,uint param_4); /* 0x1000f6a0 */
uint __cdecl strtoul(byte *param_1,undefined4 *param_2,uint param_3); /* 0x1000f930 */
uint * __cdecl strchr(uint *param_1,char param_2); /* 0x1000f960 */
undefined4 * __cdecl memcpy(undefined4 *param_1,undefined4 *param_2,uint param_3); /* 0x1000fa20 */
void longjmp(int param_1); /* 0x1000fd58 */
char * __cdecl strerror(int param_1); /* 0x1000fec0 */
void __cdecl _dosmaperr(undefined *param_1); /* 0x1000ff30 */
int * _errno(void); /* 0x1000ffb0 */
int * __doserrno(void); /* 0x1000ffc0 */
uint __cdecl system(int param_1); /* 0x1000ffd0 */
undefined4 __cdecl remove(int param_1); /* 0x10010090 */
undefined4 __cdecl rename(int param_1,int param_2); /* 0x100100c0 */
char * __cdecl tmpnam(char *param_1); /* 0x10010100 */
int __cdecl getenv(byte *param_1); /* 0x10010310 */
int __cdecl _getenv_lk(byte *param_1); /* 0x10010340 */
void __cdecl strftime(byte *param_1,uint param_2,byte *param_3,int *param_4); /* 0x100103d0 */
int __cdecl _Strftime(byte *param_1,uint param_2,byte *param_3,int *param_4,undefined *param_5); /* 0x100103f0 */
void __cdecl _expandtime(undefined1 param_1,int *param_2,byte *param_3,uint *param_4,int param_5); /* 0x10010540 */
void __cdecl _store_str(char *param_1,int *param_2,int *param_3); /* 0x10010ae0 */
void __cdecl _store_num(int param_1,uint param_2,int *param_3,uint *param_4); /* 0x10010b10 */
void __cdecl _store_number(int param_1,int *param_2,uint *param_3); /* 0x10010bb0 */
void __cdecl _store_winword(byte *param_1,int *param_2,byte *param_3,int *param_4,int param_5); /* 0x10010c20 */
int * __cdecl localtime(int *param_1); /* 0x10010f70 */
void __cdecl time(int *param_1); /* 0x10011160 */
char * __cdecl setlocale(int param_1,uint *param_2); /* 0x10011290 */
undefined4 __cdecl _setlocale_set_cat(int param_1,uint *param_2); /* 0x10011560 */
char * _setlocale_get_all(void); /* 0x100116c0 */
char * __cdecl _expandlocale(uint *param_1,char *param_2,undefined4 *param_3,uint *param_4); /* 0x100117e0 */
undefined4 __cdecl __lc_strtolc(uint *param_1,uint *param_2); /* 0x10011a40 */
void __cdecl __lc_lctostr(char *param_1,char *param_2); /* 0x10011b50 */
uint __cdecl toupper(uint param_1); /* 0x10011bc0 */
uint __cdecl _toupper_lk(uint param_1); /* 0x10011c50 */
float __cdecl _CIasin(void); /* 0x10011d50 */
void __cdecl _asin(int param_1,uint param_2); /* 0x10011d6d */
float __cdecl _CIacos(void); /* 0x10011e20 */
void __cdecl _acos(int param_1,uint param_2); /* 0x10011e3d */
float __cdecl floor(uint param_1,uint param_2); /* 0x10011ef0 */
float __cdecl ceil(uint param_1,uint param_2); /* 0x10011ff0 */
float __cdecl _CIpow(void); /* 0x10012130 */
void FUN_10012152(void); /* 0x10012152 */
undefined4 __cdecl _ftol_10012325(void); /* 0x10012325 */
uint __cdecl bsearch(undefined4 param_1,uint param_2,uint param_3,int param_4,undefined *param_5); /* 0x10012390 */
void __cdecl qsort(undefined1 *param_1,uint param_2,uint param_3,undefined *param_4); /* 0x10012430 */
void __cdecl shortsort(undefined1 *param_1,undefined1 *param_2,int param_3,undefined *param_4); /* 0x100125e0 */
void __cdecl qsort_swap(undefined1 *param_1,undefined1 *param_2,int param_3); /* 0x10012640 */
uint * __cdecl strncpy(uint *param_1,uint *param_2,uint param_3); /* 0x10012670 */
uint __cdecl tolower(uint param_1); /* 0x10012770 */
uint __cdecl _tolower_lk(uint param_1); /* 0x10012800 */
uint __cdecl _isctype(int param_1,uint param_2); /* 0x10012900 */
byte * __cdecl strpbrk(byte *param_1,byte *param_2); /* 0x10012a20 */
uint __cdecl strncmp(char *param_1,char *param_2,int param_3); /* 0x10012a60 */
int __cdecl sscanf(char *str,char *fmt,...); /* 0x10012aa0 */
int __cdecl strcoll(byte *param_1,byte *param_2); /* 0x10012af0 */
undefined4 __stdcall _CRT_INIT(int a1,int a2,int a3); /* 0x10012cb0 */
undefined4 __stdcall entry(int a1,int a2,int a3); /* 0x10012dd0 */
void __cdecl _amsg_exit(int param_1); /* 0x10012e80 */
undefined1 * __cdecl _cftoe(undefined4 *param_1,undefined1 *param_2,int param_3,int param_4); /* 0x100130b0 */
undefined1 * __cdecl _cftoe2(undefined1 *param_1,int param_2,int param_3,int *param_4,char param_5); /* 0x10013130 */
char * __cdecl _cftof(undefined4 *param_1,char *param_2,uint param_3); /* 0x10013230 */
char * __cdecl _cftof2(char *param_1,uint param_2,int *param_3,char param_4); /* 0x100132a0 */
void __cdecl _cftog(undefined4 *param_1,char *param_2,uint param_3,int param_4); /* 0x10013360 */
void __cdecl _shift(char *param_1,int param_2); /* 0x10013490 */
undefined4 __cdecl __InternalCxxFrameHandler (int *param_1,int param_2,int param_3,undefined4 param_4,int *param_5,int param_6, int param_7,char param_8); /* 0x100134c0 */
void __cdecl FindHandler(int *param_1,int param_2,int param_3,undefined4 param_4,int param_5,char param_6, int param_7,int param_8); /* 0x10013590 */
void __cdecl Eh_FindForeignHandler (undefined4 *param_1,int param_2,int param_3,undefined4 param_4,int param_5,int param_6, int param_7,int param_8); /* 0x10013850 */
void __cdecl FrameUnwindToState(int param_1,undefined4 param_2,int param_3,int param_4); /* 0x10013930 */
void __cdecl CatchIt(int param_1,int param_2,int param_3,undefined4 param_4,int param_5,byte *param_6, byte *param_7,int *param_8,int param_9,int param_10); /* 0x10013a10 */
undefined4 __cdecl CallCatchBlock(int param_1,undefined4 param_2,int param_3,undefined4 param_4,undefined4 param_5, int param_6,int param_7); /* 0x10013aa0 */
void Eh_CallCatchBlockInner(void); /* 0x10013b98 */
void __cdecl BuildCatchObject(int param_1,int param_2,byte *param_3,byte *param_4); /* 0x10013c30 */
undefined4 _mtinit(void); /* 0x10013f40 */
void _mtterm(void); /* 0x10013fa0 */
void __cdecl _initptd(int param_1); /* 0x10013fd0 */
int * _getptd(void); /* 0x10013ff0 */
void __cdecl _freeptd(undefined *param_1); /* 0x10014070 */
void terminate(void); /* 0x10014120 */
uint __cdecl _flsbuf(uint param_1,int *param_2); /* 0x10014240 */
int __cdecl _output(int *param_1,char *param_2,undefined4 *param_3); /* 0x10014370 */
void __cdecl write_char(uint param_1,int *param_2,int *param_3); /* 0x10014d00 */
void __cdecl write_multi_char(uint param_1,int param_2,int *param_3,int *param_4); /* 0x10014d50 */
void __cdecl write_string(char *param_1,int param_2,int *param_3,int *param_4); /* 0x10014d90 */
undefined4 __cdecl get_int_arg(int *param_1); /* 0x10014dd0 */
undefined8 __cdecl get_short_arg(int *param_1); /* 0x10014df0 */
undefined4 __cdecl get_int64_arg(undefined4 *param_1); /* 0x10014e10 */
void _mtinitlocks(void); /* 0x10014e30 */
void _mtdeletelocks(void); /* 0x10014e60 */
void __cdecl _lock(int param_1); /* 0x10014ee0 */
void __cdecl _unlock(int param_1); /* 0x10014f60 */
void __cdecl _lock_file2(int param_1,int param_2); /* 0x10014fc0 */
void __cdecl _unlock_file2(int param_1,int param_2); /* 0x10015030 */
undefined4 __cdecl _stbuf(undefined4 *param_1); /* 0x10015060 */
void __cdecl _ftbuf(int param_1,int *param_2); /* 0x10015120 */
void _ioinit(void); /* 0x100151d0 */
void _ioterm(void); /* 0x100153e0 */
int * __cdecl calloc(int param_1,int param_2); /* 0x10015440 */
void _cinit(void); /* 0x10015590 */
void __cdecl exit(undefined4 param_1); /* 0x100155c0 */
void _cexit(void); /* 0x100155e0 */
void __cdecl doexit(int param_1,int param_2,int param_3); /* 0x100155f0 */
void _lockexit(void); /* 0x100156b0 */
void _unlockexit(void); /* 0x100156c0 */
void __cdecl _initterm(undefined4 *param_1,undefined4 *param_2); /* 0x100156d0 */
undefined4 __cdecl _flush(int *param_1); /* 0x10015730 */
int * __cdecl malloc(uint param_1); /* 0x10015870 */
int * __cdecl _nh_malloc(uint param_1,int param_2); /* 0x10015890 */
int * __cdecl _heap_alloc(int param_1); /* 0x100158e0 */
int __cdecl _spawnvpe_search(undefined4 param_1,uint *param_2,undefined4 *param_3,undefined4 *param_4); /* 0x10015940 */
int __cdecl _spawnvpe(undefined4 param_1,uint *param_2,undefined4 *param_3,undefined4 *param_4); /* 0x10015b30 */
int __cdecl _spawnve(undefined4 param_1,char *param_2,undefined4 *param_3,undefined4 *param_4); /* 0x10015d30 */
undefined4 __cdecl _access(uint param_1,byte param_2); /* 0x10015da0 */
char * __cdecl _strdup(char *param_1); /* 0x10015ef0 */
byte * __cdecl _mbschr(byte *param_1,uint param_2); /* 0x10016020 */
int __cdecl _strnicoll(byte *param_1,byte *param_2,int param_3); /* 0x10016130 */
undefined4 __crtsetenv_from_wenviron(void); /* 0x10016170 */
void __tzset(void); /* 0x100161f0 */
void _tzset_lk(void); /* 0x10016230 */
int __cdecl _isindst(int *param_1); /* 0x10016510 */
int __cdecl _isindst_lk(int *param_1); /* 0x10016540 */
void __cdecl _cvtdate(int param_1,int param_2,uint param_3,int param_4,int param_5,int param_6,int param_7, int param_8,int param_9,int param_10,int param_11); /* 0x100167b0 */
uint __cdecl _stricmp(byte *param_1,byte *param_2); /* 0x10016950 */
int * __cdecl gmtime(int *param_1); /* 0x10016a20 */
int __cdecl __loctotime_t(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6,int param_7); /* 0x10016b90 */
void __cdecl free(undefined *param_1); /* 0x10017ba0 */
undefined4 __cdecl __get_qualified_locale(char *param_1,uint param_2,int param_3); /* 0x10017c50 */
short * __cdecl __crtLCMapStringW(int param_1,uint param_2,short *param_3,int param_4,uint *param_5,short *param_6, uint *param_7); /* 0x10018790 */
int __cdecl wcsncnt(short *param_1,int param_2); /* 0x100189a0 */
int __cdecl __crtLCMapStringA(int param_1,uint param_2,char *param_3,int param_4,int param_5,int param_6, uint param_7,int param_8); /* 0x100189e0 */
float __cdecl _frnd(double param_1); /* 0x10018fd0 */
void __cdecl _raise_exc(uint *param_1,uint *param_2,byte param_3,uint param_4,uint *param_5,uint *param_6); /* 0x10019100 */
int __cdecl _handle_exc(uint param_1,double *param_2,uint param_3); /* 0x10019440 */
undefined4 __cdecl _pow_special_cases(double param_1,double param_2,double *param_3); /* 0x1001ad40 */
undefined4 __cdecl _is_integer_double(double param_1); /* 0x1001af70 */
int * __cdecl __crtGetStringTypeW(int param_1,int param_2,int param_3,undefined4 *param_4,int param_5,int param_6); /* 0x1001b000 */
int __cdecl __crtGetStringTypeA(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6, int param_7); /* 0x1001b190 */
int __cdecl _input(int *param_1,byte *param_2,undefined4 *param_3); /* 0x1001b2d0 */
uint __cdecl _hextodec(uint param_1); /* 0x1001c010 */
uint __cdecl _inc(int *param_1); /* 0x1001c050 */
void __cdecl _un_inc(uint param_1,int *param_2); /* 0x1001c080 */
uint __cdecl _whiteout(int *param_1,int *param_2); /* 0x1001c0a0 */
int __cdecl __crtCompareStringA(int param_1,int param_2,byte *param_3,int param_4,byte *param_5,int param_6, int param_7); /* 0x1001c0f0 */
int __cdecl _strncnt(char *param_1,int param_2); /* 0x1001c3c0 */
uint __cdecl wcstol(short *param_1,undefined4 *param_2,uint param_3); /* 0x1001c3f0 */
uint __cdecl wcstoxl(short *param_1,undefined4 *param_2,uint param_3,uint param_4); /* 0x1001c410 */
int __cdecl __crtGetLocaleInfoA(int param_1,int param_2,int param_3,int param_4,int param_5); /* 0x1001c5f0 */
void _setenvp(void); /* 0x1001c860 */
void _setargv(void); /* 0x1001c950 */
undefined4 __cdecl _setmbcp(int param_1); /* 0x1001cc00 */
void __initmbctable(void); /* 0x1001d100 */
char * __crtGetEnvironmentStringsA(void); /* 0x1001d110 */
undefined4 _heap_init(void); /* 0x1001d270 */
void _heap_term(void); /* 0x1001d2b0 */
void _FF_MSGBANNER(void); /* 0x1001d300 */
void __cdecl _NMSG_WRITE(int param_1); /* 0x1001d340 */
undefined4 __cdecl _ld12tocvt(ushort *param_1,uint *param_2,int *param_3); /* 0x1001d940 */
void __cdecl _ld12tod(ushort *param_1,uint *param_2); /* 0x1001db10 */
void __cdecl _ld12tof(ushort *param_1,uint *param_2); /* 0x1001db30 */
void __cdecl _atodbl(uint *param_1,byte *param_2); /* 0x1001db50 */
void __cdecl _atoflt(uint *param_1,byte *param_2); /* 0x1001db90 */
void __cdecl _fptostr(char *param_1,int param_2,int param_3); /* 0x1001dbd0 */
int __cdecl _ValidateRead(int param_1,int param_2); /* 0x1001de60 */
int __cdecl _ValidateWrite(int param_1,int param_2); /* 0x1001de80 */
int __cdecl _ValidateExecute(int param_1); /* 0x1001dea0 */
void abort(void); /* 0x1001dfa0 */
int __cdecl _lseek(uint param_1,undefined4 param_2,undefined4 param_3); /* 0x1001dfc0 */
int __cdecl _lseek_lk(uint param_1,int param_2,int param_3); /* 0x1001e040 */
int __cdecl _write(uint param_1,char *param_2,uint param_3); /* 0x1001e0c0 */
int __cdecl _write_lk(uint param_1,char *param_2,uint param_3); /* 0x1001e140 */
void __cdecl _getbuf(int *param_1); /* 0x1001e350 */
uint __cdecl _isatty(uint param_1); /* 0x1001e3b0 */
int __cdecl wctomb(undefined1 *param_1,ushort param_2); /* 0x1001e3e0 */
int __cdecl _wctomb_lk(undefined1 *param_1,ushort param_2); /* 0x1001e450 */
int __stdcall _aulldiv(int a1,int a2,int a3,int a4); /* 0x1001e4d0 */
int __stdcall _aullrem(int a1,int a2,int a3,int a4); /* 0x1001e540 */
undefined4 __cdecl _callnewh(undefined4 param_1); /* 0x1001e5c0 */
undefined ** __sbh_alloc_new_region(void); /* 0x1001e5e0 */
void __cdecl __sbh_release_region(undefined **param_1); /* 0x1001e750 */
void __cdecl __sbh_decommit_pages(int param_1); /* 0x1001e7b0 */
int __cdecl __sbh_find_block(undefined *param_1,undefined4 *param_2,uint *param_3); /* 0x1001e880 */
void __cdecl __sbh_free_block(int param_1,int param_2,byte *param_3); /* 0x1001e8e0 */
int * __cdecl __sbh_alloc_block(uint param_1); /* 0x1001e940 */
int __cdecl __sbh_alloc_new_group(int *param_1,uint param_2,uint param_3); /* 0x1001eb80 */
undefined4 __cdecl __sbh_resize_block(int param_1,int *param_2,byte *param_3,uint param_4); /* 0x1001ed00 */
uint * __cdecl _mbschr_lk(uint *param_1,uint param_2); /* 0x1001efc0 */
int __cdecl _dospawn(int param_1,int param_2,char *param_3,int param_4); /* 0x1001f090 */
undefined4 __thiscall _cenvarg(void *this,undefined4 *param_1,undefined4 *param_2,int *param_3,int *param_4); /* 0x1001f320 */
int __cdecl _get_osfhandle(uint param_1); /* 0x1001f670 */
void __cdecl _lock_fhandle(uint param_1); /* 0x1001f6c0 */
void __cdecl _unlock_fhandle(uint param_1); /* 0x1001f730 */
int __cdecl _read(uint param_1,char *param_2,int param_3); /* 0x1001f760 */
int __cdecl _read_lk(uint param_1,char *param_2,int param_3); /* 0x1001f7e0 */
char * __cdecl strrchr(char *param_1,char param_2); /* 0x1001fa10 */
undefined4 __cdecl __crtsetenv(uint *param_1,int param_2); /* 0x1001fa40 */
int __cdecl findenv(byte *param_1,int param_2); /* 0x1001fc50 */
undefined4 * __cdecl copy_environ(int *param_1); /* 0x1001fcd0 */
int __cdecl atol(byte *param_1); /* 0x1001fd40 */
uint __cdecl wcstombs(int param_1,ushort *param_2,uint param_3); /* 0x1001fde0 */
uint __cdecl _wcstombs_lk(int param_1,ushort *param_2,uint param_3); /* 0x1001fe60 */
int __cdecl wcsncnt_10020050(short *param_1,int param_2); /* 0x10020050 */
undefined4 __cdecl _strnicmp(byte *param_1,char *param_2,int param_3); /* 0x10020240 */
void __cdecl _except1(uint param_1,int *param_2,ushort *param_3); /* 0x10020350 */
uint __cdecl mbtowc(ushort *param_1,byte *param_2,uint param_3); /* 0x10020510 */
uint __cdecl _mbtowc_lk(ushort *param_1,byte *param_2,uint param_3); /* 0x10020590 */
int __stdcall _allmul(int a1,int a2,int a3,int a4); /* 0x10020690 */
uint __cdecl _filbuf(int *param_1); /* 0x100206f0 */
uint __cdecl _ungetc_lk(uint param_1,int *param_2); /* 0x100207e0 */
uint __cdecl towupper(uint param_1); /* 0x10020870 */
uint __cdecl _towupper_lk(uint param_1); /* 0x10020900 */
uint __cdecl iswctype(uint param_1,uint param_2); /* 0x10020980 */
int __cdecl wcslen(short *param_1); /* 0x100209f0 */
undefined4 __cdecl __crtMessageBoxA(undefined4 param_1,undefined4 param_2,undefined4 param_3); /* 0x10020a10 */
undefined4 __cdecl raise(int *param_1); /* 0x10020aa0 */
uint __cdecl siglookup(int param_1,uint param_2); /* 0x10020cb0 */
undefined4 __cdecl __addl(uint param_1,uint param_2,uint *param_3); /* 0x10020cf0 */
void __cdecl __add_12(uint *param_1,uint *param_2); /* 0x10020d20 */
void __cdecl __shl_12(uint *param_1); /* 0x10020d90 */
void __cdecl __shr_12(uint *param_1); /* 0x10020dc0 */
void __cdecl __mtold12(char *param_1,int param_2,uint *param_3); /* 0x10020df0 */
undefined4 __cdecl __strgtold12(ushort *param_1,int *param_2,byte *param_3,int param_4,int param_5,int param_6, int param_7); /* 0x10020ef0 */
undefined4 __cdecl _I10_OUTPUT(uint param_1,uint param_2,uint param_3,int param_4,byte param_5,short *param_6); /* 0x10021680 */
int * __cdecl realloc(int *param_1,uint param_2); /* 0x10021a80 */
void __cdecl __ld12mul(int *param_1,int *param_2); /* 0x10021c30 */
void __cdecl __multtenpow12(int *param_1,uint param_2,int param_3); /* 0x10021ef0 */

/* ===== crt_unnamed.c ===== */
void FUN_1000f070(undefined4 param_1,undefined *UNRECOVERED_JUMPTABLE); /* 0x1000f070 */
undefined4 __cdecl FUN_1000f0e0(int *param_1,int param_2,int param_3,undefined4 param_4); /* 0x1000f0e0 */
undefined4 __cdecl FUN_1000f120(int param_1,undefined4 param_2,int param_3,int param_4,int param_5); /* 0x1000f120 */
undefined4 __cdecl FUN_1000f1b0(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4, undefined4 param_5,undefined4 param_6,undefined4 param_7); /* 0x1000f1b0 */
undefined4 __cdecl FUN_1000f280(int *param_1,int param_2,int param_3); /* 0x1000f280 */
int __cdecl FUN_1000f310(int param_1,int param_2,int param_3,uint *param_4,uint *param_5); /* 0x1000f310 */
void __fastcall FUN_1000f45d(undefined4 param_1); /* 0x1000f45d */
uint __cdecl FUN_1000f5c0(int param_1); /* 0x1000f5c0 */
uint __cdecl FUN_1000f5f0(int param_1); /* 0x1000f5f0 */
uint __cdecl FUN_1000f620(int param_1); /* 0x1000f620 */
uint __cdecl FUN_1000f650(int param_1); /* 0x1000f650 */
void FUN_1000fde0(void); /* 0x1000fde0 */
int __stdcall FUN_1000fea0(int a1,int a2,int a3); /* 0x1000fea0 */
undefined4 FUN_100119e0(void); /* 0x100119e0 */
void __cdecl FUN_100119f0(char *param_1,int param_2); /* 0x100119f0 */
float __fastcall FUN_100120fa(undefined4 param_1); /* 0x100120fa */
float10 FUN_10012104(void); /* 0x10012104 */
void __cdecl FUN_10012350(int param_1); /* 0x10012350 */
uint FUN_10012360(void); /* 0x10012360 */
uint * __cdecl FUN_100129a0(uint *param_1,char *param_2); /* 0x100129a0 */
void FUN_10012ec0(void); /* 0x10012ec0 */
undefined4 FUN_10012ee0(void); /* 0x10012ee0 */
undefined4 FUN_10012f30(void); /* 0x10012f30 */
void __cdecl FUN_10012f60(char *param_1); /* 0x10012f60 */
void __cdecl FUN_10012fc0(char *param_1); /* 0x10012fc0 */
undefined4 __cdecl FUN_10013030(double *param_1); /* 0x10013030 */
void __cdecl FUN_10013050(int param_1,uint *param_2,byte *param_3); /* 0x10013050 */
void __cdecl FUN_10013420(undefined4 *param_1,char *param_2,int param_3,uint param_4,int param_5); /* 0x10013420 */
void FUN_100139a6(void); /* 0x100139a6 */
void FUN_100139b3(void); /* 0x100139b3 */
undefined4 FUN_100139f0(undefined4 *param_1); /* 0x100139f0 */
void FUN_10013b57(void); /* 0x10013b57 */
undefined4 FUN_10013b64(void); /* 0x10013b64 */
void FUN_10013b8f(void); /* 0x10013b8f */
undefined4 FUN_10013c00(int *param_1); /* 0x10013c00 */
undefined4 FUN_10013e0b(void); /* 0x10013e0b */
void FUN_10013e11(void); /* 0x10013e11 */
void __cdecl FUN_10013e40(int param_1); /* 0x10013e40 */
int FUN_10013e8a(void); /* 0x10013e8a */
void FUN_10013e95(void); /* 0x10013e95 */
int __cdecl FUN_10013ec0(int param_1,int *param_2); /* 0x10013ec0 */
undefined4 __stdcall FUN_10013ef0(int a1,int a2,int a3); /* 0x10013ef0 */
undefined4 FUN_1001416a(void); /* 0x1001416a */
void FUN_10014170(void); /* 0x10014170 */
void FUN_10014197(void); /* 0x10014197 */
void FUN_100141b0(void); /* 0x100141b0 */
undefined4 FUN_100141f1(void); /* 0x100141f1 */
void FUN_100141f7(void); /* 0x100141f7 */
void FUN_1001421e(void); /* 0x1001421e */
void FUN_10014f80(uint param_1); /* 0x10014f80 */
void FUN_10014ff0(uint param_1); /* 0x10014ff0 */
undefined4 FUN_10015160(int a1); /* 0x10015160 */
int FUN_1001519c(void); /* 0x1001519c */
undefined4 __stdcall FUN_100151b0(int a1); /* 0x100151b0 */
int FUN_100156f0(int *param_1); /* 0x100156f0 */
void FUN_100157a0(void); /* 0x100157a0 */
int FUN_100157b0(int param_1); /* 0x100157b0 */
undefined4 FUN_10015df0(uint param_1); /* 0x10015df0 */
undefined4 FUN_10015e60(uint param_1); /* 0x10015e60 */
char * __cdecl FUN_10015f40(uint param_1,char *param_2,uint param_3); /* 0x10015f40 */
void __cdecl FUN_10015f80(uint param_1,char *param_2,uint param_3,int param_4); /* 0x10015f80 */
char * __cdecl FUN_10015ff0(uint param_1,char *param_2,uint param_3); /* 0x10015ff0 */
int FUN_100160b0(void); /* 0x100160b0 */
undefined4 FUN_10016c80(void); /* 0x10016c80 */
uint FUN_10016d30(char *param_1); /* 0x10016d30 */
void FUN_100170b0(undefined4 *param_1); /* 0x100170b0 */
uint FUN_100172f0(char *param_1,int param_2); /* 0x100172f0 */
undefined4 FUN_100173f0(void); /* 0x100173f0 */
undefined4 FUN_100175f0(void); /* 0x100175f0 */
uint __cdecl FUN_100176e0(int param_1); /* 0x100176e0 */
void __cdecl FUN_10017830(char *param_1); /* 0x10017830 */
void __cdecl FUN_10017870(int param_1); /* 0x10017870 */
undefined4 FUN_100178e0(void); /* 0x100178e0 */
int __cdecl FUN_10017c10(byte *param_1,byte *param_2); /* 0x10017c10 */
void __cdecl FUN_10017df0(int param_1,int param_2,int *param_3); /* 0x10017df0 */
void __fastcall FUN_10018c77(undefined4 param_1,int param_2); /* 0x10018c77 */
float10 FUN_10018d14(void); /* 0x10018d14 */
float10 FUN_10018d4d(void); /* 0x10018d4d */
float10 FUN_10018d4f(void); /* 0x10018d4f */
float10 FUN_10018d77(void); /* 0x10018d77 */
unkbyte10 FUN_10018db6(void); /* 0x10018db6 */
float10 __fastcall FUN_10018de0(undefined4 param_1,uint param_2,undefined2 param_3,undefined4 param_4, undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8); /* 0x10018de0 */
float10 __fastcall FUN_10018df7(undefined4 param_1,uint param_2,ushort param_3,undefined4 param_4,undefined4 param_5, undefined4 param_6); /* 0x10018df7 */
undefined1 *FUN_10018e40(void); /* 0x10018e40 */
undefined4 FUN_10018e55(void); /* 0x10018e55 */
undefined4 FUN_10018e6c(void); /* 0x10018e6c */
uint __fastcall FUN_10018e85(undefined4 param_1,int param_2); /* 0x10018e85 */
uint __cdecl FUN_10018ec8(undefined4 param_1,uint param_2); /* 0x10018ec8 */
void FUN_10018ede(void); /* 0x10018ede */
void __fastcall FUN_10018eeb(undefined4 param_1,uint param_2,undefined4 param_3,undefined4 param_4, undefined4 param_5); /* 0x10018eeb */
void __fastcall FUN_10018f29(undefined4 param_1,uint param_2,undefined4 param_3,undefined4 param_4, undefined4 param_5,undefined4 param_6,undefined4 param_7); /* 0x10018f29 */
float10 __cdecl FUN_10018ff0(int param_1,int param_2,uint param_3); /* 0x10018ff0 */
float10 __cdecl FUN_10019040(uint param_1,uint param_2,uint param_3,uint param_4,uint param_5,uint param_6, uint param_7); /* 0x10019040 */
float10 * __cdecl FUN_10019770(float10 *__return_storage_ptr__,int param_1,int param_2,uint param_3,uint param_4, uint param_5,uint param_6,uint param_7,uint param_8); /* 0x10019770 */
void __cdecl FUN_10019820(int param_1); /* 0x10019820 */
undefined4 __cdecl FUN_10019850(int param_1); /* 0x10019850 */
int __cdecl FUN_10019880(uint param_1); /* 0x10019880 */
float __cdecl FUN_100198c0(undefined4 param_1,undefined4 param_2,short param_3); /* 0x100198c0 */
undefined4 __cdecl FUN_10019900(int param_1,uint param_2); /* 0x10019900 */
float __cdecl FUN_10019960(uint param_1,uint param_2,int *param_3); /* 0x10019960 */
int FUN_10019a70(void); /* 0x10019a70 */
int FUN_10019a80(void); /* 0x10019a80 */
int FUN_10019aa0(void); /* 0x10019aa0 */
void FUN_10019ad0(void); /* 0x10019ad0 */
void __fastcall FUN_10019b30(undefined4 param_1,int param_2); /* 0x10019b30 */
void FUN_10019bfa(void); /* 0x10019bfa */
undefined4 __cdecl FUN_1001a5a6(undefined4 param_1,uint param_2,ushort param_3,uint param_4,uint param_5,uint param_6, uint param_7,uint param_8,ushort param_9); /* 0x1001a5a6 */
float10 FUN_1001a7ac(void); /* 0x1001a7ac */
int __cdecl FUN_1001c720(int param_1,int param_2,int param_3,int param_4,int param_5); /* 0x1001c720 */
undefined4 __cdecl FUN_1001ce80(undefined4 param_1); /* 0x1001ce80 */
undefined4 __stdcall FUN_1001d2f0(int a1,int a2,int a3); /* 0x1001d2f0 */
uint __thiscall FUN_1001d520(void *this,uint param_1,uint param_2); /* 0x1001d520 */
void __cdecl FUN_1001d560(void *param_1,uint param_2); /* 0x1001d560 */
uint __cdecl FUN_1001d580(uint param_1); /* 0x1001d580 */
void FUN_1001d620(void); /* 0x1001d620 */
undefined4 __cdecl FUN_1001d6b0(int param_1,int param_2); /* 0x1001d6b0 */
int __cdecl FUN_1001d720(int param_1,int param_2); /* 0x1001d720 */
undefined4 __cdecl FUN_1001d790(int param_1,int param_2); /* 0x1001d790 */
void __cdecl FUN_1001d830(int param_1,undefined4 *param_2); /* 0x1001d830 */
void __cdecl FUN_1001d850(undefined4 *param_1); /* 0x1001d850 */
undefined4 __cdecl FUN_1001d860(int *param_1); /* 0x1001d860 */
void __cdecl FUN_1001d880(uint *param_1,int param_2); /* 0x1001d880 */
int * __cdecl FUN_1001dc70(undefined4 param_1,undefined4 param_2,int *param_3,char *param_4); /* 0x1001dc70 */
void __cdecl FUN_1001dd00(uint *param_1,uint *param_2); /* 0x1001dd00 */
void FUN_1001ddc0(void); /* 0x1001ddc0 */
undefined4 __stdcall FUN_1001ddd0(int a1); /* 0x1001ddd0 */
void FUN_1001de30(void); /* 0x1001de30 */
void FUN_1001de50(void); /* 0x1001de50 */
undefined4 FUN_1001edd0(int param_1); /* 0x1001edd0 */
undefined4 FUN_1001ee10(int *param_1); /* 0x1001ee10 */
undefined4 FUN_1001ee80(uint param_1); /* 0x1001ee80 */
uint __cdecl FUN_1001ef20(char *param_1,char *param_2,int param_3); /* 0x1001ef20 */
undefined4 FUN_1001f5d0(uint param_1); /* 0x1001f5d0 */
undefined4 __cdecl FUN_10020090(int param_1,int param_2,int param_3,char *param_4); /* 0x10020090 */
int __cdecl FUN_10020470(int param_1,uint param_2); /* 0x10020470 */
int __fastcall FUN_100206d0(byte param_1,int param_2); /* 0x100206d0 */
void FUN_10021a10(undefined4 *param_1); /* 0x10021a10 */
void FUN_10021f90(void); /* 0x10021f90 */
void FUN_10021f9b(void); /* 0x10021f9b */
void __cdecl FUN_10021fa6(int *param_1,int param_2,int param_3,undefined4 param_4); /* 0x10021fa6 */
void FUN_10021fb0(void); /* 0x10021fb0 */
undefined4 FUN_10021fbb(int *param_1,int param_2,int param_3,undefined4 param_4); /* 0x10021fbb */
void FUN_10021fd0(void); /* 0x10021fd0 */
void FUN_10021fdb(void); /* 0x10021fdb */
void __cdecl FUN_10021fe6(int *param_1,int param_2,int param_3,undefined4 param_4); /* 0x10021fe6 */
void FUN_10021ff0(void); /* 0x10021ff0 */
void __cdecl FUN_10021ffb(int *param_1,int param_2,int param_3,undefined4 param_4); /* 0x10021ffb */
void FUN_10022010(void); /* 0x10022010 */
undefined4 FUN_1002201b(int *param_1,int param_2,int param_3,undefined4 param_4); /* 0x1002201b */
void FUN_10022030(void); /* 0x10022030 */
void __cdecl FUN_1002203b(int *param_1,int param_2,int param_3,undefined4 param_4); /* 0x1002203b */
void FUN_10022050(void); /* 0x10022050 */
void __cdecl FUN_1002205b(int *param_1,int param_2,int param_3,undefined4 param_4); /* 0x1002205b */

/* ===== tmpnam.c ===== */
void __cdecl tmpnam_genfname(int param_1); /* 0x10010220 */
undefined4 __cdecl FUN_100102a0(byte *param_1); /* 0x100102a0 */

/* ===== getlcidfromlangcountry.c ===== */
void GetLcidFromLangCountry(void); /* 0x10017e50 */
undefined4 __stdcall FUN_10017ee0(int a1); /* 0x10017ee0 */

/* ===== getlcidfromlanguage.c ===== */
void GetLcidFromLanguage(void); /* 0x100181c0 */
undefined4 __stdcall FUN_10018220(int a1); /* 0x10018220 */

/* ===== getlcidfromcountryonly.c ===== */
void GetLcidFromCountryOnly(void); /* 0x10018300 */
undefined4 __stdcall FUN_10018340(int a1); /* 0x10018340 */

/* ===== getlcidfromdefault.c ===== */
void GetLcidFromDefault(void); /* 0x100183e0 */

/* ===== translatename.c ===== */
undefined4 __cdecl TranslateName(byte *param_1); /* 0x10018400 */
undefined4 __cdecl FUN_100184f0(short param_1); /* 0x100184f0 */
undefined4 __cdecl FUN_10018520(int param_1); /* 0x10018520 */
undefined4 FUN_100185b0(void); /* 0x100185b0 */
int __stdcall FUN_100185f0(int a1,int a2,int a3,int a4); /* 0x100185f0 */
int __cdecl FUN_10018720(char *param_1); /* 0x10018720 */
int __cdecl FUN_10018760(char *param_1); /* 0x10018760 */

/* ===== parse.c ===== */
void __cdecl parse_cmdline(byte *param_1,undefined4 *param_2,byte *param_3,int *param_4,int *param_5); /* 0x1001c9f0 */

/* ===== getsystemcp.c ===== */
int __cdecl getSystemCP(int param_1); /* 0x1001ce30 */

/* ===== setsbcs.c ===== */
void setSBCS(void); /* 0x1001cee0 */

/* ===== setsbuplow.c ===== */
void setSBUpLow(void); /* 0x1001cf20 */

/* ===== referenced, not decompiled here (thunks, imports, unknown FUN_) ===== */
int STDCALL CloseHandle() __asm__("_CloseHandle@4"); /* import */
int STDCALL CompareStringA() __asm__("_CompareStringA@24"); /* import */
int STDCALL CompareStringW() __asm__("_CompareStringW@24"); /* import */
int STDCALL CreateProcessA() __asm__("_CreateProcessA@40"); /* import */
int STDCALL DeleteCriticalSection() __asm__("_DeleteCriticalSection@4"); /* import */
int STDCALL DeleteFileA() __asm__("_DeleteFileA@4"); /* import */
int STDCALL EnterCriticalSection() __asm__("_EnterCriticalSection@4"); /* import */
int STDCALL EnumSystemLocalesA() __asm__("_EnumSystemLocalesA@8"); /* import */
int STDCALL ExitProcess() __asm__("_ExitProcess@4"); /* import */
int STDCALL FlushFileBuffers() __asm__("_FlushFileBuffers@4"); /* import */
int STDCALL FreeEnvironmentStringsA() __asm__("_FreeEnvironmentStringsA@4"); /* import */
int STDCALL FreeEnvironmentStringsW() __asm__("_FreeEnvironmentStringsW@4"); /* import */
int STDCALL GetACP() __asm__("_GetACP@0"); /* import */
int STDCALL GetCPInfo() __asm__("_GetCPInfo@8"); /* import */
int STDCALL GetCommandLineA() __asm__("_GetCommandLineA@0"); /* import */
int STDCALL GetCurrentProcess() __asm__("_GetCurrentProcess@0"); /* import */
int STDCALL GetCurrentProcessId() __asm__("_GetCurrentProcessId@0"); /* import */
int STDCALL GetCurrentThreadId() __asm__("_GetCurrentThreadId@0"); /* import */
int STDCALL GetEnvironmentStrings() __asm__("_GetEnvironmentStrings@0"); /* import */
int STDCALL GetEnvironmentStringsW() __asm__("_GetEnvironmentStringsW@0"); /* import */
int STDCALL GetExitCodeProcess() __asm__("_GetExitCodeProcess@8"); /* import */
int STDCALL GetFileAttributesA() __asm__("_GetFileAttributesA@4"); /* import */
int STDCALL GetFileType() __asm__("_GetFileType@4"); /* import */
int STDCALL GetLastError() __asm__("_GetLastError@0"); /* import */
int STDCALL GetLocalTime() __asm__("_GetLocalTime@4"); /* import */
int STDCALL GetLocaleInfoA() __asm__("_GetLocaleInfoA@16"); /* import */
int STDCALL GetLocaleInfoW() __asm__("_GetLocaleInfoW@16"); /* import */
int STDCALL GetModuleFileNameA() __asm__("_GetModuleFileNameA@12"); /* import */
int STDCALL GetModuleHandleA() __asm__("_GetModuleHandleA@4"); /* import */
int STDCALL GetOEMCP() __asm__("_GetOEMCP@0"); /* import */
int STDCALL GetProcAddress() __asm__("_GetProcAddress@8"); /* import */
int STDCALL GetStartupInfoA() __asm__("_GetStartupInfoA@4"); /* import */
int STDCALL GetStdHandle() __asm__("_GetStdHandle@4"); /* import */
int STDCALL GetStringTypeA() __asm__("_GetStringTypeA@20"); /* import */
int STDCALL GetStringTypeW() __asm__("_GetStringTypeW@16"); /* import */
int STDCALL GetSystemTime() __asm__("_GetSystemTime@4"); /* import */
int STDCALL GetTimeZoneInformation() __asm__("_GetTimeZoneInformation@4"); /* import */
int STDCALL GetUserDefaultLCID() __asm__("_GetUserDefaultLCID@0"); /* import */
int STDCALL GetVersion() __asm__("_GetVersion@0"); /* import */
int STDCALL GetVersionExA() __asm__("_GetVersionExA@4"); /* import */
int STDCALL HeapAlloc() __asm__("_HeapAlloc@12"); /* import */
int STDCALL HeapCreate() __asm__("_HeapCreate@12"); /* import */
int STDCALL HeapDestroy() __asm__("_HeapDestroy@4"); /* import */
int STDCALL HeapFree() __asm__("_HeapFree@12"); /* import */
int STDCALL HeapReAlloc() __asm__("_HeapReAlloc@16"); /* import */
int STDCALL InitializeCriticalSection() __asm__("_InitializeCriticalSection@4"); /* import */
int STDCALL InterlockedDecrement() __asm__("_InterlockedDecrement@4"); /* import */
int STDCALL InterlockedIncrement() __asm__("_InterlockedIncrement@4"); /* import */
int STDCALL IsBadCodePtr() __asm__("_IsBadCodePtr@4"); /* import */
int STDCALL IsBadReadPtr() __asm__("_IsBadReadPtr@8"); /* import */
int STDCALL IsBadWritePtr() __asm__("_IsBadWritePtr@8"); /* import */
int STDCALL IsValidCodePage() __asm__("_IsValidCodePage@4"); /* import */
int STDCALL IsValidLocale() __asm__("_IsValidLocale@8"); /* import */
int STDCALL LCMapStringA() __asm__("_LCMapStringA@24"); /* import */
int STDCALL LCMapStringW() __asm__("_LCMapStringW@24"); /* import */
int STDCALL LeaveCriticalSection() __asm__("_LeaveCriticalSection@4"); /* import */
int STDCALL LoadLibraryA() __asm__("_LoadLibraryA@4"); /* import */
int STDCALL MoveFileA() __asm__("_MoveFileA@8"); /* import */
int STDCALL MultiByteToWideChar() __asm__("_MultiByteToWideChar@24"); /* import */
int STDCALL RaiseException() __asm__("_RaiseException@16"); /* import */
int STDCALL ReadFile() __asm__("_ReadFile@20"); /* import */
int STDCALL RtlUnwind() __asm__("_RtlUnwind@16"); /* import */
int STDCALL SetEnvironmentVariableA() __asm__("_SetEnvironmentVariableA@8"); /* import */
int STDCALL SetFilePointer() __asm__("_SetFilePointer@16"); /* import */
int STDCALL SetHandleCount() __asm__("_SetHandleCount@4"); /* import */
int STDCALL SetLastError() __asm__("_SetLastError@4"); /* import */
int STDCALL SetStdHandle() __asm__("_SetStdHandle@8"); /* import */
int STDCALL SetUnhandledExceptionFilter() __asm__("_SetUnhandledExceptionFilter@4"); /* import */
int STDCALL Sleep() __asm__("_Sleep@4"); /* import */
int STDCALL TerminateProcess() __asm__("_TerminateProcess@8"); /* import */
int STDCALL TlsAlloc() __asm__("_TlsAlloc@0"); /* import */
int STDCALL TlsFree() __asm__("_TlsFree@4"); /* import */
int STDCALL TlsGetValue() __asm__("_TlsGetValue@4"); /* import */
int STDCALL TlsSetValue() __asm__("_TlsSetValue@8"); /* import */
int STDCALL VirtualAlloc() __asm__("_VirtualAlloc@16"); /* import */
int STDCALL VirtualFree() __asm__("_VirtualFree@12"); /* import */
int STDCALL WaitForSingleObject() __asm__("_WaitForSingleObject@8"); /* import */
int STDCALL WideCharToMultiByte() __asm__("_WideCharToMultiByte@32"); /* import */
int STDCALL WriteFile() __asm__("_WriteFile@20"); /* import */
extern int (STDCALL *GetLocaleInfoA_exref)(); /* import address table slot */
