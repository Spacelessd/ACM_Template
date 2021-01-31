	.file	"rp_SIMPLEX_greedy.cpp"
	.text
	.p2align 4,,15
.globl __Z5pivotii
	.def	__Z5pivotii;	.scl	2;	.type	32;	.endef
__Z5pivotii:
LFB22:
	pushl	%ebp
LCFI0:
	movl	%esp, %ebp
LCFI1:
	pushl	%edi
LCFI2:
	pushl	%esi
LCFI3:
	pushl	%ebx
LCFI4:
	subl	$44, %esp
LCFI5:
	imull	$12, 12(%ebp), %edx
	imull	$12120, 8(%ebp), %esi
	imull	$12, 8(%ebp), %eax
	fldt	_A(%edx,%esi)
	fldt	_b(%eax)
	fdiv	%st(1), %st
	fstpt	_b(%edx)
	imull	$12120, 12(%ebp), %edx
	fdivrs	LC0
	fstpt	_A(%eax,%edx)
	movl	_N, %eax
	testl	%eax, %eax
	movl	%eax, -36(%ebp)
	jle	L2
	movl	12(%ebp), %ecx
	movl	$1, %eax
	leal	(%ecx,%ecx,2), %edx
	sall	$2, %edx
	movl	%edx, %edi
	movl	%edx, -40(%ebp)
	addl	%esi, %edi
	jmp	L5
	.p2align 4,,7
L3:
	leal	(%edx,%edx,2), %edx
	addl	$1, %eax
	leal	0(,%edx,4), %ecx
	fldt	_A(%ecx,%esi)
	imull	$12120, 12(%ebp), %ebx
	fldt	_A(%edi)
	cmpl	-36(%ebp), %eax
	fdivrp	%st, %st(1)
	fld	%st(0)
	fstpt	_A(%ecx,%ebx)
	movl	-40(%ebp), %ecx
	fldt	_c(%ecx)
	fmulp	%st, %st(1)
	fldt	_c(,%edx,4)
	fsubp	%st, %st(1)
	fstpt	_c(,%edx,4)
	jg	L2
L5:
	movl	_N(,%eax,4), %edx
	cmpl	12(%ebp), %edx
	jne	L3
	movl	%eax, -52(%ebp)
	addl	$1, %eax
	cmpl	-36(%ebp), %eax
	jle	L5
L2:
	movl	_B, %eax
	testl	%eax, %eax
	movl	%eax, -40(%ebp)
	jle	L6
	movl	12(%ebp), %edx
	movl	$1, %eax
	leal	(%edx,%edx,2), %edi
	sall	$2, %edi
	.p2align 4,,7
L7:
	movl	_B(,%eax,4), %ecx
	addl	$1, %eax
	leal	(%ecx,%ecx,2), %edx
	imull	$12120, %ecx, %ecx
	cmpl	-40(%ebp), %eax
	movl	_A+8(%ecx,%edi), %esi
	movl	_A+4(%ecx,%edi), %ebx
	movl	_A(%ecx,%edi), %ecx
	movl	%esi, _a1+8(,%edx,4)
	movl	%ebx, _a1+4(,%edx,4)
	movl	%ecx, _a1(,%edx,4)
	jle	L7
L6:
	cmpl	$0, -36(%ebp)
	jle	L8
	imull	$12120, 12(%ebp), %edi
	movl	$1, %eax
	.p2align 4,,7
L9:
	movl	_N(,%eax,4), %edx
	addl	$1, %eax
	cmpl	-36(%ebp), %eax
	leal	(%edx,%edx,2), %edx
	movl	_A(%edi,%edx,4), %ecx
	movl	_A+4(%edi,%edx,4), %ebx
	movl	_A+8(%edi,%edx,4), %esi
	movl	%ecx, _a2(,%edx,4)
	movl	%ebx, _a2+4(,%edx,4)
	movl	%esi, _a2+8(,%edx,4)
	jle	L9
L8:
	call	_clock
	movl	_B, %ecx
	testl	%ecx, %ecx
	movl	%ecx, -36(%ebp)
	movl	%eax, _tt
	jle	L10
	movl	8(%ebp), %edx
	movl	$1, %edi
	movl	_N, %ebx
	leal	(%edx,%edx,2), %eax
	sall	$2, %eax
	movl	%eax, -40(%ebp)
	imull	$12120, 12(%ebp), %eax
	addl	-40(%ebp), %eax
	movl	%eax, -44(%ebp)
	.p2align 4,,7
L14:
	movl	_B(,%edi,4), %eax
	cmpl	8(%ebp), %eax
	je	L22
	movl	12(%ebp), %ecx
	imull	$12120, %eax, %esi
	testl	%ebx, %ebx
	leal	(%eax,%eax,2), %eax
	leal	(%ecx,%ecx,2), %edx
	movl	-40(%ebp), %ecx
	fldt	_A(%esi,%edx,4)
	fldt	_b(,%edx,4)
	movl	-44(%ebp), %edx
	fmul	%st(1), %st
	fldt	_b(,%eax,4)
	fsubp	%st, %st(1)
	fstpt	_b(,%eax,4)
	fchs
	fldt	_A(%edx)
	fmulp	%st, %st(1)
	fstpt	_A(%esi,%ecx)
	fldt	_a1(,%eax,4)
	jle	L23
	movl	$1, %eax
	.p2align 4,,7
L13:
	movl	_N(,%eax,4), %edx
	addl	$1, %eax
	cmpl	%eax, %ebx
	leal	(%edx,%edx,2), %ecx
	fldt	_a2(,%ecx,4)
	leal	(%esi,%ecx,4), %edx
	fmul	%st(1), %st
	fldt	_A(%edx)
	fsubp	%st, %st(1)
	fstpt	_A(%edx)
	jge	L13
	fstp	%st(0)
	jmp	L12
L23:
	fstp	%st(0)
	.p2align 4,,7
L12:
	addl	$1, %edi
	cmpl	%edi, -36(%ebp)
	jge	L14
L10:
	call	_clock
	movl	-48(%ebp), %ecx
	imull	$12120, 12(%ebp), %edx
	addl	_s1, %eax
	subl	_tt, %eax
	movl	%eax, _s1
	imull	$12, 12(%ebp), %eax
	fldt	_c(%eax)
	fldt	_b(%eax)
	imull	$12, 8(%ebp), %eax
	fmul	%st(1), %st
	faddl	_v
	fstpl	_v
	fldt	_A(%eax,%edx)
	movl	8(%ebp), %edx
	fchs
	fmulp	%st, %st(1)
	fstpt	_c(%eax)
	movl	-52(%ebp), %eax
	movl	%edx, _N(,%eax,4)
	movl	12(%ebp), %eax
	movl	%eax, _B(,%ecx,4)
	addl	$44, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
L22:
	movl	%edi, -48(%ebp)
	addl	$1, %edi
	cmpl	%edi, -36(%ebp)
	jge	L14
	jmp	L10
LFE22:
	.p2align 4,,15
.globl __Z7delete0v
	.def	__Z7delete0v;	.scl	2;	.type	32;	.endef
__Z7delete0v:
LFB24:
	pushl	%ebp
LCFI6:
	movl	%esp, %ebp
LCFI7:
	subl	$24, %esp
LCFI8:
	movl	_B, %edx
	testl	%edx, %edx
	jle	L25
	movl	_B+4, %ecx
	movl	$1, %eax
	testl	%ecx, %ecx
	jne	L27
	jmp	L26
	.p2align 4,,7
L28:
	movl	_B(,%eax,4), %ecx
	testl	%ecx, %ecx
	je	L26
L27:
	addl	$1, %eax
	cmpl	%edx, %eax
	jle	L28
L25:
	movl	_N, %ecx
	testl	%ecx, %ecx
	jle	L29
	cmpl	$0, _N+4
	movl	$1, %eax
	movl	$1, %edx
	jne	L39
	jmp	L31
	.p2align 4,,7
