/* CHORE.DLL: every global / string symbol referenced by the decompiled code.
 * Named globals carry their Ghidra type. For DAT_/PTR_/s_ symbols Ghidra exported
 * no type; the type below is inferred from how the code uses the symbol
 * (see infer_global_types in tools/build_src.py) - fix it in Ghidra, not here. */
#pragma once
#include "ghidra_types.h"

/* ---- named globals (type from Ghidra) ---- */
extern char g_szParseLine[1024]; /* 0x10013e10 */
extern uint g_aTagLookups[100]; /* 0x10014210 */
extern int g_nCosInitialize; /* 0x100143a0 */
extern int g_nCosStartup; /* 0x100143a4 */
extern GrimServices * g_pSvcChore; /* 0x100143a8 */
extern int g_nCostumes; /* 0x100143ac */
extern int g_nMaxCostumes; /* 0x100143b0 */
extern Costume * g_aCostumes; /* 0x100143b4 */
extern uint g_dwNumComponentTags; /* 0x100143b8 */
extern uint g_dwMaxComponentTags; /* 0x100143bc */
extern ComponentTag * g_aComponentTags; /* 0x100143c0 */
extern int g_nInstances; /* 0x100143c4 */
extern int g_nMaxInstances; /* 0x100143c8 */
extern CosInstance * g_aCostumeInstances; /* 0x100143cc */
extern int * g_aComponentLookups; /* 0x100143d0 */
extern uint g_dwNumComponentLookups; /* 0x100143d4 */
extern void * g_pfnCompNotifier; /* 0x100143d8 */
extern void * g_pfnBitmapMunger; /* 0x100143dc */
extern void * g_pfnInstanceHook; /* 0x100143e0 */
extern void * g_pfnSaveHook; /* 0x100143e4 */
extern void * g_pfnSaveVerify; /* 0x100143e8 */
extern int g_nLineNum; /* 0x100143ec */
extern int g_nNextCostumeID; /* 0x100143f0 */

