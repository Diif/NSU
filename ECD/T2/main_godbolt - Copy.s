.LC0:
        .string "stoi"
main:
        pushq   %rbp
        movq    %rsp, %rbp
        pushq   %rbx
        subq    $168, %rsp
        movl    %edi, -164(%rbp)
        movq    %rsi, -176(%rbp)
        movl    $0, -24(%rbp)
        cmpl    $1, -164(%rbp)
        jle     .L25
        leaq    -113(%rbp), %rax
        movq    %rax, %rdi
        call    std::allocator<char>::allocator() [complete object constructor]
        movq    -176(%rbp), %rax
        addq    $8, %rax
        movq    (%rax), %rcx
        leaq    -113(%rbp), %rdx
        leaq    -160(%rbp), %rax
        movq    %rcx, %rsi
        movq    %rax, %rdi
        call    std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&) [complete object constructor]
        leaq    -160(%rbp), %rax
        movl    $10, %edx
        movl    $0, %esi
        movq    %rax, %rdi
        call    std::__cxx11::stoi(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, unsigned long*, int)
        movl    %eax, -20(%rbp)
        leaq    -160(%rbp), %rax
        movq    %rax, %rdi
        call    std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string() [complete object destructor]
        leaq    -113(%rbp), %rax
        movq    %rax, %rdi
        call    std::allocator<char>::~allocator() [complete object destructor]
        cmpl    $0, -20(%rbp)
        jne     .L26
        movl    $600000000, -20(%rbp)
        jmp     .L26
.L25:
        movl    $600000000, -20(%rbp)
.L26:
        cmpl    $3, -164(%rbp)
        jle     .L27
        movl    $1, -24(%rbp)
.L27:
        cmpl    $2, -164(%rbp)
        jle     .L28
        leaq    -65(%rbp), %rax
        movq    %rax, %rdi
        call    std::allocator<char>::allocator() [complete object constructor]
        movq    -176(%rbp), %rax
        addq    $16, %rax
        movq    (%rax), %rcx
        leaq    -65(%rbp), %rdx
        leaq    -112(%rbp), %rax
        movq    %rcx, %rsi
        movq    %rax, %rdi
        call    std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&) [complete object constructor]
        leaq    -112(%rbp), %rax
        movl    $10, %edx
        movl    $0, %esi
        movq    %rax, %rdi
        call    std::__cxx11::stoi(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, unsigned long*, int)
        movl    %eax, -28(%rbp)
        leaq    -112(%rbp), %rax
        movq    %rax, %rdi
        call    std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string() [complete object destructor]
        leaq    -65(%rbp), %rax
        movq    %rax, %rdi
        call    std::allocator<char>::~allocator() [complete object destructor]
        cmpl    $0, -24(%rbp)
        je      .L29
        leaq    -64(%rbp), %rax
        movl    $_ZL8kOutFile, %esi
        movq    %rax, %rdi
        call    std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&) [complete object constructor]
        leaq    -64(%rbp), %rdx
        movl    -28(%rbp), %eax
        movq    %rdx, %rsi
        movl    %eax, %edi
        call    WriteTestedValuesToFile(int, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >)
        leaq    -64(%rbp), %rax
        movq    %rax, %rdi
        call    std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string() [complete object destructor]
.L29:
        movl    -20(%rbp), %edx
        movl    -28(%rbp), %eax
        movl    %edx, %esi
        movl    %eax, %edi
        call    MakeNMeasurementsAndPrintToFile(int, int)
        jmp     .L30
.L28:
        movl    -20(%rbp), %eax
        movl    %eax, %esi
        movl    $1, %edi
        call    MakeNMeasurementsAndPrintToFile(int, int)
.L30:
        movl    $0, %eax
        jmp     .L42
        movq    %rax, %rbx
        leaq    -160(%rbp), %rax
        movq    %rax, %rdi
        call    std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string() [complete object destructor]
        jmp     .L33
        movq    %rax, %rbx
.L33:
        leaq    -113(%rbp), %rax
        movq    %rax, %rdi
        call    std::allocator<char>::~allocator() [complete object destructor]
        movq    %rbx, %rax
        movq    %rax, %rdi
        call    _Unwind_Resume
        movq    %rax, %rbx
        leaq    -112(%rbp), %rax
        movq    %rax, %rdi
        call    std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string() [complete object destructor]
        jmp     .L35
        movq    %rax, %rbx
.L35:
        leaq    -65(%rbp), %rax
        movq    %rax, %rdi
        call    std::allocator<char>::~allocator() [complete object destructor]
        movq    %rbx, %rax
        movq    %rax, %rdi
        call    _Unwind_Resume
        movq    %rax, %rbx
        leaq    -64(%rbp), %rax
        movq    %rax, %rdi
        call    std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string() [complete object destructor]
        movq    %rbx, %rax
        movq    %rax, %rdi
        call    _Unwind_Resume
.L42:
        movq    -8(%rbp), %rbx
        leave
        ret
WriteTestedValuesToFile(int, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >):
        pushq   %rbp
        movq    %rsp, %rbp
        pushq   %rbx
        subq    $120, %rsp
        movl    %edi, -116(%rbp)
        movq    %rsi, -128(%rbp)
        cmpl    $1, -116(%rbp)
        jle     .L44
        pxor    %xmm1, %xmm1
        cvtsi2sdl       -116(%rbp), %xmm1
        movsd   .LC1(%rip), %xmm0
        divsd   %xmm1, %xmm0
        movsd   %xmm0, -24(%rbp)
        movsd   -24(%rbp), %xmm0
        movsd   %xmm0, -32(%rbp)
        movsd   -24(%rbp), %xmm0
        movsd   .LC1(%rip), %xmm2
        movapd  %xmm0, %xmm1
        divsd   %xmm2, %xmm1
        movsd   .LC1(%rip), %xmm0
        addsd   %xmm1, %xmm0
        movsd   %xmm0, -40(%rbp)
        jmp     .L45
.L44:
        movsd   .LC2(%rip), %xmm0
        movsd   %xmm0, -24(%rbp)
        movsd   -24(%rbp), %xmm0
        movsd   %xmm0, -32(%rbp)
        movsd   -24(%rbp), %xmm0
        movsd   .LC1(%rip), %xmm2
        movapd  %xmm0, %xmm1
        divsd   %xmm2, %xmm1
        movsd   .LC2(%rip), %xmm0
        addsd   %xmm1, %xmm0
        movsd   %xmm0, -40(%rbp)
.L45:
        movsd   -32(%rbp), %xmm0
        movsd   %xmm0, -48(%rbp)
        jmp     .L46
.L47:
        movq    -128(%rbp), %rdx
        leaq    -112(%rbp), %rax
        movq    %rdx, %rsi
        movq    %rax, %rdi
        call    std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&) [complete object constructor]
        leaq    -112(%rbp), %rdx
        movq    -48(%rbp), %rax
        movq    %rdx, %rdi
        movq    %rax, %xmm0
        call    WriteDoubleToTable(double, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >)
        leaq    -112(%rbp), %rax
        movq    %rax, %rdi
        call    std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string() [complete object destructor]
        movsd   -48(%rbp), %xmm0
        addsd   -24(%rbp), %xmm0
        movsd   %xmm0, -48(%rbp)
.L46:
        movsd   -40(%rbp), %xmm0
        comisd  -48(%rbp), %xmm0
        jnb     .L47
        movq    -128(%rbp), %rdx
        leaq    -80(%rbp), %rax
        movq    %rdx, %rsi
        movq    %rax, %rdi
        call    std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&) [complete object constructor]
        leaq    -80(%rbp), %rax
        movq    %rax, %rdi
        call    WriteNewRowToTable(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >)
        leaq    -80(%rbp), %rax
        movq    %rax, %rdi
        call    std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string() [complete object destructor]
        jmp     .L52
        movq    %rax, %rbx
        leaq    -112(%rbp), %rax
        movq    %rax, %rdi
        call    std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string() [complete object destructor]
        movq    %rbx, %rax
        movq    %rax, %rdi
        call    _Unwind_Resume
        movq    %rax, %rbx
        leaq    -80(%rbp), %rax
        movq    %rax, %rdi
        call    std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string() [complete object destructor]
        movq    %rbx, %rax
        movq    %rax, %rdi
        call    _Unwind_Resume
.L52:
        movq    -8(%rbp), %rbx
        leave
        ret
