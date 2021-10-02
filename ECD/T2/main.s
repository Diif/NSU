	.file	"main.cpp"
	.section	.rodata
	.type	_ZStL19piecewise_construct, @object
	.size	_ZStL19piecewise_construct, 1
_ZStL19piecewise_construct:
	.zero	1
	.section	.text._ZNSt11char_traitsIcE7compareEPKcS2_m,"axG",@progbits,_ZNSt11char_traitsIcE7compareEPKcS2_m,comdat
	.weak	_ZNSt11char_traitsIcE7compareEPKcS2_m
	.type	_ZNSt11char_traitsIcE7compareEPKcS2_m, @function
_ZNSt11char_traitsIcE7compareEPKcS2_m:
.LFB542:
	pushq	%rbp
.LCFI0:
	movq	%rsp, %rbp
.LCFI1:
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	cmpq	$0, -24(%rbp)
	jne	.L2
	movl	$0, %eax
	jmp	.L3
.L2:
	movq	-24(%rbp), %rdx
	movq	-16(%rbp), %rcx
	movq	-8(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	memcmp
.L3:
	leave
.LCFI2:
	ret
.LFE542:
	.size	_ZNSt11char_traitsIcE7compareEPKcS2_m, .-_ZNSt11char_traitsIcE7compareEPKcS2_m
	.section	.rodata
.LC0:
	.string	"stoi"
	.section	.text._ZNSt7__cxx114stoiERKNS_12basic_stringIcSt11char_traitsIcESaIcEEEPmi,"axG",@progbits,_ZNSt7__cxx114stoiERKNS_12basic_stringIcSt11char_traitsIcESaIcEEEPmi,comdat
	.weak	_ZNSt7__cxx114stoiERKNS_12basic_stringIcSt11char_traitsIcESaIcEEEPmi
	.type	_ZNSt7__cxx114stoiERKNS_12basic_stringIcSt11char_traitsIcESaIcEEEPmi, @function
_ZNSt7__cxx114stoiERKNS_12basic_stringIcSt11char_traitsIcESaIcEEEPmi:
.LFB999:
	pushq	%rbp
.LCFI3:
	movq	%rsp, %rbp
.LCFI4:
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movl	%edx, -20(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE5c_strEv
	movq	%rax, %rsi
	movl	-20(%rbp), %edx
	movq	-16(%rbp), %rax
	movl	%edx, %r8d
	movq	%rax, %rcx
	movq	%rsi, %rdx
	movl	$.LC0, %esi
	movl	$strtol, %edi
	call	_ZN9__gnu_cxx6__stoaIlicJiEEET0_PFT_PKT1_PPS3_DpT2_EPKcS5_PmS9_
	leave
.LCFI5:
	ret
.LFE999:
	.size	_ZNSt7__cxx114stoiERKNS_12basic_stringIcSt11char_traitsIcESaIcEEEPmi, .-_ZNSt7__cxx114stoiERKNS_12basic_stringIcSt11char_traitsIcESaIcEEEPmi
	.section	.text._ZStanSt13_Ios_FmtflagsS_,"axG",@progbits,_ZStanSt13_Ios_FmtflagsS_,comdat
	.weak	_ZStanSt13_Ios_FmtflagsS_
	.type	_ZStanSt13_Ios_FmtflagsS_, @function
_ZStanSt13_Ios_FmtflagsS_:
.LFB1198:
	pushq	%rbp
.LCFI6:
	movq	%rsp, %rbp
.LCFI7:
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	-4(%rbp), %eax
	andl	-8(%rbp), %eax
	popq	%rbp
.LCFI8:
	ret
.LFE1198:
	.size	_ZStanSt13_Ios_FmtflagsS_, .-_ZStanSt13_Ios_FmtflagsS_
	.section	.text._ZStorSt13_Ios_FmtflagsS_,"axG",@progbits,_ZStorSt13_Ios_FmtflagsS_,comdat
	.weak	_ZStorSt13_Ios_FmtflagsS_
	.type	_ZStorSt13_Ios_FmtflagsS_, @function
_ZStorSt13_Ios_FmtflagsS_:
.LFB1199:
	pushq	%rbp
.LCFI9:
	movq	%rsp, %rbp
.LCFI10:
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	-4(%rbp), %eax
	orl	-8(%rbp), %eax
	popq	%rbp
.LCFI11:
	ret
.LFE1199:
	.size	_ZStorSt13_Ios_FmtflagsS_, .-_ZStorSt13_Ios_FmtflagsS_
	.section	.text._ZStcoSt13_Ios_Fmtflags,"axG",@progbits,_ZStcoSt13_Ios_Fmtflags,comdat
	.weak	_ZStcoSt13_Ios_Fmtflags
	.type	_ZStcoSt13_Ios_Fmtflags, @function
_ZStcoSt13_Ios_Fmtflags:
.LFB1201:
	pushq	%rbp
.LCFI12:
	movq	%rsp, %rbp
.LCFI13:
	movl	%edi, -4(%rbp)
	movl	-4(%rbp), %eax
	notl	%eax
	popq	%rbp
.LCFI14:
	ret
.LFE1201:
	.size	_ZStcoSt13_Ios_Fmtflags, .-_ZStcoSt13_Ios_Fmtflags
	.section	.text._ZStoRRSt13_Ios_FmtflagsS_,"axG",@progbits,_ZStoRRSt13_Ios_FmtflagsS_,comdat
	.weak	_ZStoRRSt13_Ios_FmtflagsS_
	.type	_ZStoRRSt13_Ios_FmtflagsS_, @function
_ZStoRRSt13_Ios_FmtflagsS_:
.LFB1202:
	pushq	%rbp
.LCFI15:
	movq	%rsp, %rbp
.LCFI16:
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	movq	-8(%rbp), %rax
	movl	(%rax), %eax
	movl	-12(%rbp), %edx
	movl	%edx, %esi
	movl	%eax, %edi
	call	_ZStorSt13_Ios_FmtflagsS_
	movl	%eax, %edx
	movq	-8(%rbp), %rax
	movl	%edx, (%rax)
	movq	-8(%rbp), %rax
	leave
.LCFI17:
	ret
.LFE1202:
	.size	_ZStoRRSt13_Ios_FmtflagsS_, .-_ZStoRRSt13_Ios_FmtflagsS_
	.section	.text._ZStaNRSt13_Ios_FmtflagsS_,"axG",@progbits,_ZStaNRSt13_Ios_FmtflagsS_,comdat
	.weak	_ZStaNRSt13_Ios_FmtflagsS_
	.type	_ZStaNRSt13_Ios_FmtflagsS_, @function
_ZStaNRSt13_Ios_FmtflagsS_:
.LFB1203:
	pushq	%rbp
.LCFI18:
	movq	%rsp, %rbp
.LCFI19:
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	movq	-8(%rbp), %rax
	movl	(%rax), %eax
	movl	-12(%rbp), %edx
	movl	%edx, %esi
	movl	%eax, %edi
	call	_ZStanSt13_Ios_FmtflagsS_
	movl	%eax, %edx
	movq	-8(%rbp), %rax
	movl	%edx, (%rax)
	movq	-8(%rbp), %rax
	leave
.LCFI20:
	ret
.LFE1203:
	.size	_ZStaNRSt13_Ios_FmtflagsS_, .-_ZStaNRSt13_Ios_FmtflagsS_
	.section	.text._ZNSt8ios_base4setfESt13_Ios_FmtflagsS0_,"axG",@progbits,_ZNSt8ios_base4setfESt13_Ios_FmtflagsS0_,comdat
	.align 2
	.weak	_ZNSt8ios_base4setfESt13_Ios_FmtflagsS0_
	.type	_ZNSt8ios_base4setfESt13_Ios_FmtflagsS0_, @function
_ZNSt8ios_base4setfESt13_Ios_FmtflagsS0_:
.LFB1232:
	pushq	%rbp
.LCFI21:
	movq	%rsp, %rbp
.LCFI22:
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movl	%edx, -32(%rbp)
	movq	-24(%rbp), %rax
	movl	24(%rax), %eax
	movl	%eax, -4(%rbp)
	movl	-32(%rbp), %eax
	movl	%eax, %edi
	call	_ZStcoSt13_Ios_Fmtflags
	movl	%eax, %edx
	movq	-24(%rbp), %rax
	addq	$24, %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	_ZStaNRSt13_Ios_FmtflagsS_
	movl	-32(%rbp), %edx
	movl	-28(%rbp), %eax
	movl	%edx, %esi
	movl	%eax, %edi
	call	_ZStanSt13_Ios_FmtflagsS_
	movl	%eax, %edx
	movq	-24(%rbp), %rax
	addq	$24, %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	_ZStoRRSt13_Ios_FmtflagsS_
	movl	-4(%rbp), %eax
	leave
.LCFI23:
	ret
.LFE1232:
	.size	_ZNSt8ios_base4setfESt13_Ios_FmtflagsS0_, .-_ZNSt8ios_base4setfESt13_Ios_FmtflagsS0_
	.section	.text._ZNSt8ios_base9precisionEl,"axG",@progbits,_ZNSt8ios_base9precisionEl,comdat
	.align 2
	.weak	_ZNSt8ios_base9precisionEl
	.type	_ZNSt8ios_base9precisionEl, @function
_ZNSt8ios_base9precisionEl:
.LFB1235:
	pushq	%rbp
.LCFI24:
	movq	%rsp, %rbp
.LCFI25:
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-24(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -8(%rbp)
	movq	-24(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, 8(%rax)
	movq	-8(%rbp), %rax
	popq	%rbp
.LCFI26:
	ret
.LFE1235:
	.size	_ZNSt8ios_base9precisionEl, .-_ZNSt8ios_base9precisionEl
	.section	.text._ZSt5fixedRSt8ios_base,"axG",@progbits,_ZSt5fixedRSt8ios_base,comdat
	.weak	_ZSt5fixedRSt8ios_base
	.type	_ZSt5fixedRSt8ios_base, @function
_ZSt5fixedRSt8ios_base:
.LFB1262:
	pushq	%rbp
.LCFI27:
	movq	%rsp, %rbp
.LCFI28:
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	$260, %edx
	movl	$4, %esi
	movq	%rax, %rdi
	call	_ZNSt8ios_base4setfESt13_Ios_FmtflagsS0_
	movq	-8(%rbp), %rax
	leave
.LCFI29:
	ret
.LFE1262:
	.size	_ZSt5fixedRSt8ios_base, .-_ZSt5fixedRSt8ios_base
	.section	.rodata
	.type	_ZStL13allocator_arg, @object
	.size	_ZStL13allocator_arg, 1
_ZStL13allocator_arg:
	.zero	1
	.type	_ZStL6ignore, @object
	.size	_ZStL6ignore, 1
_ZStL6ignore:
	.zero	1
	.section	.text._ZSt12setprecisioni,"axG",@progbits,_ZSt12setprecisioni,comdat
	.weak	_ZSt12setprecisioni
	.type	_ZSt12setprecisioni, @function
_ZSt12setprecisioni:
.LFB2116:
	pushq	%rbp
.LCFI30:
	movq	%rsp, %rbp
.LCFI31:
	movl	%edi, -4(%rbp)
	movl	-4(%rbp), %eax
	popq	%rbp
.LCFI32:
	ret
.LFE2116:
	.size	_ZSt12setprecisioni, .-_ZSt12setprecisioni
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.local	_ZL8kOutFile
	.comm	_ZL8kOutFile,32,32
	.local	_ZL14kOutFileValues
	.comm	_ZL14kOutFileValues,32,32
	.section	.rodata
	.align 4
	.type	_ZL11kNFor40Secs, @object
	.size	_ZL11kNFor40Secs, 4
_ZL11kNFor40Secs:
	.long	600000000
	.text
	.globl	main
	.type	main, @function
main:
.LFB2130:
	pushq	%rbp
.LCFI33:
	movq	%rsp, %rbp
.LCFI34:
	pushq	%rbx
	subq	$88, %rsp
.LCFI35:
	movl	%edi, -84(%rbp)
	movq	%rsi, -96(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	movl	$0, -72(%rbp)
	cmpl	$1, -84(%rbp)
	jle	.L25
	leaq	-77(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcEC1Ev
	movq	-96(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rcx
	leaq	-77(%rbp), %rdx
	leaq	-64(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
.LEHB0:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1EPKcRKS3_
.LEHE0:
	leaq	-64(%rbp), %rax
	movl	$10, %edx
	movl	$0, %esi
	movq	%rax, %rdi
.LEHB1:
	call	_ZNSt7__cxx114stoiERKNS_12basic_stringIcSt11char_traitsIcESaIcEEEPmi
.LEHE1:
	movl	%eax, -76(%rbp)
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev
	leaq	-77(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev
	cmpl	$0, -76(%rbp)
	jne	.L26
	movl	$600000000, -76(%rbp)
	jmp	.L26
.L25:
	movl	$600000000, -76(%rbp)
.L26:
	cmpl	$3, -84(%rbp)
	jle	.L27
	movl	$1, -72(%rbp)
.L27:
	cmpl	$2, -84(%rbp)
	jle	.L28
	leaq	-77(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcEC1Ev
	movq	-96(%rbp), %rax
	addq	$16, %rax
	movq	(%rax), %rcx
	leaq	-77(%rbp), %rdx
	leaq	-64(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
.LEHB2:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1EPKcRKS3_
.LEHE2:
	leaq	-64(%rbp), %rax
	movl	$10, %edx
	movl	$0, %esi
	movq	%rax, %rdi
.LEHB3:
	call	_ZNSt7__cxx114stoiERKNS_12basic_stringIcSt11char_traitsIcESaIcEEEPmi
.LEHE3:
	movl	%eax, -68(%rbp)
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev
	leaq	-77(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev
	cmpl	$0, -72(%rbp)
	je	.L29
	leaq	-64(%rbp), %rax
	movl	$_ZL8kOutFile, %esi
	movq	%rax, %rdi
.LEHB4:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1ERKS4_
.LEHE4:
	leaq	-64(%rbp), %rdx
	movl	-68(%rbp), %eax
	movq	%rdx, %rsi
	movl	%eax, %edi
.LEHB5:
	call	_Z23WriteTestedValuesToFileiNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE
.LEHE5:
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev
.L29:
	movl	-76(%rbp), %edx
	movl	-68(%rbp), %eax
	movl	%edx, %esi
	movl	%eax, %edi
.LEHB6:
	call	_Z31MakeNMeasurementsAndPrintToFileii
	jmp	.L30
.L28:
	movl	-76(%rbp), %eax
	movl	%eax, %esi
	movl	$1, %edi
	call	_Z31MakeNMeasurementsAndPrintToFileii
.L30:
	movl	$0, %eax
	movq	-24(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L37
	jmp	.L43
.L39:
	movq	%rax, %rbx
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev
	jmp	.L33
.L38:
	movq	%rax, %rbx
.L33:
	leaq	-77(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev
	movq	%rbx, %rax
	movq	%rax, %rdi
	call	_Unwind_Resume
.L41:
	movq	%rax, %rbx
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev
	jmp	.L35
.L40:
	movq	%rax, %rbx
.L35:
	leaq	-77(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev
	movq	%rbx, %rax
	movq	%rax, %rdi
	call	_Unwind_Resume
.L42:
	movq	%rax, %rbx
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev
	movq	%rbx, %rax
	movq	%rax, %rdi
	call	_Unwind_Resume
.LEHE6:
.L43:
	call	__stack_chk_fail
.L37:
	addq	$88, %rsp
	popq	%rbx
	popq	%rbp
.LCFI36:
	ret
.LFE2130:
	.globl	__gxx_personality_v0
	.section	.gcc_except_table,"a",@progbits
.LLSDA2130:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2130-.LLSDACSB2130
.LLSDACSB2130:
	.uleb128 .LEHB0-.LFB2130
	.uleb128 .LEHE0-.LEHB0
	.uleb128 .L38-.LFB2130
	.uleb128 0
	.uleb128 .LEHB1-.LFB2130
	.uleb128 .LEHE1-.LEHB1
	.uleb128 .L39-.LFB2130
	.uleb128 0
	.uleb128 .LEHB2-.LFB2130
	.uleb128 .LEHE2-.LEHB2
	.uleb128 .L40-.LFB2130
	.uleb128 0
	.uleb128 .LEHB3-.LFB2130
	.uleb128 .LEHE3-.LEHB3
	.uleb128 .L41-.LFB2130
	.uleb128 0
	.uleb128 .LEHB4-.LFB2130
	.uleb128 .LEHE4-.LEHB4
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB5-.LFB2130
	.uleb128 .LEHE5-.LEHB5
	.uleb128 .L42-.LFB2130
	.uleb128 0
	.uleb128 .LEHB6-.LFB2130
	.uleb128 .LEHE6-.LEHB6
	.uleb128 0
	.uleb128 0
.LLSDACSE2130:
	.text
	.size	main, .-main
	.globl	_Z23WriteTestedValuesToFileiNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE
	.type	_Z23WriteTestedValuesToFileiNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE, @function
_Z23WriteTestedValuesToFileiNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE:
.LFB2131:
	pushq	%rbp
.LCFI37:
	movq	%rsp, %rbp
.LCFI38:
	pushq	%rbx
	subq	$120, %rsp
.LCFI39:
	movl	%edi, -100(%rbp)
	movq	%rsi, -112(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	cmpl	$1, -100(%rbp)
	jle	.L45
	pxor	%xmm0, %xmm0
	cvtsi2sd	-100(%rbp), %xmm0
	movsd	.LC1(%rip), %xmm1
	divsd	%xmm0, %xmm1
	movapd	%xmm1, %xmm0
	movsd	%xmm0, -96(%rbp)
	movsd	-96(%rbp), %xmm0
	movsd	%xmm0, -88(%rbp)
	movsd	-96(%rbp), %xmm0
	movsd	.LC1(%rip), %xmm1
	divsd	%xmm1, %xmm0
	movsd	.LC1(%rip), %xmm1
	addsd	%xmm1, %xmm0
	movsd	%xmm0, -80(%rbp)
	jmp	.L46
.L45:
	movsd	.LC2(%rip), %xmm0
	movsd	%xmm0, -96(%rbp)
	movsd	-96(%rbp), %xmm0
	movsd	%xmm0, -88(%rbp)
	movsd	-96(%rbp), %xmm0
	movsd	.LC1(%rip), %xmm1
	divsd	%xmm1, %xmm0
	movsd	.LC2(%rip), %xmm1
	addsd	%xmm1, %xmm0
	movsd	%xmm0, -80(%rbp)
.L46:
	movsd	-88(%rbp), %xmm0
	movsd	%xmm0, -72(%rbp)
.L49:
	movsd	-80(%rbp), %xmm0
	ucomisd	-72(%rbp), %xmm0
	jb	.L56
	movq	-112(%rbp), %rdx
	leaq	-64(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB7:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1ERKS4_
.LEHE7:
	leaq	-64(%rbp), %rdx
	movq	-72(%rbp), %rax
	movq	%rdx, %rdi
	movq	%rax, -120(%rbp)
	movsd	-120(%rbp), %xmm0
.LEHB8:
	call	_Z18WriteDoubleToTabledNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE
.LEHE8:
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev
	movsd	-72(%rbp), %xmm0
	addsd	-96(%rbp), %xmm0
	movsd	%xmm0, -72(%rbp)
	jmp	.L49
.L56:
	movq	-112(%rbp), %rdx
	leaq	-64(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB9:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1ERKS4_
.LEHE9:
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
.LEHB10:
	call	_Z18WriteNewRowToTableNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE
.LEHE10:
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev
	nop
	movq	-24(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L52
	jmp	.L57
.L53:
	movq	%rax, %rbx
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB11:
	call	_Unwind_Resume
.L54:
	movq	%rax, %rbx
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev
	movq	%rbx, %rax
	movq	%rax, %rdi
	call	_Unwind_Resume
.LEHE11:
.L57:
	call	__stack_chk_fail
.L52:
	addq	$120, %rsp
	popq	%rbx
	popq	%rbp
.LCFI40:
	ret
.LFE2131:
	.section	.gcc_except_table
.LLSDA2131:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2131-.LLSDACSB2131
.LLSDACSB2131:
	.uleb128 .LEHB7-.LFB2131
	.uleb128 .LEHE7-.LEHB7
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB8-.LFB2131
	.uleb128 .LEHE8-.LEHB8
	.uleb128 .L53-.LFB2131
	.uleb128 0
	.uleb128 .LEHB9-.LFB2131
	.uleb128 .LEHE9-.LEHB9
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB10-.LFB2131
	.uleb128 .LEHE10-.LEHB10
	.uleb128 .L54-.LFB2131
	.uleb128 0
	.uleb128 .LEHB11-.LFB2131
	.uleb128 .LEHE11-.LEHB11
	.uleb128 0
	.uleb128 0
.LLSDACSE2131:
	.text
	.size	_Z23WriteTestedValuesToFileiNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE, .-_Z23WriteTestedValuesToFileiNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE
	.globl	_Z31MakeNMeasurementsAndPrintToFileii
	.type	_Z31MakeNMeasurementsAndPrintToFileii, @function
_Z31MakeNMeasurementsAndPrintToFileii:
.LFB2132:
	pushq	%rbp
.LCFI41:
	movq	%rsp, %rbp
.LCFI42:
	pushq	%rbx
	subq	$120, %rsp
.LCFI43:
	movl	%edi, -116(%rbp)
	movl	%esi, -120(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	cmpl	$1, -116(%rbp)
	jle	.L59
	pxor	%xmm0, %xmm0
	cvtsi2sd	-116(%rbp), %xmm0
	movsd	.LC1(%rip), %xmm1
	divsd	%xmm0, %xmm1
	movapd	%xmm1, %xmm0
	movsd	%xmm0, -104(%rbp)
	movsd	-104(%rbp), %xmm0
	movsd	%xmm0, -96(%rbp)
	movsd	-104(%rbp), %xmm0
	movsd	.LC1(%rip), %xmm1
	divsd	%xmm1, %xmm0
	movsd	.LC1(%rip), %xmm1
	addsd	%xmm1, %xmm0
	movsd	%xmm0, -88(%rbp)
	jmp	.L60
.L59:
	movsd	.LC2(%rip), %xmm0
	movsd	%xmm0, -104(%rbp)
	movsd	-104(%rbp), %xmm0
	movsd	%xmm0, -96(%rbp)
	movsd	-104(%rbp), %xmm0
	movsd	.LC1(%rip), %xmm1
	divsd	%xmm1, %xmm0
	movsd	.LC2(%rip), %xmm1
	addsd	%xmm1, %xmm0
	movsd	%xmm0, -88(%rbp)
.L60:
	movsd	-96(%rbp), %xmm0
	movsd	%xmm0, -80(%rbp)
.L63:
	movsd	-88(%rbp), %xmm0
	ucomisd	-80(%rbp), %xmm0
	jb	.L70
	pxor	%xmm0, %xmm0
	cvtsi2sd	-120(%rbp), %xmm0
	mulsd	-80(%rbp), %xmm0
	cvttsd2siq	%xmm0, %rax
	movq	%rax, %rdi
.LEHB12:
	call	_Z28MakeMeasurementAndGetTimeSecx
	movq	%xmm0, %rax
	movq	%rax, -72(%rbp)
	leaq	-64(%rbp), %rax
	movl	$_ZL8kOutFile, %esi
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1ERKS4_
.LEHE12:
	leaq	-64(%rbp), %rdx
	movq	-72(%rbp), %rax
	movq	%rdx, %rdi
	movq	%rax, -128(%rbp)
	movsd	-128(%rbp), %xmm0
.LEHB13:
	call	_Z18WriteDoubleToTabledNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE
.LEHE13:
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev
	movsd	-80(%rbp), %xmm0
	addsd	-104(%rbp), %xmm0
	movsd	%xmm0, -80(%rbp)
	jmp	.L63
.L70:
	leaq	-64(%rbp), %rax
	movl	$_ZL8kOutFile, %esi
	movq	%rax, %rdi
.LEHB14:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1ERKS4_
.LEHE14:
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
.LEHB15:
	call	_Z18WriteNewRowToTableNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE
.LEHE15:
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev
	nop
	movq	-24(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L66
	jmp	.L71
.L67:
	movq	%rax, %rbx
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB16:
	call	_Unwind_Resume
.L68:
	movq	%rax, %rbx
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev
	movq	%rbx, %rax
	movq	%rax, %rdi
	call	_Unwind_Resume
.LEHE16:
.L71:
	call	__stack_chk_fail
.L66:
	addq	$120, %rsp
	popq	%rbx
	popq	%rbp
.LCFI44:
	ret
.LFE2132:
	.section	.gcc_except_table
.LLSDA2132:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2132-.LLSDACSB2132
.LLSDACSB2132:
	.uleb128 .LEHB12-.LFB2132
	.uleb128 .LEHE12-.LEHB12
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB13-.LFB2132
	.uleb128 .LEHE13-.LEHB13
	.uleb128 .L67-.LFB2132
	.uleb128 0
	.uleb128 .LEHB14-.LFB2132
	.uleb128 .LEHE14-.LEHB14
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB15-.LFB2132
	.uleb128 .LEHE15-.LEHB15
	.uleb128 .L68-.LFB2132
	.uleb128 0
	.uleb128 .LEHB16-.LFB2132
	.uleb128 .LEHE16-.LEHB16
	.uleb128 0
	.uleb128 0
.LLSDACSE2132:
	.text
	.size	_Z31MakeNMeasurementsAndPrintToFileii, .-_Z31MakeNMeasurementsAndPrintToFileii
	.section	.rodata
.LC3:
	.string	"    res:  "
	.text
	.globl	_Z28MakeMeasurementAndGetTimeSecx
	.type	_Z28MakeMeasurementAndGetTimeSecx, @function
_Z28MakeMeasurementAndGetTimeSecx:
.LFB2133:
	pushq	%rbp
.LCFI45:
	movq	%rsp, %rbp
.LCFI46:
	pushq	%rbx
	subq	$168, %rsp
.LCFI47:
	movq	%rdi, -168(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	movl	$2, %edi
	call	sysconf
	movq	%rax, -152(%rbp)
	movq	-168(%rbp), %rax
	movq	%rax, %rsi
	movl	$_ZSt4cout, %edi
.LEHB17:
	call	_ZNSolsEx
	movl	$.LC3, %esi
	movq	%rax, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	leaq	-128(%rbp), %rax
	movq	%rax, %rdi
	call	times
	movq	-168(%rbp), %rax
	movq	%rax, %rdi
	call	_Z17CalculateIntegralx
	movq	%xmm0, %rax
	movq	%rax, -144(%rbp)
	leaq	-96(%rbp), %rax
	movq	%rax, %rdi
	call	times
	leaq	-64(%rbp), %rax
	movl	$_ZL14kOutFileValues, %esi
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1ERKS4_
.LEHE17:
	leaq	-64(%rbp), %rdx
	movq	-144(%rbp), %rax
	movq	%rdx, %rdi
	movq	%rax, -176(%rbp)
	movsd	-176(%rbp), %xmm0
.LEHB18:
	call	_Z18WriteDoubleToTabledNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE
.LEHE18:
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev
	movl	$5, %esi
	movl	$_ZSt4cout+8, %edi
	call	_ZNSt8ios_base9precisionEl
	movq	-144(%rbp), %rax
	movq	%rax, -176(%rbp)
	movsd	-176(%rbp), %xmm0
	movl	$_ZSt4cout, %edi
.LEHB19:
	call	_ZNSolsEd
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
	movq	%rax, %rdi
	call	_ZNSolsEPFRSoS_E
	movq	-96(%rbp), %rdx
	movq	-128(%rbp), %rax
	subq	%rax, %rdx
	movq	%rdx, %rax
	movq	%rax, -136(%rbp)
	pxor	%xmm0, %xmm0
	cvtsi2sdq	-136(%rbp), %xmm0
	pxor	%xmm1, %xmm1
	cvtsi2sdq	-152(%rbp), %xmm1
	divsd	%xmm1, %xmm0
	movq	-24(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L75
	jmp	.L77
.L76:
	movq	%rax, %rbx
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev
	movq	%rbx, %rax
	movq	%rax, %rdi
	call	_Unwind_Resume
.LEHE19:
.L77:
	call	__stack_chk_fail
.L75:
	addq	$168, %rsp
	popq	%rbx
	popq	%rbp
.LCFI48:
	ret
.LFE2133:
	.section	.gcc_except_table
.LLSDA2133:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2133-.LLSDACSB2133
.LLSDACSB2133:
	.uleb128 .LEHB17-.LFB2133
	.uleb128 .LEHE17-.LEHB17
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB18-.LFB2133
	.uleb128 .LEHE18-.LEHB18
	.uleb128 .L76-.LFB2133
	.uleb128 0
	.uleb128 .LEHB19-.LFB2133
	.uleb128 .LEHE19-.LEHB19
	.uleb128 0
	.uleb128 0
.LLSDACSE2133:
	.text
	.size	_Z28MakeMeasurementAndGetTimeSecx, .-_Z28MakeMeasurementAndGetTimeSecx
	.globl	_Z18WriteDoubleToTabledNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE
	.type	_Z18WriteDoubleToTabledNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE, @function
_Z18WriteDoubleToTabledNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE:
.LFB2134:
	pushq	%rbp
.LCFI49:
	movq	%rsp, %rbp
.LCFI50:
	pushq	%rbx
	subq	$568, %rsp
.LCFI51:
	movsd	%xmm0, -552(%rbp)
	movq	%rdi, -560(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	leaq	-544(%rbp), %rax
	movq	%rax, %rdi
.LEHB20:
	call	_ZNSt14basic_ofstreamIcSt11char_traitsIcEEC1Ev
.LEHE20:
	movq	-560(%rbp), %rcx
	leaq	-544(%rbp), %rax
	movl	$1, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
.LEHB21:
	call	_ZNSt14basic_ofstreamIcSt11char_traitsIcEE4openERKNSt7__cxx1112basic_stringIcS1_SaIcEEESt13_Ios_Openmode
	movq	-560(%rbp), %rax
	movl	$_ZL14kOutFileValues, %esi
	movq	%rax, %rdi
	call	_ZSteqIcEN9__gnu_cxx11__enable_ifIXsrSt9__is_charIT_E7__valueEbE6__typeERKNSt7__cxx1112basic_stringIS3_St11char_traitsIS3_ESaIS3_EEESE_
	testb	%al, %al
	je	.L79
	movl	$8, %edi
	call	_ZSt12setprecisioni
	movl	%eax, %ebx
	leaq	-544(%rbp), %rax
	movl	$_ZSt5fixedRSt8ios_base, %esi
	movq	%rax, %rdi
	call	_ZNSolsEPFRSt8ios_baseS0_E
	movl	%ebx, %esi
	movq	%rax, %rdi
	call	_ZStlsIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_St13_Setprecision
	movq	%rax, %rdx
	movq	-552(%rbp), %rax
	movq	%rax, -568(%rbp)
	movsd	-568(%rbp), %xmm0
	movq	%rdx, %rdi
	call	_ZNSolsEd
	movl	$44, %esi
	movq	%rax, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_c
	jmp	.L80
.L79:
	movl	$3, %edi
	call	_ZSt12setprecisioni
	movl	%eax, %ebx
	leaq	-544(%rbp), %rax
	movl	$_ZSt5fixedRSt8ios_base, %esi
	movq	%rax, %rdi
	call	_ZNSolsEPFRSt8ios_baseS0_E
	movl	%ebx, %esi
	movq	%rax, %rdi
	call	_ZStlsIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_St13_Setprecision
	movq	%rax, %rdx
	movq	-552(%rbp), %rax
	movq	%rax, -568(%rbp)
	movsd	-568(%rbp), %xmm0
	movq	%rdx, %rdi
	call	_ZNSolsEd
	movl	$44, %esi
	movq	%rax, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_c
.L80:
	leaq	-544(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt14basic_ofstreamIcSt11char_traitsIcEE5closeEv
.LEHE21:
	leaq	-544(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt14basic_ofstreamIcSt11char_traitsIcEED1Ev
	nop
	movq	-24(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L82
	jmp	.L84
.L83:
	movq	%rax, %rbx
	leaq	-544(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt14basic_ofstreamIcSt11char_traitsIcEED1Ev
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB22:
	call	_Unwind_Resume
.LEHE22:
.L84:
	call	__stack_chk_fail
.L82:
	addq	$568, %rsp
	popq	%rbx
	popq	%rbp
.LCFI52:
	ret
.LFE2134:
	.section	.gcc_except_table
.LLSDA2134:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2134-.LLSDACSB2134
.LLSDACSB2134:
	.uleb128 .LEHB20-.LFB2134
	.uleb128 .LEHE20-.LEHB20
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB21-.LFB2134
	.uleb128 .LEHE21-.LEHB21
	.uleb128 .L83-.LFB2134
	.uleb128 0
	.uleb128 .LEHB22-.LFB2134
	.uleb128 .LEHE22-.LEHB22
	.uleb128 0
	.uleb128 0
.LLSDACSE2134:
	.text
	.size	_Z18WriteDoubleToTabledNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE, .-_Z18WriteDoubleToTabledNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE
	.globl	_Z18WriteNewRowToTableNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE
	.type	_Z18WriteNewRowToTableNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE, @function
_Z18WriteNewRowToTableNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE:
.LFB2135:
	pushq	%rbp
.LCFI53:
	movq	%rsp, %rbp
.LCFI54:
	pushq	%rbx
	subq	$552, %rsp
.LCFI55:
	movq	%rdi, -552(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	leaq	-544(%rbp), %rax
	movq	%rax, %rdi
.LEHB23:
	call	_ZNSt14basic_ofstreamIcSt11char_traitsIcEEC1Ev
.LEHE23:
	movq	-552(%rbp), %rcx
	leaq	-544(%rbp), %rax
	movl	$1, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
.LEHB24:
	call	_ZNSt14basic_ofstreamIcSt11char_traitsIcEE4openERKNSt7__cxx1112basic_stringIcS1_SaIcEEESt13_Ios_Openmode
	leaq	-544(%rbp), %rax
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
	movq	%rax, %rdi
	call	_ZNSolsEPFRSoS_E
	leaq	-544(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt14basic_ofstreamIcSt11char_traitsIcEE5closeEv
.LEHE24:
	leaq	-544(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt14basic_ofstreamIcSt11char_traitsIcEED1Ev
	nop
	movq	-24(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L87
	jmp	.L89
.L88:
	movq	%rax, %rbx
	leaq	-544(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt14basic_ofstreamIcSt11char_traitsIcEED1Ev
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB25:
	call	_Unwind_Resume
.LEHE25:
.L89:
	call	__stack_chk_fail
.L87:
	addq	$552, %rsp
	popq	%rbx
	popq	%rbp
.LCFI56:
	ret
.LFE2135:
	.section	.gcc_except_table
.LLSDA2135:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2135-.LLSDACSB2135
.LLSDACSB2135:
	.uleb128 .LEHB23-.LFB2135
	.uleb128 .LEHE23-.LEHB23
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB24-.LFB2135
	.uleb128 .LEHE24-.LEHB24
	.uleb128 .L88-.LFB2135
	.uleb128 0
	.uleb128 .LEHB25-.LFB2135
	.uleb128 .LEHE25-.LEHB25
	.uleb128 0
	.uleb128 0
.LLSDACSE2135:
	.text
	.size	_Z18WriteNewRowToTableNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE, .-_Z18WriteNewRowToTableNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE
	.globl	_Z17CalculateIntegralx
	.type	_Z17CalculateIntegralx, @function
_Z17CalculateIntegralx:
.LFB2136:
	pushq	%rbp
.LCFI57:
	movq	%rsp, %rbp
.LCFI58:
	subq	$80, %rsp
	movq	%rdi, -72(%rbp)
	pxor	%xmm0, %xmm0
	movsd	%xmm0, -32(%rbp)
	movsd	.LC5(%rip), %xmm0
	movsd	%xmm0, -24(%rbp)
	movsd	-32(%rbp), %xmm0
	movsd	%xmm0, -48(%rbp)
	pxor	%xmm0, %xmm0
	cvtsi2sdq	-72(%rbp), %xmm0
	movsd	.LC5(%rip), %xmm1
	divsd	%xmm0, %xmm1
	movapd	%xmm1, %xmm0
	movsd	%xmm0, -16(%rbp)
	pxor	%xmm0, %xmm0
	movsd	%xmm0, -40(%rbp)
	movsd	-24(%rbp), %xmm0
	subsd	-32(%rbp), %xmm0
	pxor	%xmm1, %xmm1
	cvtsi2sdq	-72(%rbp), %xmm1
	divsd	%xmm1, %xmm0
	movsd	%xmm0, -8(%rbp)
	movl	$0, -52(%rbp)
.L92:
	movl	-52(%rbp), %eax
	cltq
	cmpq	-72(%rbp), %rax
	jge	.L91
	movq	-48(%rbp), %rax
	movq	%rax, -80(%rbp)
	movsd	-80(%rbp), %xmm0
	call	_Z12MathFunctiond
	movsd	%xmm0, -80(%rbp)
	movsd	-48(%rbp), %xmm0
	addsd	-16(%rbp), %xmm0
	call	_Z12MathFunctiond
	addsd	-80(%rbp), %xmm0
	movsd	.LC1(%rip), %xmm1
	divsd	%xmm1, %xmm0
	movsd	-40(%rbp), %xmm1
	addsd	%xmm1, %xmm0
	movsd	%xmm0, -40(%rbp)
	movsd	-48(%rbp), %xmm0
	addsd	-16(%rbp), %xmm0
	movsd	%xmm0, -48(%rbp)
	addl	$1, -52(%rbp)
	jmp	.L92
.L91:
	movsd	-40(%rbp), %xmm0
	mulsd	-8(%rbp), %xmm0
	leave
.LCFI59:
	ret
.LFE2136:
	.size	_Z17CalculateIntegralx, .-_Z17CalculateIntegralx
	.globl	_Z12MathFunctiond
	.type	_Z12MathFunctiond, @function
_Z12MathFunctiond:
.LFB2137:
	pushq	%rbp
.LCFI60:
	movq	%rsp, %rbp
.LCFI61:
	subq	$32, %rsp
	movsd	%xmm0, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, -16(%rbp)
	movsd	-16(%rbp), %xmm0
	call	sin
	movsd	%xmm0, -16(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, -24(%rbp)
	movsd	-24(%rbp), %xmm0
	call	exp
	mulsd	-16(%rbp), %xmm0
	leave
.LCFI62:
	ret
.LFE2137:
	.size	_Z12MathFunctiond, .-_Z12MathFunctiond
	.section	.text._ZN9__gnu_cxx6__stoaIlicJiEEET0_PFT_PKT1_PPS3_DpT2_EPKcS5_PmS9_,"axG",@progbits,_ZN9__gnu_cxx6__stoaIlicJiEEET0_PFT_PKT1_PPS3_DpT2_EPKcS5_PmS9_,comdat
	.weak	_ZN9__gnu_cxx6__stoaIlicJiEEET0_PFT_PKT1_PPS3_DpT2_EPKcS5_PmS9_
	.type	_ZN9__gnu_cxx6__stoaIlicJiEEET0_PFT_PKT1_PPS3_DpT2_EPKcS5_PmS9_, @function
_ZN9__gnu_cxx6__stoaIlicJiEEET0_PFT_PKT1_PPS3_DpT2_EPKcS5_PmS9_:
.LFB2139:
	pushq	%rbp
.LCFI63:
	movq	%rsp, %rbp
.LCFI64:
	subq	$80, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movq	%rdx, -56(%rbp)
	movq	%rcx, -64(%rbp)
	movl	%r8d, -68(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	call	__errno_location
	movl	$0, (%rax)
	movl	-68(%rbp), %edx
	leaq	-24(%rbp), %rsi
	movq	-56(%rbp), %rcx
	movq	-40(%rbp), %rax
	movq	%rcx, %rdi
	call	*%rax
	movq	%rax, -16(%rbp)
	movq	-24(%rbp), %rax
	cmpq	-56(%rbp), %rax
	jne	.L97
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt24__throw_invalid_argumentPKc
.L97:
	call	__errno_location
	movl	(%rax), %eax
	cmpl	$34, %eax
	je	.L98
	cmpq	$-2147483648, -16(%rbp)
	jl	.L98
	cmpq	$2147483647, -16(%rbp)
	jle	.L99
.L98:
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt20__throw_out_of_rangePKc
.L99:
	movq	-16(%rbp), %rax
	movl	%eax, -28(%rbp)
	cmpq	$0, -64(%rbp)
	je	.L100
	movq	-24(%rbp), %rax
	movq	%rax, %rdx
	movq	-56(%rbp), %rax
	subq	%rax, %rdx
	movq	%rdx, %rax
	movq	%rax, %rdx
	movq	-64(%rbp), %rax
	movq	%rdx, (%rax)
.L100:
	movl	-28(%rbp), %eax
	movq	-8(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L102
	call	__stack_chk_fail
.L102:
	leave
.LCFI65:
	ret
.LFE2139:
	.size	_ZN9__gnu_cxx6__stoaIlicJiEEET0_PFT_PKT1_PPS3_DpT2_EPKcS5_PmS9_, .-_ZN9__gnu_cxx6__stoaIlicJiEEET0_PFT_PKT1_PPS3_DpT2_EPKcS5_PmS9_
	.weak	_ZN9__gnu_cxx6__stoaIlicIiEEET0_PFT_PKT1_PPS3_DpT2_EPKcS5_PmS9_
	.set	_ZN9__gnu_cxx6__stoaIlicIiEEET0_PFT_PKT1_PPS3_DpT2_EPKcS5_PmS9_,_ZN9__gnu_cxx6__stoaIlicJiEEET0_PFT_PKT1_PPS3_DpT2_EPKcS5_PmS9_
	.section	.text._ZSteqIcEN9__gnu_cxx11__enable_ifIXsrSt9__is_charIT_E7__valueEbE6__typeERKNSt7__cxx1112basic_stringIS3_St11char_traitsIS3_ESaIS3_EEESE_,"axG",@progbits,_ZSteqIcEN9__gnu_cxx11__enable_ifIXsrSt9__is_charIT_E7__valueEbE6__typeERKNSt7__cxx1112basic_stringIS3_St11char_traitsIS3_ESaIS3_EEESE_,comdat
	.weak	_ZSteqIcEN9__gnu_cxx11__enable_ifIXsrSt9__is_charIT_E7__valueEbE6__typeERKNSt7__cxx1112basic_stringIS3_St11char_traitsIS3_ESaIS3_EEESE_
	.type	_ZSteqIcEN9__gnu_cxx11__enable_ifIXsrSt9__is_charIT_E7__valueEbE6__typeERKNSt7__cxx1112basic_stringIS3_St11char_traitsIS3_ESaIS3_EEESE_, @function
_ZSteqIcEN9__gnu_cxx11__enable_ifIXsrSt9__is_charIT_E7__valueEbE6__typeERKNSt7__cxx1112basic_stringIS3_St11char_traitsIS3_ESaIS3_EEESE_:
.LFB2241:
	pushq	%rbp
.LCFI66:
	movq	%rsp, %rbp
.LCFI67:
	pushq	%r12
	pushq	%rbx
	subq	$16, %rsp
.LCFI68:
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE4sizeEv
	movq	%rax, %rbx
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE4sizeEv
	cmpq	%rax, %rbx
	jne	.L104
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE4sizeEv
	movq	%rax, %r12
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE4dataEv
	movq	%rax, %rbx
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE4dataEv
	movq	%r12, %rdx
	movq	%rbx, %rsi
	movq	%rax, %rdi
	call	_ZNSt11char_traitsIcE7compareEPKcS2_m
	testl	%eax, %eax
	jne	.L104
	movl	$1, %eax
	jmp	.L106
.L104:
	movl	$0, %eax
.L106:
	addq	$16, %rsp
	popq	%rbx
	popq	%r12
	popq	%rbp
.LCFI69:
	ret
.LFE2241:
	.size	_ZSteqIcEN9__gnu_cxx11__enable_ifIXsrSt9__is_charIT_E7__valueEbE6__typeERKNSt7__cxx1112basic_stringIS3_St11char_traitsIS3_ESaIS3_EEESE_, .-_ZSteqIcEN9__gnu_cxx11__enable_ifIXsrSt9__is_charIT_E7__valueEbE6__typeERKNSt7__cxx1112basic_stringIS3_St11char_traitsIS3_ESaIS3_EEESE_
	.section	.rodata
.LC6:
	.string	"outtime.csv"
.LC7:
	.string	"outval.csv"
	.text
	.type	_Z41__static_initialization_and_destruction_0ii, @function
_Z41__static_initialization_and_destruction_0ii:
.LFB2398:
	pushq	%rbp
.LCFI70:
	movq	%rsp, %rbp
.LCFI71:
	pushq	%rbx
	subq	$40, %rsp
.LCFI72:
	movl	%edi, -36(%rbp)
	movl	%esi, -40(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	cmpl	$1, -36(%rbp)
	jne	.L107
	cmpl	$65535, -40(%rbp)
	jne	.L107
	movl	$_ZStL8__ioinit, %edi
.LEHB26:
	call	_ZNSt8ios_base4InitC1Ev
.LEHE26:
	movl	$__dso_handle, %edx
	movl	$_ZStL8__ioinit, %esi
	movl	$_ZNSt8ios_base4InitD1Ev, %edi
	call	__cxa_atexit
	leaq	-25(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcEC1Ev
	leaq	-25(%rbp), %rax
	movq	%rax, %rdx
	movl	$.LC6, %esi
	movl	$_ZL8kOutFile, %edi
.LEHB27:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1EPKcRKS3_
.LEHE27:
	leaq	-25(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev
	movl	$__dso_handle, %edx
	movl	$_ZL8kOutFile, %esi
	movl	$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev, %edi
	call	__cxa_atexit
	leaq	-25(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcEC1Ev
	leaq	-25(%rbp), %rax
	movq	%rax, %rdx
	movl	$.LC7, %esi
	movl	$_ZL14kOutFileValues, %edi
.LEHB28:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1EPKcRKS3_
.LEHE28:
	leaq	-25(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev
	movl	$__dso_handle, %edx
	movl	$_ZL14kOutFileValues, %esi
	movl	$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev, %edi
	call	__cxa_atexit
	jmp	.L107
.L112:
	movq	%rax, %rbx
	leaq	-25(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB29:
	call	_Unwind_Resume
.L113:
	movq	%rax, %rbx
	leaq	-25(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev
	movq	%rbx, %rax
	movq	%rax, %rdi
	call	_Unwind_Resume
.LEHE29:
.L107:
	movq	-24(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L111
	call	__stack_chk_fail
.L111:
	addq	$40, %rsp
	popq	%rbx
	popq	%rbp
.LCFI73:
	ret
.LFE2398:
	.section	.gcc_except_table
.LLSDA2398:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2398-.LLSDACSB2398
.LLSDACSB2398:
	.uleb128 .LEHB26-.LFB2398
	.uleb128 .LEHE26-.LEHB26
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB27-.LFB2398
	.uleb128 .LEHE27-.LEHB27
	.uleb128 .L112-.LFB2398
	.uleb128 0
	.uleb128 .LEHB28-.LFB2398
	.uleb128 .LEHE28-.LEHB28
	.uleb128 .L113-.LFB2398
	.uleb128 0
	.uleb128 .LEHB29-.LFB2398
	.uleb128 .LEHE29-.LEHB29
	.uleb128 0
	.uleb128 0
.LLSDACSE2398:
	.text
	.size	_Z41__static_initialization_and_destruction_0ii, .-_Z41__static_initialization_and_destruction_0ii
	.type	_GLOBAL__sub_I_main, @function
_GLOBAL__sub_I_main:
.LFB2399:
	pushq	%rbp
.LCFI74:
	movq	%rsp, %rbp
.LCFI75:
	movl	$65535, %esi
	movl	$1, %edi
	call	_Z41__static_initialization_and_destruction_0ii
	popq	%rbp
.LCFI76:
	ret
.LFE2399:
	.size	_GLOBAL__sub_I_main, .-_GLOBAL__sub_I_main
	.section	.init_array,"aw"
	.align 8
	.quad	_GLOBAL__sub_I_main
	.section	.rodata
	.align 8
.LC1:
	.long	0
	.long	1073741824
	.align 8
.LC2:
	.long	0
	.long	1072693248
	.align 8
.LC5:
	.long	1413754136
	.long	1074340347
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
	.long	.LFB999
	.long	.LFE999-.LFB999
	.uleb128 0x4
	.long	0
	.byte	0x4
	.long	.LCFI3-.LFB999
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI4-.LCFI3
	.byte	0xd
	.uleb128 0x6
	.byte	0x4
	.long	.LCFI5-.LCFI4
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.align 8
.LEFDE1:
.LSFDE3:
	.long	.LEFDE3-.LASFDE3
.LASFDE3:
	.long	.LASFDE3-.Lframe1
	.long	.LFB2130
	.long	.LFE2130-.LFB2130
	.uleb128 0x4
	.long	.LLSDA2130
	.byte	0x4
	.long	.LCFI33-.LFB2130
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI34-.LCFI33
	.byte	0xd
	.uleb128 0x6
	.byte	0x4
	.long	.LCFI35-.LCFI34
	.byte	0x83
	.uleb128 0x3
	.byte	0x4
	.long	.LCFI36-.LCFI35
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.align 8
.LEFDE3:
.LSFDE5:
	.long	.LEFDE5-.LASFDE5
.LASFDE5:
	.long	.LASFDE5-.Lframe1
	.long	.LFB2131
	.long	.LFE2131-.LFB2131
	.uleb128 0x4
	.long	.LLSDA2131
	.byte	0x4
	.long	.LCFI37-.LFB2131
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI38-.LCFI37
	.byte	0xd
	.uleb128 0x6
	.byte	0x4
	.long	.LCFI39-.LCFI38
	.byte	0x83
	.uleb128 0x3
	.byte	0x4
	.long	.LCFI40-.LCFI39
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.align 8
.LEFDE5:
.LSFDE7:
	.long	.LEFDE7-.LASFDE7
.LASFDE7:
	.long	.LASFDE7-.Lframe1
	.long	.LFB2132
	.long	.LFE2132-.LFB2132
	.uleb128 0x4
	.long	.LLSDA2132
	.byte	0x4
	.long	.LCFI41-.LFB2132
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI42-.LCFI41
	.byte	0xd
	.uleb128 0x6
	.byte	0x4
	.long	.LCFI43-.LCFI42
	.byte	0x83
	.uleb128 0x3
	.byte	0x4
	.long	.LCFI44-.LCFI43
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.align 8
.LEFDE7:
.LSFDE9:
	.long	.LEFDE9-.LASFDE9
.LASFDE9:
	.long	.LASFDE9-.Lframe1
	.long	.LFB2133
	.long	.LFE2133-.LFB2133
	.uleb128 0x4
	.long	.LLSDA2133
	.byte	0x4
	.long	.LCFI45-.LFB2133
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI46-.LCFI45
	.byte	0xd
	.uleb128 0x6
	.byte	0x4
	.long	.LCFI47-.LCFI46
	.byte	0x83
	.uleb128 0x3
	.byte	0x4
	.long	.LCFI48-.LCFI47
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.align 8
.LEFDE9:
.LSFDE11:
	.long	.LEFDE11-.LASFDE11
.LASFDE11:
	.long	.LASFDE11-.Lframe1
	.long	.LFB2134
	.long	.LFE2134-.LFB2134
	.uleb128 0x4
	.long	.LLSDA2134
	.byte	0x4
	.long	.LCFI49-.LFB2134
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI50-.LCFI49
	.byte	0xd
	.uleb128 0x6
	.byte	0x4
	.long	.LCFI51-.LCFI50
	.byte	0x83
	.uleb128 0x3
	.byte	0x4
	.long	.LCFI52-.LCFI51
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.align 8
.LEFDE11:
.LSFDE13:
	.long	.LEFDE13-.LASFDE13
.LASFDE13:
	.long	.LASFDE13-.Lframe1
	.long	.LFB2135
	.long	.LFE2135-.LFB2135
	.uleb128 0x4
	.long	.LLSDA2135
	.byte	0x4
	.long	.LCFI53-.LFB2135
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI54-.LCFI53
	.byte	0xd
	.uleb128 0x6
	.byte	0x4
	.long	.LCFI55-.LCFI54
	.byte	0x83
	.uleb128 0x3
	.byte	0x4
	.long	.LCFI56-.LCFI55
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.align 8
.LEFDE13:
.LSFDE15:
	.long	.LEFDE15-.LASFDE15
.LASFDE15:
	.long	.LASFDE15-.Lframe1
	.long	.LFB2139
	.long	.LFE2139-.LFB2139
	.uleb128 0x4
	.long	0
	.byte	0x4
	.long	.LCFI63-.LFB2139
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI64-.LCFI63
	.byte	0xd
	.uleb128 0x6
	.byte	0x4
	.long	.LCFI65-.LCFI64
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.align 8
.LEFDE15:
.LSFDE17:
	.long	.LEFDE17-.LASFDE17
.LASFDE17:
	.long	.LASFDE17-.Lframe1
	.long	.LFB2398
	.long	.LFE2398-.LFB2398
	.uleb128 0x4
	.long	.LLSDA2398
	.byte	0x4
	.long	.LCFI70-.LFB2398
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI71-.LCFI70
	.byte	0xd
	.uleb128 0x6
	.byte	0x4
	.long	.LCFI72-.LCFI71
	.byte	0x83
	.uleb128 0x3
	.byte	0x4
	.long	.LCFI73-.LCFI72
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.align 8
.LEFDE17:
	.hidden	__dso_handle
	.ident	"GCC: (Ubuntu 5.5.0-12ubuntu1~16.04) 5.5.0 20171010"
	.section	.note.GNU-stack,"",@progbits