/* ---- unnamed data (type inferred from use) ---- */
extern undefined UNK_1000e0fc; /* used by 1 fn(s), first 0x100061d0 */
extern undefined UNK_1000e3e8; /* used by 1 fn(s), first 0x100089e0 */
extern undefined UNK_1000e414; /* used by 1 fn(s), first 0x100089e0 */
extern undefined UNK_1000e430; /* used by 1 fn(s), first 0x100089e0 */
extern undefined UNK_1000e434; /* used by 1 fn(s), first 0x100089e0 */
extern undefined UNK_1000eacc; /* used by 3 fn(s), first 0x1000a710 */
extern undefined UNK_1000ead0; /* used by 3 fn(s), first 0x1000a710 */
extern undefined UNK_1000eb04; /* used by 1 fn(s), first 0x1000b7a0 */
extern undefined DAT_10010000; /* used by 1 fn(s), first 0x10007950 */
extern char s_C__grimsrc_libs_chore_Costume_c_1001020c[]; /* used by 33 fn(s), first 0x10001110 */
extern undefined DAT_10010284; /* used by 5 fn(s), first 0x10001a80 */
extern undefined DAT_100106a8; /* used by 1 fn(s), first 0x10007950 */
extern undefined DAT_100106c0; /* used by 1 fn(s), first 0x10006120 */
extern undefined DAT_100106c8; /* used by 1 fn(s), first 0x10005700 */
extern undefined DAT_100106cc; /* used by 1 fn(s), first 0x10005700 */
extern undefined DAT_100106d0; /* used by 2 fn(s), first 0x10005700 */
extern undefined DAT_100106d4; /* used by 1 fn(s), first 0x10005700 */
extern undefined DAT_100106d8; /* used by 1 fn(s), first 0x10005700 */
extern undefined DAT_100106dc; /* used by 1 fn(s), first 0x10005700 */
extern undefined DAT_100106e4; /* used by 1 fn(s), first 0x10006790 */
extern undefined DAT_10010704; /* used by 1 fn(s), first 0x10006790 */
extern undefined DAT_10010714; /* used by 1 fn(s), first 0x10006790 */
extern undefined DAT_10010724; /* used by 1 fn(s), first 0x10006790 */
extern undefined DAT_10010908; /* used by 4 fn(s), first 0x10007ab0 */
extern undefined DAT_10010ac8; /* used by 1 fn(s), first 0x100089e0 */
extern undefined DAT_10010acc; /* used by 7 fn(s), first 0x10006200 */
extern undefined DAT_10010ad0; /* used by 1 fn(s), first 0x10009ea0 */
extern undefined DAT_10010ad8; /* used by 10 fn(s), first 0x10006200 */
extern undefined DAT_10010adc; /* used by 1 fn(s), first 0x1000a390 */
extern undefined DAT_100117a8; /* used by 5 fn(s), first 0x10008950 */
extern undefined DAT_100117ac; /* used by 2 fn(s), first 0x1000b080 */
extern undefined DAT_100117b8; /* used by 2 fn(s), first 0x1000b080 */
extern undefined DAT_100137c8; /* used by 2 fn(s), first 0x1000b1f0 */
extern undefined DAT_100137cc; /* used by 2 fn(s), first 0x100095f0 */
extern undefined DAT_1001387c; /* used by 1 fn(s), first 0x10009730 */
extern undefined DAT_10013888; /* used by 1 fn(s), first 0x1000a0a0 */
extern undefined DAT_1001388c; /* used by 1 fn(s), first 0x1000a0a0 */
extern undefined DAT_10013890; /* used by 1 fn(s), first 0x1000a0a0 */
extern undefined DAT_100138b8; /* used by 2 fn(s), first 0x10009ea0 */
extern undefined DAT_100143f8; /* used by 1 fn(s), first 0x100056d0 */
extern undefined DAT_100143fc; /* used by 2 fn(s), first 0x10005f50 */
extern undefined DAT_10014400; /* used by 2 fn(s), first 0x10005f50 */
extern undefined DAT_10014408; /* used by 3 fn(s), first 0x10006120 */
extern undefined DAT_1001440c; /* used by 4 fn(s), first 0x10006120 */
extern undefined DAT_10014478; /* used by 7 fn(s), first 0x10005740 */
extern undefined DAT_1001447c; /* used by 1 fn(s), first 0x1000a0a0 */
extern undefined DAT_10014480; /* used by 1 fn(s), first 0x10009ea0 */
extern undefined DAT_10014484; /* used by 1 fn(s), first 0x10009730 */
extern undefined DAT_10014488; /* used by 1 fn(s), first 0x1000a390 */
extern undefined DAT_1001449c; /* used by 1 fn(s), first 0x10005f50 */
extern undefined DAT_100144a0; /* used by 1 fn(s), first 0x10005f50 */
extern undefined DAT_100144a4; /* used by 1 fn(s), first 0x10005f50 */
extern undefined DAT_100144a8; /* used by 1 fn(s), first 0x10005f50 */
extern undefined DAT_100144ac; /* used by 1 fn(s), first 0x10007ff0 */
extern undefined DAT_100144b0; /* used by 1 fn(s), first 0x10007ff0 */
extern undefined DAT_100144b8; /* used by 1 fn(s), first 0x10007f00 */
extern undefined DAT_100144c8; /* used by 1 fn(s), first 0x10007ff0 */
extern undefined DAT_100144d0; /* used by 2 fn(s), first 0x100079b0 */
extern undefined DAT_100144d4; /* used by 2 fn(s), first 0x10005f50 */
extern undefined DAT_100144d8; /* used by 1 fn(s), first 0x100079b0 */
extern undefined DAT_100147f0; /* used by 3 fn(s), first 0x100082a0 */
extern undefined DAT_100147f4; /* used by 3 fn(s), first 0x100082a0 */
extern undefined DAT_100147f8; /* used by 2 fn(s), first 0x100082a0 */
extern undefined DAT_100147fc; /* used by 2 fn(s), first 0x100082a0 */
extern undefined DAT_10014800; /* used by 2 fn(s), first 0x100082a0 */
extern undefined DAT_10014804; /* used by 2 fn(s), first 0x100082a0 */
extern undefined DAT_1001480c; /* used by 1 fn(s), first 0x100087b0 */
extern undefined DAT_10014810; /* used by 1 fn(s), first 0x100089a0 */
extern undefined DAT_10014814; /* used by 1 fn(s), first 0x1000cda0 */
extern undefined DAT_10014818; /* used by 1 fn(s), first 0x10009730 */
extern undefined DAT_1001481c; /* used by 1 fn(s), first 0x10009ea0 */
extern undefined DAT_10014820; /* used by 1 fn(s), first 0x10009ea0 */
extern undefined DAT_10014824; /* used by 1 fn(s), first 0x10009ea0 */
extern undefined DAT_10014828; /* used by 1 fn(s), first 0x1000a0a0 */
extern undefined DAT_1001482c; /* used by 1 fn(s), first 0x1000a390 */
extern undefined DAT_10014830; /* used by 1 fn(s), first 0x1000a390 */
extern undefined DAT_10014844; /* used by 1 fn(s), first 0x1000a390 */
extern undefined DAT_1001484c; /* used by 1 fn(s), first 0x1000a190 */
extern undefined DAT_10014852; /* used by 1 fn(s), first 0x10009ea0 */
extern undefined DAT_10014856; /* used by 1 fn(s), first 0x100097e0 */
extern undefined DAT_10014858; /* used by 1 fn(s), first 0x100097e0 */
extern undefined DAT_10014884; /* used by 1 fn(s), first 0x1000a710 */
extern undefined DAT_10014888; /* used by 1 fn(s), first 0x1000adb0 */
extern undefined DAT_1001488c; /* used by 1 fn(s), first 0x1000af40 */
extern undefined DAT_10014890; /* used by 2 fn(s), first 0x1000b250 */
extern undefined DAT_10014894; /* used by 1 fn(s), first 0x1000b7a0 */
extern undefined DAT_10014898; /* used by 1 fn(s), first 0x1000b7a0 */
extern undefined DAT_1001489c; /* used by 1 fn(s), first 0x1000b7a0 */
extern undefined DAT_100148b4; /* used by 2 fn(s), first 0x10009580 */
extern undefined DAT_100148b8; /* used by 1 fn(s), first 0x1000c550 */
extern undefined DAT_10014994; /* used by 1 fn(s), first 0x1000d530 */
extern undefined DAT_10014998; /* used by 1 fn(s), first 0x1000d660 */
extern undefined DAT_100149a4; /* used by 3 fn(s), first 0x10009650 */
extern undefined DAT_100159c0; /* used by 3 fn(s), first 0x10009650 */
extern undefined DAT_100159c4; /* used by 7 fn(s), first 0x10008910 */
extern undefined DAT_100159c8; /* used by 2 fn(s), first 0x100082a0 */
extern undefined DAT_100159e0; /* used by 16 fn(s), first 0x10007c90 */
extern undefined DAT_10015ae0; /* used by 7 fn(s), first 0x10007c90 */
extern undefined DAT_10015ae4; /* used by 1 fn(s), first 0x100079b0 */
extern undefined DAT_10015ae8; /* used by 1 fn(s), first 0x100079b0 */
extern undefined DAT_10015aec; /* used by 3 fn(s), first 0x10005740 */
extern undefined DAT_10015af0; /* used by 1 fn(s), first 0x10005740 */
extern undefined DAT_10015af4; /* used by 2 fn(s), first 0x10005f50 */
extern undefined DAT_10015af8; /* used by 1 fn(s), first 0x10006070 */