MakeNMeasurementsAndPrintToFile(int, int):
        pushq   %rbp
        movq    %rsp, %rbp
        pushq   %rbx
        subq    $136, %rsp
        movl    %edi, -132(%rbp)
        movl    %esi, -136(%rbp)
        cmpl    $1, -132(%rbp)
        jle     .L54
        pxor    %xmm1, %xmm1
        cvtsi2sdl       -132(%rbp), %xmm1
        movsd   .LC1(%rip), %xmm0
        divsd   %xmm1, %xmm0
        movsd   %xmm0, -24(%rbp)
        movsd   -24(%rbp), %xmm0
        movsd   %xmm0, -32(%rbp)
        movsd   -24(%rbp), %xmm0
        movsd   .LC1(%rip), %xmm2
        movapd  %xmm0, %xmm1
        divsd   %xmm2, %xmm1
        movsd   .LC1(%rip), %xmm0
        addsd   %xmm1, %xmm0
        movsd   %xmm0, -40(%rbp)
        jmp     .L55
.L54:
        movsd   .LC2(%rip), %xmm0
        movsd   %xmm0, -24(%rbp)
        movsd   -24(%rbp), %xmm0
        movsd   %xmm0, -32(%rbp)
        movsd   -24(%rbp), %xmm0
        movsd   .LC1(%rip), %xmm2
        movapd  %xmm0, %xmm1
        divsd   %xmm2, %xmm1
        movsd   .LC2(%rip), %xmm0
        addsd   %xmm1, %xmm0
        movsd   %xmm0, -40(%rbp)
.L55:
        movsd   -32(%rbp), %xmm0
        movsd   %xmm0, -48(%rbp)
        jmp     .L56
.L57:
        pxor    %xmm0, %xmm0
        cvtsi2sdl       -136(%rbp), %xmm0
        mulsd   -48(%rbp), %xmm0
        cvttsd2siq      %xmm0, %rax
        movq    %rax, %rdi
        call    MakeMeasurementAndGetTimeSec(long long)
        movq    %xmm0, %rax
        movq    %rax, -56(%rbp)
        leaq    -128(%rbp), %rax
        movl    $_ZL8kOutFile, %esi
        movq    %rax, %rdi
        call    std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&) [complete object constructor]
        leaq    -128(%rbp), %rdx
        movq    -56(%rbp), %rax
        movq    %rdx, %rdi
        movq    %rax, %xmm0
        call    WriteDoubleToTable(double, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >)
        leaq    -128(%rbp), %rax
        movq    %rax, %rdi
        call    std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string() [complete object destructor]
        movsd   -48(%rbp), %xmm0
        addsd   -24(%rbp), %xmm0
        movsd   %xmm0, -48(%rbp)
.L56:
        movsd   -40(%rbp), %xmm0
        comisd  -48(%rbp), %xmm0
        jnb     .L57
        leaq    -96(%rbp), %rax
        movl    $_ZL8kOutFile, %esi
        movq    %rax, %rdi
        call    std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&) [complete object constructor]
        leaq    -96(%rbp), %rax
        movq    %rax, %rdi
        call    WriteNewRowToTable(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >)
        leaq    -96(%rbp), %rax
        movq    %rax, %rdi
        call    std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string() [complete object destructor]
        jmp     .L62
        movq    %rax, %rbx
        leaq    -128(%rbp), %rax
        movq    %rax, %rdi
        call    std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string() [complete object destructor]
        movq    %rbx, %rax
        movq    %rax, %rdi
        call    _Unwind_Resume
        movq    %rax, %rbx
        leaq    -96(%rbp), %rax
        movq    %rax, %rdi
        call    std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string() [complete object destructor]
        movq    %rbx, %rax
        movq    %rax, %rdi
        call    _Unwind_Resume
.L62:
        movq    -8(%rbp), %rbx
        leave
        ret
.LC3:
        .string "    res:  "
