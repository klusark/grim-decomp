# Callers of the original machine code with the original callers' frames recreated (agent r1, build/difftest/imuse_r1).
	.intel_syntax noprefix
	.text

# int call_orig_6560(int id, unsigned esi, unsigned edi): ESI / EDI as the dispatcher ScriptCall has them at its call
# (ESI = 0xffffffff there); FUN_10006560 saves both under its return address, where ImSetTrigger reads them.
	.globl _call_orig_6560
_call_orig_6560:
	push ebx
	push esi
	push edi
	push ebp
	mov eax, [esp+0x14]
	mov esi, [esp+0x18]
	mov edi, [esp+0x1c]
	push eax
	call _orig_FUN_10006560
	add esp, 4
	pop ebp
	pop edi
	pop esi
	pop ebx
	ret

	.globl _call_orig_6620
_call_orig_6620:
	push ebx
	push esi
	push edi
	push ebp
	mov eax, [esp+0x14]
	mov esi, [esp+0x18]
	mov edi, [esp+0x1c]
	push eax
	call _orig_Script_SetSequence
	add esp, 4
	pop ebp
	pop edi
	pop esi
	pop ebx
	ret

# int call_orig_64d0(unsigned esi, unsigned edi): FUN_100064d0 (transcribed below) as the dispatcher calls it
	.globl _call_orig_64d0
_call_orig_64d0:
	push ebx
	push esi
	push edi
	push ebp
	mov esi, [esp+0x14]
	mov edi, [esp+0x18]
	call _orig_FUN_100064d0
	pop ebp
	pop edi
	pop esi
	pop ebx
	ret

# void call_orig_68b0(char *entry, int index, int no_attr, unsigned w10, unsigned w14): Script_Trans with the two words
# its callers' frames hold at [entry+0x10] / [entry+0x14] (the callers' saved EDI / ESI); its return address is
# _orig68b0_ret.
	.globl _call_orig_68b0
	.globl _orig68b0_ret
_call_orig_68b0:
	push ebx
	push esi
	push edi
	push ebp
	push dword ptr [esp+0x24]
	push dword ptr [esp+0x24]
	push dword ptr [esp+0x24]
	push dword ptr [esp+0x24]
	push dword ptr [esp+0x24]
	mov ebx, 0x0b0b0b0b
	mov esi, 0x5e5e5e5e
	mov edi, 0xd1d1d1d1
	mov ebp, 0xb9b9b9b9
	call _orig_Script_Trans
_orig68b0_ret:
	add esp, 0x14
	pop ebp
	pop edi
	pop esi
	pop ebx
	ret

# FUN_100064d0 of the original IMUSE.DLL, transcribed from `objdump -d IMUSE.DLL --start-address=0x100064d0` (it is compiled
# C in the build, so the base assembly has no copy).  0x10004d00 ImGetNextSound, 0x10004d30 ImGetParam, 0x10004380
# ImFlushSounds, 0x1002e304 / 0x1002e308 = _sect_data + 0x17304 / 0x17308.
	.globl _orig_FUN_100064d0
_orig_FUN_100064d0:
	mov eax, [_sect_data+0x17304]
	push esi
	test eax, eax
	je 1f
	push 0
	call _orig_Script_SetSequence
	add esp, 4
	mov dword ptr [_sect_data+0x17304], 0
1:	push 0
	call _ImGetNextSound
	mov esi, eax
	add esp, 4
	test esi, esi
	je 4f
2:	push 0x1800
	push esi
	call _ImGetParam
	add esp, 8
	test eax, eax
	je 3f
	push 0x1900
	push esi
	call _ImGetParam
	add esp, 8
	cmp eax, 2
	je 5f
3:	push esi
	call _ImGetNextSound
	mov esi, eax
	add esp, 4
	test esi, esi
	jne 2b
5:	test esi, esi
	jne 6f
4:	mov eax, [_sect_data+0x17308]
	test eax, eax
	je 6f
	push 0
	call _orig_Script_SetSequence
	add esp, 4
6:	call _ImFlushSounds
	xor eax, eax
	pop esi
	ret
