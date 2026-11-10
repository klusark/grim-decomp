/* CHORE.DLL: prototypes of every decompiled function, by module */
#pragma once
#include "ghidra_types.h"

/* ===== costume.c ===== */
int __cdecl Cos_InstRescue(int hInst,int hCostume); /* 0x10001000 */
int __cdecl Cos_Free(int hCostume); /* 0x10001040 */
void __cdecl Cos_NewEntry(Costume *pCostume); /* 0x100010d0 */
int __cdecl Cos_New(void); /* 0x100016a0 */
int __cdecl Cos_Load(char *fileName); /* 0x100016e0 */
uint __cdecl Cos_LoadEntry(char *name,int handle); /* 0x10001770 */
int __cdecl Cos_FreeCosInstance(int hInst); /* 0x10001a30 */
int __cdecl Cos_CreateCosInstance(int hCostume,int userData); /* 0x10001a80 */
int __cdecl Cos_InstGetInstanceData(int hInst,int compNum,int *outTagId); /* 0x10001d70 */
void * __cdecl Cos_RegisterInstanceHook(void *hook); /* 0x10001e00 */
void * __cdecl Cos_RegisterSaveHook(void *hook); /* 0x10001e10 */
int __cdecl Cos_InstGetUserData(int hInst); /* 0x10001e20 */
int __cdecl Cos_InstSetUserData(int hInst,int userData); /* 0x10001e50 */
uint __cdecl Cos_NewStateBasedTag(uint id,uint name,uint unused,uint *handlers,int extra); /* 0x10001e80 */
int __cdecl Cos_NewTagEntry(ComponentTag **ppTag,int tagId,char *name,int unused,int userData); /* 0x10001ed0 */
uint __cdecl Cos_NewIntTag(uint id,uint name,uint unused,uint *handlers,int extra); /* 0x10001f80 */
uint __cdecl Cos_NewFloatTag(uint id,uint name,uint unused,uint *handlers,int extra); /* 0x10001fd0 */
int __cdecl Cos_RegisterComponent (uint hCostume,char *name,int data,int tagId,int parentData,int parentTagId,int *pStates); /* 0x10002080 */
int __cdecl Cos_RemoveComponent(int hCostume,int tagId,int data); /* 0x100021f0 */
int __cdecl Cos_InstCountComponents(int hInst); /* 0x10002ee0 */
int __cdecl Cos_InstComponentInfo(int inst,uint index,int *outTag,undefined4 *outA,undefined4 *outB); /* 0x10002f20 */
int __cdecl Cos_InstCountChores(int hInst); /* 0x10002f70 */
char * __cdecl Cos_GetCostumeName(int hCostume); /* 0x10002fb0 */
Costume * __cdecl Cos_InstGetCostume(int hInst,int *outHandle); /* 0x10003000 */
char * __cdecl Cos_InstChoreName(int hInst,uint choreNum); /* 0x10003050 */
int __cdecl Cos_InstStopChores(uint hInst); /* 0x10003160 */
int __cdecl Cos_InstStopChore(int hInst,uint choreNum); /* 0x10003240 */
int __cdecl Cos_InstPauseChores(int hInst); /* 0x10003300 */
int __cdecl Cos_InstPauseChore(int hInst,uint choreNum); /* 0x10003360 */
int __cdecl Cos_InstCompleteChore(int hInst,uint choreNum); /* 0x100033b0 */
int __cdecl Cos_InstCompleteChores(int hInst); /* 0x10003430 */
int __cdecl Cos_InstPlayChore(int hInst,uint choreNum,int loop,int manual); /* 0x100034c0 */
int __cdecl Cos_InstUpdateChore(int hInst,uint choreNum,int dt); /* 0x10003530 */
int __cdecl Cos_InstUpdateChores(int hInst,int dt); /* 0x100035a0 */
int __cdecl Cos_InstSetChoreLoop(int hInst,uint choreNum,int loop); /* 0x10003620 */
int __cdecl Cos_InstSetChoreAdv(int hInst,uint choreNum,int manual); /* 0x10003690 */
uint __cdecl Cos_InstChoreStatus(int hInst,uint choreNum); /* 0x10003700 */
int __cdecl Cos_Initialize(GrimServices *svc,void **moduleIface); /* 0x10003750 */
uint __cdecl Cos_Save(void *io); /* 0x100037a0 */
int __cdecl Cos_SaveInstance(int hInst,void *io); /* 0x10003890 */
uint __cdecl Cos_Restore(void *io); /* 0x10003970 */
int __cdecl Cos_RestoreInstance(int hInst,void *io); /* 0x10003b40 */
uint __cdecl Cos_CollectUsedTags(Costume *pCostume); /* 0x10003c20 */
ChoreKey * __cdecl Cos_AddKey(Costume *pCostume,uint choreNum,int compNum,uint time); /* 0x10003c90 */
int __cdecl Cos_CompareKeys(ChoreKey *a,ChoreKey *b); /* 0x10003e50 */
uint __cdecl Cos_InitComponentStates(CosComponent *pComponent,int *pStates); /* 0x10003e70 */
void __cdecl Cos_InitComponent(Costume *pCostume,CosComponent *pComponent,char *name,int tag,int data,int parent); /* 0x10004090 */
void __cdecl Cos_InitChore(Chore *pChore); /* 0x10004140 */
int __cdecl Cos_FindComponent(Costume *pCostume,int tagId,int hash,char *name); /* 0x10004170 */
uint __cdecl Cos_ReadTagsSection(uint file,uint unused2,uint unused3); /* 0x100041e0 */
int __cdecl Cos_FindTag(int tagId,char *name,int kind); /* 0x10004320 */
uint __cdecl Cos_ReadComponentsSection(uint file,uint handle,uint unused3,uint unused4); /* 0x10004390 */
int __cdecl Cos_FindComponentWithParent(Costume *pCostume,int tagId,int hash,char *name,int parent); /* 0x10004770 */
uint __cdecl Cos_ReadChoresSection(uint file,int costume,uint unused3); /* 0x100047f0 */
uint __cdecl Cos_ReadKeysSection(uint file,int costume); /* 0x10004970 */
int __cdecl Cos_ReadLine(int file,char *buf,int size); /* 0x10004bb0 */
void __cdecl Cos_InitChoreInstances(Chore *pChores,ChoreInstance *pChoreInstances,uint numChores); /* 0x10004c40 */
void __cdecl Cos_FreeCostume(int hCostume); /* 0x10004c70 */
void __cdecl Cos_FreeComponent(int hCostume,ComponentTag *pTag,CosComponent *pComponent); /* 0x10004d70 */
int __cdecl Cos_AllocCostumeSlot(void); /* 0x10004e50 */
uint __cdecl Cos_AllocTagSlot(void); /* 0x10004f30 */
void __cdecl Cos_FreeInstanceData(int instIndex); /* 0x10004f70 */
int __cdecl Cos_AllocInstanceSlot(void); /* 0x10005090 */
int __cdecl Cos_HandleToIndex(int hCostume); /* 0x10005160 */
int __cdecl Cos_IndexToHandle(int index); /* 0x10005180 */
int __cdecl Cos_InstHandleToIndex(int hInst); /* 0x100051a0 */
int __cdecl Cos_InstIndexToHandle(int index); /* 0x100051c0 */
void __cdecl Cos_Terminate(void); /* 0x100051e0 */
int __cdecl Cos_Startup(void); /* 0x10005200 */
void __cdecl Cos_Shutdown(void); /* 0x10005350 */
void * __cdecl Cos_RegisterSaveVerify(void *verify); /* 0x10005590 */

