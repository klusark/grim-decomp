# Plain register save / restore setjmp and longjmp for the differential tests.  msvcrt's longjmp raises STATUS_LONGJUMP
# through RtlUnwind, which nothing handles in a test process; for a jump inside one function (sys_timer_dispatcher)
# this does the same thing.
	.intel_syntax noprefix
	.text
	.globl __setjmp3
__setjmp3:
	mov eax, [esp+4]
	mov [eax], ebx
	mov [eax+4], esi
	mov [eax+8], edi
	mov [eax+12], ebp
	lea ecx, [esp+4]
	mov [eax+16], ecx
	mov ecx, [esp]
	mov [eax+20], ecx
	xor eax, eax
	ret
	.globl _longjmp
_longjmp:
	mov edx, [esp+4]
	mov eax, [esp+8]
	test eax, eax
	jnz 1f
	inc eax
1:
	mov ebx, [edx]
	mov esi, [edx+4]
	mov edi, [edx+8]
	mov ebp, [edx+12]
	mov esp, [edx+16]
	jmp [edx+20]