L34:
	movl	_N(,%eax,4), %edx
	testl	%edx, %edx
	je	L35
L39:
	addl	$1, %eax
	cmpl	%ecx, %eax
	jle	L34
L35:
	movl	%eax, %edx
L31:
	cmpl	%ecx, %edx
	jge	L29
	addl	$1, %edx
	leal	_N(,%edx,4), %eax
	jmp	L36
	.p2align 4,,7
L41:
	addl	$1, %edx
L36:
	movl	(%eax), %ecx
	movl	%ecx, -4(%eax)
	movl	_N, %ecx
	addl	$4, %eax
	cmpl	%edx, %ecx
	jg	L41
L29:
	subl	$1, %ecx
	movl	%ecx, _N
	leave
	ret
L26:
	movl	_N+4, %eax
	movl	$0, (%esp)
	movl	%eax, 4(%esp)
	call	__Z5pivotii
	jmp	L25
LFE24:
	.p2align 4,,15
.globl __Z3optv
	.def	__Z3optv;	.scl	2;	.type	32;	.endef
__Z3optv:
LFB23:
	pushl	%ebp
LCFI9:
	movl	%esp, %ebp
LCFI10:
	pushl	%edi
LCFI11:
	pushl	%esi
LCFI12:
	pushl	%ebx
LCFI13:
	subl	$60, %esp
LCFI14:
	call	_clock
	movl	$1, -32(%ebp)
	movl	%eax, _tt
	movl	_N, %eax
	fld1
	fchs
	movl	%eax, -40(%ebp)
	jmp	L43
	.p2align 4,,7
L71:
	fldl	LC5
	fucompp
	fnstsw	%ax
	sahf
	ja	L70
	call	_clock
	movl	-36(%ebp), %edx
	addl	_s2, %eax
	subl	_tt, %eax
	movl	%edx, 4(%esp)
	movl	%eax, _s2
	movl	-44(%ebp), %eax
	movl	%eax, (%esp)
	call	__Z5pivotii
	call	_clock
	movl	_N, %edx
	movl	$1, -32(%ebp)
	movl	%edx, -40(%ebp)
	movl	%eax, _tt
	movl	-36(%ebp), %eax
	fld1
	fchs
	movl	%eax, -28(%ebp)
L61:
	movl	-28(%ebp), %eax
	movl	%eax, -36(%ebp)
L43:
	movl	-40(%ebp), %edx
	cmpl	%edx, -32(%ebp)
	jg	L71
	movl	-32(%ebp), %edx
	movl	_N(,%edx,4), %edx
	leal	(%edx,%edx,2), %eax
	fldt	_c(,%eax,4)
	movl	%edx, -28(%ebp)
	leal	0(,%eax,4), %esi
	fldl	LC3
	fld	%st(0)
	fxch	%st(2)
	fucom	%st(2)
	fnstsw	%ax
	fstp	%st(2)
	sahf
	jbe	L74
	movl	_B, %edi
	testl	%edi, %edi
	jle	L75
	fldl	LC4
	movl	$1010, %ebx
	movl	$1, %ecx
	jmp	L54
	.p2align 4,,7
L72:
	leal	(%edx,%edx,2), %eax
	fldt	_b(,%eax,4)
	fdivp	%st, %st(1)
	fxch	%st(1)
	fucom	%st(1)
	fnstsw	%ax
	sahf
	ja	L76
	fxch	%st(1)
	fucom	%st(1)
	fnstsw	%ax
	sahf
	jne	L77
	jp	L78
	cmpl	%ebx, %edx
	.p2align 4,,4
	jge	L79
	fstp	%st(1)
	.p2align 4,,7
	jmp	L49
	.p2align 4,,7
L76:
	fstp	%st(0)
