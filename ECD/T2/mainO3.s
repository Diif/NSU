	.file	"main.cpp"
	.section	.text.unlikely._ZNKSt5ctypeIcE8do_widenEc,"axG",@progbits,_ZNKSt5ctypeIcE8do_widenEc,comdat
	.align 2
.LCOLDB0:
	.section	.text._ZNKSt5ctypeIcE8do_widenEc,"axG",@progbits,_ZNKSt5ctypeIcE8do_widenEc,comdat
.LHOTB0:
	.align 2
	.p2align 4,,15
	.weak	_ZNKSt5ctypeIcE8do_widenEc
	.type	_ZNKSt5ctypeIcE8do_widenEc, @function
_ZNKSt5ctypeIcE8do_widenEc:
.LFB1447:
	movl	%esi, %eax
	ret
.LFE1447:
	.size	_ZNKSt5ctypeIcE8do_widenEc, .-_ZNKSt5ctypeIcE8do_widenEc
	.section	.text.unlikely._ZNKSt5ctypeIcE8do_widenEc,"axG",@progbits,_ZNKSt5ctypeIcE8do_widenEc,comdat
.LCOLDE0:
	.section	.text._ZNKSt5ctypeIcE8do_widenEc,"axG",@progbits,_ZNKSt5ctypeIcE8do_widenEc,comdat
.LHOTE0:
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC1:
	.string	"basic_string::_M_construct null not valid"
	.section	.text.unlikely,"ax",@progbits
	.align 2
.LCOLDB2:
	.text
.LHOTB2:
	.align 2
	.p2align 4,,15
	.type	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE12_M_constructIPcEEvT_S7_St20forward_iterator_tag.isra.28, @function
_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE12_M_constructIPcEEvT_S7_St20forward_iterator_tag.isra.28:
.LFB2514:
	pushq	%r12
.LCFI0:
	pushq	%rbp
.LCFI1:
	movq	%rsi, %r12
	pushq	%rbx
.LCFI2:
	movq	%rdi, %rbp
	subq	$16, %rsp
.LCFI3:
	movq	%fs:40, %rax
	movq	%rax, 8(%rsp)
	xorl	%eax, %eax
	testq	%rsi, %rsi
	jne	.L5
	testq	%rdx, %rdx
	je	.L5
	movl	$.LC1, %edi
	call	_ZSt19__throw_logic_errorPKc
	.p2align 4,,10
	.p2align 3
.L5:
	movq	%rdx, %rbx
	subq	%r12, %rbx
	cmpq	$15, %rbx
	movq	%rbx, (%rsp)
	ja	.L24
	movq	0(%rbp), %rdx
	cmpq	$1, %rbx
	movq	%rdx, %rdi
	je	.L25
	testq	%rbx, %rbx
	jne	.L6
.L8:
	movq	(%rsp), %rax
	movq	%rax, 8(%rbp)
	movb	$0, (%rdx,%rax)
	movq	8(%rsp), %rax
	xorq	%fs:40, %rax
	jne	.L26
	addq	$16, %rsp
.LCFI4:
	popq	%rbx
.LCFI5:
	popq	%rbp
.LCFI6:
	popq	%r12
.LCFI7:
	ret
.L24:
.LCFI8:
	movq	%rbp, %rdi
	xorl	%edx, %edx
	movq	%rsp, %rsi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_createERmm
	movq	%rax, %rdi
	movq	%rax, 0(%rbp)
	movq	(%rsp), %rax
	movq	%rax, 16(%rbp)
.L6:
	movq	%rbx, %rdx
	movq	%r12, %rsi
	call	memcpy
	movq	0(%rbp), %rdx
	jmp	.L8
.L25:
	movzbl	(%r12), %eax
	movb	%al, (%rdx)
	movq	0(%rbp), %rdx
	jmp	.L8
.L26:
	call	__stack_chk_fail
.LFE2514:
	.size	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE12_M_constructIPcEEvT_S7_St20forward_iterator_tag.isra.28, .-_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE12_M_constructIPcEEvT_S7_St20forward_iterator_tag.isra.28
	.section	.text.unlikely
.LCOLDE2:
	.text
.LHOTE2:
	.set	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE12_M_constructIPKcEEvT_S8_St20forward_iterator_tag.isra.23,_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE12_M_constructIPcEEvT_S7_St20forward_iterator_tag.isra.28
	.section	.text.unlikely
	.align 2
.LCOLDB3:
	.text
.LHOTB3:
	.align 2
	.p2align 4,,15
	.type	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC2EPKcRKS3_.isra.25, @function
_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC2EPKcRKS3_.isra.25:
.LFB2511:
	pushq	%rbp
.LCFI9:
	pushq	%rbx
.LCFI10:
	leaq	16(%rdi), %rax
	orq	$-1, %rdx
	movq	%rdi, %rbp
	movq	%rsi, %rbx
	subq	$8, %rsp
.LCFI11:
	testq	%rsi, %rsi
	movq	%rax, (%rdi)
	je	.L28
	movq	%rsi, %rdi
	call	strlen
	leaq	(%rbx,%rax), %rdx
.L28:
	addq	$8, %rsp
.LCFI12:
	movq	%rbx, %rsi
	movq	%rbp, %rdi
	popq	%rbx
.LCFI13:
	popq	%rbp
.LCFI14:
	jmp	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE12_M_constructIPKcEEvT_S8_St20forward_iterator_tag.isra.23
.LFE2511:
	.size	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC2EPKcRKS3_.isra.25, .-_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC2EPKcRKS3_.isra.25
	.section	.text.unlikely
.LCOLDE3:
	.text
.LHOTE3:
	.section	.text.unlikely
.LCOLDB4:
	.text
.LHOTB4:
	.p2align 4,,15
	.globl	_Z18WriteDoubleToTabledNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE
	.type	_Z18WriteDoubleToTabledNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE, @function
_Z18WriteDoubleToTabledNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE:
.LFB2220:
	pushq	%r12
.LCFI15:
	pushq	%rbp
.LCFI16:
	movq	%rdi, %rbp
	pushq	%rbx
.LCFI17:
	subq	$560, %rsp
.LCFI18:
	leaq	280(%rsp), %rdi
	movsd	%xmm0, 8(%rsp)
	movq	%fs:40, %rax
	movq	%rax, 552(%rsp)
	xorl	%eax, %eax
	call	_ZNSt8ios_baseC2Ev
	movq	_ZTTSt14basic_ofstreamIcSt11char_traitsIcEE+8(%rip), %rbx
	movb	$0, 504(%rsp)
	leaq	32(%rsp), %rdi
	movq	_ZTTSt14basic_ofstreamIcSt11char_traitsIcEE+16(%rip), %r12
	movq	$_ZTVSt9basic_iosIcSt11char_traitsIcEE+16, 280(%rsp)
	xorl	%esi, %esi
	movq	$0, 496(%rsp)
	movb	$0, 505(%rsp)
	addq	-24(%rbx), %rdi
	movq	$0, 512(%rsp)
	movq	$0, 520(%rsp)
	movq	$0, 528(%rsp)
	movq	$0, 536(%rsp)
	movq	%rbx, 32(%rsp)
	movq	%r12, (%rdi)
.LEHB0:
	call	_ZNSt9basic_iosIcSt11char_traitsIcEE4initEPSt15basic_streambufIcS1_E
.LEHE0:
	leaq	32(%rsp), %rax
	movq	$_ZTVSt14basic_ofstreamIcSt11char_traitsIcEE+24, 32(%rsp)
	movq	$_ZTVSt14basic_ofstreamIcSt11char_traitsIcEE+64, 280(%rsp)
	leaq	8(%rax), %rdi
.LEHB1:
	call	_ZNSt13basic_filebufIcSt11char_traitsIcEEC1Ev
.LEHE1:
	leaq	32(%rsp), %rax
	leaq	40(%rsp), %rsi
	leaq	248(%rax), %rdi
.LEHB2:
	call	_ZNSt9basic_iosIcSt11char_traitsIcEE4initEPSt15basic_streambufIcS1_E
.LEHE2:
	leaq	32(%rsp), %rax
	movq	0(%rbp), %rsi
	movl	$17, %edx
	leaq	8(%rax), %rdi
.LEHB3:
	call	_ZNSt13basic_filebufIcSt11char_traitsIcEE4openEPKcSt13_Ios_Openmode
	testq	%rax, %rax
	leaq	32(%rsp), %rdi
	movq	32(%rsp), %rax
	je	.L61
	addq	-24(%rax), %rdi
	xorl	%esi, %esi
	call	_ZNSt9basic_iosIcSt11char_traitsIcEE5clearESt12_Ios_Iostate
.L41:
	movq	8(%rbp), %rdx
	cmpq	_ZL14kOutFileValues+8(%rip), %rdx
	je	.L62
.L40:
	movq	32(%rsp), %rax
	leaq	32(%rsp), %rdx
	leaq	32(%rsp), %rdi
	movsd	8(%rsp), %xmm0
	addq	-24(%rax), %rdx
	movl	24(%rdx), %eax
	movq	$3, 8(%rdx)
	andl	$-261, %eax
	orl	$4, %eax
	movl	%eax, 24(%rdx)
	call	_ZNSo9_M_insertIdEERSoT_
	leaq	31(%rsp), %rsi
	movl	$1, %edx
	movq	%rax, %rdi
	movb	$44, 31(%rsp)
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
.L43:
	leaq	32(%rsp), %rax
	leaq	8(%rax), %rdi
	call	_ZNSt13basic_filebufIcSt11char_traitsIcEE5closeEv
.LEHE3:
	testq	%rax, %rax
	je	.L44
.L45:
	leaq	40(%rsp), %rdi
	movq	$_ZTVSt14basic_ofstreamIcSt11char_traitsIcEE+24, 32(%rsp)
	movq	$_ZTVSt14basic_ofstreamIcSt11char_traitsIcEE+64, 280(%rsp)
	movq	$_ZTVSt13basic_filebufIcSt11char_traitsIcEE+16, 40(%rsp)
	call	_ZNSt13basic_filebufIcSt11char_traitsIcEE5closeEv
	leaq	144(%rsp), %rdi
	call	_ZNSt12__basic_fileIcED1Ev
	leaq	96(%rsp), %rdi
	movq	$_ZTVSt15basic_streambufIcSt11char_traitsIcEE+16, 40(%rsp)
	call	_ZNSt6localeD1Ev
	movq	-24(%rbx), %rax
	leaq	280(%rsp), %rdi
	movq	%r12, 32(%rsp,%rax)
	movq	$_ZTVSt9basic_iosIcSt11char_traitsIcEE+16, 280(%rsp)
	call	_ZNSt8ios_baseD2Ev
	movq	552(%rsp), %rax
	xorq	%fs:40, %rax
	jne	.L63
	addq	$560, %rsp
.LCFI19:
	popq	%rbx
.LCFI20:
	popq	%rbp
.LCFI21:
	popq	%r12
.LCFI22:
	ret
	.p2align 4,,10
	.p2align 3
.L62:
.LCFI23:
	testq	%rdx, %rdx
	jne	.L64
.L42:
	movq	32(%rsp), %rax
	leaq	32(%rsp), %rdx
	leaq	32(%rsp), %rdi
	movsd	8(%rsp), %xmm0
	addq	-24(%rax), %rdx
	movl	24(%rdx), %eax
	movq	$8, 8(%rdx)
	andl	$-261, %eax
	orl	$4, %eax
	movl	%eax, 24(%rdx)
.LEHB4:
	call	_ZNSo9_M_insertIdEERSoT_
	leaq	30(%rsp), %rsi
	movl	$1, %edx
	movq	%rax, %rdi
	movb	$44, 30(%rsp)
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
	jmp	.L43
	.p2align 4,,10
	.p2align 3
.L64:
	movq	_ZL14kOutFileValues(%rip), %rsi
	movq	0(%rbp), %rdi
	call	memcmp
	testl	%eax, %eax
	jne	.L40
	jmp	.L42
	.p2align 4,,10
	.p2align 3
.L61:
	addq	-24(%rax), %rdi
	movl	32(%rdi), %esi
	orl	$4, %esi
	call	_ZNSt9basic_iosIcSt11char_traitsIcEE5clearESt12_Ios_Iostate
	jmp	.L41
	.p2align 4,,10
	.p2align 3
.L44:
	movq	32(%rsp), %rax
	leaq	32(%rsp), %rdi
	addq	-24(%rax), %rdi
	movl	32(%rdi), %esi
	orl	$4, %esi
	call	_ZNSt9basic_iosIcSt11char_traitsIcEE5clearESt12_Ios_Iostate
.LEHE4:
	jmp	.L45
.L63:
	call	__stack_chk_fail
.L51:
	leaq	40(%rsp), %rdi
	movq	%rax, %rbp
	call	_ZNSt13basic_filebufIcSt11char_traitsIcEED1Ev
	movq	%rbp, %rax
.L36:
	movq	-24(%rbx), %rdx
	movq	%rax, %rbx
	movq	%r12, 32(%rsp,%rdx)
.L37:
	leaq	280(%rsp), %rdi
	movq	$_ZTVSt9basic_iosIcSt11char_traitsIcEE+16, 280(%rsp)
	call	_ZNSt8ios_baseD2Ev
	movq	%rbx, %rdi
.LEHB5:
	call	_Unwind_Resume
.L50:
	jmp	.L36
.L48:
	leaq	32(%rsp), %rdi
	movq	%rax, %rbx
	call	_ZNSt14basic_ofstreamIcSt11char_traitsIcEED1Ev
	movq	%rbx, %rdi
	call	_Unwind_Resume
.LEHE5:
.L49:
	movq	%rax, %rbx
	jmp	.L37
.LFE2220:
	.globl	__gxx_personality_v0
	.section	.gcc_except_table,"a",@progbits
.LLSDA2220:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2220-.LLSDACSB2220
.LLSDACSB2220:
	.uleb128 .LEHB0-.LFB2220
	.uleb128 .LEHE0-.LEHB0
	.uleb128 .L49-.LFB2220
	.uleb128 0
	.uleb128 .LEHB1-.LFB2220
	.uleb128 .LEHE1-.LEHB1
	.uleb128 .L50-.LFB2220
	.uleb128 0
	.uleb128 .LEHB2-.LFB2220
	.uleb128 .LEHE2-.LEHB2
	.uleb128 .L51-.LFB2220
	.uleb128 0
	.uleb128 .LEHB3-.LFB2220
	.uleb128 .LEHE3-.LEHB3
	.uleb128 .L48-.LFB2220
	.uleb128 0
	.uleb128 .LEHB4-.LFB2220
	.uleb128 .LEHE4-.LEHB4
	.uleb128 .L48-.LFB2220
	.uleb128 0
	.uleb128 .LEHB5-.LFB2220
	.uleb128 .LEHE5-.LEHB5
	.uleb128 0
	.uleb128 0
.LLSDACSE2220:
	.text
	.size	_Z18WriteDoubleToTabledNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE, .-_Z18WriteDoubleToTabledNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE
	.section	.text.unlikely
.LCOLDE4:
	.text
.LHOTE4:
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC6:
	.string	"    res:  "
	.section	.text.unlikely
.LCOLDB9:
	.text
.LHOTB9:
	.p2align 4,,15
	.globl	_Z28MakeMeasurementAndGetTimeSecx
	.type	_Z28MakeMeasurementAndGetTimeSecx, @function
_Z28MakeMeasurementAndGetTimeSecx:
.LFB2219:
	pushq	%r12
.LCFI24:
	pushq	%rbp
.LCFI25:
	movq	%rdi, %rbp
	pushq	%rbx
.LCFI26:
	movl	$2, %edi
	subq	$176, %rsp
.LCFI27:
	movq	%fs:40, %rax
	movq	%rax, 168(%rsp)
	xorl	%eax, %eax
	call	sysconf
	movq	%rbp, %rsi
	movl	$_ZSt4cout, %edi
	movq	%rax, %r12
.LEHB6:
	call	_ZNSo9_M_insertIxEERSoT_
	movl	$10, %edx
	movl	$.LC6, %esi
	movq	%rax, %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
	leaq	64(%rsp), %rdi
	call	times
	pxor	%xmm0, %xmm0
	testq	%rbp, %rbp
	movsd	.LC7(%rip), %xmm1
	cvtsi2sdq	%rbp, %xmm0
	divsd	%xmm0, %xmm1
	movsd	%xmm1, 40(%rsp)
	pxor	%xmm1, %xmm1
	jle	.L66
	pxor	%xmm7, %xmm7
	xorl	%ebx, %ebx
	movsd	%xmm7, 16(%rsp)
	movapd	%xmm7, %xmm1
	movsd	%xmm7, 8(%rsp)
	.p2align 4,,10
	.p2align 3
.L67:
	movsd	8(%rsp), %xmm0
	addq	$1, %rbx
	movsd	%xmm1, 32(%rsp)
	call	exp
	movsd	8(%rsp), %xmm2
	mulsd	16(%rsp), %xmm0
	addsd	40(%rsp), %xmm2
	movsd	%xmm0, 24(%rsp)
	movapd	%xmm2, %xmm0
	movsd	%xmm2, 8(%rsp)
	call	sin
	movsd	%xmm0, 16(%rsp)
	movsd	8(%rsp), %xmm0
	call	exp
	mulsd	16(%rsp), %xmm0
	cmpq	%rbp, %rbx
	movsd	32(%rsp), %xmm1
	addsd	24(%rsp), %xmm0
	mulsd	.LC8(%rip), %xmm0
	addsd	%xmm0, %xmm1
	jne	.L67
.L66:
	mulsd	40(%rsp), %xmm1
	leaq	96(%rsp), %rdi
	movsd	%xmm1, 8(%rsp)
	call	times
	movq	_ZL14kOutFileValues(%rip), %rbp
	leaq	144(%rsp), %rax
	movq	_ZL14kOutFileValues+8(%rip), %rbx
	movq	%rax, 128(%rsp)
	movq	%rbp, %rax
	addq	%rbx, %rax
	je	.L70
	testq	%rbp, %rbp
	jne	.L70
	movl	$.LC1, %edi
	call	_ZSt19__throw_logic_errorPKc
.LEHE6:
	.p2align 4,,10
	.p2align 3
.L70:
	cmpq	$15, %rbx
	movq	%rbx, 56(%rsp)
	ja	.L98
	cmpq	$1, %rbx
	je	.L99
	testq	%rbx, %rbx
	leaq	144(%rsp), %rax
	jne	.L100
.L73:
	leaq	128(%rsp), %rdi
	movsd	8(%rsp), %xmm0
	movq	%rbx, 136(%rsp)
	movb	$0, (%rax,%rbx)
.LEHB7:
	call	_Z18WriteDoubleToTabledNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE
.LEHE7:
	movq	128(%rsp), %rdi
	leaq	144(%rsp), %rax
	cmpq	%rax, %rdi
	je	.L74
	call	_ZdlPv
.L74:
	movsd	8(%rsp), %xmm0
	movl	$_ZSt4cout, %edi
	movq	$5, _ZSt4cout+16(%rip)
.LEHB8:
	call	_ZNSo9_M_insertIdEERSoT_
	movq	%rax, %rbp
	movq	(%rax), %rax
	movq	-24(%rax), %rax
	movq	240(%rbp,%rax), %rbx
	testq	%rbx, %rbx
	je	.L101
	cmpb	$0, 56(%rbx)
	je	.L76
	movsbl	67(%rbx), %esi
.L77:
	movq	%rbp, %rdi
	call	_ZNSo3putEc
	movq	%rax, %rdi
	call	_ZNSo5flushEv
	movq	96(%rsp), %rax
	subq	64(%rsp), %rax
	pxor	%xmm0, %xmm0
	pxor	%xmm1, %xmm1
	cvtsi2sdq	%rax, %xmm0
	cvtsi2sdq	%r12, %xmm1
	movq	168(%rsp), %rax
	xorq	%fs:40, %rax
	divsd	%xmm1, %xmm0
	jne	.L102
	addq	$176, %rsp
.LCFI28:
	popq	%rbx
.LCFI29:
	popq	%rbp
.LCFI30:
	popq	%r12
.LCFI31:
	ret
	.p2align 4,,10
	.p2align 3
.L76:
.LCFI32:
	movq	%rbx, %rdi
	call	_ZNKSt5ctypeIcE13_M_widen_initEv
	movq	(%rbx), %rax
	movl	$10, %esi
	movq	48(%rax), %rax
	cmpq	$_ZNKSt5ctypeIcE8do_widenEc, %rax
	je	.L77
	movq	%rbx, %rdi
	call	*%rax
	movsbl	%al, %esi
	jmp	.L77
	.p2align 4,,10
	.p2align 3
.L98:
	leaq	128(%rsp), %rdi
	leaq	56(%rsp), %rsi
	xorl	%edx, %edx
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_createERmm
	movq	%rax, %rdi
	movq	%rax, 128(%rsp)
	movq	56(%rsp), %rax
	movq	%rax, 144(%rsp)
.L71:
	movq	%rbx, %rdx
	movq	%rbp, %rsi
	call	memcpy
	movq	56(%rsp), %rbx
	movq	128(%rsp), %rax
	jmp	.L73
	.p2align 4,,10
	.p2align 3
.L99:
	movzbl	0(%rbp), %eax
	movb	%al, 144(%rsp)
	leaq	144(%rsp), %rax
	jmp	.L73
.L100:
	movq	%rax, %rdi
	jmp	.L71
.L101:
	call	_ZSt16__throw_bad_castv
.L86:
	movq	128(%rsp), %rdi
	movq	%rax, %rbx
	leaq	144(%rsp), %rax
	cmpq	%rax, %rdi
	je	.L79
	call	_ZdlPv
.L79:
	movq	%rbx, %rdi
	call	_Unwind_Resume
.LEHE8:
.L102:
	call	__stack_chk_fail
.LFE2219:
	.section	.gcc_except_table
.LLSDA2219:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2219-.LLSDACSB2219
.LLSDACSB2219:
	.uleb128 .LEHB6-.LFB2219
	.uleb128 .LEHE6-.LEHB6
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB7-.LFB2219
	.uleb128 .LEHE7-.LEHB7
	.uleb128 .L86-.LFB2219
	.uleb128 0
	.uleb128 .LEHB8-.LFB2219
	.uleb128 .LEHE8-.LEHB8
	.uleb128 0
	.uleb128 0
.LLSDACSE2219:
	.text
	.size	_Z28MakeMeasurementAndGetTimeSecx, .-_Z28MakeMeasurementAndGetTimeSecx
	.section	.text.unlikely
.LCOLDE9:
	.text
.LHOTE9:
	.section	.text.unlikely
.LCOLDB10:
	.text
.LHOTB10:
	.p2align 4,,15
	.globl	_Z18WriteNewRowToTableNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE
	.type	_Z18WriteNewRowToTableNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE, @function
_Z18WriteNewRowToTableNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE:
.LFB2221:
	pushq	%r12
.LCFI33:
	pushq	%rbp
.LCFI34:
	pushq	%rbx
.LCFI35:
	movq	%rdi, %rbx
	subq	$528, %rsp
.LCFI36:
	leaq	248(%rsp), %rdi
	movq	%fs:40, %rax
	movq	%rax, 520(%rsp)
	xorl	%eax, %eax
	call	_ZNSt8ios_baseC2Ev
	movq	_ZTTSt14basic_ofstreamIcSt11char_traitsIcEE+8(%rip), %rbp
	movb	$0, 472(%rsp)
	xorl	%esi, %esi
	movq	_ZTTSt14basic_ofstreamIcSt11char_traitsIcEE+16(%rip), %r12
	movq	$_ZTVSt9basic_iosIcSt11char_traitsIcEE+16, 248(%rsp)
	movq	$0, 464(%rsp)
	movb	$0, 473(%rsp)
	movq	-24(%rbp), %rax
	movq	$0, 480(%rsp)
	movq	$0, 488(%rsp)
	movq	$0, 496(%rsp)
	movq	$0, 504(%rsp)
	movq	%rbp, (%rsp)
	leaq	(%rsp,%rax), %rdi
	movq	%r12, (%rdi)
.LEHB9:
	call	_ZNSt9basic_iosIcSt11char_traitsIcEE4initEPSt15basic_streambufIcS1_E
.LEHE9:
	leaq	8(%rsp), %rdi
	movq	$_ZTVSt14basic_ofstreamIcSt11char_traitsIcEE+24, (%rsp)
	movq	$_ZTVSt14basic_ofstreamIcSt11char_traitsIcEE+64, 248(%rsp)
.LEHB10:
	call	_ZNSt13basic_filebufIcSt11char_traitsIcEEC1Ev
.LEHE10:
	leaq	8(%rsp), %rsi
	leaq	248(%rsp), %rdi
.LEHB11:
	call	_ZNSt9basic_iosIcSt11char_traitsIcEE4initEPSt15basic_streambufIcS1_E
.LEHE11:
	movq	(%rbx), %rsi
	leaq	8(%rsp), %rdi
	movl	$17, %edx
.LEHB12:
	call	_ZNSt13basic_filebufIcSt11char_traitsIcEE4openEPKcSt13_Ios_Openmode
	testq	%rax, %rax
	movq	(%rsp), %rax
	movq	-24(%rax), %rax
	leaq	(%rsp,%rax), %rdi
	je	.L131
	xorl	%esi, %esi
	call	_ZNSt9basic_iosIcSt11char_traitsIcEE5clearESt12_Ios_Iostate
.L111:
	movq	(%rsp), %rax
	movq	-24(%rax), %rax
	movq	240(%rsp,%rax), %rbx
	testq	%rbx, %rbx
	je	.L132
	cmpb	$0, 56(%rbx)
	je	.L112
	movsbl	67(%rbx), %esi
.L113:
	movq	%rsp, %rdi
	call	_ZNSo3putEc
	movq	%rax, %rdi
	call	_ZNSo5flushEv
	leaq	8(%rsp), %rdi
	call	_ZNSt13basic_filebufIcSt11char_traitsIcEE5closeEv
.LEHE12:
	testq	%rax, %rax
	je	.L114
.L115:
	leaq	8(%rsp), %rdi
	movq	$_ZTVSt14basic_ofstreamIcSt11char_traitsIcEE+24, (%rsp)
	movq	$_ZTVSt14basic_ofstreamIcSt11char_traitsIcEE+64, 248(%rsp)
	movq	$_ZTVSt13basic_filebufIcSt11char_traitsIcEE+16, 8(%rsp)
	call	_ZNSt13basic_filebufIcSt11char_traitsIcEE5closeEv
	leaq	112(%rsp), %rdi
	call	_ZNSt12__basic_fileIcED1Ev
	leaq	64(%rsp), %rdi
	movq	$_ZTVSt15basic_streambufIcSt11char_traitsIcEE+16, 8(%rsp)
	call	_ZNSt6localeD1Ev
	movq	-24(%rbp), %rax
	leaq	248(%rsp), %rdi
	movq	%r12, (%rsp,%rax)
	movq	$_ZTVSt9basic_iosIcSt11char_traitsIcEE+16, 248(%rsp)
	call	_ZNSt8ios_baseD2Ev
	movq	520(%rsp), %rax
	xorq	%fs:40, %rax
	jne	.L133
	addq	$528, %rsp
.LCFI37:
	popq	%rbx
.LCFI38:
	popq	%rbp
.LCFI39:
	popq	%r12
.LCFI40:
	ret
	.p2align 4,,10
	.p2align 3
.L112:
.LCFI41:
	movq	%rbx, %rdi
.LEHB13:
	call	_ZNKSt5ctypeIcE13_M_widen_initEv
	movq	(%rbx), %rax
	movl	$10, %esi
	movq	48(%rax), %rax
	cmpq	$_ZNKSt5ctypeIcE8do_widenEc, %rax
	je	.L113
	movq	%rbx, %rdi
	call	*%rax
	movsbl	%al, %esi
	jmp	.L113
	.p2align 4,,10
	.p2align 3
.L131:
	movl	32(%rdi), %esi
	orl	$4, %esi
	call	_ZNSt9basic_iosIcSt11char_traitsIcEE5clearESt12_Ios_Iostate
	jmp	.L111
	.p2align 4,,10
	.p2align 3
.L114:
	movq	(%rsp), %rax
	movq	-24(%rax), %rax
	leaq	(%rsp,%rax), %rdi
	movl	32(%rdi), %esi
	orl	$4, %esi
	call	_ZNSt9basic_iosIcSt11char_traitsIcEE5clearESt12_Ios_Iostate
	jmp	.L115
