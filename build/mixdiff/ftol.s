	.intel_syntax noprefix
# __ftol of the MSVC runtime for the sliced original code (build/mixdiff/twin.sh): ST0 truncated to a 64-bit integer in
# EDX:EAX, ST0 popped; the control word is restored.  (Today's build has no __ftol: its generated code converts inline.)
	.text
	.globl __ftol
__ftol:
	push ebp
	mov ebp, esp
	sub esp, 12
	fnstcw [ebp-2]
	mov ax, [ebp-2]
	or ah, 0x0c
	mov [ebp-4], ax
	fldcw [ebp-4]
	fistp qword ptr [ebp-12]
	fldcw [ebp-2]
	mov eax, [ebp-12]
	mov edx, [ebp-8]
	leave
	ret
