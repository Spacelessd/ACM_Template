	.file	"1.cpp"
.globl _a
	.bss
	.align 32
_a:
	.space 80
	.def	___main;	.scl	2;	.type	32;	.endef
	.text
.globl _main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
LFB0:
	pushl	%ebp
LCFI0:
	movl	%esp, %ebp
LCFI1:
	andl	$-16, %esp
LCFI2:
	call	___main
	fldl	_a+8
	fldl	_a+16
	faddp	%st, %st(1)
	fstpl	_a+8
	movl	$0, %eax
	movl	%ebp, %esp
	popl	%ebp
	ret
LFE0:
