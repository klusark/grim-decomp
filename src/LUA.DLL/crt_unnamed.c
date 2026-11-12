/* LUA.DLL :: crt_unnamed.c
 * functions 0x1000f070 .. 0x1002205b (153 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x1000f070  FUN_1000f070 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x1000f0e0  FUN_1000f0e0 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x1000f120  FUN_1000f120 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x1000f1b0  FUN_1000f1b0 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x1000f280  FUN_1000f280 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x1000f310  FUN_1000f310 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x1000f45d  FUN_1000f45d ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x1000f5c0  FUN_1000f5c0 ---- */
uint __cdecl FUN_1000f5c0(int param_1)

{
  uint uVar1;
  
  if (1 < DAT_10028b5c) {
    uVar1 = _isctype(param_1,0x103);
    return uVar1;
  }
  return *(ushort *)(PTR_DAT_10028950 + param_1 * 2) & 0x103;
}

/* ---- 0x1000f5f0  FUN_1000f5f0 ---- */
uint __cdecl FUN_1000f5f0(int param_1)

{
  uint uVar1;
  
  if (1 < DAT_10028b5c) {
    uVar1 = _isctype(param_1,4);
    return uVar1;
  }
  return (byte)PTR_DAT_10028950[param_1 * 2] & 4;
}

/* ---- 0x1000f620  FUN_1000f620 ---- */
uint __cdecl FUN_1000f620(int param_1)

{
  uint uVar1;
  
  if (1 < DAT_10028b5c) {
    uVar1 = _isctype(param_1,8);
    return uVar1;
  }
  return (byte)PTR_DAT_10028950[param_1 * 2] & 8;
}

/* ---- 0x1000f650  FUN_1000f650 ---- */
uint __cdecl FUN_1000f650(int param_1)

{
  uint uVar1;
  
  if (1 < DAT_10028b5c) {
    uVar1 = _isctype(param_1,0x107);
    return uVar1;
  }
  return *(ushort *)(PTR_DAT_10028950 + param_1 * 2) & 0x107;
}

/* ---- 0x1000fde0  FUN_1000fde0 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x1000fea0  FUN_1000fea0 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x100119e0  FUN_100119e0 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x100119f0  FUN_100119f0 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x100120fa  FUN_100120fa ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
float __fastcall FUN_100120fa(undefined4 param_1)

{
  float10 fVar1;
  
  fVar1 = (float10)((code *)FUN_10019b30)(param_1,((unsigned)(uintptr_t)&DAT_100288f0));
  return (float)fVar1;
}
#endif


/* ---- 0x10012104  FUN_10012104 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10012350  FUN_10012350 ---- */
/* not in the source: names/lib_replace.json (host): the system C runtime (msvcrt.dll) has it */


/* ---- 0x10012360  FUN_10012360 ---- */
/* not in the source: names/lib_replace.json (host): the system C runtime (msvcrt.dll) has it */


/* ---- 0x100129a0  FUN_100129a0 ---- */
/* not in the source: names/lib_replace.json (host): the system C runtime (msvcrt.dll) has it */