.L133:
	call	__stack_chk_fail
.L132:
	call	_ZSt16__throw_bad_castv
.LEHE13:
.L119:
	movq	%rax, %rbx
	movq	%rsp, %rdi
	call	_ZNSt14basic_ofstreamIcSt11char_traitsIcEED1Ev
	movq	%rbx, %rdi
.LEHB14:
	call	_Unwind_Resume
.L120:
	movq	%rax, %rbx
.L107:
	leaq	248(%rsp), %rdi
	movq	$_ZTVSt9basic_iosIcSt11char_traitsIcEE+16, 248(%rsp)
	call	_ZNSt8ios_baseD2Ev
	movq	%rbx, %rdi
	call	_Unwind_Resume
.LEHE14:
.L122:
	leaq	8(%rsp), %rdi
	movq	%rax, %rbx
	call	_ZNSt13basic_filebufIcSt11char_traitsIcEED1Ev
	movq	%rbx, %rax
.L106:
	movq	-24(%rbp), %rdx
	movq	%rax, %rbx
	movq	%r12, (%rsp,%rdx)
	jmp	.L107
.L121:
	jmp	.L106
.LFE2221:
	.section	.gcc_except_table
.LLSDA2221:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2221-.LLSDACSB2221
.LLSDACSB2221:
	.uleb128 .LEHB9-.LFB2221
	.uleb128 .LEHE9-.LEHB9
	.uleb128 .L120-.LFB2221
	.uleb128 0
	.uleb128 .LEHB10-.LFB2221
	.uleb128 .LEHE10-.LEHB10
	.uleb128 .L121-.LFB2221
	.uleb128 0
	.uleb128 .LEHB11-.LFB2221
	.uleb128 .LEHE11-.LEHB11
	.uleb128 .L122-.LFB2221
	.uleb128 0
	.uleb128 .LEHB12-.LFB2221
	.uleb128 .LEHE12-.LEHB12
	.uleb128 .L119-.LFB2221
	.uleb128 0
	.uleb128 .LEHB13-.LFB2221
	.uleb128 .LEHE13-.LEHB13
	.uleb128 .L119-.LFB2221
	.uleb128 0
	.uleb128 .LEHB14-.LFB2221
	.uleb128 .LEHE14-.LEHB14
	.uleb128 0
	.uleb128 0
.LLSDACSE2221:
	.text
	.size	_Z18WriteNewRowToTableNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE, .-_Z18WriteNewRowToTableNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE
	.section	.text.unlikely
.LCOLDE10:
	.text
.LHOTE10:
	.section	.text.unlikely
.LCOLDB14:
	.text
.LHOTB14:
	.p2align 4,,15
	.globl	_Z23WriteTestedValuesToFileiNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE
	.type	_Z23WriteTestedValuesToFileiNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE, @function
_Z23WriteTestedValuesToFileiNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE:
.LFB2217:
	pushq	%r12
.LCFI42:
	pushq	%rbp
.LCFI43:
	movq	%rsi, %r12
	pushq	%rbx
.LCFI44:
	addq	$-128, %rsp
.LCFI45:
	movq	%fs:40, %rax
	movq	%rax, 120(%rsp)
	xorl	%eax, %eax
	cmpl	$1, %edi
	jle	.L163
	pxor	%xmm0, %xmm0
	movsd	.LC13(%rip), %xmm1
	cvtsi2sd	%edi, %xmm0
	movapd	%xmm1, %xmm5
	divsd	%xmm0, %xmm5
	movsd	.LC8(%rip), %xmm0
	mulsd	%xmm5, %xmm0
	movsd	%xmm5, 16(%rsp)
	addsd	%xmm1, %xmm0
	movapd	%xmm0, %xmm6
	movsd	%xmm0, 24(%rsp)
	ucomisd	%xmm5, %xmm6
	jb	.L149
.L135:
	movq	(%r12), %rbp
	leaq	64(%rsp), %rax
	movq	8(%r12), %rbx
	movq	%rax, 48(%rsp)
	movq	%rbp, %rax
	addq	%rbx, %rax
	je	.L168
	testq	%rbp, %rbp
	jne	.L168
	.p2align 4,,10
	.p2align 3
.L136:
	movl	$.LC1, %edi
.LEHB15:
	call	_ZSt19__throw_logic_errorPKc
.LEHE15:
	.p2align 4,,10
	.p2align 3
.L149:
	movq	(%r12), %rbp
	leaq	96(%rsp), %rax
	movq	8(%r12), %rbx
	movq	%rax, 80(%rsp)
	movq	%rbp, %rax
	addq	%rbx, %rax
	je	.L138
	testq	%rbp, %rbp
	je	.L136
.L138:
	cmpq	$15, %rbx
	movq	%rbx, 40(%rsp)
	ja	.L187
	cmpq	$1, %rbx
	je	.L188
	testq	%rbx, %rbx
	leaq	96(%rsp), %rax
	jne	.L189
.L152:
	leaq	80(%rsp), %rdi
	movq	%rbx, 88(%rsp)
	movb	$0, (%rax,%rbx)
.LEHB16:
	call	_Z18WriteNewRowToTableNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE
.LEHE16:
	movq	80(%rsp), %rdi
	leaq	96(%rsp), %rax
	cmpq	%rax, %rdi
	je	.L134
	call	_ZdlPv
.L134:
	movq	120(%rsp), %rax
	xorq	%fs:40, %rax
	jne	.L190
	subq	$-128, %rsp
.LCFI46:
	popq	%rbx
.LCFI47:
	popq	%rbp
.LCFI48:
	popq	%r12
.LCFI49:
	ret
	.p2align 4,,10
	.p2align 3
.L187:
.LCFI50:
	leaq	80(%rsp), %rdi
	leaq	40(%rsp), %rsi
	xorl	%edx, %edx
.LEHB17:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_createERmm
.LEHE17:
	movq	%rax, %rdi
	movq	%rax, 80(%rsp)
	movq	40(%rsp), %rax
	movq	%rax, 96(%rsp)
.L150:
	movq	%rbx, %rdx
	movq	%rbp, %rsi
	call	memcpy
	movq	40(%rsp), %rbx
	movq	80(%rsp), %rax
	jmp	.L152
	.p2align 4,,10
	.p2align 3
.L163:
	movsd	.LC11(%rip), %xmm7
	movsd	%xmm7, 24(%rsp)
	movsd	.LC12(%rip), %xmm7
	movsd	%xmm7, 16(%rsp)
	jmp	.L135
.L188:
	movzbl	0(%rbp), %eax
	movb	%al, 96(%rsp)
	leaq	96(%rsp), %rax
	jmp	.L152
.L168:
	movsd	16(%rsp), %xmm7
	movsd	%xmm7, 8(%rsp)
	.p2align 4,,10
	.p2align 3
.L143:
	cmpq	$15, %rbx
	movq	%rbx, 40(%rsp)
	ja	.L191
.L181:
	cmpq	$1, %rbx
	je	.L192
	testq	%rbx, %rbx
	leaq	64(%rsp), %rax
	jne	.L193
.L146:
	leaq	48(%rsp), %rdi
	movsd	8(%rsp), %xmm0
	movq	%rbx, 56(%rsp)
	movb	$0, (%rax,%rbx)
.LEHB18:
	call	_Z18WriteDoubleToTabledNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE
.LEHE18:
	movq	48(%rsp), %rdi
	leaq	64(%rsp), %rax
	cmpq	%rax, %rdi
	je	.L147
	call	_ZdlPv
.L147:
	movsd	8(%rsp), %xmm2
	movsd	24(%rsp), %xmm4
	addsd	16(%rsp), %xmm2
	ucomisd	%xmm2, %xmm4
	movsd	%xmm2, 8(%rsp)
	jb	.L149
	movq	(%r12), %rbp
	leaq	64(%rsp), %rax
	movq	8(%r12), %rbx
	movq	%rax, 48(%rsp)
	movq	%rbp, %rax
	addq	%rbx, %rax
	je	.L143
	testq	%rbp, %rbp
	je	.L136
	cmpq	$15, %rbx
	movq	%rbx, 40(%rsp)
	jbe	.L181
	.p2align 4,,10
	.p2align 3
.L191:
	leaq	48(%rsp), %rdi
	leaq	40(%rsp), %rsi
	xorl	%edx, %edx
.LEHB19:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_createERmm
	movq	%rax, %rdi
	movq	%rax, 48(%rsp)
	movq	40(%rsp), %rax
	movq	%rax, 64(%rsp)
.L144:
	movq	%rbx, %rdx
	movq	%rbp, %rsi
	call	memcpy
	movq	40(%rsp), %rbx
	movq	48(%rsp), %rax
	jmp	.L146
	.p2align 4,,10
	.p2align 3
.L192:
	movzbl	0(%rbp), %eax
	movb	%al, 64(%rsp)
	movq	48(%rsp), %rax
	jmp	.L146
	.p2align 4,,10
	.p2align 3
.L193:
	movq	%rax, %rdi
	jmp	.L144
.L189:
	movq	%rax, %rdi
	jmp	.L150
.L190:
	call	__stack_chk_fail
.L167:
	movq	80(%rsp), %rdi
	movq	%rax, %rbx
	leaq	96(%rsp), %rax
	cmpq	%rax, %rdi
	je	.L157
.L184:
	call	_ZdlPv
.L157:
	movq	%rbx, %rdi
	call	_Unwind_Resume