L49:
	fld	%st(2)
	fmul	%st(1), %st
	fxch	%st(4)
	fucom	%st(4)
	fnstsw	%ax
	fstp	%st(4)
	sahf
	ja	L51
	addl	$1, %ecx
	cmpl	%ecx, %edi
	jl	L80
L73:
	movl	%edx, %ebx
L54:
	movl	_B(,%ecx,4), %edx
	imull	$12120, %edx, %eax
	fldt	_A(%eax,%esi)
	fucom	%st(2)
	fnstsw	%ax
	sahf
	ja	L72
	fstp	%st(0)
	jmp	L47
	.p2align 4,,7
L77:
	fstp	%st(0)
	jmp	L47
L78:
	fstp	%st(0)
	.p2align 4,,5
	jmp	L47
	.p2align 4,,7
L79:
	fstp	%st(0)
	.p2align 4,,7
L47:
	addl	$1, %ecx
	movl	%ebx, %edx
	cmpl	%ecx, %edi
	jge	L73
	fstp	%st(1)
	jmp	L53
	.p2align 4,,7
L80:
	fstp	%st(1)
L53:
	cmpl	$1010, %edx
	je	L81
	fmulp	%st, %st(1)
	fucom	%st(1)
	fnstsw	%ax
	sahf
	jbe	L82
	fstp	%st(1)
	movl	%edx, -44(%ebp)
	jmp	L56
	.p2align 4,,7
L74:
	fstp	%st(0)
	fstp	%st(0)
	jmp	L44
	.p2align 4,,7
L82:
	fstp	%st(0)
L44:
	movl	-36(%ebp), %edx
	movl	%edx, -28(%ebp)
L56:
	addl	$1, -32(%ebp)
	jmp	L61
	.p2align 4,,7
L51:
	fstp	%st(1)
	jmp	L53
L70:
	addl	$60, %esp
	movl	$1, %eax
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
L75:
	fstp	%st(0)
	fstp	%st(0)
	fstp	%st(0)
	jmp	L46
L81:
	fstp	%st(0)
	fstp	%st(0)
	fstp	%st(0)
L46:
	addl	$60, %esp
	xorl	%eax, %eax
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
LFE23:
	.p2align 4,,15
.globl __Z10initializev
	.def	__Z10initializev;	.scl	2;	.type	32;	.endef
__Z10initializev:
LFB25:
	pushl	%ebp
LCFI15:
	movl	%esp, %ebp
LCFI16:
	pushl	%edi
LCFI17:
	pushl	%esi
LCFI18:
	pushl	%ebx
LCFI19:
	subl	$44, %esp
LCFI20:
	movl	_n, %eax
	movl	$0, _B
	movl	$0, _N
	testl	%eax, %eax
	movl	%eax, -36(%ebp)
	jle	L84
	xorl	%edx, %edx
	movl	$1, %eax
	movl	-36(%ebp), %ecx
	jmp	L85
	.p2align 4,,7
L109:
	movl	_N, %edx
L85:
	addl	$1, %edx
	movl	%edx, _N
	movl	%eax, _N(,%edx,4)
	addl	$1, %eax
	cmpl	%ecx, %eax
	jle	L109
L84:
	movl	_m, %edx
	testl	%edx, %edx
	movl	%edx, -40(%ebp)
	jle	L86
	xorl	%edx, %edx
	movl	$1, %eax
	movl	-36(%ebp), %ebx
	movl	-40(%ebp), %esi
	jmp	L88
	.p2align 4,,7
L110:
	movl	_B, %edx
L88:
	leal	(%eax,%ebx), %ecx
	addl	$1, %eax
	addl	$1, %edx
	cmpl	%esi, %eax
	movl	%edx, _B
	movl	%ecx, _B(,%edx,4)
	jle	L110
	movl	_B, %esi
	fldz
	fstpl	_v
	movl	_B+4, %ebx
	cmpl	$1, %esi
	jle	L89
	movl	$2, %edx
	.p2align 4,,7
