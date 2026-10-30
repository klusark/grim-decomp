/* CHORE.DLL: prototypes of every decompiled function, by module */
#pragma once
#include "ghidra_types.h"

/* ===== costume.c ===== */
int __cdecl Cos_InstRescue(int param_1,undefined4 param_2); /* 0x10001000 */
int __cdecl Cos_Free(undefined4 param_1); /* 0x10001040 */
void FUN_100010d0(int param_1); /* 0x100010d0 */
undefined4 Cos_New(void); /* 0x100016a0 */
undefined4 Cos_Load(undefined4 param_1); /* 0x100016e0 */
undefined4 Cos_LoadEntry(char *param_1,int param_2); /* 0x10001770 */
int __cdecl Cos_FreeCosInstance(int param_1); /* 0x10001a30 */
int Cos_CreateCosInstance(uint *param_1,uint param_2); /* 0x10001a80 */
undefined4 Cos_InstGetInstanceData(int param_1,int param_2,int *param_3); /* 0x10001d70 */
undefined4 Cos_RegisterInstanceHook(undefined4 param_1); /* 0x10001e00 */
undefined4 Cos_RegisterSaveHook(undefined4 param_1); /* 0x10001e10 */
undefined4 Cos_InstGetUserData(int param_1); /* 0x10001e20 */
int __cdecl Cos_InstSetUserData(int param_1,undefined4 param_2); /* 0x10001e50 */
undefined4 Cos_NewStateBasedTag (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 *param_4,int param_5); /* 0x10001e80 */
undefined4 FUN_10001ed0(int *param_1,int param_2,char *param_3,undefined4 param_4,undefined4 param_5); /* 0x10001ed0 */
undefined4 Cos_NewIntTag(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 *param_4, int param_5); /* 0x10001f80 */
undefined4 Cos_NewFloatTag(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 *param_4, int param_5); /* 0x10001fd0 */
undefined4 Cos_RegisterComponent (uint param_1,int param_2,undefined4 param_3,int param_4,int param_5,int param_6, undefined4 param_7); /* 0x10002080 */
int __cdecl Cos_RemoveComponent(undefined4 param_1,int param_2,int param_3); /* 0x100021f0 */
undefined4 Cos_InstCountComponents(int param_1); /* 0x10002ee0 */
int __cdecl Cos_InstComponentInfo(int inst,uint index,int *outTag,undefined4 *outA,undefined4 *outB); /* 0x10002f20 */
undefined4 Cos_InstCountChores(int param_1); /* 0x10002f70 */
int Cos_GetCostumeName(undefined4 param_1); /* 0x10002fb0 */
int Cos_InstGetCostume(int param_1,undefined4 *param_2); /* 0x10003000 */
int Cos_InstChoreName(int param_1,uint param_2); /* 0x10003050 */
undefined4 Cos_InstStopChores(uint param_1); /* 0x10003160 */
undefined4 Cos_InstStopChore(int param_1,uint param_2); /* 0x10003240 */
undefined4 Cos_InstPauseChores(int param_1); /* 0x10003300 */
undefined4 Cos_InstPauseChore(int param_1,uint param_2); /* 0x10003360 */
undefined4 Cos_InstCompleteChore(int param_1,uint param_2); /* 0x100033b0 */
undefined4 Cos_InstCompleteChores(int param_1); /* 0x10003430 */
undefined4 __cdecl Cos_InstPlayChore(int param_1,uint param_2,int param_3,int param_4); /* 0x100034c0 */
undefined4 __cdecl Cos_InstUpdateChore(int param_1,uint param_2,int param_3); /* 0x10003530 */
undefined4 Cos_InstUpdateChores(int param_1,int param_2); /* 0x100035a0 */
undefined4 Cos_InstSetChoreLoop(int param_1,uint param_2,int param_3); /* 0x10003620 */
undefined4 Cos_InstSetChoreAdv(int param_1,uint param_2,int param_3); /* 0x10003690 */
undefined4 Cos_InstChoreStatus(int param_1,uint param_2); /* 0x10003700 */
undefined4 Cos_Initialize(undefined4 param_1,undefined4 *param_2); /* 0x10003750 */
undefined4 Cos_Save(code *param_1); /* 0x100037a0 */
undefined4 Cos_SaveInstance(int param_1,code *param_2); /* 0x10003890 */
undefined4 Cos_Restore(code *param_1); /* 0x10003970 */
undefined4 Cos_RestoreInstance(int param_1,code *param_2); /* 0x10003b40 */
int FUN_10003c20(int param_1); /* 0x10003c20 */
undefined4 FUN_10003c90(int param_1,uint param_2,int param_3,uint param_4); /* 0x10003c90 */
uint FUN_10003e50(uint *param_1,uint *param_2); /* 0x10003e50 */
uint FUN_10003e70(int param_1,int *param_2); /* 0x10003e70 */
void FUN_10004090(undefined4 param_1,int param_2,char *param_3,int param_4,undefined4 param_5, undefined4 param_6); /* 0x10004090 */
void FUN_10004140(int param_1); /* 0x10004140 */
uint FUN_10004170(int param_1,int param_2,int param_3,undefined4 param_4); /* 0x10004170 */
undefined4 FUN_100041e0(undefined4 param_1,undefined4 param_2,uint param_3); /* 0x100041e0 */
uint FUN_10004320(int param_1,undefined4 param_2,int param_3); /* 0x10004320 */
undefined4 FUN_10004390(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4); /* 0x10004390 */
uint FUN_10004770(int param_1,int param_2,int param_3,undefined4 param_4,int param_5); /* 0x10004770 */
undefined4 FUN_100047f0(undefined4 param_1,int param_2,undefined4 param_3); /* 0x100047f0 */
undefined4 FUN_10004970(undefined4 param_1,int param_2); /* 0x10004970 */
undefined4 FUN_10004bb0(undefined4 param_1,char *param_2,int param_3); /* 0x10004bb0 */
void FUN_10004c40(undefined4 param_1,int param_2,uint param_3); /* 0x10004c40 */
void FUN_10004c70(undefined4 param_1); /* 0x10004c70 */
void FUN_10004d70(undefined4 param_1,undefined4 *param_2,int param_3); /* 0x10004d70 */
int FUN_10004e50(void); /* 0x10004e50 */
int FUN_10004f30(void); /* 0x10004f30 */
void FUN_10004f70(int param_1); /* 0x10004f70 */
int FUN_10005090(void); /* 0x10005090 */
int FUN_10005160(int param_1); /* 0x10005160 */
int FUN_10005180(int param_1); /* 0x10005180 */
int __cdecl FUN_100051a0(int param_1); /* 0x100051a0 */
int FUN_100051c0(int param_1); /* 0x100051c0 */
void FUN_100051e0(void); /* 0x100051e0 */
undefined4 FUN_10005200(void); /* 0x10005200 */
void FUN_10005350(void); /* 0x10005350 */
undefined4 __cdecl Cos_RegisterSaveVerify(undefined4 param_1); /* 0x10005590 */
uint * FUN_100055a0(uint *param_1,uint *param_2,uint param_3); /* 0x100055a0 */
char * FUN_100056a0(char *param_1,char param_2); /* 0x100056a0 */
void FUN_100056d0(void); /* 0x100056d0 */
void FUN_100056f0(void); /* 0x100056f0 */
void FUN_10005700(void); /* 0x10005700 */
int FUN_10005740(byte *param_1,byte *param_2); /* 0x10005740 */
int __cdecl FUN_10005810(char *param_1,char *param_2,...); /* 0x10005810 */
undefined4 * FUN_10005860(undefined4 *param_1,undefined4 *param_2,uint param_3); /* 0x10005860 */
void FUN_10005ba0(uint param_1,uint param_2,uint param_3,code *param_4); /* 0x10005ba0 */
void FUN_10005d50(uint param_1,uint param_2,int param_3,code *param_4); /* 0x10005d50 */
void FUN_10005db0(undefined1 *param_1,undefined1 *param_2,int param_3); /* 0x10005db0 */
uint FUN_10005de0(undefined4 param_1,uint param_2,uint param_3,int param_4,code *param_5); /* 0x10005de0 */
uint * FUN_10005e90(uint *param_1,char param_2); /* 0x10005e90 */
undefined4 __stdcall FUN_10005f50(int a1,int a2,int a3); /* 0x10005f50 */