.LEHE19:
.L166:
	movq	48(%rsp), %rdi
	leaq	64(%rsp), %rdx
	movq	%rax, %rbx
	cmpq	%rdx, %rdi
	jne	.L184
	jmp	.L157
.LFE2217:
	.section	.gcc_except_table
.LLSDA2217:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2217-.LLSDACSB2217
.LLSDACSB2217:
	.uleb128 .LEHB15-.LFB2217
	.uleb128 .LEHE15-.LEHB15
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB16-.LFB2217
	.uleb128 .LEHE16-.LEHB16
	.uleb128 .L167-.LFB2217
	.uleb128 0
	.uleb128 .LEHB17-.LFB2217
	.uleb128 .LEHE17-.LEHB17
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB18-.LFB2217
	.uleb128 .LEHE18-.LEHB18
	.uleb128 .L166-.LFB2217
	.uleb128 0
	.uleb128 .LEHB19-.LFB2217
	.uleb128 .LEHE19-.LEHB19
	.uleb128 0
	.uleb128 0
.LLSDACSE2217:
	.text
	.size	_Z23WriteTestedValuesToFileiNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE, .-_Z23WriteTestedValuesToFileiNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE
	.section	.text.unlikely
.LCOLDE14:
	.text
.LHOTE14:
	.section	.text.unlikely
.LCOLDB15:
	.text
.LHOTB15:
	.p2align 4,,15
	.globl	_Z31MakeNMeasurementsAndPrintToFileii
	.type	_Z31MakeNMeasurementsAndPrintToFileii, @function
_Z31MakeNMeasurementsAndPrintToFileii:
.LFB2218:
	pushq	%r12
.LCFI51:
	pushq	%rbp
.LCFI52:
	pushq	%rbx
.LCFI53:
	subq	$144, %rsp
.LCFI54:
	movq	%fs:40, %rax
	movq	%rax, 136(%rsp)
	xorl	%eax, %eax
	cmpl	$1, %edi
	jle	.L220
	pxor	%xmm0, %xmm0
	movsd	.LC13(%rip), %xmm1
	cvtsi2sd	%edi, %xmm0
	movapd	%xmm1, %xmm6
	divsd	%xmm0, %xmm6
	movsd	.LC8(%rip), %xmm0
	mulsd	%xmm6, %xmm0
	movsd	%xmm6, 16(%rsp)
	addsd	%xmm1, %xmm0
	movapd	%xmm0, %xmm7
	movsd	%xmm0, 24(%rsp)
	ucomisd	%xmm6, %xmm7
	jb	.L206
.L195:
	pxor	%xmm1, %xmm1
	leaq	80(%rsp), %r12
	movsd	16(%rsp), %xmm7
	cvtsi2sd	%esi, %xmm1
	movsd	%xmm7, 8(%rsp)
	movsd	%xmm1, 32(%rsp)
	.p2align 4,,10
	.p2align 3
.L205:
	movsd	8(%rsp), %xmm0
	mulsd	32(%rsp), %xmm0
	cvttsd2siq	%xmm0, %rdi
.LEHB20:
	call	_Z28MakeMeasurementAndGetTimeSecx
	movq	_ZL8kOutFile(%rip), %rbp
	movq	_ZL8kOutFile+8(%rip), %rbx
	movq	%r12, 64(%rsp)
	movq	%rbp, %rax
	addq	%rbx, %rax
	je	.L200
	testq	%rbp, %rbp
	jne	.L200
.L196:
	movl	$.LC1, %edi
	call	_ZSt19__throw_logic_errorPKc
.LEHE20:
	.p2align 4,,10
	.p2align 3
.L200:
	cmpq	$15, %rbx
	movq	%rbx, 56(%rsp)
	ja	.L240
	cmpq	$1, %rbx
	je	.L241
	testq	%rbx, %rbx
	movq	%r12, %rax
	jne	.L242
.L203:
	leaq	64(%rsp), %rdi
	movq	%rbx, 72(%rsp)
	movb	$0, (%rax,%rbx)
.LEHB21:
	call	_Z18WriteDoubleToTabledNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE
.LEHE21:
	movq	64(%rsp), %rdi
	cmpq	%r12, %rdi
	je	.L204
	call	_ZdlPv
.L204:
	movsd	8(%rsp), %xmm2
	movsd	24(%rsp), %xmm5
	addsd	16(%rsp), %xmm2
	ucomisd	%xmm2, %xmm5
	movsd	%xmm2, 8(%rsp)
	jnb	.L205
.L206:
	movq	_ZL8kOutFile(%rip), %rbp
	leaq	112(%rsp), %rax
	movq	_ZL8kOutFile+8(%rip), %rbx
	movq	%rax, 96(%rsp)
	movq	%rbp, %rax
	addq	%rbx, %rax
	je	.L198
	testq	%rbp, %rbp
	je	.L196
.L198:
	cmpq	$15, %rbx
	movq	%rbx, 56(%rsp)
	ja	.L243
	cmpq	$1, %rbx
	je	.L244
	testq	%rbx, %rbx
	leaq	112(%rsp), %rax
	jne	.L245
.L209:
	leaq	96(%rsp), %rdi
	movq	%rbx, 104(%rsp)
	movb	$0, (%rax,%rbx)
.LEHB22:
	call	_Z18WriteNewRowToTableNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE
.LEHE22:
	movq	96(%rsp), %rdi
	leaq	112(%rsp), %rax
	cmpq	%rax, %rdi
	je	.L194
	call	_ZdlPv
.L194:
	movq	136(%rsp), %rax
	xorq	%fs:40, %rax
	jne	.L246
	addq	$144, %rsp
.LCFI55:
	popq	%rbx
.LCFI56:
	popq	%rbp
.LCFI57:
	popq	%r12
.LCFI58:
	ret
	.p2align 4,,10
	.p2align 3
.L240:
.LCFI59:
	leaq	64(%rsp), %rdi
	leaq	56(%rsp), %rsi
	xorl	%edx, %edx
	movsd	%xmm0, 40(%rsp)
.LEHB23:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_createERmm
	movq	%rax, %rdi
	movq	%rax, 64(%rsp)
	movq	56(%rsp), %rax
	movsd	40(%rsp), %xmm0
	movq	%rax, 80(%rsp)
.L201:
	movq	%rbx, %rdx
	movq	%rbp, %rsi
	movsd	%xmm0, 40(%rsp)
	call	memcpy
	movq	56(%rsp), %rbx
	movq	64(%rsp), %rax
	movsd	40(%rsp), %xmm0
	jmp	.L203
	.p2align 4,,10
	.p2align 3
.L241:
	movzbl	0(%rbp), %eax
	movb	%al, 80(%rsp)
	movq	%r12, %rax
	jmp	.L203
	.p2align 4,,10
	.p2align 3
.L242:
	movq	%r12, %rdi
	jmp	.L201
	.p2align 4,,10
	.p2align 3
.L243:
	leaq	96(%rsp), %rdi
	leaq	56(%rsp), %rsi
	xorl	%edx, %edx
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_createERmm
	movq	%rax, %rdi
	movq	%rax, 96(%rsp)
	movq	56(%rsp), %rax
	movq	%rax, 112(%rsp)
.L207:
	movq	%rbx, %rdx
	movq	%rbp, %rsi
	call	memcpy
	movq	56(%rsp), %rbx
	movq	96(%rsp), %rax
	jmp	.L209
	.p2align 4,,10
	.p2align 3
.L220:
	movsd	.LC11(%rip), %xmm1
	movsd	%xmm1, 24(%rsp)
	movsd	.LC12(%rip), %xmm1
	movsd	%xmm1, 16(%rsp)
	jmp	.L195
.L244:
	movzbl	0(%rbp), %eax
	movb	%al, 112(%rsp)
	leaq	112(%rsp), %rax
	jmp	.L209
.L245:
	movq	%rax, %rdi
	jmp	.L207
.L223:
	movq	64(%rsp), %rdi
	leaq	80(%rsp), %rdx
	movq	%rax, %rbx
	cmpq	%rdx, %rdi
	je	.L214
.L237:
	call	_ZdlPv
.L214:
	movq	%rbx, %rdi
	call	_Unwind_Resume
.LEHE23:
.L246:
	call	__stack_chk_fail
.L224:
	movq	96(%rsp), %rdi
	movq	%rax, %rbx
	leaq	112(%rsp), %rax
	cmpq	%rax, %rdi
	jne	.L237
	jmp	.L214
.LFE2218:
	.section	.gcc_except_table
.LLSDA2218:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2218-.LLSDACSB2218
.LLSDACSB2218:
	.uleb128 .LEHB20-.LFB2218
	.uleb128 .LEHE20-.LEHB20
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB21-.LFB2218
	.uleb128 .LEHE21-.LEHB21
	.uleb128 .L223-.LFB2218
	.uleb128 0
	.uleb128 .LEHB22-.LFB2218
	.uleb128 .LEHE22-.LEHB22
	.uleb128 .L224-.LFB2218
	.uleb128 0
	.uleb128 .LEHB23-.LFB2218
	.uleb128 .LEHE23-.LEHB23
	.uleb128 0
	.uleb128 0
.LLSDACSE2218:
	.text
	.size	_Z31MakeNMeasurementsAndPrintToFileii, .-_Z31MakeNMeasurementsAndPrintToFileii
	.section	.text.unlikely
.LCOLDE15:
	.text
.LHOTE15:
	.section	.text.unlikely
.LCOLDB16:
	.text
.LHOTB16:
	.p2align 4,,15
	.globl	_Z17CalculateIntegralx
	.type	_Z17CalculateIntegralx, @function
_Z17CalculateIntegralx:
.LFB2222:
	pxor	%xmm1, %xmm1
	pushq	%rbp