/* ===== cosutil.c ===== */
int __cdecl CosUtil_Write(char *fileName,Costume *pCostume,char *comment); /* 0x10001110 */
CosComponent * __cdecl CosUtil_CompPtrFromHandle(Costume *pCostume,uint compNum); /* 0x10002020 */
Costume * __cdecl CosUtil_PtrFromHandle(int hCostume); /* 0x10002040 */
void * __cdecl CosUtil_RegisterCompNotifier(void *notifier); /* 0x10002060 */
void * __cdecl CosUtil_RegisterBitmapMunger(void *munger); /* 0x10002070 */
int __cdecl CosUtil_DeleteComponent(uint hCostume,uint compNum); /* 0x10002260 */
int __cdecl CosUtil_AdjustComponent(Costume *pCostume,uint compNum); /* 0x100026a0 */
int __cdecl CosUtil_ComponentHasAdjuster(Costume *pCostume,uint compNum); /* 0x10002740 */
int __cdecl CosUtil_AddComponent(int hCostume,char *name,int tagId,int parentData,int parentTagId); /* 0x100027e0 */
int __cdecl CosUtil_AddChore(Costume *pCostume); /* 0x10002880 */
Chore * __cdecl CosUtil_DeleteChore(Costume *pCostume,uint choreNum); /* 0x100028f0 */
Chore * __cdecl CosUtil_SetChoreLength(Costume *pCostume,uint choreNum,uint length); /* 0x100029e0 */
char * __cdecl CosUtil_NameChore(Costume *pCostume,int choreNum,char *name); /* 0x10002ab0 */
int __cdecl CosUtil_DeleteKey(Costume *pCostume,uint choreNum,uint compNum,int time); /* 0x10002b40 */
ChoreKey * __cdecl CosUtil_QueryValueAtTime(Costume *pCostume,uint choreNum,uint compNum,uint time); /* 0x10002c50 */
int __cdecl CosUtil_AddFSKey(Costume *pCostume,uint choreNum,int compNum,uint time,int value); /* 0x10002cf0 */
int __cdecl CosUtil_AddIntKey(Costume *pCostume,uint choreNum,int compNum,uint time,int value); /* 0x10002d50 */
int __cdecl CosUtil_AddFloatKey(Costume *pCostume,uint choreNum,int compNum,uint time,int value); /* 0x10002db0 */
uint __cdecl CosUtil_CountComponents(Costume *pCostume); /* 0x10002e10 */
int __cdecl CosUtil_ComponentInfo(int cos,uint index,int *outTag,undefined4 *outA,undefined4 *outB,int *outKind); /* 0x10002e40 */
uint __cdecl CosUtil_CountChores(Costume *pCostume); /* 0x10002fa0 */
char * __cdecl CosUtil_ChoreName(Costume *pCostume,uint choreNum); /* 0x100030b0 */
uint __cdecl CosUtil_CountTags(void); /* 0x100030f0 */
char * __cdecl CosUtil_TagInfo(uint whichTag,int *outTagId); /* 0x10003100 */

/* ===== chore.c ===== */
void __cdecl Chore_AdvanceTime(Costume *pCostume,CosInstance *pInst,int choreNum,int dt,int hInst); /* 0x100053e0 */
void __cdecl Chore_ApplyKey(int reason,ComponentTag *pTag,int instData,ChoreKey *pKey,int dt,ChoreKey *pKey2, int zero,int user); /* 0x10005530 */

/* ===== msvc.c ===== */
uint * msvc_strncpy(uint *param_1,uint *param_2,uint param_3); /* 0x100055a0 */
char * msvc_strrchr(char *param_1,char param_2); /* 0x100056a0 */
void msvc_fpmath(void); /* 0x100056d0 */
void msvc_fpclear(void); /* 0x100056f0 */
void msvc_cfltcvt_init(void); /* 0x10005700 */
int __cdecl msvc_stricmp(byte *a,byte *b); /* 0x10005740 */
int __cdecl msvc_sscanf(char *param_1,char *param_2,...); /* 0x10005810 */
undefined4 * msvc_memmove(undefined4 *param_1,undefined4 *param_2,uint param_3); /* 0x10005860 */
void msvc_qsort(uint param_1,uint param_2,uint param_3,code *param_4); /* 0x10005ba0 */
void msvc_shortsort(uint param_1,uint param_2,int param_3,code *param_4); /* 0x10005d50 */
void msvc_qsort_swap(undefined1 *param_1,undefined1 *param_2,int param_3); /* 0x10005db0 */
uint msvc_bsearch(undefined4 param_1,uint param_2,uint param_3,int param_4,code *param_5); /* 0x10005de0 */
uint * msvc_strchr(uint *param_1,char param_2); /* 0x10005e90 */
undefined4 __stdcall FUN_10005f50(int a1,int a2,int a3); /* 0x10005f50 */
undefined4 msvc_CPtoLCID(undefined4 param_1); /* 0x10008520 */

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

/* ===== region_10008580.c ===== */
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
