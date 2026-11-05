# int gcall(void *fn, int a, int b, int c, int d): calls fn(a, b, c, d) (cdecl; a stdcall callee is fine too, ESP is
# restored from the saved value).  Returns 0, the callee's EAX in _g_ret; returns 1 if the vectored exception handler
# (rt.c) redirected a fault to _gcall_recover.
	.intel_syntax noprefix
	.text
	.globl _gcall
	.globl _gcall_recover
_gcall:
	push ebp
	push ebx
	push esi
	push edi
	mov dword ptr [_g_saved_esp], esp
	push dword ptr [esp+0x24]
	push dword ptr [esp+0x24]
	push dword ptr [esp+0x24]
	push dword ptr [esp+0x24]
	call dword ptr [esp+0x24]
	mov dword ptr [_g_ret], eax
	mov esp, dword ptr [_g_saved_esp]
	pop edi
	pop esi
	pop ebx
	pop ebp
	xor eax, eax
	ret
_gcall_recover:
	mov esp, dword ptr [_g_saved_esp]
	fninit
	pop edi
	pop esi
	pop ebx
	pop ebp
	mov eax, 1
	ret

# int gcall8(void *fn, const int *args8): calls fn(args8[0..7]) the same way (g_ret: EAX, g_ret_st0: ST0 popped
# into a long double slot when g_want_st0 is set).
	.globl _gcall8
_gcall8:
	push ebp
	push ebx
	push esi
	push edi
	mov dword ptr [_g_saved_esp], esp
	mov eax, dword ptr [esp+0x18]
	push dword ptr [eax+0x1c]
	push dword ptr [eax+0x18]
	push dword ptr [eax+0x14]
	push dword ptr [eax+0x10]
	push dword ptr [eax+0x0c]
	push dword ptr [eax+0x08]
	push dword ptr [eax+0x04]
	push dword ptr [eax]
	mov eax, dword ptr [esp+0x34]
	call eax
	mov dword ptr [_g_ret], eax
	cmp dword ptr [_g_want_st0], 0
	jz 1f
	fstp tbyte ptr [_g_ret_st0]
1:
	mov esp, dword ptr [_g_saved_esp]
	pop edi
	pop esi
	pop ebx
	pop ebp
	xor eax, eax
	ret

# Recorder thunks.  rt_patch(addr, id, argbytes) writes "push id; jmp _rec_thunk_N" at a callee's 1.01 address, so
# the original code and the C both reach the recorder (rec_dispatch in rt.c).  The thunk passes rec_dispatch a
# pointer to the frame: [0] id, [1] return address, [2..] the arguments; rec_dispatch is C (keeps EBX/ESI/EDI/EBP);
# the thunk returns with "ret" (cdecl) or "ret N" (stdcall).
	.globl _rec_thunkf_0
# float-returning cdecl callee: rec_dispatch's EAX is the float's bit pattern, loaded into ST0
_rec_thunkf_0:
	push esp
	call _rec_dispatch
	mov dword ptr [esp], eax
	fld dword ptr [esp]
	add esp, 8
	ret
	.globl _rec_thunk_0
_rec_thunk_0:
	push esp
	call _rec_dispatch
	add esp, 8
	ret
.macro RECN n
	.globl _rec_thunk_\n
_rec_thunk_\n:
	push esp
	call _rec_dispatch
	add esp, 8
	ret \n
.endm
	RECN 4
	RECN 8
	RECN 12
	RECN 16
	RECN 20
	RECN 24
	RECN 28
	RECN 32