MakeMeasurementAndGetTimeSec(long long):
        pushq   %rbp
        movq    %rsp, %rbp
        pushq   %rbx
        subq    $152, %rsp
        movq    %rdi, -152(%rbp)
        movl    $2, %edi
        call    sysconf
        movq    %rax, -24(%rbp)
        movq    -152(%rbp), %rax
        movq    %rax, %rsi
        movl    $_ZSt4cout, %edi
        call    std::basic_ostream<char, std::char_traits<char> >::operator<<(long long)
        movl    $.LC3, %esi
        movq    %rax, %rdi
        call    std::basic_ostream<char, std::char_traits<char> >& std::operator<< <std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*)
        leaq    -112(%rbp), %rax
        movq    %rax, %rdi
        call    times
        movq    -152(%rbp), %rax
        movq    %rax, %rdi
        call    CalculateIntegral(long long)
        movq    %xmm0, %rax
        movq    %rax, -32(%rbp)
        leaq    -144(%rbp), %rax
        movq    %rax, %rdi
        call    times
        leaq    -80(%rbp), %rax
        movl    $_ZL14kOutFileValues, %esi
        movq    %rax, %rdi
        call    std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&) [complete object constructor]
        leaq    -80(%rbp), %rdx
        movq    -32(%rbp), %rax
        movq    %rdx, %rdi
        movq    %rax, %xmm0
        call    WriteDoubleToTable(double, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >)
        leaq    -80(%rbp), %rax
        movq    %rax, %rdi
        call    std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string() [complete object destructor]
        movl    $5, %esi
        movl    $_ZSt4cout+8, %edi
        call    std::ios_base::precision(long)
        movq    -32(%rbp), %rax
        movq    %rax, %xmm0
        movl    $_ZSt4cout, %edi
        call    std::basic_ostream<char, std::char_traits<char> >::operator<<(double)
        movl    $_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
        movq    %rax, %rdi
        call    std::basic_ostream<char, std::char_traits<char> >::operator<<(std::basic_ostream<char, std::char_traits<char> >& (*)(std::basic_ostream<char, std::char_traits<char> >&))
        movq    -144(%rbp), %rax
        movq    -112(%rbp), %rdx
        subq    %rdx, %rax
        movq    %rax, -40(%rbp)
        pxor    %xmm0, %xmm0
        cvtsi2sdq       -40(%rbp), %xmm0
        pxor    %xmm1, %xmm1
        cvtsi2sdq       -24(%rbp), %xmm1
        divsd   %xmm1, %xmm0
        movq    %xmm0, %rax
        jmp     .L67
        movq    %rax, %rbx
        leaq    -80(%rbp), %rax
        movq    %rax, %rdi
        call    std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string() [complete object destructor]
        movq    %rbx, %rax
        movq    %rax, %rdi
        call    _Unwind_Resume
.L67:
        movq    %rax, %xmm0
        movq    -8(%rbp), %rbx
        leave
        ret
WriteDoubleToTable(double, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >):
        pushq   %rbp
        movq    %rsp, %rbp
        pushq   %rbx
        subq    $536, %rsp
        movsd   %xmm0, -536(%rbp)
        movq    %rdi, -544(%rbp)
        leaq    -528(%rbp), %rax
        movq    %rax, %rdi
        call    std::basic_ofstream<char, std::char_traits<char> >::basic_ofstream() [complete object constructor]
        movq    -544(%rbp), %rcx
        leaq    -528(%rbp), %rax
        movl    $1, %edx
        movq    %rcx, %rsi
        movq    %rax, %rdi
        call    std::basic_ofstream<char, std::char_traits<char> >::open(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, std::_Ios_Openmode)
        movq    -544(%rbp), %rax
        movl    $_ZL14kOutFileValues, %esi
        movq    %rax, %rdi
        call    __gnu_cxx::__enable_if<std::__is_char<char>::__value, bool>::__type std::operator==<char>(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&)
        testb   %al, %al
        je      .L69
        leaq    -528(%rbp), %rax
        movl    $_ZSt5fixedRSt8ios_base, %esi
        movq    %rax, %rdi
        call    std::basic_ostream<char, std::char_traits<char> >::operator<<(std::ios_base& (*)(std::ios_base&))
        movq    %rax, %rbx
        movl    $8, %edi
        call    std::setprecision(int)
        movl    %eax, %esi
        movq    %rbx, %rdi
        call    std::basic_ostream<char, std::char_traits<char> >& std::operator<< <char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, std::_Setprecision)
        movq    %rax, %rdx
        movq    -536(%rbp), %rax
        movq    %rax, %xmm0
        movq    %rdx, %rdi
        call    std::basic_ostream<char, std::char_traits<char> >::operator<<(double)
        movl    $44, %esi
        movq    %rax, %rdi
        call    std::basic_ostream<char, std::char_traits<char> >& std::operator<< <std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char)
        jmp     .L70
.L69:
        leaq    -528(%rbp), %rax
        movl    $_ZSt5fixedRSt8ios_base, %esi
        movq    %rax, %rdi
        call    std::basic_ostream<char, std::char_traits<char> >::operator<<(std::ios_base& (*)(std::ios_base&))
        movq    %rax, %rbx
        movl    $3, %edi
        call    std::setprecision(int)
        movl    %eax, %esi
        movq    %rbx, %rdi
        call    std::basic_ostream<char, std::char_traits<char> >& std::operator<< <char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, std::_Setprecision)
        movq    %rax, %rdx
        movq    -536(%rbp), %rax
        movq    %rax, %xmm0
        movq    %rdx, %rdi
        call    std::basic_ostream<char, std::char_traits<char> >::operator<<(double)
        movl    $44, %esi
        movq    %rax, %rdi
        call    std::basic_ostream<char, std::char_traits<char> >& std::operator<< <std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char)