/* ---- re-typed views of the symbols above ---- */
#define _DAT_100106a8 (*(code * *)&DAT_100106a8) /* same address as DAT_100106a8, other width */
#define _DAT_100106c0 (*(code * *)&DAT_100106c0) /* same address as DAT_100106c0, other width */
#define _DAT_100106c8 (*(undefined4 *)&DAT_100106c8) /* same address as DAT_100106c8, other width */
#define _DAT_100106cc (*(undefined4 *)&DAT_100106cc) /* same address as DAT_100106cc, other width */
#define _DAT_100106d0 (*(code * *)&DAT_100106d0) /* same address as DAT_100106d0, other width */
#define _DAT_100106d4 (*(undefined4 *)&DAT_100106d4) /* same address as DAT_100106d4, other width */
#define _DAT_100106d8 (*(undefined4 *)&DAT_100106d8) /* same address as DAT_100106d8, other width */
#define _DAT_100106dc (*(undefined4 *)&DAT_100106dc) /* same address as DAT_100106dc, other width */
#define _DAT_100106e4 (*(undefined4 *)&DAT_100106e4) /* same address as DAT_100106e4, other width */
#define _DAT_10010704 (*(undefined4 *)&DAT_10010704) /* same address as DAT_10010704, other width */
#define _DAT_10010714 (*(undefined4 *)&DAT_10010714) /* same address as DAT_10010714, other width */
#define _DAT_10010724 (*(undefined4 *)&DAT_10010724) /* same address as DAT_10010724, other width */
#define _DAT_10010908 (*(undefined4 *)&DAT_10010908) /* same address as DAT_10010908, other width */
#define _DAT_10010ac8 (*(undefined4 *)&DAT_10010ac8) /* same address as DAT_10010ac8, other width */
#define _DAT_10010ad0 (*(undefined4 *)&DAT_10010ad0) /* same address as DAT_10010ad0, other width */
#define _DAT_10010ad8 (*(undefined4 *)&DAT_10010ad8) /* same address as DAT_10010ad8, other width */
#define _DAT_10010adc (*(undefined4 *)&DAT_10010adc) /* same address as DAT_10010adc, other width */
#define _DAT_100117a8 (*(undefined4 *)&DAT_100117a8) /* same address as DAT_100117a8, other width */
#define _DAT_100117ac (*(undefined4 * *)&DAT_100117ac) /* same address as DAT_100117ac, other width */
#define _DAT_100117b8 (*(undefined4 *)&DAT_100117b8) /* same address as DAT_100117b8, other width */
#define _DAT_100137c8 (*(int * *)&DAT_100137c8) /* same address as DAT_100137c8, other width */
#define _DAT_100137cc (*(undefined4 *)&DAT_100137cc) /* same address as DAT_100137cc, other width */
#define _DAT_1001387c (*(int *)&DAT_1001387c) /* same address as DAT_1001387c, other width */
#define _DAT_10013888 (*(undefined4 *)&DAT_10013888) /* same address as DAT_10013888, other width */
#define _DAT_1001388c (*(undefined4 *)&DAT_1001388c) /* same address as DAT_1001388c, other width */
#define _DAT_10013890 (*(undefined4 *)&DAT_10013890) /* same address as DAT_10013890, other width */
#define _DAT_100138b8 (*(undefined4 * *)&DAT_100138b8) /* same address as DAT_100138b8, other width */
#define _DAT_100143f8 (*(undefined4 *)&DAT_100143f8) /* same address as DAT_100143f8, other width */
#define _DAT_100143fc (*(undefined4 *)&DAT_100143fc) /* same address as DAT_100143fc, other width */
#define _DAT_10014400 (*(undefined4 * *)&DAT_10014400) /* same address as DAT_10014400, other width */
#define _DAT_10014408 (*(undefined4 *)&DAT_10014408) /* same address as DAT_10014408, other width */
#define _DAT_1001440c (*(undefined4 *)&DAT_1001440c) /* same address as DAT_1001440c, other width */
#define _DAT_10014478 (*(int *)&DAT_10014478) /* same address as DAT_10014478, other width */
#define _DAT_1001447c (*(undefined4 *)&DAT_1001447c) /* same address as DAT_1001447c, other width */
#define _DAT_10014480 (*(undefined4 *)&DAT_10014480) /* same address as DAT_10014480, other width */
#define _DAT_10014484 (*(undefined4 *)&DAT_10014484) /* same address as DAT_10014484, other width */
#define _DAT_10014488 (*(int *)&DAT_10014488) /* same address as DAT_10014488, other width */
#define _DAT_1001449c (*(undefined4 *)&DAT_1001449c) /* same address as DAT_1001449c, other width */
#define _DAT_100144a0 (*(undefined4 *)&DAT_100144a0) /* same address as DAT_100144a0, other width */
#define _DAT_100144a4 (*(undefined4 *)&DAT_100144a4) /* same address as DAT_100144a4, other width */
#define _DAT_100144a8 (*(undefined4 *)&DAT_100144a8) /* same address as DAT_100144a8, other width */
#define _DAT_100144ac (*(undefined4 *)&DAT_100144ac) /* same address as DAT_100144ac, other width */
#define _DAT_100144b0 (*(undefined4 *)&DAT_100144b0) /* same address as DAT_100144b0, other width */
#define _DAT_100144b8 (*(undefined4 *)&DAT_100144b8) /* same address as DAT_100144b8, other width */
#define _DAT_100144c8 (*(undefined4 *)&DAT_100144c8) /* same address as DAT_100144c8, other width */
#define _DAT_100144d4 (*(undefined4 *)&DAT_100144d4) /* same address as DAT_100144d4, other width */
#define _DAT_100144d8 (*(undefined4 *)&DAT_100144d8) /* same address as DAT_100144d8, other width */
#define _DAT_100147f0 (*(undefined4 *)&DAT_100147f0) /* same address as DAT_100147f0, other width */
#define _DAT_100147f4 (*(undefined4 *)&DAT_100147f4) /* same address as DAT_100147f4, other width */
#define _DAT_100147f8 (*(undefined4 *)&DAT_100147f8) /* same address as DAT_100147f8, other width */
#define _DAT_100147fc (*(undefined4 *)&DAT_100147fc) /* same address as DAT_100147fc, other width */
#define _DAT_10014800 (*(undefined4 *)&DAT_10014800) /* same address as DAT_10014800, other width */
#define _DAT_10014804 (*(undefined4 *)&DAT_10014804) /* same address as DAT_10014804, other width */
#define _DAT_1001480c (*(undefined4 *)&DAT_1001480c) /* same address as DAT_1001480c, other width */
#define _DAT_10014810 (*(code * *)&DAT_10014810) /* same address as DAT_10014810, other width */
#define _DAT_10014814 (*(undefined4 *)&DAT_10014814) /* same address as DAT_10014814, other width */
#define _DAT_10014818 (*(int *)&DAT_10014818) /* same address as DAT_10014818, other width */
#define _DAT_1001481c (*(undefined4 *)&DAT_1001481c) /* same address as DAT_1001481c, other width */
#define _DAT_10014820 (*(undefined4 *)&DAT_10014820) /* same address as DAT_10014820, other width */
#define _DAT_10014824 (*(undefined4 *)&DAT_10014824) /* same address as DAT_10014824, other width */
#define _DAT_10014828 (*(undefined4 * *)&DAT_10014828) /* same address as DAT_10014828, other width */
#define _DAT_1001482c (*(undefined4 *)&DAT_1001482c) /* same address as DAT_1001482c, other width */
#define _DAT_10014830 (*(undefined4 *)&DAT_10014830) /* same address as DAT_10014830, other width */
#define _DAT_10014844 (*(undefined2 *)&DAT_10014844) /* same address as DAT_10014844, other width */
#define _DAT_1001484c (*(undefined2 *)&DAT_1001484c) /* same address as DAT_1001484c, other width */
#define _DAT_10014852 (*(undefined2 *)&DAT_10014852) /* same address as DAT_10014852, other width */
#define _DAT_10014856 (*(undefined2 *)&DAT_10014856) /* same address as DAT_10014856, other width */
#define _DAT_10014858 (*(undefined2 *)&DAT_10014858) /* same address as DAT_10014858, other width */
#define _DAT_10014884 (*(undefined4 *)&DAT_10014884) /* same address as DAT_10014884, other width */
#define _DAT_10014888 (*(undefined4 *)&DAT_10014888) /* same address as DAT_10014888, other width */
#define _DAT_1001488c (*(undefined4 *)&DAT_1001488c) /* same address as DAT_1001488c, other width */
#define _DAT_10014890 (*(undefined4 *)&DAT_10014890) /* same address as DAT_10014890, other width */
#define _DAT_10014894 (*(code * *)&DAT_10014894) /* same address as DAT_10014894, other width */
#define _DAT_10014898 (*(code * *)&DAT_10014898) /* same address as DAT_10014898, other width */
#define _DAT_1001489c (*(code * *)&DAT_1001489c) /* same address as DAT_1001489c, other width */
#define _DAT_100148b4 (*(undefined4 *)&DAT_100148b4) /* same address as DAT_100148b4, other width */
#define _DAT_100148b8 (*(code * *)&DAT_100148b8) /* same address as DAT_100148b8, other width */
#define _DAT_10014994 (*(undefined4 *)&DAT_10014994) /* same address as DAT_10014994, other width */
#define _DAT_10014998 (*(undefined4 *)&DAT_10014998) /* same address as DAT_10014998, other width */
#define _DAT_100149a4 (*(undefined4 *)&DAT_100149a4) /* same address as DAT_100149a4, other width */
#define _DAT_100159c0 (*(undefined4 *)&DAT_100159c0) /* same address as DAT_100159c0, other width */
#define _DAT_100159c4 (*(undefined4 *)&DAT_100159c4) /* same address as DAT_100159c4, other width */
#define _DAT_100159c8 (*(undefined4 *)&DAT_100159c8) /* same address as DAT_100159c8, other width */
#define _DAT_100159e0 (*(undefined4 * *)&DAT_100159e0) /* same address as DAT_100159e0, other width */
#define _DAT_10015ae0 (*(undefined4 *)&DAT_10015ae0) /* same address as DAT_10015ae0, other width */
#define _DAT_10015ae4 (*(undefined4 *)&DAT_10015ae4) /* same address as DAT_10015ae4, other width */
#define _DAT_10015ae8 (*(undefined4 * *)&DAT_10015ae8) /* same address as DAT_10015ae8, other width */
#define _DAT_10015aec (*(undefined4 *)&DAT_10015aec) /* same address as DAT_10015aec, other width */
#define _DAT_10015af0 (*(int *)&DAT_10015af0) /* same address as DAT_10015af0, other width */
#define _DAT_10015af4 (*(undefined4 * *)&DAT_10015af4) /* same address as DAT_10015af4, other width */
#define _DAT_10015af8 (*(code * *)&DAT_10015af8) /* same address as DAT_10015af8, other width */

