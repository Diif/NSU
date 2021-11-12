	.file	"prog.cpp"
	.text
	.globl	_Z5func1PdS_
	.type	_Z5func1PdS_, @function
_Z5func1PdS_:
.LFB2:
	pushq	%rbp
.LCFI0:
	movq	%rsp, %rbp
.LCFI1:
	pushq	%rbx
	subq	$40, %rsp
.LCFI2:
	movq	%rdi, -40(%rbp) # double* v1 --> -40rbp
	movq	%rsi, -48(%rbp) # double* v2 --> -48rbp
	movq	$0, %r12 # int i = 0 ---> -20rbp
.L3:
	cmpq	$49999999, %r12
	jg	.L2 # if i < 49999999
	leaq	0(,%r12,8), %rbx # rdx = i * 8
	addq	-40(%rbp), %rbx #
	call	rand # берет случайное число, но т.к. зерна нет, то исход один
	pxor	%xmm0, %xmm0 # v1[i*8] = rand() * const1 / const 2 - const 3
	cvtsi2sd	%eax, %xmm0 # convert eax to double
	mulsd	.LC0(%rip), %xmm0 # xmm1 * xmm0
	divsd	.LC1(%rip), %xmm0 # xmm0 / xmm1
	subsd	.LC2(%rip), %xmm0 # xmm0 - xmm1;
	movsd	%xmm0, (%rbx) # v1[i*8] = result
	leaq	0(,%r12,8), %rbx # i * 8 --> rdx
	addq	-48(%rbp), %rbx
	call	rand
	pxor	%xmm0, %xmm0
	cvtsi2sd	%eax, %xmm0
	mulsd	.LC0(%rip), %xmm0
	divsd	.LC1(%rip), %xmm0
	subsd	.LC2(%rip), %xmm0
	movsd	%xmm0, (%rbx)
	addq	$1, %r12 # i++
	jmp	.L3
.L2: # else
	movl	$0, %eax
	addq	$40, %rsp
	popq	%rbx
	popq	%rbp
.LCFI3:
	ret
.LFE2:
	.size	_Z5func1PdS_, .-_Z5func1PdS_
	.globl	_Z5func2PdS_
	.type	_Z5func2PdS_, @function
_Z5func2PdS_:
.LFB3:
	pushq	%rbp
.LCFI4:
	movq	%rsp, %rbp
.LCFI5:
	subq	$48, %rsp
	movq	%rdi, -24(%rbp) # v1 -> -24
	movq	%rsi, -32(%rbp) # v2 -> -32
	movq	$0, %r12 # int i = 0
	movq	%r12, -8(%rbp)
.L7:
	cmpq	$49999999, %r12
	jg	.L6 # if i <= 49999999
	leaq	0(,%r12,8), %rdx # rdx = i * 8
	addq	-24(%rbp), %rdx
	movsd	(%rdx), %xmm0
	call	sin # sin(v1[i*8])
	mulsd	.LC4(%rip), %xmm0 # xmm1 = const1 * xmm1
	movsd	%xmm0, -40(%rbp) # xmm1 -> -40rbp, -40rbp = sin(v1[i*8]) * const1
	leaq	0(,%r12,8), %rdx # rdx = i * 8
	addq	-32(%rbp), %rdx
	movsd	(%rdx), %xmm0
	call	cos # cos(v2[i*8])

	mulsd	-40(%rbp), %xmm0 # xmm0 = cos(v2[i*8]) * sin(v1[i*8]) * const1
	movsd	-8(%rbp), %xmm1 # xmm1 = k
	addsd	%xmm1, %xmm0 # xmm0 = xmm0 + k
	movsd	%xmm0, -8(%rbp) # k = k + xmm0
	addq	$1, %r12 # i++
	jmp	.L7
.L6:
	movsd	-8(%rbp), %xmm0 # return k
	leave
.LCFI6:
	ret
.LFE3:
	.size	_Z5func2PdS_, .-_Z5func2PdS_
	.section	.rodata
.LC5:
	.string	"\n\n result = %lf"
	.text
	.globl	main
	.type	main, @function
main:
.LFB4:
	pushq	%rbp
.LCFI7:
	movq	%rsp, %rbp
.LCFI8:
	subq	$48, %rsp
	movl	$400000000, %edi
	call	_Znam # new 
	movq	%rax, -16(%rbp) # double v1 = new double[400000000] --> -16rbp
	movl	$400000000, %edi
	call	_Znam
	movq	%rax, -8(%rbp) # double v2 = new double[400000000] --> -8rbp
	movq	-8(%rbp), %rdx
	movq	-16(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_Z5func1PdS_ # fun1(v1, v2)
	movq	-8(%rbp), %rdx # v2 -> rdx
	movq	-16(%rbp), %rax # v1 -> rax
	movq	%rdx, %rsi # v2 -> rsi
	movq	%rax, %rdi # v1 -> rdi
	call	_Z5func2PdS_ # get k
	movl	$.LC5, %edi
	movl	$1, %eax
	call	printf #printf("\n\n result = %lf", m);
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	_ZdlPv # delete v1
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZdlPv # delete v2
	movl	$0, %eax
	leave
.LCFI9:
	ret
.LFE4:
	.size	main, .-main
	.section	.rodata
	.align 8
.LC0:
	.long	0 # 00000000000000000000000000000000
	.long	1079574528 # 01000000010110010000000000000000
	.align 8
.LC1:
	.long	4290772992
	.long	1105199103
	.align 8
.LC2:
	.long	0
	.long	1078525952
	.align 8
.LC4:
	.long	3100958126
	.long	1075678820
	.section	.eh_frame,"a",@progbits
.LEFDE1:
	.ident	"GCC: (Ubuntu 5.5.0-12ubuntu1~16.04) 5.5.0 20171010"
	.section	.note.GNU-stack,"",@progbits