/* ===== cosutil.c ===== */
undefined4 CosUtil_Write(char *param_1,int param_2,undefined4 param_3); /* 0x10001110 */
int CosUtil_CompPtrFromHandle(int param_1,uint param_2); /* 0x10002020 */
int CosUtil_PtrFromHandle(undefined4 param_1); /* 0x10002040 */
undefined4 CosUtil_RegisterCompNotifier(undefined4 param_1); /* 0x10002060 */
undefined4 CosUtil_RegisterBitmapMunger(undefined4 param_1); /* 0x10002070 */
undefined4 CosUtil_DeleteComponent(uint param_1,uint param_2); /* 0x10002260 */
int CosUtil_AdjustComponent(int param_1,uint param_2); /* 0x100026a0 */
undefined4 CosUtil_ComponentHasAdjuster(int param_1,uint param_2); /* 0x10002740 */
int CosUtil_AddComponent (undefined4 param_1,int param_2,int param_3,undefined4 param_4,undefined4 param_5); /* 0x100027e0 */
int CosUtil_AddChore(int param_1); /* 0x10002880 */
undefined4 __cdecl CosUtil_DeleteChore(int param_1,uint param_2); /* 0x100028f0 */
int __cdecl CosUtil_SetChoreLength(int param_1,uint param_2,uint param_3); /* 0x100029e0 */
undefined1 * __cdecl CosUtil_NameChore(int param_1,int param_2,char *param_3); /* 0x10002ab0 */
undefined4 CosUtil_DeleteKey(int param_1,uint param_2,uint param_3,int param_4); /* 0x10002b40 */
uint * CosUtil_QueryValueAtTime(int param_1,uint param_2,uint param_3,uint param_4); /* 0x10002c50 */
undefined4 CosUtil_AddFSKey(int param_1,undefined4 param_2,int param_3,undefined4 param_4,undefined4 param_5); /* 0x10002cf0 */
undefined4 CosUtil_AddIntKey(int param_1,undefined4 param_2,int param_3,undefined4 param_4,undefined4 param_5); /* 0x10002d50 */
undefined4 CosUtil_AddFloatKey(int param_1,undefined4 param_2,int param_3,undefined4 param_4,undefined4 param_5 ); /* 0x10002db0 */
undefined4 CosUtil_CountComponents(int param_1); /* 0x10002e10 */
int __cdecl CosUtil_ComponentInfo(int cos,uint index,int *outTag,undefined4 *outA,undefined4 *outB,int *outKind); /* 0x10002e40 */
undefined4 CosUtil_CountChores(int param_1); /* 0x10002fa0 */
int CosUtil_ChoreName(int param_1,uint param_2); /* 0x100030b0 */
undefined4 CosUtil_CountTags(void); /* 0x100030f0 */
int * CosUtil_TagInfo(uint param_1,int *param_2); /* 0x10003100 */