.LCFI60:
	pushq	%rbx
.LCFI61:
	cvtsi2sdq	%rdi, %xmm1
	subq	$56, %rsp
.LCFI62:
	movsd	.LC7(%rip), %xmm0
	testq	%rdi, %rdi
	divsd	%xmm1, %xmm0
	pxor	%xmm1, %xmm1
	movsd	%xmm0, 40(%rsp)
	jle	.L248
	pxor	%xmm7, %xmm7
	movq	%rdi, %rbp
	xorl	%ebx, %ebx
	movsd	%xmm7, 16(%rsp)
	movapd	%xmm7, %xmm1
	movsd	%xmm7, 8(%rsp)
	.p2align 4,,10
	.p2align 3
.L249:
	movsd	8(%rsp), %xmm0
	addq	$1, %rbx
	movsd	%xmm1, 32(%rsp)
	call	exp
	movsd	8(%rsp), %xmm2
	mulsd	16(%rsp), %xmm0
	addsd	40(%rsp), %xmm2
	movsd	%xmm0, 24(%rsp)
	movapd	%xmm2, %xmm0
	movsd	%xmm2, 8(%rsp)
	call	sin
	movsd	%xmm0, 16(%rsp)
	movsd	8(%rsp), %xmm0
	call	exp
	mulsd	16(%rsp), %xmm0
	cmpq	%rbx, %rbp
	movsd	32(%rsp), %xmm1
	addsd	24(%rsp), %xmm0
	mulsd	.LC8(%rip), %xmm0
	addsd	%xmm0, %xmm1
	jne	.L249
	movsd	40(%rsp), %xmm0
.L248:
	addq	$56, %rsp
.LCFI63:
	mulsd	%xmm1, %xmm0
	popq	%rbx
.LCFI64:
	popq	%rbp
.LCFI65:
	ret
.LFE2222:
	.size	_Z17CalculateIntegralx, .-_Z17CalculateIntegralx
	.section	.text.unlikely
.LCOLDE16:
	.text
.LHOTE16:
	.section	.text.unlikely
.LCOLDB17:
	.text
.LHOTB17:
	.p2align 4,,15
	.globl	_Z12MathFunctiond
	.type	_Z12MathFunctiond, @function
_Z12MathFunctiond:
.LFB2223:
	subq	$24, %rsp
.LCFI66:
	movsd	%xmm0, 8(%rsp)
	call	sin
	movsd	8(%rsp), %xmm1
	movsd	%xmm0, (%rsp)
	movapd	%xmm1, %xmm0
	call	exp
	mulsd	(%rsp), %xmm0
	addq	$24, %rsp
.LCFI67:
	ret
.LFE2223:
	.size	_Z12MathFunctiond, .-_Z12MathFunctiond
	.section	.text.unlikely
.LCOLDE17:
	.text
.LHOTE17:
	.section	.text.unlikely._ZN9__gnu_cxx6__stoaIlicJiEEET0_PFT_PKT1_PPS3_DpT2_EPKcS5_PmS9_,"axG",@progbits,_ZN9__gnu_cxx6__stoaIlicJiEEET0_PFT_PKT1_PPS3_DpT2_EPKcS5_PmS9_,comdat
.LCOLDB18:
	.section	.text._ZN9__gnu_cxx6__stoaIlicJiEEET0_PFT_PKT1_PPS3_DpT2_EPKcS5_PmS9_,"axG",@progbits,_ZN9__gnu_cxx6__stoaIlicJiEEET0_PFT_PKT1_PPS3_DpT2_EPKcS5_PmS9_,comdat
.LHOTB18:
	.p2align 4,,15
	.weak	_ZN9__gnu_cxx6__stoaIlicJiEEET0_PFT_PKT1_PPS3_DpT2_EPKcS5_PmS9_
	.type	_ZN9__gnu_cxx6__stoaIlicJiEEET0_PFT_PKT1_PPS3_DpT2_EPKcS5_PmS9_, @function
_ZN9__gnu_cxx6__stoaIlicJiEEET0_PFT_PKT1_PPS3_DpT2_EPKcS5_PmS9_:
.LFB2225:
	pushq	%r15
.LCFI68:
	pushq	%r14
.LCFI69:
	movl	%r8d, %r15d
	pushq	%r13
.LCFI70:
	pushq	%r12
.LCFI71:
	movq	%rdi, %r14
	pushq	%rbp
.LCFI72:
	pushq	%rbx
.LCFI73:
	movq	%rdx, %rbx
	movq	%rsi, %r12
	movq	%rcx, %r13
	subq	$24, %rsp
.LCFI74:
	movq	%fs:40, %rax
	movq	%rax, 8(%rsp)
	xorl	%eax, %eax
	call	__errno_location
	movl	%r15d, %edx
	movq	%rax, %rbp
	movl	$0, (%rax)
	movq	%rsp, %rsi
	movq	%rbx, %rdi
	call	*%r14
	movq	(%rsp), %rdx
	cmpq	%rdx, %rbx
	je	.L265
	cmpl	$34, 0(%rbp)
	je	.L257
	movl	$2147483648, %esi
	movl	$4294967295, %ecx
	addq	%rax, %rsi
	cmpq	%rcx, %rsi
	ja	.L257
	testq	%r13, %r13
	je	.L259
	subq	%rbx, %rdx
	movq	%rdx, 0(%r13)
.L259:
	movq	8(%rsp), %rdi
	xorq	%fs:40, %rdi
	jne	.L266
	addq	$24, %rsp
.LCFI75:
	popq	%rbx
.LCFI76:
	popq	%rbp
.LCFI77:
	popq	%r12
.LCFI78:
	popq	%r13
.LCFI79:
	popq	%r14
.LCFI80:
	popq	%r15
.LCFI81:
	ret
.L257:
.LCFI82:
	movq	%r12, %rdi
	call	_ZSt20__throw_out_of_rangePKc
.L265:
	movq	%r12, %rdi
	call	_ZSt24__throw_invalid_argumentPKc
.L266:
	call	__stack_chk_fail
.LFE2225:
	.size	_ZN9__gnu_cxx6__stoaIlicJiEEET0_PFT_PKT1_PPS3_DpT2_EPKcS5_PmS9_, .-_ZN9__gnu_cxx6__stoaIlicJiEEET0_PFT_PKT1_PPS3_DpT2_EPKcS5_PmS9_
	.section	.text.unlikely._ZN9__gnu_cxx6__stoaIlicJiEEET0_PFT_PKT1_PPS3_DpT2_EPKcS5_PmS9_,"axG",@progbits,_ZN9__gnu_cxx6__stoaIlicJiEEET0_PFT_PKT1_PPS3_DpT2_EPKcS5_PmS9_,comdat
.LCOLDE18:
	.section	.text._ZN9__gnu_cxx6__stoaIlicJiEEET0_PFT_PKT1_PPS3_DpT2_EPKcS5_PmS9_,"axG",@progbits,_ZN9__gnu_cxx6__stoaIlicJiEEET0_PFT_PKT1_PPS3_DpT2_EPKcS5_PmS9_,comdat
.LHOTE18:
	.weak	_ZN9__gnu_cxx6__stoaIlicIiEEET0_PFT_PKT1_PPS3_DpT2_EPKcS5_PmS9_
	.set	_ZN9__gnu_cxx6__stoaIlicIiEEET0_PFT_PKT1_PPS3_DpT2_EPKcS5_PmS9_,_ZN9__gnu_cxx6__stoaIlicJiEEET0_PFT_PKT1_PPS3_DpT2_EPKcS5_PmS9_
	.section	.rodata.str1.1
.LC19:
	.string	"stoi"
	.section	.text.unlikely
.LCOLDB20:
	.section	.text.startup,"ax",@progbits
.LHOTB20:
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB2216:
	pushq	%r13
.LCFI83:
	pushq	%r12
.LCFI84:
	pushq	%rbp
.LCFI85:
	pushq	%rbx
.LCFI86:
	subq	$56, %rsp
.LCFI87:
	movq	%fs:40, %rax
	movq	%rax, 40(%rsp)
	xorl	%eax, %eax
	cmpl	$1, %edi
	jle	.L283
	movq	%rsi, %r12
	movq	8(%rsi), %rsi
	movl	%edi, %ebp
	movq	%rsp, %rdi
.LEHB24:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC2EPKcRKS3_.isra.25
.LEHE24:
	movq	(%rsp), %rdx
	movl	$10, %r8d
	xorl	%ecx, %ecx
	movl	$.LC19, %esi
	movl	$strtol, %edi
.LEHB25:
	call	_ZN9__gnu_cxx6__stoaIlicJiEEET0_PFT_PKT1_PPS3_DpT2_EPKcS5_PmS9_
.LEHE25:
	movq	(%rsp), %rdi
	movl	%eax, %ebx
	leaq	16(%rsp), %rax
	cmpq	%rax, %rdi
	je	.L269
	call	_ZdlPv
.L269:
	testl	%ebx, %ebx
	movl	$600000000, %eax
	movl	$1, %r13d
	cmove	%eax, %ebx
	cmpl	$3, %ebp
	jle	.L297
.L271:
	movq	16(%r12), %rsi
	movq	%rsp, %rdi
.LEHB26:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC2EPKcRKS3_.isra.25
.LEHE26:
	movq	(%rsp), %rdx
	movl	$10, %r8d
	xorl	%ecx, %ecx
	movl	$.LC19, %esi
	movl	$strtol, %edi
.LEHB27:
	call	_ZN9__gnu_cxx6__stoaIlicJiEEET0_PFT_PKT1_PPS3_DpT2_EPKcS5_PmS9_