.L70:
        leaq    -528(%rbp), %rax
        movq    %rax, %rdi
        call    std::basic_ofstream<char, std::char_traits<char> >::close()
        leaq    -528(%rbp), %rax
        movq    %rax, %rdi
        call    std::basic_ofstream<char, std::char_traits<char> >::~basic_ofstream() [complete object destructor]
        jmp     .L73
        movq    %rax, %rbx
        leaq    -528(%rbp), %rax
        movq    %rax, %rdi
        call    std::basic_ofstream<char, std::char_traits<char> >::~basic_ofstream() [complete object destructor]
        movq    %rbx, %rax
        movq    %rax, %rdi
        call    _Unwind_Resume
.L73:
        movq    -8(%rbp), %rbx
        leave
        ret
WriteNewRowToTable(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >):
        pushq   %rbp
        movq    %rsp, %rbp
        pushq   %rbx
        subq    $536, %rsp
        movq    %rdi, -536(%rbp)
        leaq    -528(%rbp), %rax
        movq    %rax, %rdi
        call    std::basic_ofstream<char, std::char_traits<char> >::basic_ofstream() [complete object constructor]
        movq    -536(%rbp), %rcx
        leaq    -528(%rbp), %rax
        movl    $1, %edx
        movq    %rcx, %rsi
        movq    %rax, %rdi
        call    std::basic_ofstream<char, std::char_traits<char> >::open(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, std::_Ios_Openmode)
        leaq    -528(%rbp), %rax
        movl    $_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
        movq    %rax, %rdi
        call    std::basic_ostream<char, std::char_traits<char> >::operator<<(std::basic_ostream<char, std::char_traits<char> >& (*)(std::basic_ostream<char, std::char_traits<char> >&))
        leaq    -528(%rbp), %rax
        movq    %rax, %rdi
        call    std::basic_ofstream<char, std::char_traits<char> >::close()
        leaq    -528(%rbp), %rax
        movq    %rax, %rdi
        call    std::basic_ofstream<char, std::char_traits<char> >::~basic_ofstream() [complete object destructor]
        jmp     .L77
        movq    %rax, %rbx
        leaq    -528(%rbp), %rax
        movq    %rax, %rdi
        call    std::basic_ofstream<char, std::char_traits<char> >::~basic_ofstream() [complete object destructor]
        movq    %rbx, %rax
        movq    %rax, %rdi
        call    _Unwind_Resume
.L77:
        movq    -8(%rbp), %rbx
        leave
        ret
CalculateIntegral(long long):
        pushq   %rbp
        movq    %rsp, %rbp
        subq    $80, %rsp
        movq    %rdi, -72(%rbp)
        pxor    %xmm0, %xmm0
        movsd   %xmm0, -32(%rbp)
        movsd   .LC5(%rip), %xmm0
        movsd   %xmm0, -40(%rbp)
        movsd   -32(%rbp), %xmm0
        movsd   %xmm0, -8(%rbp)
        pxor    %xmm1, %xmm1
        cvtsi2sdq       -72(%rbp), %xmm1
        movsd   .LC5(%rip), %xmm0
        divsd   %xmm1, %xmm0
        movsd   %xmm0, -48(%rbp)
        pxor    %xmm0, %xmm0
        movsd   %xmm0, -16(%rbp)
        movsd   -40(%rbp), %xmm0
        subsd   -32(%rbp), %xmm0
        pxor    %xmm1, %xmm1
        cvtsi2sdq       -72(%rbp), %xmm1
        divsd   %xmm1, %xmm0
        movsd   %xmm0, -56(%rbp)
        movl    $0, -20(%rbp)
        jmp     .L79
