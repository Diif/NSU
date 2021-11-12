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
	#movq	%r12, %rax # do i --> eax
	#cltq # convert long to quad
	leaq	0(,%r12,8), %rbx # rdx = i * 8
	#movq	-40(%rbp), %rax #  в rax кладет v1
	addq	-40(%rbp), %rbx #
	#leaq	(%rdx,%rax), %rbx # rbx = rdx + rax, rbx = v1[i*8]
	call	rand # берет случайное число, но т.к. зерна нет, то исход один
	pxor	%xmm0, %xmm0 # v1[i*8] = rand() * const1 / const 2 - const 3
	cvtsi2sd	%eax, %xmm0 # convert eax to double
	#movsd	.LC0(%rip), %xmm1 # const1 -> xmm1
	mulsd	.LC0(%rip), %xmm0 # xmm1 * xmm0
	#movsd	.LC1(%rip), %xmm1 # const2 --> xmm1
	divsd	.LC1(%rip), %xmm0 # xmm0 / xmm1
	#movsd	.LC2(%rip), %xmm1 # const3 --> xmm1
	subsd	.LC2(%rip), %xmm0 # xmm0 - xmm1;
	movsd	%xmm0, (%rbx) # v1[i*8] = result
	movq	%r12, %rax # i--> eax
	#cltq
	leaq	0(,%rax,8), %rdx # i * 8 --> rdx
	movq	-48(%rbp), %rax # v2[0] -->rax
	leaq	(%rdx,%rax), %rbx # rbx = rax + rdx
	call	rand
	pxor	%xmm0, %xmm0
	cvtsi2sd	%eax, %xmm0
	movsd	.LC0(%rip), %xmm1
	mulsd	%xmm1, %xmm0
	movsd	.LC1(%rip), %xmm1
	divsd	%xmm1, %xmm0
	movsd	.LC2(%rip), %xmm1
	subsd	%xmm1, %xmm0
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
	pxor	%xmm0, %xmm0
	movsd	%xmm0, -8(%rbp) # k = 0 -> -8rbp
	movl	$0, -12(%rbp) # int i = 0
.L7:
	cmpl	$49999999, -12(%rbp)
	jg	.L6 # if i <= 49999999
	movl	-12(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx # rdx = i * 8
	movq	-24(%rbp), %rax # rax = v1
	addq	%rdx, %rax # rax = v1 + i*8
	movq	(%rax), %rax # rax = v1[i*8]
	movq	%rax, -40(%rbp) # -40rbp = v1[i*8]
	movsd	-40(%rbp), %xmm0 # v1[i*8] -> xmm0
	call	sin # sin(v1[i*8])
	movapd	%xmm0, %xmm1 # copy xmm0 -> xmm1
	movsd	.LC4(%rip), %xmm0 # const1 -> xmm0
	mulsd	%xmm0, %xmm1 # xmm1 = const1 * xmm1
	movsd	%xmm1, -40(%rbp) # xmm1 -> -40rbp, -40rbp = sin(v1[i*8]) * const1
	movl	-12(%rbp), %eax  # eax = i
	cltq
	leaq	0(,%rax,8), %rdx # rdx = i * 8
	movq	-32(%rbp), %rax # rax = v2
	addq	%rdx, %rax # rdx = v2 + i * 8
	movq	(%rax), %rax # rax = v2[i*8]
	movq	%rax, -48(%rbp) # v2[i*8] -> -48rbp
	movsd	-48(%rbp), %xmm0
	call	cos # cos(v2[i*8])
	mulsd	-40(%rbp), %xmm0 # xmm0 = cos(v2[i*8]) * sin(v1[i*8]) * const1
	movsd	-8(%rbp), %xmm1 # xmm1 = k
	addsd	%xmm1, %xmm0 # xmm0 = xmm0 + k
	movsd	%xmm0, -8(%rbp) # k = k + xmm0
	addl	$1, -12(%rbp) # i++
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
	pxor	%xmm0, %xmm0
	movsd	%xmm0, -24(%rbp) # -24(%rbp) = 0
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
	movq	%xmm0, %rax
	movq	%rax, -24(%rbp) # -24rbp = fun2 = k
	movq	-24(%rbp), %rax # -24rbp -> rax
	movq	%rax, -40(%rbp) # double m = k
	movsd	-40(%rbp), %xmm0
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
