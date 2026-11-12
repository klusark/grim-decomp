/* LUA.DLL :: crt.c
 * functions 0x1000ef80 .. 0x10021ef0 (235 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x1000ef80  _ftol ---- */
/* not in the source: names/lib_replace.json (host): the system C runtime (msvcrt.dll) has it */


/* ---- 0x1000efa8  _setjmp3 ---- */
/* not in the source: names/lib_replace.json (host): the system C runtime (msvcrt.dll) has it */


/* ---- 0x1000f030  _CallSettingFrame ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1000f080  _UnwindNestedFrames ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1000f180  __CxxFrameHandler ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1000f390  _global_unwind2 ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1000f3d2  _local_unwind2 ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1000f43a  _unwind_handler ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1000f466  _NLG_Notify ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x1000f480  vsprintf ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1000f4f0  sprintf ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1000f560  printf ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1000f680  strtol ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1000f6a0  strtoxl ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1000f930  strtoul ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1000f960  strchr ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1000fa20  memcpy ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1000fd58  longjmp ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1000fec0  strerror ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1000ff30  _dosmaperr ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1000ffb0  _errno ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1000ffc0  __doserrno ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1000ffd0  system ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10010090  remove ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x100100c0  rename ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10010100  tmpnam ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10010310  getenv ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10010340  _getenv_lk ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x100103d0  strftime ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x100103f0  _Strftime ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10010540  _expandtime ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10010ae0  _store_str ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10010b10  _store_num ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10010bb0  _store_number ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10010c20  _store_winword ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10010f70  localtime ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10011160  time ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10011290  setlocale ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10011560  _setlocale_set_cat ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x100116c0  _setlocale_get_all ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x100117e0  _expandlocale ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10011a40  __lc_strtolc ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10011b50  __lc_lctostr ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10011bc0  toupper ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10011c50  _toupper_lk ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10011d50  _CIasin ---- */
/* not in the source: names/lib_replace.json (host): the system C runtime (msvcrt.dll) has it */


/* ---- 0x10011d6d  _asin ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10011e20  _CIacos ---- */
/* not in the source: names/lib_replace.json (host): the system C runtime (msvcrt.dll) has it */


/* ---- 0x10011e3d  _acos ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10011ef0  floor ---- */
/* not in the source: names/lib_replace.json (host): the system C runtime (msvcrt.dll) has it */


/* ---- 0x10011ff0  ceil ---- */
/* not in the source: names/lib_replace.json (host): the system C runtime (msvcrt.dll) has it */


/* ---- 0x10012130  _CIpow ---- */
/* replaced by the hand-written version in build/overrides*.c; the original C runtime code is not kept */


/* ---- 0x10012152  _pow ---- */
/* replaced by the hand-written version in build/overrides*.c; the original C runtime code is not kept */


/* ---- 0x10012325  _ftol  (renamed _ftol_10012325: duplicate name) ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10012390  bsearch ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10012430  qsort ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x100125e0  shortsort ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10012640  qsort_swap ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10012670  strncpy ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10012770  tolower ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10012800  _tolower_lk ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10012900  _isctype ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10012a20  strpbrk ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10012a60  strncmp ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10012aa0  sscanf ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10012af0  strcoll ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10012cb0  _CRT_INIT ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10012dd0  entry ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10012e80  _amsg_exit ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x100130b0  _cftoe ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10013130  _cftoe2 ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10013230  _cftof ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x100132a0  _cftof2 ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10013360  _cftog ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10013490  _shift ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x100134c0  __InternalCxxFrameHandler ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10013590  FindHandler ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10013850  Eh_FindForeignHandler ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10013930  FrameUnwindToState ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10013a10  CatchIt ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10013aa0  CallCatchBlock ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10013b98  Eh_CallCatchBlockInner ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10013c30  BuildCatchObject ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10013f40  _mtinit ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10013fa0  _mtterm ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10013fd0  _initptd ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10013ff0  _getptd ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10014070  _freeptd ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10014120  terminate ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10014240  _flsbuf ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10014370  _output ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10014d00  write_char ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10014d50  write_multi_char ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10014d90  write_string ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10014dd0  get_int_arg ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10014df0  get_short_arg ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10014e10  get_int64_arg ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10014e30  _mtinitlocks ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10014e60  _mtdeletelocks ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10014ee0  _lock ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10014f60  _unlock ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10014fc0  _lock_file2 ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10015030  _unlock_file2 ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10015060  _stbuf ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10015120  _ftbuf ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x100151d0  _ioinit ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x100153e0  _ioterm ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10015440  calloc ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10015590  _cinit ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x100155c0  exit ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x100155e0  _cexit ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x100155f0  doexit ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x100156b0  _lockexit ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x100156c0  _unlockexit ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x100156d0  _initterm ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10015730  _flush ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10015870  malloc ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10015890  _nh_malloc ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x100158e0  _heap_alloc ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10015940  _spawnvpe_search ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10015b30  _spawnvpe ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10015d30  _spawnve ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10015da0  _access ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10015ef0  _strdup ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10016020  _mbschr ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10016130  _strnicoll ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10016170  __crtsetenv_from_wenviron ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x100161f0  __tzset ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10016230  _tzset_lk ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10016510  _isindst ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10016540  _isindst_lk ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x100167b0  _cvtdate ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10016950  _stricmp ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10016a20  gmtime ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10016b90  __loctotime_t ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10017ba0  free ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10017c50  __get_qualified_locale ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10018790  __crtLCMapStringW ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x100189a0  wcsncnt ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x100189e0  __crtLCMapStringA ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10018fd0  _frnd ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10019100  _raise_exc ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10019440  _handle_exc ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x1001ad40  _pow_special_cases ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1001af70  _is_integer_double ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1001b000  __crtGetStringTypeW ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1001b190  __crtGetStringTypeA ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1001b2d0  _input ---- */
/* replaced by the hand-written version in build/overrides*.c; the original C runtime code is not kept */