.LEHE27:
	movq	(%rsp), %rdi
	movl	%eax, %ebp
	leaq	16(%rsp), %rax
	cmpq	%rax, %rdi
	je	.L272
	call	_ZdlPv
.L272:
	testl	%r13d, %r13d
	je	.L273
	movq	_ZL8kOutFile(%rip), %rsi
	leaq	16(%rsp), %rax
	movq	%rsp, %rdi
	movq	%rax, (%rsp)
	movq	%rsi, %rdx
	addq	_ZL8kOutFile+8(%rip), %rdx
.LEHB28:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE12_M_constructIPcEEvT_S7_St20forward_iterator_tag.isra.28
.LEHE28:
	movq	%rsp, %rsi
	movl	%ebp, %edi
.LEHB29:
	call	_Z23WriteTestedValuesToFileiNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE
.LEHE29:
	movq	(%rsp), %rdi
	leaq	16(%rsp), %rax
	cmpq	%rax, %rdi
	je	.L273
	call	_ZdlPv
.L273:
	movl	%ebx, %esi
	movl	%ebp, %edi
.LEHB30:
	call	_Z31MakeNMeasurementsAndPrintToFileii
.L275:
	xorl	%eax, %eax
	movq	40(%rsp), %rcx
	xorq	%fs:40, %rcx
	jne	.L298
	addq	$56, %rsp
.LCFI88:
	popq	%rbx
.LCFI89:
	popq	%rbp
.LCFI90:
	popq	%r12
.LCFI91:
	popq	%r13
.LCFI92:
	ret
.L283:
.LCFI93:
	movl	$600000000, %ebx
.L268:
	movl	%ebx, %esi
	movl	$1, %edi
	call	_Z31MakeNMeasurementsAndPrintToFileii
	jmp	.L275
.L297:
	cmpl	$2, %ebp
	jle	.L268
	xorl	%r13d, %r13d
	jmp	.L271
.L298:
	call	__stack_chk_fail
.L286:
.L295:
	movq	(%rsp), %rdi
	movq	%rax, %rbx
	leaq	16(%rsp), %rax
	cmpq	%rax, %rdi
	je	.L281
.L293:
	call	_ZdlPv
.L281:
	movq	%rbx, %rdi
	call	_Unwind_Resume
.LEHE30:
.L285:
	jmp	.L295
.L287:
	movq	(%rsp), %rdi
	leaq	16(%rsp), %rdx
	movq	%rax, %rbx
	cmpq	%rdx, %rdi
	jne	.L293
	jmp	.L281
.LFE2216:
	.section	.gcc_except_table
.LLSDA2216:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2216-.LLSDACSB2216
.LLSDACSB2216:
	.uleb128 .LEHB24-.LFB2216
	.uleb128 .LEHE24-.LEHB24
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB25-.LFB2216
	.uleb128 .LEHE25-.LEHB25
	.uleb128 .L285-.LFB2216
	.uleb128 0
	.uleb128 .LEHB26-.LFB2216
	.uleb128 .LEHE26-.LEHB26
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB27-.LFB2216
	.uleb128 .LEHE27-.LEHB27
	.uleb128 .L286-.LFB2216
	.uleb128 0
	.uleb128 .LEHB28-.LFB2216
	.uleb128 .LEHE28-.LEHB28
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB29-.LFB2216
	.uleb128 .LEHE29-.LEHB29
	.uleb128 .L287-.LFB2216
	.uleb128 0
	.uleb128 .LEHB30-.LFB2216
	.uleb128 .LEHE30-.LEHB30
	.uleb128 0
	.uleb128 0
.LLSDACSE2216:
	.section	.text.startup
	.size	main, .-main
	.section	.text.unlikely
.LCOLDE20:
	.section	.text.startup
.LHOTE20:
	.section	.rodata.str1.1
.LC21:
	.string	"outtime.csv"
.LC22:
	.string	"outval.csv"
	.section	.text.unlikely
.LCOLDB23:
	.section	.text.startup
.LHOTB23:
	.p2align 4,,15
	.type	_GLOBAL__sub_I_main, @function
_GLOBAL__sub_I_main:
.LFB2485:
	subq	$8, %rsp
.LCFI94:
	movl	$_ZStL8__ioinit, %edi
	call	_ZNSt8ios_base4InitC1Ev
	movl	$__dso_handle, %edx
	movl	$_ZStL8__ioinit, %esi
	movl	$_ZNSt8ios_base4InitD1Ev, %edi
	call	__cxa_atexit
	movl	$.LC21, %esi
	movl	$_ZL8kOutFile, %edi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC2EPKcRKS3_.isra.25
	movl	$__dso_handle, %edx
	movl	$_ZL8kOutFile, %esi
	movl	$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev, %edi
	call	__cxa_atexit
	movl	$.LC22, %esi
	movl	$_ZL14kOutFileValues, %edi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC2EPKcRKS3_.isra.25
	movl	$__dso_handle, %edx
	movl	$_ZL14kOutFileValues, %esi
	movl	$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev, %edi
	addq	$8, %rsp
.LCFI95:
	jmp	__cxa_atexit
.LFE2485:
	.size	_GLOBAL__sub_I_main, .-_GLOBAL__sub_I_main
	.section	.text.unlikely
.LCOLDE23:
	.section	.text.startup
.LHOTE23:
	.section	.init_array,"aw"
	.align 8
	.quad	_GLOBAL__sub_I_main
	.local	_ZL14kOutFileValues
	.comm	_ZL14kOutFileValues,32,32
	.local	_ZL8kOutFile
	.comm	_ZL8kOutFile,32,32
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC7:
	.long	1413754136
	.long	1074340347
	.align 8
.LC8:
	.long	0
	.long	1071644672
	.align 8
.LC11:
	.long	0
	.long	1073217536
	.align 8
.LC12:
	.long	0
	.long	1072693248
	.align 8
.LC13:
	.long	0
	.long	1073741824
	.section	.eh_frame,"a",@progbits
.Lframe1:
	.long	.LECIE1-.LSCIE1
.LSCIE1:
	.long	0
	.byte	0x3
	.string	"zPLR"
	.uleb128 0x1
	.sleb128 -8
	.uleb128 0x10
	.uleb128 0x7
	.byte	0x3
	.long	__gxx_personality_v0
	.byte	0x3
	.byte	0x3
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.byte	0x90
	.uleb128 0x1
	.align 8
.LECIE1:
.LSFDE1:
	.long	.LEFDE1-.LASFDE1
.LASFDE1:
	.long	.LASFDE1-.Lframe1
	.long	.LFB2514
	.long	.LFE2514-.LFB2514
	.uleb128 0x4
	.long	0
	.byte	0x4
	.long	.LCFI0-.LFB2514
	.byte	0xe
	.uleb128 0x10
	.byte	0x8c
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI1-.LCFI0
	.byte	0xe
	.uleb128 0x18
	.byte	0x86
	.uleb128 0x3
	.byte	0x4
	.long	.LCFI2-.LCFI1
	.byte	0xe
	.uleb128 0x20
	.byte	0x83
	.uleb128 0x4
	.byte	0x4
	.long	.LCFI3-.LCFI2
	.byte	0xe
	.uleb128 0x30
	.byte	0x4
	.long	.LCFI4-.LCFI3
	.byte	0xa
	.byte	0xe
	.uleb128 0x20
	.byte	0x4
	.long	.LCFI5-.LCFI4
	.byte	0xe
	.uleb128 0x18
	.byte	0x4
	.long	.LCFI6-.LCFI5
	.byte	0xe
	.uleb128 0x10
	.byte	0x4
	.long	.LCFI7-.LCFI6
	.byte	0xe
	.uleb128 0x8
	.byte	0x4
	.long	.LCFI8-.LCFI7
	.byte	0xb
	.align 8
.LEFDE1:
.LSFDE3:
	.long	.LEFDE3-.LASFDE3
.LASFDE3:
	.long	.LASFDE3-.Lframe1
	.long	.LFB2220
	.long	.LFE2220-.LFB2220
	.uleb128 0x4
	.long	.LLSDA2220
	.byte	0x4
	.long	.LCFI15-.LFB2220
	.byte	0xe
	.uleb128 0x10
	.byte	0x8c
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI16-.LCFI15
	.byte	0xe
	.uleb128 0x18
	.byte	0x86
	.uleb128 0x3
	.byte	0x4
	.long	.LCFI17-.LCFI16
	.byte	0xe
	.uleb128 0x20
	.byte	0x83
	.uleb128 0x4
	.byte	0x4
	.long	.LCFI18-.LCFI17
	.byte	0xe
	.uleb128 0x250
	.byte	0x4
	.long	.LCFI19-.LCFI18
	.byte	0xa
	.byte	0xe
	.uleb128 0x20
	.byte	0x4
	.long	.LCFI20-.LCFI19
	.byte	0xe
	.uleb128 0x18
	.byte	0x4
	.long	.LCFI21-.LCFI20
	.byte	0xe
	.uleb128 0x10
	.byte	0x4
	.long	.LCFI22-.LCFI21
	.byte	0xe
	.uleb128 0x8
	.byte	0x4
	.long	.LCFI23-.LCFI22
	.byte	0xb
	.align 8
.LEFDE3:
.LSFDE5:
	.long	.LEFDE5-.LASFDE5
