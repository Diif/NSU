main:
        push    {r7, lr} #: r7 служит как base pointer, lr (link register) хранит адрес команды, на которую нужно вернуться
        add     r7, sp, #0
        mov     r1, #17920 #: инструкции в 32 бита не позволяют сразу большое число положить.
        movt    r1, 9155 #: в инструкции 8 бит под числу, 4 бита под двойной сдвиг. r1 = kNFor40Secs
        movs    r0, #1 #: update flags
        bl      MakeNMeasurementsAndPrint(int, int)
        movs    r3, #0
        mov     r0, r3
        pop     {r7, pc}
MakeNMeasurementsAndPrint(int, int):
        push    {r7, lr}
        sub     sp, sp, #48
        add     r7, sp, #0
        str     r0, [r7, #4]
        str     r1, [r7]
        mov     r2, #0
        mov     r3, #0
        movt    r3, 16368
        strd    r2, [r7, #32]
        ldrd    r2, [r7, #32]
        strd    r2, [r7, #24]
        vldr.64 d17, [r7, #32]
        vmov.f64        d18, #2.0e+0
        vdiv.f64        d16, d17, d18
        vmov.f64        d17, #1.0e+0
        vadd.f64        d16, d16, d17
        vstr.64 d16, [r7, #16]
        ldrd    r2, [r7, #24]
        strd    r2, [r7, #40]
        b       .L6
.L7:
        ldr     r3, [r7]
        vmov    s15, r3 @ int
        vcvt.f64.s32    d17, s15
        vldr.64 d16, [r7, #40]
        vmul.f64        d16, d17, d16
        vmov    r0, r1, d16
        bl      __aeabi_d2lz
        mov     r2, r0
        mov     r3, r1
        mov     r0, r2
        mov     r1, r3
        bl      MakeMeasurementAndGetTimeSec(long long)
        vmov.f64        d16, d0
        vstr.64 d16, [r7, #8]
        vldr.64 d17, [r7, #40]
        vldr.64 d16, [r7, #32]
        vadd.f64        d16, d17, d16
        vstr.64 d16, [r7, #40]
.L6:
        vldr.64 d17, [r7, #40]
        vldr.64 d16, [r7, #16]
        vcmpe.f64       d17, d16
        vmrs    APSR_nzcv, FPSCR
        bls     .L7
        nop
        nop
        adds    r7, r7, #48
        mov     sp, r7
        pop     {r7, pc}
MakeMeasurementAndGetTimeSec(long long):
        push    {r4, r5, r7, r8, r9, lr}
        vpush.64        {d8}
        sub     sp, sp, #64
        add     r7, sp, #0
        strd    r0, [r7]
        movs    r0, #2
        bl      sysconf
        mov     r3, r0
        asrs    r2, r3, #31
        mov     r8, r3
        mov     r9, r2
        strd    r8, [r7, #56]
        add     r3, r7, #24
        mov     r0, r3
        bl      times
        ldrd    r0, [r7]
        bl      CalculateIntegral(long long)
        vmov.f64        d16, d0
        vstr.64 d16, [r7, #48]
        add     r3, r7, #8
        mov     r0, r3
        bl      times
        movs    r1, #5
        ldr     r0, .L10
        bl      std::ios_base::precision(int)
        vldr.64 d0, [r7, #48]
        movw    r0, #:lower16:_ZSt4cout
        movt    r0, #:upper16:_ZSt4cout
        bl      std::basic_ostream<char, std::char_traits<char> >::operator<<(double)
        mov     r3, r0
        movw    r1, #:lower16:_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_
        movt    r1, #:upper16:_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_
        mov     r0, r3
        bl      std::basic_ostream<char, std::char_traits<char> >::operator<<(std::basic_ostream<char, std::char_traits<char> >& (*)(std::basic_ostream<char, std::char_traits<char> >&))
        ldr     r2, [r7, #8]
        ldr     r3, [r7, #24]
        subs    r3, r2, r3
        asrs    r2, r3, #31
        mov     r4, r3
        mov     r5, r2
        strd    r4, [r7, #40]
        ldrd    r0, [r7, #40]
        bl      __aeabi_l2d
        vmov    d8, r0, r1
        ldrd    r0, [r7, #56]
        bl      __aeabi_l2d
        vmov    d17, r0, r1
        vdiv.f64        d16, d8, d17
        vmov.f64        d0, d16
        adds    r7, r7, #64
        mov     sp, r7
        vldm    sp!, {d8}
        pop     {r4, r5, r7, r8, r9, pc}
.L10:
        .word   _ZSt4cout+4
CalculateIntegral(long long):
        push    {r4, r5, r7, lr}
        vpush.64        {d8}
        sub     sp, sp, #64
        add     r7, sp, #0
        strd    r0, [r7]
        mov     r2, #0
        mov     r3, #0
        strd    r2, [r7, #32]
        adr     r3, .L16
        ldrd    r2, [r3]
        strd    r2, [r7, #24]
        ldrd    r2, [r7, #32]
        strd    r2, [r7, #56]
        ldrd    r0, [r7]
        bl      __aeabi_l2d
        vmov    d18, r0, r1
        vldr.64 d17, .L16
        vdiv.f64        d16, d17, d18
        vstr.64 d16, [r7, #16]
        mov     r2, #0
        mov     r3, #0
        strd    r2, [r7, #48]
        vldr.64 d17, [r7, #24]
        vldr.64 d16, [r7, #32]
        vsub.f64        d8, d17, d16
        ldrd    r0, [r7]
        bl      __aeabi_l2d
        vmov    d17, r0, r1
        vdiv.f64        d16, d8, d17
        vstr.64 d16, [r7, #8]
        movs    r3, #0
        str     r3, [r7, #44]
        b       .L13
.L14:
        vldr.64 d0, [r7, #56]
        bl      MathFunction(double)
        vmov.f64        d8, d0
        vldr.64 d17, [r7, #56]
        vldr.64 d16, [r7, #16]
        vadd.f64        d16, d17, d16
        vmov.f64        d0, d16
        bl      MathFunction(double)
        vmov.f64        d16, d0
        vadd.f64        d17, d8, d16
        vmov.f64        d18, #2.0e+0
        vdiv.f64        d16, d17, d18
        vldr.64 d17, [r7, #48]
        vadd.f64        d16, d17, d16
        vstr.64 d16, [r7, #48]
        vldr.64 d17, [r7, #56]
        vldr.64 d16, [r7, #16]
        vadd.f64        d16, d17, d16
        vstr.64 d16, [r7, #56]
        ldr     r3, [r7, #44]
        adds    r3, r3, #1
        str     r3, [r7, #44]
.L13:
        ldr     r3, [r7, #44]
        asrs    r2, r3, #31
        mov     r4, r3
        mov     r5, r2
        ldrd    r2, [r7]
        cmp     r4, r2
        sbcs    r3, r5, r3
        blt     .L14
        vldr.64 d17, [r7, #48]
        vldr.64 d16, [r7, #8]
        vmul.f64        d16, d17, d16
        vmov.f64        d0, d16
        adds    r7, r7, #64
        mov     sp, r7
        vldm    sp!, {d8}
        pop     {r4, r5, r7, pc}
.L16:
        .word   1413754136
        .word   1074340347
MathFunction(double):
        push    {r7, lr}
        vpush.64        {d8}
        sub     sp, sp, #8
        add     r7, sp, #0
        vstr.64 d0, [r7]
        vldr.64 d0, [r7]
        bl      sin
        vmov.f64        d8, d0
        vldr.64 d0, [r7]
        bl      exp
        vmov.f64        d16, d0
        vmul.f64        d16, d8, d16
        vmov.f64        d0, d16
        adds    r7, r7, #8
        mov     sp, r7
        vldm    sp!, {d8}
        pop     {r7, pc}
__static_initialization_and_destruction_0(int, int):
        push    {r7, lr}
        sub     sp, sp, #8
        add     r7, sp, #0
        str     r0, [r7, #4]
        str     r1, [r7]
        ldr     r3, [r7, #4]
        cmp     r3, #1
        bne     .L22
        ldr     r3, [r7]
        movw    r2, #65535
        cmp     r3, r2
        bne     .L22
        movw    r0, #:lower16:_ZStL8__ioinit
        movt    r0, #:upper16:_ZStL8__ioinit
        bl      std::ios_base::Init::Init() [complete object constructor]
        movw    r2, #:lower16:__dso_handle
        movt    r2, #:upper16:__dso_handle
        movw    r1, #:lower16:_ZNSt8ios_base4InitD1Ev
        movt    r1, #:upper16:_ZNSt8ios_base4InitD1Ev
        movw    r0, #:lower16:_ZStL8__ioinit
        movt    r0, #:upper16:_ZStL8__ioinit
        bl      __aeabi_atexit
.L22:
        nop
        adds    r7, r7, #8
        mov     sp, r7
        pop     {r7, pc}
_GLOBAL__sub_I_main:
        push    {r7, lr}
        add     r7, sp, #0
        movw    r1, #65535
        movs    r0, #1
        bl      __static_initialization_and_destruction_0(int, int)
        pop     {r7, pc}