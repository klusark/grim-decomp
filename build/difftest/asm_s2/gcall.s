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
