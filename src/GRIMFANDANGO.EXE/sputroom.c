/* GRIMFANDANGO.EXE :: sputroom.c
 * functions 0x004a48c0 .. 0x004a5890 (6 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004a48c0  sputRoom_Initialize ---- */
/* Subsystem init entry registered through EngineModule_Init; fills the module's 8-entry interface
   {init, shutdown, save, restore, ...} */

undefined * __cdecl sputRoom_Initialize(uint param_1,undefined **param_2)

{
  int iVar1;
  uint *puVar2;
  
  g_pSputRoomHS = (GrimServices *)param_1;
  *param_2 = sputRoom_Initialize;
  param_2[1] = sputRoom_Terminate;
  param_2[2] = sputRoom_Startup;
  param_2[3] = sputRoom_Shutdown;
  param_2[4] = sputRoom_Save;
  param_2[5] = sputRoom_Restore;
  param_2[6] = (undefined *)0x0;
  param_2[7] = (undefined *)0x0;
  puVar2 = &g_dwSputRoom_pCurrentRoom;
  for (iVar1 = 0xd; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  g_dwSputRoomInitialize = 1;
  g_dwSputRoom_pCurrentRoom = 0;
  return (undefined *)0x0;
}

/* ---- 0x004a5390  sputRoom_Terminate ---- */
/* Module interface slot 1 (sputRoom): called by Engine_ResetSubsystems / when registration fails;
   drops the service table pointer and clears the initialised flag. */

void sputRoom_Terminate(void)

{
  g_pSputRoomHS = (GrimServices *)0x0;
  if (g_dwSputRoomInitialize != 0) {
    g_dwSputRoomInitialize = 0;
  }
  return;
}

/* ---- 0x004a53b0  sputRoom_Startup ---- */
/* Module interface slot 2 (sputRoom): called by Engine_InitSubsystems, returns 0 on success
   (non-zero makes the whole start-up unwind). _Start registers the set-file chunk handlers
   (colormaps, setups, lights, sectors) and creates the positioned-sound pool. Original name
   sputRoom_Startup (the remaster's GrimFandango (Linux): strings: 'setups' | 'colormaps' |
   'sectors'); was sputRoom_Start. */

undefined4 sputRoom_Startup(void)

{
  if (g_dwSputRoomStartup != 0) {
    return 1;
  }
  Set_RegisterHandle(s_colormaps_004ec734,sputRoom_ParseColormaps);
  Set_RegisterHandle(s_setups_004ec72c,sputRoom_ParseSetups);
  Set_RegisterHandle(s_lights_004ec724,sputRoom_ParseLights);
  Set_RegisterHandle(s_sectors_004ec71c,sputRoom_ParseSectors);
  g_pSoundPool = (void **)Memory_AllocatePool(0x24,0x10,8);
  g_dwSputRoomStartup = 1;
  return 0;
}

/* ---- 0x004a5430  sputRoom_Shutdown ---- */
/* Module interface slot 3 (sputRoom): called by Engine_ShutdownSubsystems in reverse order;
   releases what _Start created. Original name sputRoom_Shutdown (the remaster's GrimFandango
   (Linux): the module's shutdown slot: frees the room list with psputRoomHS); was sputRoom_Stop. */

void sputRoom_Shutdown(void)

{
  int iVar1;
  void *pvVar2;
  void *pvVar3;
  int iVar4;
  
  pvVar3 = g_pRoomList;
  while (pvVar3 != (void *)0x0) {
    iVar4 = *(int *)((int)pvVar3 + 0x80);
    while (iVar4 != 0) {
      iVar1 = *(int *)(iVar4 + 8);
      (*g_pSputRoomHS->pFree)(iVar4);
      iVar4 = iVar1;
    }
    pvVar2 = *(void **)((int)pvVar3 + 0x84);
    (*g_pSputRoomHS->pFree)(pvVar3);
    pvVar3 = pvVar2;
  }
  if (g_pSoundPool != (void **)0x0) {
    Memory_FreePool(g_pSoundPool);
    g_pSoundPool = (void **)0x0;
  }
  g_dwSputRoomStartup = 0;
  return;
}

/* ---- 0x004a5600  sputRoom_ParseLights ---- */
/* Text set "section: lights" parser. Light record 0x68 bytes from set+0xbc, embedded rdLight at
   +0x2c: type +0x30 (omni 2, spot 3, direct 0), direction +0x38 (normalised), position +0x20,
   intensity +0x44 (raw), color +0x48 (packed RGB), umbraangle +0x4c, penumbraangle +0x54. */

undefined4 sputRoom_ParseLights(void)

{
  unsigned char _frame[0x120] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  byte *pbVar6;
  undefined4 *puVar7;
  byte *pbVar8;
  byte *pbVar9;
  bool bVar10;
  #define local_110 (*(uint *)(_frame + (0x120 - 0x110)))
  #define local_10c (*(uint *)(_frame + (0x120 - 0x10c)))
  #define local_108 (*(uint *)(_frame + (0x120 - 0x108)))
  #define local_104 (*(uint *)(_frame + (0x120 - 0x104)))
  #define local_100 (*(byte (*)[256])(_frame + (0x120 - 0x100)))
  
  uVar2 = g_dwLoadingRoom;
  puVar7 = (undefined4 *)(g_dwLoadingRoom + 0xb8);
  *puVar7 = 0;
  pbVar6 = (byte *)0x0;
  local_10c = (uint)puVar7;
  iVar3 = stdConffile_ReadLine();
  if (iVar3 == 0) {
    return 1;
  }
  do {
    if (*(char *)g_dwStdConffile_aLine != '\0') {
      iVar3 = sscanf((char *)g_dwStdConffile_aLine,s_section___s_004ec7e0,local_100);
      if (iVar3 == 0) {
        iVar3 = sscanf((char *)g_dwStdConffile_aLine,s_numlights__d_004ec7d0,puVar7);
        pbVar8 = pbVar6;
        if (iVar3 == 1) {
          pbVar8 = (byte *)(uVar2 + 0x54);
          puVar7 = (undefined4 *)(uVar2 + 0xbc);
          for (iVar3 = 0x680; iVar3 != 0; iVar3 = iVar3 + -1) {
            *puVar7 = 0;
            puVar7 = puVar7 + 1;
          }
        }
        pbVar6 = pbVar8;
        if (pbVar8 != (byte *)0x0) {
          iVar3 = sscanf((char *)g_dwStdConffile_aLine,s_light__s_004ec7c4,local_100);
          if (iVar3 == 1) {
            pbVar6 = pbVar8 + 0x68;
            rdLight_NewEntry(pbVar8 + 0x94);
            uVar4 = 0xffffffff;
            pbVar8 = local_100;
            do {
              pbVar9 = pbVar8;
              if (uVar4 == 0) break;
              uVar4 = uVar4 - 1;
              pbVar9 = pbVar8 + 1;
              bVar1 = *pbVar8;
              pbVar8 = pbVar9;
            } while (bVar1 != 0);
            uVar4 = ~uVar4;
            pbVar8 = pbVar9 + -uVar4;
            pbVar9 = pbVar6;
            for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
              *(undefined4 *)pbVar9 = *(undefined4 *)pbVar8;
              pbVar8 = pbVar8 + 4;
              pbVar9 = pbVar9 + 4;
            }
            for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
              *pbVar9 = *pbVar8;
              pbVar8 = pbVar8 + 1;
              pbVar9 = pbVar9 + 1;
            }
          }
          iVar3 = sscanf((char *)g_dwStdConffile_aLine,s_type__s_004ec7b8,local_100);
          if (iVar3 == 1) {
            iVar3 = _stricmp(local_100,&DAT_004ec5b4);
            if (iVar3 == 0) {
              iVar3 = 2;
            }
            else {
              pbVar9 = &DAT_004ec598;
              pbVar8 = local_100;
              do {
                bVar1 = *pbVar8;
                bVar10 = bVar1 < *pbVar9;
                if (bVar1 != *pbVar9) {
LAB_004a5762:
                  iVar3 = (1 - (uint)bVar10) - (uint)(bVar10 != 0);
                  goto LAB_004a5767;
                }
                if (bVar1 == 0) break;
                bVar1 = pbVar8[1];
                bVar10 = bVar1 < pbVar9[1];
                if (bVar1 != pbVar9[1]) goto LAB_004a5762;
                pbVar8 = pbVar8 + 2;
                pbVar9 = pbVar9 + 2;
              } while (bVar1 != 0);
              iVar3 = 0;
LAB_004a5767:
              iVar3 = (-(uint)(iVar3 != 0) & 0xfffffffd) + 3;
            }
            *(int *)(pbVar6 + 0x30) = iVar3;
          }
          iVar3 = sscanf((char *)g_dwStdConffile_aLine,s_direction__f__f__f_004ec7a4,pbVar6 + 0x38,
                         pbVar6 + 0x3c,pbVar6 + 0x40);
          if (iVar3 == 3) {
            rdVector_Normalize3Acc((float *)(pbVar6 + 0x38));
          }
          sscanf((char *)g_dwStdConffile_aLine,s_position__f__f__f_004ec790,pbVar6 + 0x20,
                 pbVar6 + 0x24,pbVar6 + 0x28);
          sscanf((char *)g_dwStdConffile_aLine,s_intensity__f_004ec780,pbVar6 + 0x44);
          sscanf((char *)g_dwStdConffile_aLine,s_umbraangle__f_004ec770,pbVar6 + 0x4c);
          sscanf((char *)g_dwStdConffile_aLine,s_penumbraangle__f_004ec75c,pbVar6 + 0x54);
          iVar3 = sscanf((char *)g_dwStdConffile_aLine,s_color__d__d__d_004ec74c,&local_104,
                         &local_110,&local_108);
          if (iVar3 == 3) {
            *(uint *)(pbVar6 + 0x48) = (local_104 << 8 | local_110) << 8 | local_108;
          }
        }
      }
      else {
        iVar3 = Set_IsHandleValid((char *)local_100);
        if (iVar3 == 0) {
          return 0;
        }
      }
    }
    iVar3 = stdConffile_ReadLine();
    puVar7 = (undefined4 *)local_10c;
    if (iVar3 == 0) {
      return 1;
    }
  } while( true );
}
#undef local_100
#undef local_104
#undef local_108
#undef local_10c
#undef local_110