/* ===== chore.c ===== */
void __cdecl Chore_AdvanceTime(int param_1,int param_2,int param_3,int param_4,undefined4 param_5); /* 0x100053e0 */
void __cdecl FUN_10005530(undefined4 param_1,undefined4 *param_2,undefined4 param_3,int param_4, undefined4 param_5,int param_6,undefined4 param_7,undefined4 param_8); /* 0x10005530 */

/* ===== crt.c ===== */
undefined4 __stdcall entry(int a1,int a2,int a3); /* 0x10006070 */

/* ===== region_10006120.c ===== */
void FUN_10006120(undefined4 param_1); /* 0x10006120 */
void FUN_10006160(void); /* 0x10006160 */
undefined4 FUN_100061d0(void); /* 0x100061d0 */
void FUN_10006200(char *param_1); /* 0x10006200 */
void FUN_10006260(char *param_1); /* 0x10006260 */
undefined4 FUN_100062d0(double *param_1); /* 0x100062d0 */
void FUN_100062f0(int param_1,undefined4 *param_2,undefined4 param_3); /* 0x100062f0 */
int FUN_10006350(undefined4 *param_1,int param_2,int param_3,undefined4 param_4); /* 0x10006350 */
undefined1 * FUN_100063d0(undefined1 *param_1,int param_2,int param_3,int *param_4,char param_5); /* 0x100063d0 */
int FUN_100064d0(undefined4 *param_1,int param_2,int param_3); /* 0x100064d0 */
undefined1 * FUN_10006540(undefined1 *param_1,uint param_2,int *param_3,char param_4); /* 0x10006540 */
void FUN_10006600(undefined4 *param_1,int param_2,int param_3,undefined4 param_4); /* 0x10006600 */
void FUN_100066c0(undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4, undefined4 param_5); /* 0x100066c0 */
void FUN_10006730(char *param_1,int param_2); /* 0x10006730 */
void FUN_10006760(void); /* 0x10006760 */
void FUN_10006790(void); /* 0x10006790 */
void FUN_10006810(int param_1); /* 0x10006810 */
int FUN_10006890(void); /* 0x10006890 */
void FUN_100068b0(uint param_1); /* 0x100068b0 */
void FUN_100068f0(int param_1,int param_2); /* 0x100068f0 */
void FUN_10006920(uint param_1); /* 0x10006920 */
void FUN_10006960(int param_1,int param_2); /* 0x10006960 */
undefined4 FUN_10006990(void); /* 0x10006990 */
int FUN_100069a0(int param_1); /* 0x100069a0 */
uint FUN_10006a30(uint param_1); /* 0x10006a30 */
int FUN_10006b30(undefined4 param_1,byte *param_2,undefined4 *param_3); /* 0x10006b30 */
uint FUN_10007870(uint param_1); /* 0x10007870 */
uint FUN_100078b0(undefined4 *param_1); /* 0x100078b0 */
void FUN_100078e0(int param_1,undefined4 param_2); /* 0x100078e0 */
undefined4 FUN_10007900(int *param_1,undefined4 param_2); /* 0x10007900 */
void FUN_10007950(void); /* 0x10007950 */
void FUN_10007980(undefined4 param_1); /* 0x10007980 */
void FUN_100079a0(void); /* 0x100079a0 */
void FUN_100079b0(undefined4 param_1,int param_2,int param_3); /* 0x100079b0 */
void FUN_10007a70(void); /* 0x10007a70 */
void FUN_10007a80(void); /* 0x10007a80 */
void FUN_10007a90(undefined4 *param_1,undefined4 *param_2); /* 0x10007a90 */
undefined4 FUN_10007ab0(void); /* 0x10007ab0 */
void FUN_10007b10(void); /* 0x10007b10 */
void FUN_10007b40(int param_1); /* 0x10007b40 */
int * FUN_10007b60(void); /* 0x10007b60 */
void FUN_10007be0(int param_1); /* 0x10007be0 */
void FUN_10007c90(void); /* 0x10007c90 */
void FUN_10007ea0(void); /* 0x10007ea0 */
void FUN_10007f00(void); /* 0x10007f00 */
void FUN_10007ff0(void); /* 0x10007ff0 */
void FUN_10008090(byte *param_1,undefined4 *param_2,byte *param_3,int *param_4,int *param_5); /* 0x10008090 */
undefined4 FUN_100082a0(undefined4 param_1); /* 0x100082a0 */
int FUN_100084d0(int param_1); /* 0x100084d0 */
undefined4 FUN_10008520(undefined4 param_1); /* 0x10008520 */
void FUN_10008580(void); /* 0x10008580 */
void FUN_100085c0(void); /* 0x100085c0 */
void FUN_100087a0(void); /* 0x100087a0 */
char * FUN_100087b0(void); /* 0x100087b0 */
undefined4 FUN_10008910(void); /* 0x10008910 */
void FUN_10008950(void); /* 0x10008950 */
undefined4 __stdcall FUN_10008990(int a1,int a2,int a3); /* 0x10008990 */
void FUN_100089a0(void); /* 0x100089a0 */
void FUN_100089e0(int param_1); /* 0x100089e0 */
uint FUN_10008bc0(uint param_1,uint param_2); /* 0x10008bc0 */
void FUN_10008c00(undefined4 param_1,uint param_2); /* 0x10008c00 */
uint FUN_10008c20(uint param_1); /* 0x10008c20 */
int FUN_10008cc0(void); /* 0x10008cc0 */
uint FUN_10008d50(int param_1,uint param_2); /* 0x10008d50 */
undefined4 FUN_10008df0(int param_1,int param_2); /* 0x10008df0 */
int FUN_10008e60(void); /* 0x10008e60 */
int FUN_10008ed0(int param_1,int param_2); /* 0x10008ed0 */
void FUN_10008f70(int param_1,undefined4 *param_2); /* 0x10008f70 */
void FUN_10008f90(undefined4 *param_1); /* 0x10008f90 */
undefined4 FUN_10008fa0(int *param_1); /* 0x10008fa0 */
void FUN_10008fc0(uint *param_1,int param_2); /* 0x10008fc0 */
undefined4 FUN_10009080(ushort *param_1,uint *param_2,int *param_3); /* 0x10009080 */
void FUN_10009250(undefined4 param_1,undefined4 param_2); /* 0x10009250 */
void FUN_10009270(undefined4 param_1,undefined4 param_2); /* 0x10009270 */
void FUN_10009290(undefined4 param_1,undefined4 param_2); /* 0x10009290 */
void FUN_100092d0(undefined4 param_1,undefined4 param_2); /* 0x100092d0 */
void FUN_10009310(char *param_1,int param_2,int param_3); /* 0x10009310 */
int * FUN_100093b0(undefined4 param_1,undefined4 param_2,int *param_3,char *param_4); /* 0x100093b0 */
void FUN_10009440(uint *param_1,uint *param_2); /* 0x10009440 */
void FUN_10009500(void); /* 0x10009500 */
int FUN_10009510(void); /* 0x10009510 */
undefined4 FUN_10009580(undefined4 param_1); /* 0x10009580 */
int FUN_100095a0(uint param_1,int param_2); /* 0x100095a0 */
int FUN_100095f0(int param_1); /* 0x100095f0 */
void FUN_10009650(void); /* 0x10009650 */
int __stdcall FUN_10009710(int a1,int a2,int a3,int a4); /* 0x10009710 */
undefined4 FUN_10009730(void); /* 0x10009730 */
uint FUN_100097e0(int param_1); /* 0x100097e0 */
void FUN_10009b60(int param_1); /* 0x10009b60 */
uint FUN_10009da0(undefined4 param_1,char *param_2,int param_3); /* 0x10009da0 */
undefined4 FUN_10009ea0(void); /* 0x10009ea0 */
undefined4 FUN_1000a0a0(void); /* 0x1000a0a0 */
uint FUN_1000a190(int param_1); /* 0x1000a190 */
void FUN_1000a2e0(char *param_1); /* 0x1000a2e0 */
void FUN_1000a320(int param_1); /* 0x1000a320 */
undefined4 FUN_1000a390(void); /* 0x1000a390 */
int FUN_1000a710(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4, undefined4 param_5,undefined4 param_6,int param_7,int param_8); /* 0x1000a710 */
int FUN_1000a940(char *param_1,int param_2); /* 0x1000a940 */
undefined4 FUN_1000a970(undefined4 param_1,undefined4 param_2,undefined4 param_3); /* 0x1000a970 */
uint FUN_1000a9f0(ushort *param_1,byte *param_2,uint param_3); /* 0x1000a9f0 */
uint FUN_1000aaf0(int param_1); /* 0x1000aaf0 */
int __stdcall FUN_1000ab20(int a1,int a2,int a3,int a4); /* 0x1000ab20 */
int __fastcall FUN_1000ab60(byte param_1,int param_2); /* 0x1000ab60 */
uint FUN_1000ab80(undefined4 *param_1); /* 0x1000ab80 */
uint FUN_1000ac70(uint param_1,int *param_2); /* 0x1000ac70 */
undefined4 * FUN_1000ad00(int param_1,int param_2); /* 0x1000ad00 */
int FUN_1000adb0(undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4,int param_5); /* 0x1000adb0 */
int FUN_1000af40(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4, int param_5,int param_6,int param_7); /* 0x1000af40 */
undefined4 * FUN_1000b080(void); /* 0x1000b080 */
void FUN_1000b1f0(int *param_1); /* 0x1000b1f0 */
void FUN_1000b250(int param_1); /* 0x1000b250 */
int FUN_1000b320(uint param_1,undefined4 *param_2,uint *param_3); /* 0x1000b320 */
void FUN_1000b380(int param_1,int param_2,byte *param_3); /* 0x1000b380 */
int * FUN_1000b3e0(uint param_1); /* 0x1000b3e0 */
int FUN_1000b620(int *param_1,uint param_2,uint param_3); /* 0x1000b620 */
undefined4 FUN_1000b7a0(undefined4 param_1,undefined4 param_2,undefined4 param_3); /* 0x1000b7a0 */
undefined4 FUN_1000b830(uint param_1,uint param_2,uint *param_3); /* 0x1000b830 */
void FUN_1000b860(undefined4 *param_1,undefined4 *param_2); /* 0x1000b860 */
void FUN_1000b8d0(uint *param_1); /* 0x1000b8d0 */
void FUN_1000b900(uint *param_1); /* 0x1000b900 */
void FUN_1000b930(char *param_1,int param_2,uint *param_3); /* 0x1000b930 */
undefined4 FUN_1000ba30(ushort *param_1,int *param_2,byte *param_3,undefined4 param_4,int param_5,int param_6, int param_7); /* 0x1000ba30 */
undefined4 FUN_1000c1c0(int param_1,uint param_2,uint param_3,int param_4,byte param_5,short *param_6); /* 0x1000c1c0 */
undefined4 FUN_1000c550(undefined4 param_1); /* 0x1000c550 */
int FUN_1000c610(int param_1); /* 0x1000c610 */
undefined4 FUN_1000c650(int *param_1); /* 0x1000c650 */
void FUN_1000c6c0(void); /* 0x1000c6c0 */
int FUN_1000c6d0(int param_1); /* 0x1000c6d0 */
undefined4 FUN_1000c790(int param_1,undefined4 param_2,undefined4 param_3,int *param_4); /* 0x1000c790 */
int FUN_1000ca50(void); /* 0x1000ca50 */
int FUN_1000cad0(void); /* 0x1000cad0 */
int FUN_1000cae0(void); /* 0x1000cae0 */
undefined4 FUN_1000caf0(uint param_1,undefined4 param_2,undefined4 param_3); /* 0x1000caf0 */
int FUN_1000cb70(uint param_1,char *param_2,int param_3); /* 0x1000cb70 */
void FUN_1000cda0(undefined4 param_1,int *param_2); /* 0x1000cda0 */
void FUN_1000ce00(int *param_1,int *param_2); /* 0x1000ce00 */
void FUN_1000d0c0(undefined2 *param_1,uint param_2,int param_3); /* 0x1000d0c0 */
undefined4 FUN_1000d150(int param_1); /* 0x1000d150 */
undefined4 FUN_1000d190(int param_1); /* 0x1000d190 */
undefined4 FUN_1000d200(uint param_1); /* 0x1000d200 */
undefined4 FUN_1000d2a0(uint param_1,undefined4 param_2,undefined4 param_3); /* 0x1000d2a0 */
int FUN_1000d320(uint param_1,char *param_2,uint param_3); /* 0x1000d320 */
int FUN_1000d530(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4); /* 0x1000d530 */
int FUN_1000d660(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4); /* 0x1000d660 */
undefined4 FUN_1000d890(uint param_1); /* 0x1000d890 */
undefined4 FUN_1000d930(uint param_1); /* 0x1000d930 */
void FUN_1000d980(uint param_1); /* 0x1000d980 */
void FUN_1000d9f0(uint param_1); /* 0x1000d9f0 */
int FUN_1000da20(uint param_1,undefined4 param_2,undefined4 param_3); /* 0x1000da20 */
undefined4 FUN_1000daa0(uint param_1); /* 0x1000daa0 */
undefined4 FUN_1000db10(uint param_1); /* 0x1000db10 */
void FUN_1000dba0(undefined4 *param_1); /* 0x1000dba0 */