L92:
	movl	_B(,%edx,4), %ecx
	leal	(%ebx,%ebx,2), %eax
	leal	(%ecx,%ecx,2), %edi
	fldt	_b(,%edi,4)
	fldt	_b(,%eax,4)
	fucompp
	fnstsw	%ax
	sahf
	jbe	L90
	movl	%ecx, %ebx
L90:
	addl	$1, %edx
	cmpl	%esi, %edx
	jle	L92
L89:
	movl	_B(,%ebx,4), %esi
	testl	%esi, %esi
	js	L111
L93:
	movl	$1, %edx
L98:
	addl	$44, %esp
	movl	%edx, %eax
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
L111:
	movl	-36(%ebp), %ecx
	movl	-40(%ebp), %edx
	movl	$_c, 4(%esp)
	movl	$_origC, (%esp)
	leal	1(%ecx,%edx), %eax
	imull	$12, %eax, %eax
	movl	%eax, 8(%esp)
	call	_memcpy
	movl	_N, %eax
	movl	_B, %ecx
	addl	$1, %eax
	testl	%ecx, %ecx
	movl	%eax, _N
	movl	$0, _N(,%eax,4)
	jle	L94
	movl	$1, %eax
	.p2align 4,,7
L95:
	imull	$12120, _B(,%eax,4), %edx
	addl	$1, %eax
	cmpl	%ecx, %eax
	movl	$0, _A(%edx)
	movl	$-2147483648, _A+4(%edx)
	movl	$49151, _A+8(%edx)
	jle	L95
L94:
	movl	_n, %eax
	addl	_m, %eax
	movl	$0, 4(%esp)
	movl	$_c, (%esp)
	addl	$1, %eax
	imull	$12, %eax, %eax
	movl	%eax, 8(%esp)
	call	_memset
	movl	$0, _c
	movl	$-2147483648, _c+4
	movl	$49151, _c+8
	movl	$0, 4(%esp)
	movl	%ebx, (%esp)
	call	__Z5pivotii
	call	__Z3optv
	xorl	%edx, %edx
	fldl	_v
	fldl	LC7
	fucompp
	fnstsw	%ax
	sahf
	ja	L98
	call	__Z7delete0v
	movl	_n, %eax
	addl	_m, %eax
	movl	$_origC, 4(%esp)
	movl	$_c, (%esp)
	addl	$1, %eax
	imull	$12, %eax, %eax
	movl	%eax, 8(%esp)
	call	_memcpy
	movl	_B, %edx
	testl	%edx, %edx
	movl	%edx, -36(%ebp)
	jle	L93
	movl	_N, %ecx
	movl	$1, %edi
	fldl	_v
	.p2align 4,,7
L101:
	movl	_B(,%edi,4), %ebx
	testl	%ecx, %ecx
	leal	(%ebx,%ebx,2), %eax
	fldt	_c(,%eax,4)
	leal	0(,%eax,4), %esi
	fldt	_b(,%eax,4)
	fmul	%st(1), %st
	faddp	%st, %st(2)
	fxch	%st(1)
	fstpl	-32(%ebp)
	fldl	-32(%ebp)
	jle	L113
	movl	$1, %eax
	imull	$12120, %ebx, %ebx
	jmp	L100
	.p2align 4,,7
L112:
	fldt	_c(%esi)
	fxch	%st(1)
L100:
	movl	_N(,%eax,4), %edx
	addl	$1, %eax
	cmpl	%ecx, %eax
	leal	(%edx,%edx,2), %edx
	fldt	_A(%ebx,%edx,4)
	fmulp	%st, %st(2)
	fldt	_c(,%edx,4)
	fsubp	%st, %st(2)
	fxch	%st(1)
	fstpt	_c(,%edx,4)
	jle	L112
	jmp	L99
L113:
	fstp	%st(1)
	.p2align 4,,7
L99:
	addl	$1, %edi
	cmpl	%edi, -36(%ebp)
	jge	L101
	fstpl	_v
	movl	$1, %edx
	jmp	L98