.LASFDE5:
	.long	.LASFDE5-.Lframe1
	.long	.LFB2219
	.long	.LFE2219-.LFB2219
	.uleb128 0x4
	.long	.LLSDA2219
	.byte	0x4
	.long	.LCFI24-.LFB2219
	.byte	0xe
	.uleb128 0x10
	.byte	0x8c
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI25-.LCFI24
	.byte	0xe
	.uleb128 0x18
	.byte	0x86
	.uleb128 0x3
	.byte	0x4
	.long	.LCFI26-.LCFI25
	.byte	0xe
	.uleb128 0x20
	.byte	0x83
	.uleb128 0x4
	.byte	0x4
	.long	.LCFI27-.LCFI26
	.byte	0xe
	.uleb128 0xd0
	.byte	0x4
	.long	.LCFI28-.LCFI27
	.byte	0xa
	.byte	0xe
	.uleb128 0x20
	.byte	0x4
	.long	.LCFI29-.LCFI28
	.byte	0xe
	.uleb128 0x18
	.byte	0x4
	.long	.LCFI30-.LCFI29
	.byte	0xe
	.uleb128 0x10
	.byte	0x4
	.long	.LCFI31-.LCFI30
	.byte	0xe
	.uleb128 0x8
	.byte	0x4
	.long	.LCFI32-.LCFI31
	.byte	0xb
	.align 8
.LEFDE5:
.LSFDE7:
	.long	.LEFDE7-.LASFDE7
.LASFDE7:
	.long	.LASFDE7-.Lframe1
	.long	.LFB2221
	.long	.LFE2221-.LFB2221
	.uleb128 0x4
	.long	.LLSDA2221
	.byte	0x4
	.long	.LCFI33-.LFB2221
	.byte	0xe
	.uleb128 0x10
	.byte	0x8c
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI34-.LCFI33
	.byte	0xe
	.uleb128 0x18
	.byte	0x86
	.uleb128 0x3
	.byte	0x4
	.long	.LCFI35-.LCFI34
	.byte	0xe
	.uleb128 0x20
	.byte	0x83
	.uleb128 0x4
	.byte	0x4
	.long	.LCFI36-.LCFI35
	.byte	0xe
	.uleb128 0x230
	.byte	0x4
	.long	.LCFI37-.LCFI36
	.byte	0xa
	.byte	0xe
	.uleb128 0x20
	.byte	0x4
	.long	.LCFI38-.LCFI37
	.byte	0xe
	.uleb128 0x18
	.byte	0x4
	.long	.LCFI39-.LCFI38
	.byte	0xe
	.uleb128 0x10
	.byte	0x4
	.long	.LCFI40-.LCFI39
	.byte	0xe
	.uleb128 0x8
	.byte	0x4
	.long	.LCFI41-.LCFI40
	.byte	0xb
	.align 8
.LEFDE7:
.LSFDE9:
	.long	.LEFDE9-.LASFDE9
.LASFDE9:
	.long	.LASFDE9-.Lframe1
	.long	.LFB2217
	.long	.LFE2217-.LFB2217
	.uleb128 0x4
	.long	.LLSDA2217
	.byte	0x4
	.long	.LCFI42-.LFB2217
	.byte	0xe
	.uleb128 0x10
	.byte	0x8c
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI43-.LCFI42
	.byte	0xe
	.uleb128 0x18
	.byte	0x86
	.uleb128 0x3
	.byte	0x4
	.long	.LCFI44-.LCFI43
	.byte	0xe
	.uleb128 0x20
	.byte	0x83
	.uleb128 0x4
	.byte	0x4
	.long	.LCFI45-.LCFI44
	.byte	0xe
	.uleb128 0xa0
	.byte	0x4
	.long	.LCFI46-.LCFI45
	.byte	0xa
	.byte	0xe
	.uleb128 0x20
	.byte	0x4
	.long	.LCFI47-.LCFI46
	.byte	0xe
	.uleb128 0x18
	.byte	0x4
	.long	.LCFI48-.LCFI47
	.byte	0xe
	.uleb128 0x10
	.byte	0x4
	.long	.LCFI49-.LCFI48
	.byte	0xe
	.uleb128 0x8
	.byte	0x4
	.long	.LCFI50-.LCFI49
	.byte	0xb
	.align 8
.LEFDE9:
.LSFDE11:
	.long	.LEFDE11-.LASFDE11
.LASFDE11:
	.long	.LASFDE11-.Lframe1
	.long	.LFB2218
	.long	.LFE2218-.LFB2218
	.uleb128 0x4
	.long	.LLSDA2218
	.byte	0x4
	.long	.LCFI51-.LFB2218
	.byte	0xe
	.uleb128 0x10
	.byte	0x8c
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI52-.LCFI51
	.byte	0xe
	.uleb128 0x18
	.byte	0x86
	.uleb128 0x3
	.byte	0x4
	.long	.LCFI53-.LCFI52
	.byte	0xe
	.uleb128 0x20
	.byte	0x83
	.uleb128 0x4
	.byte	0x4
	.long	.LCFI54-.LCFI53
	.byte	0xe
	.uleb128 0xb0
	.byte	0x4
	.long	.LCFI55-.LCFI54
	.byte	0xa
	.byte	0xe
	.uleb128 0x20
	.byte	0x4
	.long	.LCFI56-.LCFI55
	.byte	0xe
	.uleb128 0x18
	.byte	0x4
	.long	.LCFI57-.LCFI56
	.byte	0xe
	.uleb128 0x10
	.byte	0x4
	.long	.LCFI58-.LCFI57
	.byte	0xe
	.uleb128 0x8
	.byte	0x4
	.long	.LCFI59-.LCFI58
	.byte	0xb
	.align 8
.LEFDE11:
.LSFDE13:
	.long	.LEFDE13-.LASFDE13
.LASFDE13:
	.long	.LASFDE13-.Lframe1
	.long	.LFB2225
	.long	.LFE2225-.LFB2225
	.uleb128 0x4
	.long	0
	.byte	0x4
	.long	.LCFI68-.LFB2225
	.byte	0xe
	.uleb128 0x10
	.byte	0x8f
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI69-.LCFI68
	.byte	0xe
	.uleb128 0x18
	.byte	0x8e
	.uleb128 0x3
	.byte	0x4
	.long	.LCFI70-.LCFI69
	.byte	0xe
	.uleb128 0x20
	.byte	0x8d
	.uleb128 0x4
	.byte	0x4
	.long	.LCFI71-.LCFI70
	.byte	0xe
	.uleb128 0x28
	.byte	0x8c
	.uleb128 0x5
	.byte	0x4
	.long	.LCFI72-.LCFI71
	.byte	0xe
	.uleb128 0x30
	.byte	0x86
	.uleb128 0x6
	.byte	0x4
	.long	.LCFI73-.LCFI72
	.byte	0xe
	.uleb128 0x38
	.byte	0x83
	.uleb128 0x7
	.byte	0x4
	.long	.LCFI74-.LCFI73
	.byte	0xe
	.uleb128 0x50
	.byte	0x4
	.long	.LCFI75-.LCFI74
	.byte	0xa
	.byte	0xe
	.uleb128 0x38
	.byte	0x4
	.long	.LCFI76-.LCFI75
	.byte	0xe
	.uleb128 0x30
	.byte	0x4
	.long	.LCFI77-.LCFI76
	.byte	0xe
	.uleb128 0x28
	.byte	0x4
	.long	.LCFI78-.LCFI77
	.byte	0xe
	.uleb128 0x20
	.byte	0x4
	.long	.LCFI79-.LCFI78
	.byte	0xe
	.uleb128 0x18
	.byte	0x4
	.long	.LCFI80-.LCFI79
	.byte	0xe
	.uleb128 0x10
	.byte	0x4
	.long	.LCFI81-.LCFI80
	.byte	0xe
	.uleb128 0x8
	.byte	0x4
	.long	.LCFI82-.LCFI81
	.byte	0xb
	.align 8
.LEFDE13:
.LSFDE15:
	.long	.LEFDE15-.LASFDE15
.LASFDE15:
	.long	.LASFDE15-.Lframe1
	.long	.LFB2216
	.long	.LFE2216-.LFB2216
	.uleb128 0x4
	.long	.LLSDA2216
	.byte	0x4
	.long	.LCFI83-.LFB2216
	.byte	0xe
	.uleb128 0x10
	.byte	0x8d
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI84-.LCFI83
	.byte	0xe
	.uleb128 0x18
	.byte	0x8c
	.uleb128 0x3
	.byte	0x4
	.long	.LCFI85-.LCFI84
	.byte	0xe
	.uleb128 0x20
	.byte	0x86
	.uleb128 0x4
	.byte	0x4
	.long	.LCFI86-.LCFI85
	.byte	0xe
	.uleb128 0x28
	.byte	0x83
	.uleb128 0x5
	.byte	0x4
	.long	.LCFI87-.LCFI86
	.byte	0xe
	.uleb128 0x60
	.byte	0x4
	.long	.LCFI88-.LCFI87
	.byte	0xa
	.byte	0xe
	.uleb128 0x28
	.byte	0x4
	.long	.LCFI89-.LCFI88
	.byte	0xe
	.uleb128 0x20
	.byte	0x4
	.long	.LCFI90-.LCFI89
	.byte	0xe
	.uleb128 0x18
	.byte	0x4
	.long	.LCFI91-.LCFI90
	.byte	0xe
	.uleb128 0x10
	.byte	0x4
	.long	.LCFI92-.LCFI91
	.byte	0xe
	.uleb128 0x8
	.byte	0x4
	.long	.LCFI93-.LCFI92
	.byte	0xb
	.align 8
.LEFDE15:
	.hidden	__dso_handle
	.ident	"GCC: (Ubuntu 5.5.0-12ubuntu1~16.04) 5.5.0 20171010"
	.section	.note.GNU-stack,"",@progbits
