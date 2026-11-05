# reserves 0x401000 - 0x94e000 (linked there by img.ld): the 1.01 text, rdata, data and bss
	.section .grim,"bwx"
	.globl _grim_img
_grim_img:
	.space 0x54d000