L86:
	fldz
	movl	_B+4, %ebx
	fstpl	_v
	jmp	L89
LFE25:
	.section .rdata,"dr"
LC8:
	.ascii "%d%d\0"
LC9:
	.ascii "%lf\0"
	.text
	.p2align 4,,15
.globl __Z4readv
	.def	__Z4readv;	.scl	2;	.type	32;	.endef
__Z4readv:
LFB21:
	pushl	%ebp
LCFI21:
	movl	%esp, %ebp
LCFI22:
	pushl	%edi
LCFI23:
	pushl	%esi
LCFI24:
	pushl	%ebx
LCFI25:
	subl	$44, %esp
LCFI26:
	movl	$_m, 8(%esp)
	movl	$_n, 4(%esp)
	movl	$LC8, (%esp)
	call	_scanf
	movl	_n, %eax
	testl	%eax, %eax
	jle	L115
	movl	$_c+12, %edi
	movl	$1, %ebx
	leal	-32(%ebp), %esi
	.p2align 4,,7
L116:
	movl	%esi, 4(%esp)
	addl	$1, %ebx
	movl	$LC9, (%esp)
	call	_scanf
	fldl	-32(%ebp)
	fstpt	(%edi)
	addl	$12, %edi
	cmpl	%ebx, _n
	jge	L116
L115:
	movl	_m, %edi
	testl	%edi, %edi
	jle	L122
	movl	_n, %eax
	movl	$1, %edi
	leal	-32(%ebp), %esi
	.p2align 4,,7
L118:
	testl	%eax, %eax
	jle	L121
	movl	$1, %ebx
	.p2align 4,,7
L119:
	movl	%esi, 4(%esp)
	movl	$LC9, (%esp)
	call	_scanf
	movl	_n, %eax
	leal	(%ebx,%ebx,2), %ecx
	addl	$1, %ebx
	leal	(%edi,%eax), %edx
	imull	$12120, %edx, %edx
	cmpl	%ebx, %eax
	fldl	-32(%ebp)
	fstpt	_A(%edx,%ecx,4)
	jge	L119
L121:
	movl	%esi, 4(%esp)
	movl	$LC9, (%esp)
	call	_scanf
	movl	_n, %eax
	leal	(%edi,%eax), %edx
	addl	$1, %edi
	cmpl	%edi, _m
	leal	(%edx,%edx,2), %edx
	fldl	-32(%ebp)
	fstpt	_b(,%edx,4)
	jge	L118
L122:
	addl	$44, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
LFE21:
	.section .rdata,"dr"
LC10:
	.ascii "Infeasible\0"
LC11:
	.ascii "Unbounded\0"
LC12:
	.ascii "Max value is %f\12\0"
	.text
	.p2align 4,,15
.globl __Z7simplexv
	.def	__Z7simplexv;	.scl	2;	.type	32;	.endef
__Z7simplexv:
LFB26:
	pushl	%ebp
LCFI27:
	movl	%esp, %ebp
LCFI28:
	pushl	%edi
LCFI29:
	pushl	%esi
LCFI30:
	pushl	%ebx
LCFI31:
	subl	$28, %esp
LCFI32:
	call	__Z4readv
	call	__Z10initializev
	testl	%eax, %eax
	je	L132
	.p2align 4,,6
	call	__Z3optv
	testl	%eax, %eax
	.p2align 4,,4
	je	L133
	fldl	_v
	fstpl	4(%esp)
	movl	$LC12, (%esp)
	call	_printf
	movl	_n, %eax
	addl	_m, %eax
	movl	$0, 4(%esp)
	movl	$_x, (%esp)
	leal	3(%eax,%eax,2), %eax
	sall	$2, %eax
	movl	%eax, 8(%esp)
	call	_memset
	movl	_B, %ecx
	testl	%ecx, %ecx
	jle	L130
	movl	$1, %eax
	.p2align 4,,7