/* ---- 0x10012ec0  FUN_10012ec0 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10012ee0  FUN_10012ee0 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10012f30  FUN_10012f30 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10012f60  FUN_10012f60 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10012fc0  FUN_10012fc0 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10013030  FUN_10013030 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10013050  FUN_10013050 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10013420  FUN_10013420 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x100139a6  FUN_100139a6 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x100139b3  FUN_100139b3 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x100139f0  FUN_100139f0 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10013b57  FUN_10013b57 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10013b64  FUN_10013b64 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10013b8f  FUN_10013b8f ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10013c00  FUN_10013c00 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10013e0b  FUN_10013e0b ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10013e11  FUN_10013e11 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10013e40  FUN_10013e40 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10013e8a  FUN_10013e8a ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10013e95  FUN_10013e95 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10013ec0  FUN_10013ec0 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10013ef0  FUN_10013ef0 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x1001416a  FUN_1001416a ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10014170  FUN_10014170 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10014197  FUN_10014197 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x100141b0  FUN_100141b0 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x100141f1  FUN_100141f1 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x100141f7  FUN_100141f7 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x1001421e  FUN_1001421e ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10014f80  FUN_10014f80 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10014ff0  FUN_10014ff0 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10015160  FUN_10015160 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x1001519c  FUN_1001519c ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x100151b0  FUN_100151b0 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x100156f0  FUN_100156f0 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x100157a0  FUN_100157a0 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x100157b0  FUN_100157b0 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10015df0  FUN_10015df0 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10015e60  FUN_10015e60 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10015f40  FUN_10015f40 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10015f80  FUN_10015f80 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10015ff0  FUN_10015ff0 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x100160b0  FUN_100160b0 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10016c80  FUN_10016c80 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10016d30  FUN_10016d30 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x100170b0  FUN_100170b0 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x100172f0  FUN_100172f0 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x100173f0  FUN_100173f0 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x100175f0  FUN_100175f0 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x100176e0  FUN_100176e0 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10017830  FUN_10017830 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10017870  FUN_10017870 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x100178e0  FUN_100178e0 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10017c10  FUN_10017c10 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10017df0  FUN_10017df0 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10018c77  FUN_10018c77 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10018d14  FUN_10018d14 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10018d4d  FUN_10018d4d ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10018d4f  FUN_10018d4f ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10018d77  FUN_10018d77 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10018db6  FUN_10018db6 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10018de0  FUN_10018de0 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10018df7  FUN_10018df7 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10018e40  FUN_10018e40 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10018e55  FUN_10018e55 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10018e6c  FUN_10018e6c ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10018e85  FUN_10018e85 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10018ec8  FUN_10018ec8 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10018ede  FUN_10018ede ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10018eeb  FUN_10018eeb ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10018f29  FUN_10018f29 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10018ff0  FUN_10018ff0 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10019040  FUN_10019040 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10019770  FUN_10019770 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10019820  FUN_10019820 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10019850  FUN_10019850 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10019880  FUN_10019880 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x100198c0  FUN_100198c0 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10019900  FUN_10019900 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10019960  FUN_10019960 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10019a70  FUN_10019a70 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10019a80  FUN_10019a80 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10019aa0  FUN_10019aa0 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10019ad0  FUN_10019ad0 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10019b30  FUN_10019b30 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10019bfa  FUN_10019bfa ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x1001a5a6  FUN_1001a5a6 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x1001a7ac  FUN_1001a7ac ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x1001c720  FUN_1001c720 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x1001ce80  FUN_1001ce80 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x1001d2f0  FUN_1001d2f0 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x1001d520  FUN_1001d520 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x1001d560  FUN_1001d560 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x1001d580  FUN_1001d580 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x1001d620  FUN_1001d620 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x1001d6b0  FUN_1001d6b0 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x1001d720  FUN_1001d720 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x1001d790  FUN_1001d790 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x1001d830  FUN_1001d830 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x1001d850  FUN_1001d850 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x1001d860  FUN_1001d860 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x1001d880  FUN_1001d880 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x1001dc70  FUN_1001dc70 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x1001dd00  FUN_1001dd00 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x1001ddc0  FUN_1001ddc0 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x1001ddd0  FUN_1001ddd0 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x1001de30  FUN_1001de30 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x1001de50  FUN_1001de50 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x1001edd0  FUN_1001edd0 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x1001ee10  FUN_1001ee10 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x1001ee80  FUN_1001ee80 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x1001ef20  FUN_1001ef20 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x1001f5d0  FUN_1001f5d0 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10020090  FUN_10020090 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10020470  FUN_10020470 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x100206d0  FUN_100206d0 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10021a10  FUN_10021a10 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10021f90  FUN_10021f90 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10021f9b  FUN_10021f9b ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10021fa6  FUN_10021fa6 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10021fb0  FUN_10021fb0 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10021fbb  FUN_10021fbb ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10021fd0  FUN_10021fd0 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10021fdb  FUN_10021fdb ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10021fe6  FUN_10021fe6 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10021ff0  FUN_10021ff0 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10021ffb  FUN_10021ffb ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10022010  FUN_10022010 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x1002201b  FUN_1002201b ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10022030  FUN_10022030 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x1002203b  FUN_1002203b ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10022050  FUN_10022050 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x1002205b  FUN_1002205b ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */

