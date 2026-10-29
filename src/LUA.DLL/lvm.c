/* LUA.DLL :: lvm.c
 * functions 0x1000d6d0 .. 0x1000ed10 (22 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x1000d6d0  luaV_closure ---- */
/* Unidentified function of lvm.c (virtual machine) */

void __cdecl luaV_closure(uint param_1)

{
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  
  if (0 < (int)param_1) {
    piVar1 = PTR_1002bf6c + 7;
    puVar2 = luaF_newproto(param_1);
    iVar3 = *piVar1;
    puVar2[3] = *(undefined4 *)(iVar3 + -8);
    puVar2[4] = *(undefined4 *)(iVar3 + -4);
    puVar4 = (undefined4 *)(*piVar1 - (param_1 * 8 + 8));
    puVar5 = puVar2 + 5;
    for (iVar3 = (param_1 & 0x1fffffff) << 1; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar5 = *puVar4;
      puVar4 = puVar4 + 1;
      puVar5 = puVar5 + 1;
    }
    for (iVar3 = 0; iVar3 != 0; iVar3 = iVar3 + -1) {
      *(undefined1 *)puVar5 = *(undefined1 *)puVar4;
      puVar4 = (undefined4 *)((int)puVar4 + 1);
      puVar5 = (undefined4 *)((int)puVar5 + 1);
    }
    iVar3 = *piVar1 + param_1 * -8;
    *piVar1 = iVar3;
    *(undefined4 *)(iVar3 + -8) = 0xfffffff8;
    *(undefined4 **)(*piVar1 + -4) = puVar2;
  }
  return;
}

/* ---- 0x1000d740  luaV_gettable ---- */
/* Unidentified function of lvm.c (virtual machine) */

void luaV_gettable(void)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int *piVar5;
  
  iVar2 = PTR_1002bf6c[7];
  piVar1 = PTR_1002bf6c + 7;
  if (*(int *)(iVar2 + -0x10) == -3) {
    iVar3 = *(int *)(*(int *)(iVar2 + -0xc) + 0x14);
    piVar5 = (int *)(DAT_1002bf48 + iVar3 * -0x90);
    if (*piVar5 == -7) {
      piVar5 = luaH_get(*(int *)(iVar2 + -0xc),(int *)(iVar2 + -8));
      if ((piVar5 != (int *)0x0) && (*piVar5 != -7)) {
        iVar2 = *piVar1;
        *piVar1 = iVar2 + -8;
        *(int *)(iVar2 + -0x10) = *piVar5;
        *(int *)(iVar2 + -0xc) = piVar5[1];
        return;
      }
      piVar5 = (int *)(DAT_1002bf48 + iVar3 * -0x90 + 0x10);
      if (*piVar5 != -7) {
        luaD_callTM(piVar5,2,(void *)0x1);
        return;
      }
      iVar2 = *piVar1;
      *piVar1 = iVar2 + -8;
      *(undefined4 *)(iVar2 + -0x10) = 0xfffffff9;
      return;
    }
  }
  else {
    uVar4 = luaT_effectivetag((uint *)(iVar2 + -0x10));
    piVar5 = (int *)(DAT_1002bf48 + uVar4 * -0x90);
  }
  if (*piVar5 != -7) {
    luaD_callTM(piVar5,2,(void *)0x1);
    return;
  }
  lua_error((byte *)s_indexed_expression_not_a_table_10028180);
  return;
}

/* ---- 0x1000d810  luaV_settable ---- */
/* Unidentified function of lvm.c (virtual machine) */

void __cdecl luaV_settable(uint *param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  uint *puVar4;
  int *piVar5;
  uint uVar6;
  
  piVar1 = PTR_1002bf6c + 7;
  if (param_2 == 0) {
    piVar5 = (int *)0x0;
  }
  else {
    uVar6 = luaT_effectivetag(param_1);
    piVar5 = (int *)(DAT_1002bf48 + uVar6 * -0x90 + 8);
  }
  if ((*param_1 == 0xfffffffd) && ((piVar5 == (int *)0x0 || (*piVar5 == -7)))) {
    piVar5 = luaH_set(param_1[1],(int *)(param_1 + 2));
    iVar2 = *piVar1;
    *piVar5 = *(int *)(iVar2 + -8);
    piVar5[1] = *(int *)(iVar2 + -4);
    *piVar1 = *piVar1 + ((-(uint)(param_2 != 2) & 2) + 1) * -8;
    return;
  }
  if ((piVar5 != (int *)0x0) && (*piVar5 != -7)) {
    if (param_2 == 2) {
      iVar2 = PTR_1002bf6c[7];
      iVar3 = *piVar1;
      *(undefined4 *)(iVar3 + 8) = *(undefined4 *)(iVar2 + -8);
      *(undefined4 *)(iVar3 + 0xc) = *(undefined4 *)(iVar2 + -4);
      puVar4 = (uint *)*piVar1;
      *puVar4 = param_1[2];
      puVar4[1] = param_1[3];
      iVar2 = *piVar1;
      *(uint *)(iVar2 + -8) = *param_1;
      *(uint *)(iVar2 + -4) = param_1[1];
      *piVar1 = *piVar1 + 0x10;
    }
    luaD_callTM(piVar5,3,(void *)0x0);
    return;
  }
  lua_error((byte *)s_indexed_expression_not_a_table_10028180);
  return;
}

/* ---- 0x1000d900  luaV_getglobal ---- */
/* Unidentified function of lvm.c (virtual machine) */

void __cdecl luaV_getglobal(int param_1)

{
  uint *puVar1;
  int *piVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  uint *puVar6;
  
  puVar1 = (uint *)(param_1 + 0x10);
  uVar4 = luaT_effectivetag(puVar1);
  iVar5 = DAT_1002bf48 + uVar4 * -0x90;
  if (*(int *)(iVar5 + 0x18) == -7) {
    puVar6 = (uint *)PTR_1002bf6c[7];
    *puVar6 = *puVar1;
    puVar6[1] = *(uint *)(param_1 + 0x14);
    PTR_1002bf6c[7] = PTR_1002bf6c[7] + 8;
    return;
  }
  piVar2 = PTR_1002bf6c + 7;
  *(undefined4 *)PTR_1002bf6c[7] = 0xfffffffe;
  *(int *)(*piVar2 + 4) = param_1;
  iVar3 = *piVar2;
  puVar6 = (uint *)(iVar3 + 8);
  *piVar2 = (int)puVar6;
  *puVar6 = *puVar1;
  *(undefined4 *)(iVar3 + 0xc) = *(undefined4 *)(param_1 + 0x14);
  *piVar2 = *piVar2 + 8;
  luaD_callTM((undefined4 *)(iVar5 + 0x18),2,(void *)0x1);
  return;
}

/* ---- 0x1000d990  luaV_setglobal ---- */
/* Unidentified function of lvm.c (virtual machine) */

void __cdecl luaV_setglobal(int *param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  uint *puVar4;
  uint uVar5;
  int *piVar6;
  int iVar7;
  undefined4 *puVar8;
  
  uVar5 = luaT_effectivetag((uint *)(param_1 + 4));
  iVar7 = DAT_1002bf48 + uVar5 * -0x90;
  if (*(int *)(iVar7 + 0x20) == -7) {
    PTR_1002bf6c[7] = PTR_1002bf6c[7] + -8;
    lstring__94e0(param_1,(int *)PTR_1002bf6c[7]);
    return;
  }
  piVar6 = PTR_1002bf6c + 7;
  iVar1 = *piVar6;
  uVar2 = *(undefined4 *)(iVar1 + -8);
  uVar3 = *(undefined4 *)(iVar1 + -4);
  *(undefined4 *)(iVar1 + -8) = 0xfffffffe;
  *(int **)(*piVar6 + -4) = param_1;
  puVar4 = (uint *)*piVar6;
  *puVar4 = param_1[4];
  puVar4[1] = param_1[5];
  iVar1 = *piVar6;
  puVar8 = (undefined4 *)(iVar1 + 8);
  *piVar6 = (int)puVar8;
  *puVar8 = uVar2;
  *(undefined4 *)(iVar1 + 0xc) = uVar3;
  *piVar6 = *piVar6 + 8;
  luaD_callTM((undefined4 *)(iVar7 + 0x20),3,(void *)0x0);
  return;
}

/* ---- 0x1000da30  luaV_pack ---- */
/* Unidentified function of lvm.c (virtual machine) */

void __cdecl luaV_pack(int param_1,int param_2,undefined4 *param_3)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  int *piVar4;
  int *piVar5;
  #define local_10 (*(int *)(_frame + (0x20 - 0x10)))
  #define local_c (*(float *)(_frame + (0x20 - 0xc)))
  #define local_4 (*(float *)(_frame + (0x20 - 0x4)))
  
  piVar5 = (int *)(PTR_1002bf6c[8] + param_1 * 8);
  if (param_2 < 0) {
    param_2 = 0;
  }
  puVar3 = luaH_init();
  param_3[1] = puVar3;
  *param_3 = 0xfffffffd;
  param_1 = 0;
  if (0 < param_2) {
    do {
      iVar1 = *piVar5;
      local_c = (float)param_1 - -1.0;
      iVar2 = piVar5[1];
      local_10 = -1;
      piVar4 = luaH_set(param_3[1],&local_10);
      *piVar4 = iVar1;
      param_1 = param_1 + 1;
      piVar5 = piVar5 + 2;
      piVar4[1] = iVar2;
    } while (param_1 < param_2);
  }
  local_10 = -2;
  local_c = PUN(float,luaS_new(&DAT_10026994));
  local_4 = (float)param_2;
  piVar5 = luaH_set(param_3[1],&local_10);
  *piVar5 = -1;
  piVar5[1] = (int)local_4;
  return;
}
#undef local_10
#undef local_4
#undef local_c


/* ---- 0x1000db10  lvm__db10 ---- */
/* Unidentified function of lvm.c (virtual machine) */

void lvm__db10(void)

{
  void *pvVar1;
  
  if (PTR_1002bf84 != (void *)0x0) {
    do {
      pvVar1 = *(void **)((int)PTR_1002bf84 + 0xc);
      luaM_free(PTR_1002bf84);
      PTR_1002bf84 = pvVar1;
    } while (pvVar1 != (void *)0x0);
    PTR_1002bf84 = (void *)0x0;
  }
  return;
}

/* ---- 0x1000db40  lvm__db40 ---- */
/* Unidentified function of lvm.c (virtual machine) */

undefined4 __thiscall lvm__db40(void *this,int a1)

{
  int iVar1;
  
  iVar1 = a1;
  if (*(void **)((int)this + 0xc) != (void *)0x0) {
    lvm__db40(*(void **)((int)this + 0xc),a1);
  }
  (*(code *)iVar1)(this,4);
  (*(code *)iVar1)((int *)((int)this + 4),4);
  (*(code *)iVar1)((int)this + 8,4);
  (*(code *)iVar1)((int)this + 0x10,4);
  (*(code *)iVar1)((int)this + 0x14,4);
  (*(code *)iVar1)((int)this + 0x18,4);
  a1 = *(int *)((int)this + 0x20) - *(int *)(*(int *)((int)this + 4) + 0x10);
  (*(code *)iVar1)(&a1,4);
  (*(code *)iVar1)((int)this + 0x24,4);
  return 0;
}

/* ---- 0x1000dbd0  lvm__dbd0 ---- */
/* Unidentified function of lvm.c (virtual machine) */

undefined4 __thiscall lvm__dbd0(void *this,int a1,int a2,int a3)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  void *pvVar2;
  undefined4 *unaff_FS_OFFSET = (undefined4 *)TEB_BASE();
  #define local_14 (*(undefined4 *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(undefined4 *)(_frame + (0x30 - 0x10)))
  #define uStack_c (*(undefined4 *)(_frame + (0x30 - 0xc)))
  #define pcStack_8 (*(code **)(_frame + (0x30 - 0x8)))
  #define local_4 (*(undefined4 *)(_frame + (0x30 - 0x4)))
  
  iVar1 = a3;
  uStack_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  pcStack_8 = FUN_1002203b;
  *unaff_FS_OFFSET = &uStack_c;
  if (a3 != 0) {
    pvVar2 = lvm__dd10(0x30);
    local_4 = 0;
    if (pvVar2 == (void *)0x0) {
      pvVar2 = (void *)0x0;
    }
    else {
      pvVar2 = (void *)lvm__ddb0(pvVar2,0,0,0);
    }
    local_4 = 0xffffffff;
    *(void **)((int)this + 0xc) = pvVar2;
    lvm__dbd0(pvVar2,a1,a2,iVar1 + -1);
  }
  *(int *)((int)this + 0x1c) = a2;
  local_14 = 0xfffffff8;
  (*(code *)a1)(&local_10,4);
  lstate__78b0((int)&local_14);
  *(undefined4 *)this = local_10;
  local_14 = 0xfffffffc;
  (*(code *)a1)(&local_10,4);
  lstate__78b0((int)&local_14);
  *(undefined4 *)((int)this + 4) = local_10;
  (*(code *)a1)((int)this + 8,4);
  (*(code *)a1)((int)this + 0x10,4);
  (*(code *)a1)((int)this + 0x14,4);
  (*(code *)a1)((int)this + 0x18,4);
  (*(code *)a1)(&a3,4);
  *(int *)((int)this + 0x20) = *(int *)(*(int *)((int)this + 4) + 0x10) + a3;
  (*(code *)a1)((int)this + 0x24,4);
  *(undefined4 *)((int)this + 0x2c) = *(undefined4 *)(*(int *)((int)this + 4) + 8);
  *unaff_FS_OFFSET = uStack_c;
  return 0;
}
#undef local_10
#undef local_14
#undef local_4
#undef pcStack_8
#undef uStack_c


/* ---- 0x1000dd10  lvm__dd10 ---- */
/* Unidentified function of lvm.c (virtual machine) */

void * __cdecl lvm__dd10(int size)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  void *pvVar1;
  int iVar2;
  undefined4 *unaff_FS_OFFSET = (undefined4 *)TEB_BASE();
  #define local_c (*(undefined4 *)(_frame + (0x20 - 0xc)))
  #define pcStack_8 (*(code **)(_frame + (0x20 - 0x8)))
  #define local_4 (*(undefined4 *)(_frame + (0x20 - 0x4)))
  
  pcStack_8 = FUN_1002205b;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  pvVar1 = PTR_1002bf84;
  if (PTR_1002bf84 == (void *)0x0) {
    iVar2 = 10;
    do {
      local_4 = 0xffffffff;
      pvVar1 = luaM_malloc(0x30);
      local_4 = 0;
      if (pvVar1 == (void *)0x0) {
        pvVar1 = (void *)0x0;
      }
      else {
        pvVar1 = (void *)lvm__ddb0(pvVar1,(int)PTR_1002bf84,0,0);
      }
      iVar2 = iVar2 + -1;
      PTR_1002bf84 = pvVar1;
    } while (iVar2 != 0);
  }
  PTR_1002bf84 = *(void **)((int)pvVar1 + 0xc);
  *unaff_FS_OFFSET = local_c;
  return pvVar1;
}
#undef local_4
#undef local_c
#undef pcStack_8


/* ---- 0x1000dd90  lvm__dd90 ---- */
/* Unidentified function of lvm.c (virtual machine) */

void __cdecl lvm__dd90(int param_1)

{
  *(void **)(param_1 + 0xc) = PTR_1002bf84;
  PTR_1002bf84 = (void *)param_1;
  return;
}

/* ---- 0x1000ddb0  lvm__ddb0 ---- */
/* Unidentified function of lvm.c (virtual machine) */

int __thiscall lvm__ddb0(void *this,int a1,int a2,int a3)

{
  *(int *)((int)this + 0xc) = a1;
  *(int *)((int)this + 0x10) = a2;
  *(undefined4 *)((int)this + 0x28) = 0;
  *(int *)((int)this + 0x14) = a3;
  *(undefined4 *)((int)this + 0x18) = 0;
  return (int)this;
}

/* ---- 0x1000dde0  lvm__dde0 ---- */
/* Unidentified function of lvm.c (virtual machine) */

undefined4 __fastcall lvm__dde0(int param_1)

{
  return *(undefined4 *)(param_1 + 0x24);
}

/* ---- 0x1000ddf0  lvm__ddf0 ---- */
/* Unidentified function of lvm.c (virtual machine) */

int __thiscall lvm__ddf0(void *this,int a1,int a2,int a3)

{
  int iVar1;
  
  *(int *)this = a1;
  *(int *)((int)this + 4) = a2;
  *(int *)((int)this + 8) = a3;
  *(undefined4 *)((int)this + 0x20) = *(undefined4 *)(a2 + 0x10);
  iVar1 = *(int *)(a2 + 8);
  *(int *)((int)this + 0x2c) = iVar1;
  *(int **)((int)this + 0x1c) = PTR_1002bf6c + 7;
  return iVar1;
}

/* ---- 0x1000de20  lvm__de20 ---- */
/* Unidentified function of lvm.c (virtual machine) */

void __fastcall lvm__de20(int param_1)

{
  *(undefined4 *)(param_1 + 0x28) = 0;
  return;
}

/* ---- 0x1000de30  lvm__de30 ---- */
/* Unidentified function of lvm.c (virtual machine) */

int __fastcall lvm__de30(int *param_1)

{
  byte bVar1;
  int iVar2;
  
  if (param_1[6] == 0) {
    lvm__de20((int)param_1);
    if (lua_callhook != 0) {
      luaD_callHook(param_1[2],param_1[1],0);
    }
    bVar1 = *(byte *)param_1[8];
    param_1[8] = (int)((byte *)param_1[8] + 1);
    luaD_checkstack(bVar1 + 5);
    bVar1 = *(byte *)param_1[8];
    if (bVar1 < 0x40) {
      param_1[8] = (int)((byte *)param_1[8] + 1);
      luaD_adjusttop(param_1[2] + (uint)bVar1);
      param_1[6] = 1;
      iVar2 = luaV_execute(param_1);
      return iVar2;
    }
    lgc__5300();
    bVar1 = *(byte *)param_1[8];
    param_1[8] = (int)((byte *)param_1[8] + 1);
    luaV_adjust_varargs(param_1[2] + -0x40 + (uint)bVar1);
    param_1[6] = 1;
  }
  iVar2 = luaV_execute(param_1);
  return iVar2;
}

/* ---- 0x1000dee0  luaV_adjust_varargs ---- */
/* Unidentified function of lvm.c (virtual machine) */

void __cdecl luaV_adjust_varargs(int param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 *puVar1;
  #define local_8 (*(undefined4 *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(undefined4 *)(_frame + (0x20 - 0x4)))
  
  luaV_pack(param_1,(PTR_1002bf6c[7] - PTR_1002bf6c[8] >> 3) - param_1,&local_8);
  luaD_adjusttop(param_1);
  puVar1 = (undefined4 *)PTR_1002bf6c[7];
  *puVar1 = local_8;
  puVar1[1] = local_4;
  PTR_1002bf6c[7] = PTR_1002bf6c[7] + 8;
  return;
}
#undef local_4
#undef local_8


/* ---- 0x1000df40  luaV_execute ---- */
/* lvm.c: opcode interpreter loop */

int __fastcall luaV_execute(int *param_1)

{
  byte bVar1;
  byte *pbVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  bool bVar7;
  byte *pbVar8;
  int *piVar9;
  undefined4 *puVar10;
  undefined3 extraout_var;
  int iVar11;
  undefined4 uVar12;
  int iVar13;
  int *piVar14;
  uint uVar15;
  
  if ((PTR_1002bf6c[6] != 0) && (PTR_1002bf6c[2] == 0)) {
    printf(s_WARNING__Lua_nesting_level_now___1002821c);
  }
  PTR_1002bf6c[6] = PTR_1002bf6c[6] + 1;
switchD_1000dfaf_default:
  iVar13 = param_1[10];
  param_1[10] = iVar13 + 1;
  if (9999999 < iVar13) {
    lua_error((byte *)s_WARNING__Killing_Lua_script_that_100281c4);
  }
  pbVar2 = (byte *)param_1[8];
  bVar1 = *pbVar2;
  pbVar8 = pbVar2 + 1;
  param_1[9] = (uint)bVar1;
  param_1[8] = (int)pbVar8;
  switch((uint)bVar1) {
  case 0:
    goto switchD_1000dfaf_caseD_0;
  case 1:
    param_1[9] = (uint)*pbVar8;
    param_1[8] = (int)(pbVar2 + 2);
    do {
      **(undefined4 **)param_1[7] = 0xfffffff9;
      *(int *)param_1[7] = *(int *)param_1[7] + 8;
      iVar13 = param_1[9];
      param_1[9] = iVar13 + -1;
    } while (iVar13 != 0);
    goto switchD_1000dfaf_default;
  case 2:
    **(undefined4 **)param_1[7] = 0xfffffff9;
    *(int *)param_1[7] = *(int *)param_1[7] + 8;
    goto switchD_1000dfaf_default;
  case 3:
    param_1[9] = (uint)*pbVar8;
    param_1[8] = (int)(pbVar2 + 2);
    break;
  case 4:
  case 5:
  case 6:
    param_1[9] = param_1[9] + -4;
    break;
  case 7:
    param_1[8] = (int)(pbVar2 + 3);
    param_1[9] = (uint)pbVar2[1] + (uint)pbVar2[2] * 0x100;
    break;
  case 8:
    param_1[9] = (uint)*pbVar8;
    param_1[8] = (int)(pbVar2 + 2);
    goto LAB_1000e1a7;
  case 9:
  case 10:
  case 0xb:
  case 0xc:
  case 0xd:
  case 0xe:
  case 0xf:
  case 0x10:
    param_1[9] = param_1[9] + -9;
    goto LAB_1000e1a7;
  case 0x11:
    param_1[8] = (int)(pbVar2 + 3);
    param_1[9] = (uint)pbVar2[1] + (uint)pbVar2[2] * 0x100;
LAB_1000e1a7:
    iVar13 = param_1[9];
    iVar11 = param_1[0xb];
    puVar10 = *(undefined4 **)param_1[7];
    *puVar10 = *(undefined4 *)(iVar11 + iVar13 * 8);
    puVar10[1] = *(undefined4 *)(iVar11 + 4 + iVar13 * 8);
    *(int *)param_1[7] = *(int *)param_1[7] + 8;
    goto switchD_1000dfaf_default;
  case 0x12:
    param_1[9] = (uint)*pbVar8;
    param_1[8] = (int)(pbVar2 + 2);
    goto LAB_1000e1da;
  case 0x13:
  case 0x14:
    param_1[9] = param_1[9] + -0x13;
LAB_1000e1da:
    iVar13 = param_1[9];
    iVar11 = *param_1;
    puVar10 = *(undefined4 **)param_1[7];
    *puVar10 = *(undefined4 *)(iVar11 + 0x14 + iVar13 * 8);
    puVar10[1] = *(undefined4 *)(iVar11 + 0x18 + iVar13 * 8);
    *(int *)param_1[7] = *(int *)param_1[7] + 8;
    goto switchD_1000dfaf_default;
  case 0x15:
    param_1[9] = (uint)*pbVar8;
    param_1[8] = (int)(pbVar2 + 2);
    goto LAB_1000e058;
  case 0x16:
  case 0x17:
  case 0x18:
  case 0x19:
  case 0x1a:
  case 0x1b:
  case 0x1c:
  case 0x1d:
    param_1[9] = param_1[9] + -0x16;
LAB_1000e058:
    iVar13 = param_1[2];
    iVar11 = param_1[9];
    iVar4 = ((int *)param_1[7])[1];
    puVar10 = *(undefined4 **)param_1[7];
    *puVar10 = *(undefined4 *)(iVar4 + (iVar13 + iVar11) * 8);
    puVar10[1] = *(undefined4 *)(iVar4 + 4 + (iVar13 + iVar11) * 8);
    *(int *)param_1[7] = *(int *)param_1[7] + 8;
    goto switchD_1000dfaf_default;
  case 0x1e:
    param_1[9] = (uint)*pbVar8;
    param_1[8] = (int)(pbVar2 + 2);
    goto LAB_1000e0aa;
  case 0x1f:
  case 0x20:
  case 0x21:
  case 0x22:
  case 0x23:
  case 0x24:
  case 0x25:
  case 0x26:
    param_1[9] = param_1[9] + -0x1f;
    goto LAB_1000e0aa;
  case 0x27:
    param_1[8] = (int)(pbVar2 + 3);
    param_1[9] = (uint)pbVar2[1] + (uint)pbVar2[2] * 0x100;
LAB_1000e0aa:
    luaV_getglobal(*(int *)(param_1[0xb] + 4 + param_1[9] * 8));
    goto switchD_1000dfaf_default;
  case 0x28:
    goto switchD_1000dfaf_caseD_28;
  case 0x29:
    param_1[9] = (uint)*pbVar8;
    param_1[8] = (int)(pbVar2 + 2);
    goto LAB_1000e0ed;
  case 0x2a:
  case 0x2b:
  case 0x2c:
  case 0x2d:
  case 0x2e:
  case 0x2f:
  case 0x30:
  case 0x31:
    param_1[9] = param_1[9] + -0x2a;
    goto LAB_1000e0ed;
  case 0x32:
    param_1[8] = (int)(pbVar2 + 3);
    param_1[9] = (uint)pbVar2[1] + (uint)pbVar2[2] * 0x100;
LAB_1000e0ed:
    iVar13 = param_1[9];
    iVar11 = param_1[0xb];
    puVar10 = *(undefined4 **)param_1[7];
    *puVar10 = *(undefined4 *)(iVar11 + iVar13 * 8);
    puVar10[1] = *(undefined4 *)(iVar11 + 4 + iVar13 * 8);
    *(int *)param_1[7] = *(int *)param_1[7] + 8;
switchD_1000dfaf_caseD_28:
    luaV_gettable();
    goto switchD_1000dfaf_default;
  case 0x33:
    param_1[9] = (uint)*pbVar8;
    param_1[8] = (int)(pbVar2 + 2);
    goto LAB_1000e13f;
  case 0x34:
  case 0x35:
  case 0x36:
  case 0x37:
  case 0x38:
  case 0x39:
  case 0x3a:
  case 0x3b:
    param_1[9] = param_1[9] + -0x34;
    goto LAB_1000e13f;
  case 0x3c:
    param_1[8] = (int)(pbVar2 + 3);
    param_1[9] = (uint)pbVar2[1] + (uint)pbVar2[2] * 0x100;
LAB_1000e13f:
    iVar13 = param_1[9];
    puVar10 = *(undefined4 **)param_1[7];
    iVar11 = param_1[0xb];
    uVar12 = puVar10[-2];
    uVar3 = puVar10[-1];
    *puVar10 = *(undefined4 *)(iVar11 + iVar13 * 8);
    puVar10[1] = *(undefined4 *)(iVar11 + 4 + iVar13 * 8);
    *(int *)param_1[7] = *(int *)param_1[7] + 8;
    luaV_gettable();
    puVar10 = *(undefined4 **)param_1[7];
    *puVar10 = uVar12;
    puVar10[1] = uVar3;
    *(int *)param_1[7] = *(int *)param_1[7] + 8;
    goto switchD_1000dfaf_default;
  case 0x3d:
    param_1[9] = (uint)*pbVar8;
    param_1[8] = (int)(pbVar2 + 2);
    goto LAB_1000e420;
  case 0x3e:
  case 0x3f:
    param_1[9] = param_1[9] + -0x3e;
    goto LAB_1000e420;
  case 0x40:
    param_1[8] = (int)(pbVar2 + 3);
    param_1[9] = (uint)pbVar2[1] + (uint)pbVar2[2] * 0x100;
LAB_1000e420:
    lgc__5300();
    puVar10 = luaH_init();
    *(undefined4 **)(*(int *)param_1[7] + 4) = puVar10;
    **(undefined4 **)param_1[7] = 0xfffffffd;
    *(int *)param_1[7] = *(int *)param_1[7] + 8;
    goto switchD_1000dfaf_default;
  case 0x41:
    param_1[9] = (uint)*pbVar8;
    param_1[8] = (int)(pbVar2 + 2);
    goto LAB_1000e20d;
  case 0x42:
  case 0x43:
  case 0x44:
  case 0x45:
  case 0x46:
  case 0x47:
  case 0x48:
  case 0x49:
    param_1[9] = param_1[9] + -0x42;
LAB_1000e20d:
    *(int *)param_1[7] = *(int *)param_1[7] + -8;
    iVar13 = param_1[2];
    iVar11 = param_1[9];
    puVar10 = *(undefined4 **)param_1[7];
    iVar4 = ((int *)param_1[7])[1];
    *(undefined4 *)(iVar4 + (iVar13 + iVar11) * 8) = *puVar10;
    *(undefined4 *)(iVar4 + 4 + (iVar13 + iVar11) * 8) = puVar10[1];
    goto switchD_1000dfaf_default;
  case 0x4a:
    param_1[9] = (uint)*pbVar8;
    param_1[8] = (int)(pbVar2 + 2);
    goto LAB_1000e263;
  case 0x4b:
  case 0x4c:
  case 0x4d:
  case 0x4e:
  case 0x4f:
  case 0x50:
  case 0x51:
  case 0x52:
    param_1[9] = param_1[9] + -0x4b;
    goto LAB_1000e263;
  case 0x53:
    param_1[8] = (int)(pbVar2 + 3);
    param_1[9] = (uint)pbVar2[1] + (uint)pbVar2[2] * 0x100;
LAB_1000e263:
    luaV_setglobal(*(int **)(param_1[0xb] + 4 + param_1[9] * 8));
    goto switchD_1000dfaf_default;
  case 0x54:
    luaV_settable((uint *)(*(int *)param_1[7] + -0x18),1);
    goto switchD_1000dfaf_default;
  case 0x55:
    bVar1 = *pbVar8;
    iVar13 = *(int *)param_1[7];
    param_1[8] = (int)(pbVar2 + 2);
    luaV_settable((uint *)(iVar13 - ((uint)bVar1 * 8 + 0x18)),2);
    goto switchD_1000dfaf_default;
  case 0x56:
    param_1[9] = (uint)*pbVar8 << 6;
    param_1[8] = (int)(pbVar2 + 2);
    goto LAB_1000e2ed;
  case 0x57:
    param_1[9] = 0;
    goto LAB_1000e2ed;
  case 0x58:
    param_1[8] = (int)(pbVar2 + 3);
    param_1[9] = ((uint)pbVar2[1] + (uint)pbVar2[2] * 0x100) * 0x40;
LAB_1000e2ed:
    uVar15 = (uint)*(byte *)param_1[8];
    param_1[8] = (int)((byte *)param_1[8] + 1);
    iVar11 = *(int *)param_1[7];
    iVar13 = uVar15 * 8;
    for (; uVar15 != 0; uVar15 = uVar15 - 1) {
      **(undefined4 **)param_1[7] = 0xffffffff;
      *(float *)(*(int *)param_1[7] + 4) = (float)(int)uVar15 + (float)param_1[9];
      piVar9 = *(int **)param_1[7];
      iVar4 = piVar9[-2];
      iVar5 = piVar9[-1];
      piVar9 = luaH_set(*(int *)((iVar11 - (iVar13 + 8)) + 4),piVar9);
      *piVar9 = iVar4;
      piVar9[1] = iVar5;
      *(int *)param_1[7] = *(int *)param_1[7] + -8;
    }
    goto switchD_1000dfaf_default;
  case 0x59:
    param_1[9] = (uint)*pbVar8;
    param_1[8] = (int)(pbVar2 + 2);
    goto LAB_1000e37f;
  case 0x5a:
    param_1[9] = 0;
LAB_1000e37f:
    iVar13 = param_1[9];
    iVar11 = *(int *)param_1[7];
    do {
      iVar4 = *(int *)param_1[7];
      iVar5 = *(int *)(iVar4 + -8);
      iVar6 = *(int *)(iVar4 + -4);
      piVar9 = luaH_set(*(int *)(iVar11 + iVar13 * -0x10 + -0x14),(int *)(iVar4 + -0x10));
      *piVar9 = iVar5;
      piVar9[1] = iVar6;
      *(int *)param_1[7] = *(int *)param_1[7] + -0x10;
      iVar4 = param_1[9];
      param_1[9] = iVar4 + -1;
    } while (iVar4 != 0);
    goto switchD_1000dfaf_default;
  case 0x5b:
  case 0x5c:
    bVar7 = luaO_equalObj((int *)(*(int *)param_1[7] + -0x10),(int *)(*(int *)param_1[7] + -8));
    uVar15 = CONCAT31(extraout_var,bVar7);
    *(int *)param_1[7] = *(int *)param_1[7] + -8;
    if (param_1[9] == 0x5c) {
      uVar15 = (uint)(uVar15 == 0);
    }
    *(uint *)(*(int *)param_1[7] + -8) = (-(uint)(uVar15 != 0) & 6) - 7;
    *(undefined4 *)(*(int *)param_1[7] + -4) = 0x3f800000;
    goto switchD_1000dfaf_default;
  case 0x5d:
    luaV_comparison(0xffffffff,0xfffffff9,0xfffffff9,0xb);
    goto switchD_1000dfaf_default;
  case 0x5e:
    luaV_comparison(0xffffffff,0xffffffff,0xfffffff9,0xc);
    goto switchD_1000dfaf_default;
  case 0x5f:
    luaV_comparison(0xfffffff9,0xfffffff9,0xffffffff,0xd);
    goto switchD_1000dfaf_default;
  case 0x60:
    luaV_comparison(0xfffffff9,0xffffffff,0xffffffff,0xe);
    goto switchD_1000dfaf_default;
  case 0x61:
    iVar13 = *(int *)param_1[7];
    if (((*(int *)(iVar13 + -8) == -1) ||
        (iVar11 = luaU_str2number((int *)(iVar13 + -8)), iVar11 == 0)) &&
       ((*(int *)(iVar13 + -0x10) == -1 ||
        (iVar11 = luaU_str2number((int *)(iVar13 + -0x10)), iVar11 == 0)))) {
      *(float *)(iVar13 + -0xc) = *(float *)(iVar13 + -4) + *(float *)(iVar13 + -0xc);
      *(int *)param_1[7] = *(int *)param_1[7] + -8;
    }
    else {
      luaV_call_arith(5);
    }
    goto switchD_1000dfaf_default;
  case 0x62:
    iVar13 = *(int *)param_1[7];
    if (((*(int *)(iVar13 + -8) == -1) ||
        (iVar11 = luaU_str2number((int *)(iVar13 + -8)), iVar11 == 0)) &&
       ((*(int *)(iVar13 + -0x10) == -1 ||
        (iVar11 = luaU_str2number((int *)(iVar13 + -0x10)), iVar11 == 0)))) {
      *(float *)(iVar13 + -0xc) = *(float *)(iVar13 + -0xc) - *(float *)(iVar13 + -4);
      *(int *)param_1[7] = *(int *)param_1[7] + -8;
    }
    else {
      luaV_call_arith(6);
    }
    goto switchD_1000dfaf_default;
  case 99:
    iVar13 = *(int *)param_1[7];
    if (((*(int *)(iVar13 + -8) == -1) ||
        (iVar11 = luaU_str2number((int *)(iVar13 + -8)), iVar11 == 0)) &&
       ((*(int *)(iVar13 + -0x10) == -1 ||
        (iVar11 = luaU_str2number((int *)(iVar13 + -0x10)), iVar11 == 0)))) {
      *(float *)(iVar13 + -0xc) = *(float *)(iVar13 + -4) * *(float *)(iVar13 + -0xc);
      *(int *)param_1[7] = *(int *)param_1[7] + -8;
    }
    else {
      luaV_call_arith(7);
    }
    goto switchD_1000dfaf_default;
  case 100:
    iVar13 = *(int *)param_1[7];
    if (((*(int *)(iVar13 + -8) == -1) ||
        (iVar11 = luaU_str2number((int *)(iVar13 + -8)), iVar11 == 0)) &&
       ((*(int *)(iVar13 + -0x10) == -1 ||
        (iVar11 = luaU_str2number((int *)(iVar13 + -0x10)), iVar11 == 0)))) {
      *(float *)(iVar13 + -0xc) = *(float *)(iVar13 + -0xc) / *(float *)(iVar13 + -4);
      *(int *)param_1[7] = *(int *)param_1[7] + -8;
    }
    else {
      luaV_call_arith(8);
    }
    goto switchD_1000dfaf_default;
  case 0x65:
    luaV_call_arith(9);
    goto switchD_1000dfaf_default;
  case 0x66:
    iVar13 = *(int *)param_1[7];
    if (((*(int *)(iVar13 + -0x10) == -2) ||
        (iVar11 = lundump__d620((int *)(iVar13 + -0x10)), iVar11 == 0)) &&
       ((*(int *)(iVar13 + -8) == -2 || (iVar11 = lundump__d620((int *)(iVar13 + -8)), iVar11 == 0))
       )) {
      uVar12 = luaV_strconc((char *)(*(int *)(iVar13 + -0xc) + 0x18),
                            (char *)(*(int *)(iVar13 + -4) + 0x18));
      *(undefined4 *)(iVar13 + -0xc) = uVar12;
      *(int *)param_1[7] = *(int *)param_1[7] + -8;
      lgc__5300();
    }
    else {
      luaV_call_binTM(0xf,s_unexpected_type_for_concatenatio_100281a0);
      lgc__5300();
    }
    goto switchD_1000dfaf_default;
  case 0x67:
    if ((*(int *)(*(int *)param_1[7] + -8) == -1) ||
       (iVar13 = luaU_str2number((int *)(*(int *)param_1[7] + -8)), iVar13 == 0)) {
      *(float *)(*(int *)param_1[7] + -4) = -*(float *)(*(int *)param_1[7] + -4);
    }
    else {
      **(undefined4 **)param_1[7] = 0xfffffff9;
      *(int *)param_1[7] = *(int *)param_1[7] + 8;
      luaV_call_arith(10);
    }
    goto switchD_1000dfaf_default;
  case 0x68:
    *(uint *)(*(int *)param_1[7] + -8) =
         (-(uint)(*(int *)(*(int *)param_1[7] + -8) != -7) & 0xfffffffa) - 1;
    *(undefined4 *)(*(int *)param_1[7] + -4) = 0x3f800000;
    goto switchD_1000dfaf_default;
  case 0x69:
    param_1[9] = (uint)*pbVar8;
    param_1[8] = (int)(pbVar2 + 2);
    goto LAB_1000e756;
  case 0x6a:
    param_1[8] = (int)(pbVar2 + 3);
    param_1[9] = (uint)pbVar2[1] + (uint)pbVar2[2] * 0x100;
LAB_1000e756:
    piVar9 = (int *)param_1[7];
    piVar14 = (int *)(*piVar9 + -8);
    if (*piVar14 == -7) {
LAB_1000e7b5:
      *piVar9 = (int)piVar14;
    }
    else {
      param_1[8] = param_1[8] + param_1[9];
    }
    goto switchD_1000dfaf_default;
  case 0x6b:
    param_1[9] = (uint)*pbVar8;
    param_1[8] = (int)(pbVar2 + 2);
    goto LAB_1000e798;
  case 0x6c:
    param_1[8] = (int)(pbVar2 + 3);
    param_1[9] = (uint)pbVar2[1] + (uint)pbVar2[2] * 0x100;
LAB_1000e798:
    piVar9 = (int *)param_1[7];
    piVar14 = (int *)(*piVar9 + -8);
    if (*piVar14 != -7) goto LAB_1000e7b5;
    param_1[8] = param_1[8] + param_1[9];
    goto switchD_1000dfaf_default;
  case 0x6d:
    bVar1 = *pbVar8;
    param_1[8] = (int)(pbVar2 + 2);
    param_1[9] = (uint)bVar1;
    param_1[8] = (int)(pbVar2 + 2 + bVar1);
    goto switchD_1000dfaf_default;
  case 0x6e:
    param_1[8] = (int)(pbVar2 + 3);
    iVar13 = (uint)pbVar2[1] + (uint)pbVar2[2] * 0x100;
    param_1[9] = iVar13;
    param_1[8] = (int)(pbVar2 + 3 + iVar13);
    goto switchD_1000dfaf_default;
  case 0x6f:
    param_1[9] = (uint)*pbVar8;
    param_1[8] = (int)(pbVar2 + 2);
    goto LAB_1000e81c;
  case 0x70:
    param_1[8] = (int)(pbVar2 + 3);
    param_1[9] = (uint)pbVar2[1] + (uint)pbVar2[2] * 0x100;
LAB_1000e81c:
    *(int *)param_1[7] = *(int *)param_1[7] + -8;
    if (**(int **)param_1[7] == -7) {
      param_1[8] = param_1[8] + param_1[9];
    }
    goto switchD_1000dfaf_default;
  case 0x71:
    param_1[9] = (uint)*pbVar8;
    param_1[8] = (int)(pbVar2 + 2);
    goto LAB_1000e869;
  case 0x72:
    param_1[8] = (int)(pbVar2 + 3);
    param_1[9] = (uint)pbVar2[1] + (uint)pbVar2[2] * 0x100;
LAB_1000e869:
    *(int *)param_1[7] = *(int *)param_1[7] + -8;
    if (**(int **)param_1[7] != -7) {
      param_1[8] = param_1[8] - param_1[9];
    }
    goto switchD_1000dfaf_default;
  case 0x73:
    param_1[9] = (uint)*pbVar8;
    param_1[8] = (int)(pbVar2 + 2);
    goto LAB_1000e8b6;
  case 0x74:
    param_1[8] = (int)(pbVar2 + 3);
    param_1[9] = (uint)pbVar2[1] + (uint)pbVar2[2] * 0x100;
LAB_1000e8b6:
    *(int *)param_1[7] = *(int *)param_1[7] + -8;
    if (**(int **)param_1[7] == -7) {
      param_1[8] = param_1[8] - param_1[9];
    }
    goto switchD_1000dfaf_default;
  case 0x75:
    param_1[9] = (uint)*pbVar8;
    param_1[8] = (int)(pbVar2 + 2);
    goto LAB_1000e8ef;
  case 0x76:
  case 0x77:
    param_1[9] = param_1[9] + -0x76;
LAB_1000e8ef:
    luaV_closure(param_1[9]);
    lgc__5300();
    goto switchD_1000dfaf_default;
  case 0x78:
    param_1[9] = (uint)*pbVar8;
    param_1[8] = (int)(pbVar2 + 2);
    goto LAB_1000e9a0;
  case 0x79:
  case 0x7a:
    param_1[9] = param_1[9] + -0x79;
LAB_1000e9a0:
    iVar13 = *(int *)param_1[7];
    iVar11 = ((int *)param_1[7])[1];
    bVar1 = *(byte *)param_1[8];
    param_1[8] = (int)((byte *)param_1[8] + 1);
    iVar13 = -((iVar13 - iVar11 >> 3) - (uint)bVar1);
    goto LAB_1000e9fd;
  case 0x7b:
    goto switchD_1000dfaf_caseD_7b;
  case 0x7c:
    param_1[9] = (uint)*pbVar8;
    param_1[8] = (int)(pbVar2 + 2);
    goto LAB_1000e92a;
  case 0x7d:
    param_1[8] = (int)(pbVar2 + 3);
    param_1[9] = (uint)pbVar2[1] + (uint)pbVar2[2] * 0x100;
LAB_1000e92a:
    iVar13 = ((int *)param_1[7])[1];
    if (*(int *)(iVar13 + -8 + param_1[2] * 8) != -0xc) {
      luaD_openstack((*(int *)param_1[7] - iVar13 >> 3) - param_1[2]);
      iVar13 = param_1[2];
      param_1[2] = iVar13 + 1;
      *(undefined4 *)(*(int *)(param_1[7] + 4) + -8 + (iVar13 + 1) * 8) = 0xfffffff4;
    }
    *(int *)(*(int *)(param_1[7] + 4) + -4 + param_1[2] * 8) = param_1[9];
    if (lua_linehook != 0) {
      luaD_lineHook(param_1[9]);
    }
    goto switchD_1000dfaf_default;
  case 0x7e:
    param_1[9] = (uint)*pbVar8;
    param_1[8] = (int)(pbVar2 + 2);
    goto LAB_1000e3dc;
  case 0x7f:
  case 0x80:
    param_1[9] = param_1[9] + -0x7f;
LAB_1000e3dc:
    *(int *)param_1[7] = *(int *)param_1[7] + (-1 - param_1[9]) * 8;
  default:
    goto switchD_1000dfaf_default;
  }
  **(undefined4 **)param_1[7] = 0xffffffff;
  *(float *)(*(int *)param_1[7] + 4) = (float)param_1[9];
  *(int *)param_1[7] = *(int *)param_1[7] + 8;
  goto switchD_1000dfaf_default;
switchD_1000dfaf_caseD_0:
  *(int *)param_1[7] = ((int *)param_1[7])[1] + param_1[2] * 8;
switchD_1000dfaf_caseD_7b:
  if (lua_callhook != 0) {
    luaD_callHook(param_1[2],0,1);
  }
  if (param_1[9] == 0x7b) {
    uVar15 = (uint)*(byte *)param_1[8];
  }
  else {
    uVar15 = 0;
  }
  iVar13 = param_1[2] + uVar15;
LAB_1000e9fd:
  PTR_1002bf6c[6] = PTR_1002bf6c[6] + -1;
  return iVar13;
}

/* ---- 0x1000ebc0  luaV_strconc ---- */
/* lvm.c: string concatenation */

undefined4 __cdecl luaV_strconc(char *param_1,char *param_2)

{
  char cVar1;
  byte *pbVar2;
  undefined4 uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  byte *pbVar7;
  char *pcVar8;
  byte *pbVar9;
  
  uVar4 = 0xffffffff;
  pcVar8 = param_1;
  do {
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    cVar1 = *pcVar8;
    pcVar8 = pcVar8 + 1;
  } while (cVar1 != '\0');
  uVar5 = 0xffffffff;
  pcVar8 = param_2;
  do {
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    cVar1 = *pcVar8;
    pcVar8 = pcVar8 + 1;
  } while (cVar1 != '\0');
  pbVar2 = (byte *)luaL_openspace(~uVar5 + (~uVar4 - 1));
  uVar5 = 0xffffffff;
  do {
    pcVar8 = param_1;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar8 = param_1 + 1;
    cVar1 = *param_1;
    param_1 = pcVar8;
  } while (cVar1 != '\0');
  uVar5 = ~uVar5;
  pbVar7 = (byte *)(pcVar8 + -uVar5);
  pbVar9 = pbVar2;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pbVar9 = *(undefined4 *)pbVar7;
    pbVar7 = pbVar7 + 4;
    pbVar9 = pbVar9 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pbVar9 = *pbVar7;
    pbVar7 = pbVar7 + 1;
    pbVar9 = pbVar9 + 1;
  }
  uVar5 = 0xffffffff;
  do {
    pcVar8 = param_2;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar8 = param_2 + 1;
    cVar1 = *param_2;
    param_2 = pcVar8;
  } while (cVar1 != '\0');
  uVar5 = ~uVar5;
  pbVar7 = (byte *)(pcVar8 + -uVar5);
  pbVar9 = pbVar2 + (~uVar4 - 1);
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pbVar9 = *(undefined4 *)pbVar7;
    pbVar7 = pbVar7 + 4;
    pbVar9 = pbVar9 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pbVar9 = *pbVar7;
    pbVar7 = pbVar7 + 1;
    pbVar9 = pbVar9 + 1;
  }
  uVar3 = luaS_new(pbVar2);
  return uVar3;
}

/* ---- 0x1000ec50  luaV_call_binTM ---- */
/* call_binTM(event, msg): binary tag-method dispatch on the two top stack slots (was mislabelled
   luaV_gettable) */

void __cdecl luaV_call_binTM(int param_1,byte *param_2)

{
  uint uVar1;
  int iVar2;
  undefined4 *puVar3;
  
  uVar1 = luaT_effectivetag((uint *)(PTR_1002bf6c[7] + -0x10));
  iVar2 = param_1 + uVar1 * -0x12;
  puVar3 = (undefined4 *)(DAT_1002bf48 + iVar2 * 8);
  if (*(int *)(DAT_1002bf48 + iVar2 * 8) == -7) {
    uVar1 = luaT_effectivetag((uint *)(PTR_1002bf6c[7] + -8));
    iVar2 = param_1 + uVar1 * -0x12;
    puVar3 = (undefined4 *)(DAT_1002bf48 + iVar2 * 8);
    if ((*(int *)(DAT_1002bf48 + iVar2 * 8) == -7) &&
       (puVar3 = (undefined4 *)(DAT_1002bf48 + param_1 * 8),
       *(int *)(DAT_1002bf48 + param_1 * 8) == -7)) {
      lua_error(param_2);
    }
  }
  lua_pushstring((&PTR_s_gettable_10027d48)[param_1]);
  luaD_callTM(puVar3,3,(void *)0x1);
  return;
}

/* ---- 0x1000ecf0  luaV_call_arith ---- */
/* Unidentified function of lvm.c (virtual machine) */

void __cdecl luaV_call_arith(int param_1)

{
  luaV_call_binTM(param_1,s_unexpected_type_in_arithmetic_op_1002825c);
  return;
}

/* ---- 0x1000ed10  luaV_comparison ---- */
/* Unidentified function of lvm.c (virtual machine) */

void __cdecl luaV_comparison(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = PTR_1002bf6c[7];
  piVar1 = PTR_1002bf6c + 7;
  if ((*(int *)(iVar3 + -0x10) == -1) && (*(int *)(iVar3 + -8) == -1)) {
    if (*(float *)(iVar3 + -4) <= *(float *)(iVar3 + -0xc)) {
      if (*(float *)(iVar3 + -4) == *(float *)(iVar3 + -0xc)) {
        iVar3 = 0;
      }
      else {
        iVar3 = 1;
      }
    }
    else {
      iVar3 = -1;
    }
  }
  else {
    if ((*(int *)(iVar3 + -0x10) != -2) || (*(int *)(iVar3 + -8) != -2)) {
      luaV_call_binTM(param_4,s_unexpected_type_in_comparison_10028284);
      return;
    }
    iVar3 = strcoll((byte *)(*(int *)(iVar3 + -0xc) + 0x18),(byte *)(*(int *)(iVar3 + -4) + 0x18));
  }
  iVar2 = *piVar1;
  *piVar1 = iVar2 + -8;
  *(undefined4 *)(iVar2 + -0xc) = 0x3f800000;
  if (iVar3 < 0) {
    *(undefined4 *)(*piVar1 + -8) = param_1;
    return;
  }
  if (iVar3 != 0) {
    param_2 = param_3;
  }
  *(undefined4 *)(*piVar1 + -8) = param_2;
  return;
}