/* ---- data the code addressed by number (IMG_ADDR): the span at that address (src/CHORE.DLL/data.c) ---- */
extern unsigned char DAT_1000e0e0[]; /* 0x1000e0e0 */
extern unsigned char DAT_1000ead4[]; /* 0x1000ead4 */
extern unsigned char DAT_1000eae8[]; /* 0x1000eae8 */
extern unsigned char DAT_1000eaf8[]; /* 0x1000eaf8 */
extern unsigned char DAT_10010004[]; /* 0x10010004 */
extern unsigned char DAT_10010008[]; /* 0x10010008 */
extern unsigned char DAT_10010010[]; /* 0x10010010 */
extern unsigned char DAT_10010014[]; /* 0x10010014 */
extern unsigned char DAT_1001001c[]; /* 0x1001001c */
extern unsigned char DAT_10010020[]; /* 0x10010020 */
extern unsigned char DAT_10010024[]; /* 0x10010024 */
extern unsigned char DAT_10010030[]; /* 0x10010030 */
extern unsigned char DAT_10010040[]; /* 0x10010040 */
extern unsigned char DAT_10010048[]; /* 0x10010048 */
extern unsigned char DAT_10010054[]; /* 0x10010054 */
extern unsigned char DAT_10010060[]; /* 0x10010060 */
extern unsigned char DAT_10010094[]; /* 0x10010094 */
extern unsigned char DAT_100100a4[]; /* 0x100100a4 */
extern unsigned char DAT_100100b4[]; /* 0x100100b4 */
extern unsigned char DAT_100100c8[]; /* 0x100100c8 */
extern unsigned char DAT_100100e4[]; /* 0x100100e4 */
extern unsigned char DAT_100100f4[]; /* 0x100100f4 */
extern unsigned char DAT_10010108[]; /* 0x10010108 */
extern unsigned char DAT_10010120[]; /* 0x10010120 */
extern unsigned char DAT_10010130[]; /* 0x10010130 */
extern unsigned char DAT_10010150[]; /* 0x10010150 */
extern unsigned char DAT_10010164[]; /* 0x10010164 */
extern unsigned char DAT_1001017c[]; /* 0x1001017c */
extern unsigned char DAT_10010190[]; /* 0x10010190 */
extern unsigned char DAT_10010198[]; /* 0x10010198 */
extern unsigned char DAT_1001019c[]; /* 0x1001019c */
extern unsigned char DAT_100101a0[]; /* 0x100101a0 */
extern unsigned char DAT_100101b8[]; /* 0x100101b8 */
extern unsigned char DAT_100101c8[]; /* 0x100101c8 */
extern unsigned char DAT_100101d8[]; /* 0x100101d8 */
extern unsigned char DAT_100101ec[]; /* 0x100101ec */
extern unsigned char DAT_100101f4[]; /* 0x100101f4 */
extern unsigned char DAT_100101f8[]; /* 0x100101f8 */
extern unsigned char DAT_1001022c[]; /* 0x1001022c */
extern unsigned char DAT_1001023c[]; /* 0x1001023c */
extern unsigned char DAT_1001024c[]; /* 0x1001024c */
extern unsigned char DAT_10010260[]; /* 0x10010260 */
extern unsigned char DAT_10010270[]; /* 0x10010270 */
extern unsigned char DAT_10010280[]; /* 0x10010280 */
extern unsigned char DAT_10010288[]; /* 0x10010288 */
extern unsigned char DAT_100102a4[]; /* 0x100102a4 */
extern unsigned char DAT_100102cc[]; /* 0x100102cc */
extern unsigned char DAT_100102f8[]; /* 0x100102f8 */
extern unsigned char DAT_10010320[]; /* 0x10010320 */
extern unsigned char DAT_1001034c[]; /* 0x1001034c */
extern unsigned char DAT_10010364[]; /* 0x10010364 */
extern unsigned char DAT_100103b0[]; /* 0x100103b0 */
extern unsigned char DAT_10010444[]; /* 0x10010444 */
extern unsigned char DAT_10010468[]; /* 0x10010468 */
extern unsigned char DAT_10010498[]; /* 0x10010498 */
extern unsigned char DAT_100104c8[]; /* 0x100104c8 */
extern unsigned char DAT_100104f8[]; /* 0x100104f8 */
extern unsigned char DAT_10010524[]; /* 0x10010524 */
extern unsigned char DAT_10010538[]; /* 0x10010538 */
extern unsigned char DAT_10010544[]; /* 0x10010544 */
extern unsigned char DAT_10010558[]; /* 0x10010558 */
extern unsigned char DAT_10010574[]; /* 0x10010574 */
extern unsigned char DAT_10010588[]; /* 0x10010588 */
extern unsigned char DAT_100105ac[]; /* 0x100105ac */
extern unsigned char DAT_100105c0[]; /* 0x100105c0 */
extern unsigned char DAT_100105d0[]; /* 0x100105d0 */
extern unsigned char DAT_100105d8[]; /* 0x100105d8 */
extern unsigned char DAT_100105f8[]; /* 0x100105f8 */
extern unsigned char DAT_10010600[]; /* 0x10010600 */
extern unsigned char DAT_1001060c[]; /* 0x1001060c */
extern unsigned char DAT_10010638[]; /* 0x10010638 */
extern unsigned char DAT_1001065c[]; /* 0x1001065c */
extern unsigned char DAT_1001067c[]; /* 0x1001067c */
extern unsigned char DAT_100106e0[]; /* 0x100106e0 */
extern unsigned char DAT_100107a0[]; /* 0x100107a0 */
extern unsigned char DAT_100108fc[]; /* 0x100108fc */
extern unsigned char DAT_10010904[]; /* 0x10010904 */
extern unsigned char DAT_10010910[]; /* 0x10010910 */
extern unsigned char DAT_10010938[]; /* 0x10010938 */
extern unsigned char DAT_10010940[]; /* 0x10010940 */
extern unsigned char DAT_10010944[]; /* 0x10010944 */
extern unsigned char DAT_10010948[]; /* 0x10010948 */
extern unsigned char DAT_1001094c[]; /* 0x1001094c */
extern unsigned char DAT_10010950[]; /* 0x10010950 */
extern unsigned char DAT_10010a30[]; /* 0x10010a30 */
extern unsigned char DAT_10010a38[]; /* 0x10010a38 */
extern unsigned char DAT_10010a3c[]; /* 0x10010a3c */
extern unsigned char DAT_10010ae2[]; /* 0x10010ae2 */
extern unsigned char DAT_10010ce8[]; /* 0x10010ce8 */
extern unsigned char DAT_10010d00[]; /* 0x10010d00 */
extern unsigned char DAT_10010d17[]; /* 0x10010d17 */
extern unsigned char DAT_10010d18[]; /* 0x10010d18 */
extern unsigned char DAT_10010d28[]; /* 0x10010d28 */
extern unsigned char DAT_10010d88[]; /* 0x10010d88 */
extern unsigned char DAT_10010f79[]; /* 0x10010f79 */
extern unsigned char DAT_10011720[]; /* 0x10011720 */
extern unsigned char DAT_100137d0[]; /* 0x100137d0 */
extern unsigned char DAT_10013880[]; /* 0x10013880 */
extern unsigned char DAT_100138c0[]; /* 0x100138c0 */
extern unsigned char DAT_100138c4[]; /* 0x100138c4 */
extern unsigned char DAT_10013a28[]; /* 0x10013a28 */
extern unsigned char DAT_10013a80[]; /* 0x10013a80 */
extern unsigned char DAT_10013be0[]; /* 0x10013be0 */
extern unsigned char DAT_100144e0[]; /* 0x100144e0 */
extern unsigned char DAT_100145e8[]; /* 0x100145e8 */
extern unsigned char DAT_100145e9[]; /* 0x100145e9 */
extern unsigned char DAT_100146f0[]; /* 0x100146f0 */
extern unsigned char DAT_100148c8[]; /* 0x100148c8 */
extern unsigned char DAT_100148cf[]; /* 0x100148cf */
extern unsigned char DAT_100148d0[]; /* 0x100148d0 */
extern unsigned char DAT_100159e4[]; /* 0x100159e4 */