/* ===== referenced, not decompiled here (thunks, imports, unknown FUN_) ===== */
int STDCALL CloseHandle() __asm__("_CloseHandle@4"); /* import */
int STDCALL DeleteCriticalSection() __asm__("_DeleteCriticalSection@4"); /* import */
int STDCALL EnterCriticalSection() __asm__("_EnterCriticalSection@4"); /* import */
int STDCALL ExitProcess() __asm__("_ExitProcess@4"); /* import */
int STDCALL FlushFileBuffers() __asm__("_FlushFileBuffers@4"); /* import */
int STDCALL FreeEnvironmentStringsA() __asm__("_FreeEnvironmentStringsA@4"); /* import */
int STDCALL FreeEnvironmentStringsW() __asm__("_FreeEnvironmentStringsW@4"); /* import */
int STDCALL GetACP() __asm__("_GetACP@0"); /* import */
int STDCALL GetCPInfo() __asm__("_GetCPInfo@8"); /* import */
int STDCALL GetCommandLineA() __asm__("_GetCommandLineA@0"); /* import */
int STDCALL GetCurrentProcess() __asm__("_GetCurrentProcess@0"); /* import */
int STDCALL GetCurrentThreadId() __asm__("_GetCurrentThreadId@0"); /* import */
int STDCALL GetEnvironmentStrings() __asm__("_GetEnvironmentStrings@0"); /* import */
int STDCALL GetEnvironmentStringsW() __asm__("_GetEnvironmentStringsW@0"); /* import */
int STDCALL GetFileType() __asm__("_GetFileType@4"); /* import */
int STDCALL GetLastError() __asm__("_GetLastError@0"); /* import */
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
int STDCALL GetVersion() __asm__("_GetVersion@0"); /* import */
int STDCALL HeapAlloc() __asm__("_HeapAlloc@12"); /* import */
int STDCALL HeapCreate() __asm__("_HeapCreate@12"); /* import */
int STDCALL HeapDestroy() __asm__("_HeapDestroy@4"); /* import */
int STDCALL HeapFree() __asm__("_HeapFree@12"); /* import */
int STDCALL InitializeCriticalSection() __asm__("_InitializeCriticalSection@4"); /* import */
int STDCALL InterlockedDecrement() __asm__("_InterlockedDecrement@4"); /* import */
int STDCALL InterlockedIncrement() __asm__("_InterlockedIncrement@4"); /* import */
int STDCALL LCMapStringA() __asm__("_LCMapStringA@24"); /* import */
int STDCALL LCMapStringW() __asm__("_LCMapStringW@24"); /* import */
int STDCALL LeaveCriticalSection() __asm__("_LeaveCriticalSection@4"); /* import */
int STDCALL LoadLibraryA() __asm__("_LoadLibraryA@4"); /* import */
int STDCALL MultiByteToWideChar() __asm__("_MultiByteToWideChar@24"); /* import */
int STDCALL ReadFile() __asm__("_ReadFile@20"); /* import */
int STDCALL SetFilePointer() __asm__("_SetFilePointer@16"); /* import */
int STDCALL SetHandleCount() __asm__("_SetHandleCount@4"); /* import */
int STDCALL SetLastError() __asm__("_SetLastError@4"); /* import */
int STDCALL SetStdHandle() __asm__("_SetStdHandle@8"); /* import */
int STDCALL TerminateProcess() __asm__("_TerminateProcess@8"); /* import */
int STDCALL TlsAlloc() __asm__("_TlsAlloc@0"); /* import */
int STDCALL TlsFree() __asm__("_TlsFree@4"); /* import */
int STDCALL TlsGetValue() __asm__("_TlsGetValue@4"); /* import */
int STDCALL TlsSetValue() __asm__("_TlsSetValue@8"); /* import */
int STDCALL VirtualAlloc() __asm__("_VirtualAlloc@16"); /* import */
int STDCALL VirtualFree() __asm__("_VirtualFree@12"); /* import */
int STDCALL WideCharToMultiByte() __asm__("_WideCharToMultiByte@32"); /* import */
int STDCALL WriteFile() __asm__("_WriteFile@20"); /* import */