/* ---- 0x004a5890  sputRoom_ParseSetups ---- */
/* Section handler 'setups' registered by sputRoom_Startup: reads 'numsetups', and per setup its
   name, background, zbuffer, position, interest, roll, fov, nclip, fclip (300-byte setup records at
   set+0xac). */

undefined4 sputRoom_ParseSetups(void)

{
  unsigned char _frame[0x120] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *piVar1;
  char cVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  uint uVar6;
  uint uVar7;
  char *pcVar8;
  uint *puVar9;
  char *pcVar10;
  char *pcVar11;
  #define local_104 (*(uint *)(_frame + (0x120 - 0x104)))
  #define local_100 (*(char (*)[256])(_frame + (0x120 - 0x100)))
  
  uVar3 = g_dwLoadingRoom;
  puVar9 = (uint *)(g_dwLoadingRoom + 0xac);
  *puVar9 = 0;
  iVar4 = stdConffile_ReadLine();
  pcVar8 = (char *)uVar3;
  if (iVar4 == 0) {
    return 1;
  }
  do {
    if (*(char *)g_dwStdConffile_aLine != '\0') {
      iVar4 = sscanf((char *)g_dwStdConffile_aLine,s_section___s_004ec7e0,local_100);
      if (iVar4 == 0) {
        piVar1 = (int *)(uVar3 + 0xb0);
        iVar4 = sscanf((char *)g_dwStdConffile_aLine,s_numsetups__d_004ec858,piVar1);
        if (iVar4 == 1) {
          puVar5 = (undefined4 *)
                   (*g_pSputRoomHS->pAlloc)
                             (*piVar1 * 300,s_C__grimsrc_libs_grimlib_Engine_s_004ec5e0,0x8b5);
          iVar4 = *piVar1;
          *puVar9 = (uint)puVar5;
          for (uVar6 = iVar4 * 0x4b & 0x3fffffff; uVar6 != 0; uVar6 = uVar6 - 1) {
            *puVar5 = 0;
            puVar5 = puVar5 + 1;
          }
          for (iVar4 = 0; iVar4 != 0; iVar4 = iVar4 + -1) {
            *(undefined1 *)puVar5 = 0;
            puVar5 = (undefined4 *)((int)puVar5 + 1);
          }
          pcVar8 = (char *)(*puVar9 - 300);
        }
        else {
          if (*puVar9 == 0) {
            return 0;
          }
          iVar4 = sscanf((char *)g_dwStdConffile_aLine,s_setup__s_004ec84c,local_100);
          if (iVar4 == 1) {
            pcVar8 = pcVar8 + 300;
            if ((char *)(*puVar9 + *piVar1 * 300) <= pcVar8) {
              return 0;
            }
            uVar6 = 0xffffffff;
            pcVar10 = local_100;
            do {
              pcVar11 = pcVar10;
              if (uVar6 == 0) break;
              uVar6 = uVar6 - 1;
              pcVar11 = pcVar10 + 1;
              cVar2 = *pcVar10;
              pcVar10 = pcVar11;
            } while (cVar2 != '\0');
            uVar6 = ~uVar6;
            pcVar10 = pcVar11 + -uVar6;
            pcVar11 = pcVar8;
            for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
              *(undefined4 *)pcVar11 = *(undefined4 *)pcVar10;
              pcVar10 = pcVar10 + 4;
              pcVar11 = pcVar11 + 4;
            }
            for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
              *pcVar11 = *pcVar10;
              pcVar10 = pcVar10 + 1;
              pcVar11 = pcVar11 + 1;
            }
          }
          else {
            if (pcVar8 < (char *)*puVar9) {
              return 0;
            }
            iVar4 = sscanf((char *)g_dwStdConffile_aLine,s_background__s_004ec83c,pcVar8 + 0x80);
            if (((((iVar4 != 1) &&
                  (iVar4 = sscanf((char *)g_dwStdConffile_aLine,s_zbuffer__s_004ec830,pcVar8 + 0xa0)
                  , iVar4 != 1)) &&
                 (iVar4 = sscanf((char *)g_dwStdConffile_aLine,s_position__f__f__f_004ec790,
                                 pcVar8 + 0x20,pcVar8 + 0x24,pcVar8 + 0x28), iVar4 != 3)) &&
                ((iVar4 = sscanf((char *)g_dwStdConffile_aLine,s_interest__f__f__f_004ec81c,
                                 pcVar8 + 0x2c,pcVar8 + 0x30,pcVar8 + 0x34), iVar4 != 3 &&
                 (iVar4 = sscanf((char *)g_dwStdConffile_aLine,s_roll__f_004ec810,pcVar8 + 0x38),
                 iVar4 != 1)))) &&
               ((iVar4 = sscanf((char *)g_dwStdConffile_aLine,s_fov__f_004ec808,pcVar8 + 0x3c),
                iVar4 != 1 &&
                ((iVar4 = sscanf((char *)g_dwStdConffile_aLine,s_nclip__f_004ec7fc,pcVar8 + 0x40),
                 iVar4 != 1 &&
                 (iVar4 = sscanf((char *)g_dwStdConffile_aLine,s_fclip__f_004ec7f0,pcVar8 + 0x44),
                 iVar4 != 1)))))) {
              return 0;
            }
          }
        }
      }
      else {
        iVar4 = Set_IsHandleValid(local_100);
        if (iVar4 == 0) {
          return 0;
        }
      }
    }
    iVar4 = stdConffile_ReadLine();
    if (iVar4 == 0) {
      return 1;
    }
  } while( true );
}
#undef local_100
#undef local_104

