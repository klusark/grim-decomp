/* Call harnesses for the register-ABI runtime helpers of round r2 (build/difftest/r2): they set the registers the
 * helper reads, call it, and record every register and the x87 state it leaves.  i686 mingw, cdecl entry points. */
	.intel_syntax noprefix
	.text

/* void call_ftol(void *fn, const void *x80, unsigned cw, unsigned depth, unsigned *out)
 * x87: fninit, fldcw cw, `depth` x fldpi, fld tbyte x80 -> ST0; EBX/ESI/EDI/ECX/EDX = markers; call fn.
 * out[0..7] = EAX EDX ECX EBX ESI EDI, ESP after - ESP before, EBP; out[8..14] = fnstenv (CW SW TW FIP FCS FOO FOS);
 * out[15..] = the registers left on the x87 stack (fstp tbyte, 3 dwords each), depth of them. */
	.globl _call_ftol
_call_ftol:
	push ebp
	mov ebp, esp
	push ebx
	push esi
	push edi
	fninit
	fldcw word ptr [ebp+16]
	mov ecx, [ebp+20]
1:	test ecx, ecx
	jz 2f
	fldpi
	dec ecx
	jmp 1b
2:	mov eax, [ebp+12]
	fld tbyte ptr [eax]
	mov eax, [ebp+8]
	mov [f_fn], eax
	mov [f_ebp], ebp
	mov [f_esp0], esp
	mov ebx, 0x11111111
	mov esi, 0x22222222
	mov edi, 0x33333333
	mov ecx, 0x44444444
	mov edx, 0x55555555
	mov eax, 0x66666666
	mov ebp, 0x77777777
	call dword ptr [f_fn]
	mov [f_eax], eax
	mov [f_ebx], ebx
	mov eax, esp
	sub eax, [f_esp0]
	mov [f_dsp], eax
	mov ebx, ebp
	mov ebp, [f_ebp]
	mov eax, [ebp+24]
	mov [eax+28], ebx           /* EBP after */
	mov ebx, [f_eax]
	mov [eax+0], ebx
	mov [eax+4], edx
	mov [eax+8], ecx
	mov ebx, [f_ebx]
	mov [eax+12], ebx
	mov [eax+16], esi
	mov [eax+20], edi
	mov ebx, [f_dsp]
	mov [eax+24], ebx
	fnstenv [eax+32]
	mov ecx, [ebp+20]
	lea edx, [eax+60]
3:	test ecx, ecx
	jz 4f
	fstp tbyte ptr [edx]
	add edx, 12
	dec ecx
	jmp 3b
4:	fninit
	pop edi
	pop esi
	pop ebx
	pop ebp
	ret

/* void call_chk(void *fn, unsigned size, void *stack_top, void *stack_limit, unsigned *out, int trace)
 * Switches ESP to stack_top (the TIB stack base / limit are set to the region for the duration), EAX = size,
 * EBX/ESI/EDI/ECX/EDX/EBP = markers, calls fn (with the trap flag set when `trace`, see chkstk_test.c).
 * out[0..7] = EAX ECX EDX EBX ESI EDI EBP after, ESP after; out[8] = ESP before the call instruction. */
	.globl _call_chk
	.globl _chk_ret
_call_chk:
	push ebp
	mov ebp, esp
	push ebx
	push esi
	push edi
	mov eax, [ebp+8]
	mov [c_fn], eax
	mov [c_ebp], ebp
	mov [c_esp], esp
	mov eax, fs:[4]
	mov [c_base], eax
	mov eax, fs:[8]
	mov [c_limit], eax
	mov eax, [ebp+16]
	mov fs:[4], eax
	mov eax, [ebp+20]
	mov fs:[8], eax
	mov ecx, [ebp+28]
	mov eax, [ebp+12]
	mov esp, [ebp+16]
	mov [c_esp0], esp
	mov ebx, 0x11111111
	mov esi, 0x22222222
	mov edi, 0x33333333
	mov edx, 0x55555555
	mov ebp, 0x77777777
	test ecx, ecx
	mov ecx, 0x44444444
	jz 5f
	pushfd
	or dword ptr [esp], 0x100
	popfd                       /* the trap comes after the next instruction: the first step stops at fn's entry */
5:	call dword ptr [c_fn]
_chk_ret:
	mov [c_r+0], eax
	mov [c_r+4], ecx
	mov [c_r+8], edx
	mov [c_r+12], ebx
	mov [c_r+16], esi
	mov [c_r+20], edi
	mov [c_r+24], ebp
	mov [c_r+28], esp
	mov esp, [c_esp]
	mov ebp, [c_ebp]
	mov eax, [c_base]
	mov fs:[4], eax
	mov eax, [c_limit]
	mov fs:[8], eax
	mov eax, [ebp+24]
	mov ecx, 0
6:	mov edx, [c_r+ecx*4]
	mov [eax+ecx*4], edx
	inc ecx
	cmp ecx, 8
	jb 6b
	mov edx, [c_esp0]
	mov [eax+32], edx
	pop edi
	pop esi
	pop ebx
	pop ebp
	ret

/* unsigned call_chk_here(void *fn, unsigned size): the helper on the thread's own stack (guard-page growth); after it
 * returns, every byte of the allocated block is written (low to high), ESP is restored.  Returns the block size seen. */
	.globl _call_chk_here
_call_chk_here:
	push ebp
	mov ebp, esp
	push ebx
	push esi
	push edi
	mov eax, [ebp+12]
	call dword ptr [ebp+8]
	mov edi, esp
	lea ecx, [ebp-12]
	sub ecx, esp                /* the allocated block: from the new ESP up to the ESP before the call */
	mov ebx, ecx
	xor eax, eax
	cld
	rep stosb
	lea esp, [ebp-12]
	mov eax, ebx
	pop edi
	pop esi
	pop ebx
	pop ebp
	ret

	.data
	.p2align 2
f_fn: .long 0
f_ebp: .long 0
f_esp0: .long 0
f_eax: .long 0
f_ebx: .long 0
f_dsp: .long 0
c_fn: .long 0
c_ebp: .long 0
c_esp: .long 0
c_esp0: .long 0
c_base: .long 0
c_limit: .long 0
c_r: .fill 8, 4, 0