/* ---- 0x1001c010  _hextodec ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1001c050  _inc ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1001c080  _un_inc ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1001c0a0  _whiteout ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1001c0f0  __crtCompareStringA ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1001c3c0  _strncnt ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1001c3f0  wcstol ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1001c410  wcstoxl ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x1001c5f0  __crtGetLocaleInfoA ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1001c860  _setenvp ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1001c950  _setargv ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1001cc00  _setmbcp ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1001d100  __initmbctable ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1001d110  __crtGetEnvironmentStringsA ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1001d270  _heap_init ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1001d2b0  _heap_term ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1001d300  _FF_MSGBANNER ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1001d340  _NMSG_WRITE ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1001d940  _ld12tocvt ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1001db10  _ld12tod ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1001db30  _ld12tof ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1001db50  _atodbl ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1001db90  _atoflt ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1001dbd0  _fptostr ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1001de60  _ValidateRead ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1001de80  _ValidateWrite ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1001dea0  _ValidateExecute ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1001dfa0  abort ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1001dfc0  _lseek ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1001e040  _lseek_lk ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1001e0c0  _write ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1001e140  _write_lk ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1001e350  _getbuf ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1001e3b0  _isatty ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1001e3e0  wctomb ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1001e450  _wctomb_lk ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1001e4d0  _aulldiv ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x1001e540  _aullrem ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x1001e5c0  _callnewh ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1001e5e0  __sbh_alloc_new_region ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1001e750  __sbh_release_region ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1001e7b0  __sbh_decommit_pages ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1001e880  __sbh_find_block ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1001e8e0  __sbh_free_block ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1001e940  __sbh_alloc_block ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1001eb80  __sbh_alloc_new_group ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1001ed00  __sbh_resize_block ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1001efc0  _mbschr_lk ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1001f090  _dospawn ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1001f320  _cenvarg ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1001f670  _get_osfhandle ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1001f6c0  _lock_fhandle ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1001f730  _unlock_fhandle ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1001f760  _read ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1001f7e0  _read_lk ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1001fa10  strrchr ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1001fa40  __crtsetenv ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1001fc50  findenv ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1001fcd0  copy_environ ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1001fd40  atol ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1001fde0  wcstombs ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x1001fe60  _wcstombs_lk ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10020050  wcsncnt  (renamed wcsncnt_10020050: duplicate name) ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10020240  _strnicmp ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10020350  _except1 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10020510  mbtowc ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10020590  _mbtowc_lk ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10020690  _allmul ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x100206f0  _filbuf ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x100207e0  _ungetc_lk ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10020870  towupper ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10020900  _towupper_lk ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10020980  iswctype ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x100209f0  wcslen ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10020a10  __crtMessageBoxA ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10020aa0  raise ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10020cb0  siglookup ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10020cf0  __addl ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10020d20  __add_12 ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10020d90  __shl_12 ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10020dc0  __shr_12 ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10020df0  __mtold12 ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10020ef0  __strgtold12 ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10021680  _I10_OUTPUT ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10021a80  realloc ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10021c30  __ld12mul ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */


/* ---- 0x10021ef0  __multtenpow12 ---- */
/* not in the source: Microsoft's C runtime (module crt, which build/link.py does not link; the system msvcrt.dll has it) */