L129:
	movl	_B(,%eax,4), %edx
	addl	$1, %eax
	cmpl	%ecx, %eax
	leal	(%edx,%edx,2), %edx
	movl	_b(,%edx,4), %ebx
	movl	_b+4(,%edx,4), %esi
	movl	_b+8(,%edx,4), %edi
	movl	%ebx, _x(,%edx,4)
	movl	%esi, _x+4(,%edx,4)
	movl	%edi, _x+8(,%edx,4)
	jle	L129
L130:
	addl	$28, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
L133:
	movl	$LC11, (%esp)
	call	_puts
	addl	$28, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.p2align 4,,7
L132:
	movl	$LC10, (%esp)
	call	_puts
	addl	$28, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
LFE26:
	.def	___main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
LC13:
	.ascii "r\0"
LC14:
	.ascii "a.in\0"
LC15:
	.ascii "w\0"
LC16:
	.ascii "rp_a_greedy.out\0"
LC17:
	.ascii "%d\12\0"
LC18:
	.ascii "%d %d\12\0"
	.text
	.p2align 4,,15
.globl _main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
LFB27:
	pushl	%ebp
LCFI33:
	movl	%esp, %ebp
LCFI34:
	andl	$-16, %esp
LCFI35:
	pushl	%ebx
LCFI36:
	subl	$28, %esp
LCFI37:
	call	___main
	movl	__imp___iob, %ebx
	movl	$LC13, 4(%esp)
	movl	$LC14, (%esp)
	movl	%ebx, 8(%esp)
	addl	$32, %ebx
	call	_freopen
	movl	%ebx, 8(%esp)
	movl	$LC15, 4(%esp)
	movl	$LC16, (%esp)
	call	_freopen
	call	_clock
	movl	%eax, %ebx
	call	__Z7simplexv
	call	_clock
	movl	$LC17, (%esp)
	subl	%ebx, %eax
	movl	%eax, 4(%esp)
	call	_printf
	movl	_s2, %eax
	movl	$LC18, (%esp)
	movl	%eax, 8(%esp)
	movl	_s1, %eax
	movl	%eax, 4(%esp)
	call	_printf
	addl	$28, %esp
	xorl	%eax, %eax
	popl	%ebx
	movl	%ebp, %esp
	popl	%ebp
	ret
LFE27:
.globl _A
	.bss
	.align 32
_A:
	.space 12241200
.globl _b
	.align 32
_b:
	.space 12120
.globl _c
	.align 32
_c:
	.space 12120
.globl _x
	.align 32
_x:
	.space 12120
.globl _origC
	.align 32
_origC:
	.space 12120
.globl _a1
	.align 32
_a1:
	.space 12120
.globl _a2
	.align 32
_a2:
	.space 12120
.globl _N
	.align 32
_N:
	.space 4040
.globl _B
	.align 32
_B:
	.space 4040
.globl _n
	.align 4
_n:
	.space 4
.globl _m
	.align 4
_m:
	.space 4
.globl _s1
	.align 4
_s1:
	.space 4
.globl _s2
	.align 4
_s2:
	.space 4
.globl _tt
	.align 4
_tt:
	.space 4
.globl _v
	.align 8
_v:
	.space 8
	.section .rdata,"dr"
	.align 4
LC0:
	.long	1065353216
	.align 8
LC3:
	.long	-640172613
	.long	1037794527
	.align 8
LC4:
	.long	2025163840
	.long	1142271773
	.align 8
LC5:
	.long	2061584302
	.long	-1074811372
	.align 8
LC7:
	.long	-640172613
	.long	-1109689121
	.def	_memcpy;	.scl	2;	.type	32;	.endef
	.def	_scanf;	.scl	2;	.type	32;	.endef
	.def	_memset;	.scl	2;	.type	32;	.endef
	.def	_puts;	.scl	2;	.type	32;	.endef
	.def	_freopen;	.scl	2;	.type	32;	.endef
	.def	_clock;	.scl	2;	.type	32;	.endef
	.def	_printf;	.scl	2;	.type	32;	.endef