.L80:
        movq    -8(%rbp), %rax
        movq    %rax, %xmm0
        call    MathFunction(double)
        movsd   %xmm0, -80(%rbp)
        movsd   -8(%rbp), %xmm0
        movapd  %xmm0, %xmm2
        addsd   -48(%rbp), %xmm2
        movq    %xmm2, %rax
        movq    %rax, %xmm0
        call    MathFunction(double)
        addsd   -80(%rbp), %xmm0
        movsd   .LC1(%rip), %xmm1
        divsd   %xmm1, %xmm0
        movsd   -16(%rbp), %xmm1
        addsd   %xmm1, %xmm0
        movsd   %xmm0, -16(%rbp)
        movsd   -8(%rbp), %xmm0
        addsd   -48(%rbp), %xmm0
        movsd   %xmm0, -8(%rbp)
        addl    $1, -20(%rbp)
.L79:
        movl    -20(%rbp), %eax
        cltq
        cmpq    %rax, -72(%rbp)
        jg      .L80
        movsd   -16(%rbp), %xmm0
        mulsd   -56(%rbp), %xmm0
        movq    %xmm0, %rax
        movq    %rax, %xmm0
        leave
        ret
MathFunction(double):
        pushq   %rbp
        movq    %rsp, %rbp
        subq    $16, %rsp
        movsd   %xmm0, -8(%rbp)
        movq    -8(%rbp), %rax
        movq    %rax, %xmm0
        call    sin
        movsd   %xmm0, -16(%rbp)
        movq    -8(%rbp), %rax
        movq    %rax, %xmm0
        call    exp
        mulsd   -16(%rbp), %xmm0
        movq    %xmm0, %rax
        movq    %rax, %xmm0
        leave
        ret
.LC6:
        .string "outtime.csv"
.LC7:
        .string "outval.csv"
__static_initialization_and_destruction_0(int, int):
        pushq   %rbp
        movq    %rsp, %rbp
        pushq   %rbx
        subq    $40, %rsp
        movl    %edi, -36(%rbp)
        movl    %esi, -40(%rbp)
        cmpl    $1, -36(%rbp)
        jne     .L108
        cmpl    $65535, -40(%rbp)
        jne     .L108
        movl    $_ZStL8__ioinit, %edi
        call    std::ios_base::Init::Init() [complete object constructor]
        movl    $__dso_handle, %edx
        movl    $_ZStL8__ioinit, %esi
        movl    $_ZNSt8ios_base4InitD1Ev, %edi
        call    __cxa_atexit
        leaq    -18(%rbp), %rax
        movq    %rax, %rdi
        call    std::allocator<char>::allocator() [complete object constructor]
        leaq    -18(%rbp), %rax
        movq    %rax, %rdx
        movl    $.LC6, %esi
        movl    $_ZL8kOutFile, %edi
        call    std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&) [complete object constructor]
        leaq    -18(%rbp), %rax
        movq    %rax, %rdi
        call    std::allocator<char>::~allocator() [complete object destructor]
        movl    $__dso_handle, %edx
        movl    $_ZL8kOutFile, %esi
        movl    $std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string() [complete object destructor], %edi
        call    __cxa_atexit
        leaq    -17(%rbp), %rax
        movq    %rax, %rdi
        call    std::allocator<char>::allocator() [complete object constructor]
        leaq    -17(%rbp), %rax
        movq    %rax, %rdx
        movl    $.LC7, %esi
        movl    $_ZL14kOutFileValues, %edi
        call    std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&) [complete object constructor]
        leaq    -17(%rbp), %rax
        movq    %rax, %rdi
        call    std::allocator<char>::~allocator() [complete object destructor]
        movl    $__dso_handle, %edx
        movl    $_ZL14kOutFileValues, %esi
        movl    $std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string() [complete object destructor], %edi
        call    __cxa_atexit
        jmp     .L108
        movq    %rax, %rbx
        leaq    -18(%rbp), %rax
        movq    %rax, %rdi
        call    std::allocator<char>::~allocator() [complete object destructor]
        movq    %rbx, %rax
        movq    %rax, %rdi
        call    _Unwind_Resume
        movq    %rax, %rbx
        leaq    -17(%rbp), %rax
        movq    %rax, %rdi
        call    std::allocator<char>::~allocator() [complete object destructor]
        movq    %rbx, %rax
        movq    %rax, %rdi
        call    _Unwind_Resume
.L108:
        movq    -8(%rbp), %rbx
        leave
        ret
_GLOBAL__sub_I_main:
        pushq   %rbp
        movq    %rsp, %rbp
        movl    $65535, %esi
        movl    $1, %edi
        call    __static_initialization_and_destruction_0(int, int)
        popq    %rbp
        ret
.LC1:
        .long   0
        .long   1073741824
.LC2:
        .long   0
        .long   1072693248
.LC5:
        .long   1413754136
        .long   1074340347