MathFunction:
        push    {r3, lr}
        vpush.64        {d8, d9}
        vmov.f64        d9, d0
        bl      sin
        vmov.f64        d8, d0
        vmov.f64        d0, d9
        bl      exp
        vmul.f64        d0, d8, d0
        vldm    sp!, {d8-d9}
        pop     {r3, pc}
CalculateIntegral:
        push    {r3, r4, r5, r6, r7, lr}
        vpush.64        {d8, d9, d10, d11, d12}
        mov     r6, r0
        mov     r7, r1
        bl      __aeabi_l2d
        vmov    d16, r0, r1
        vldr.64 d17, .L9
        vdiv.f64        d11, d17, d16
        cmp     r6, #1
        sbcs    r3, r7, #0
        blt     .L6
        movs    r4, #1
        movs    r5, #0
        vmov.i64        d10, #0 @ float
        vmov.f64        d9, d10
        vmov.f64        d12, #5.0e-1
.L5:
        vmov.f64        d0, d9
        bl      MathFunction
        vmov.f64        d8, d0
        vadd.f64        d9, d9, d11
        vmov.f64        d0, d9
        bl      MathFunction
        vadd.f64        d8, d8, d0
        vmla.f64        d10, d8, d12
        mov     r2, r4
        mov     r3, r5
        adds    r4, r4, #1
        adc     r5, r5, #0
        cmp     r7, r3
        it      eq
        cmpeq   r6, r2
        bne     .L5
.L4:
        vmul.f64        d0, d11, d10
        vldm    sp!, {d8-d12}
        pop     {r3, r4, r5, r6, r7, pc}
.L6:
        vmov.i64        d10, #0 @ float
        b       .L4
.L9:
        .word   1413754136
        .word   1074340347
.LC0:
        .ascii  "%0.5lf\012\000"
MakeMeasurementAndGetTimeSec:
        push    {r4, r5, lr}
        vpush.64        {d8}
        sub     sp, sp, #36
        mov     r5, r0
        mov     r4, r1
        movs    r0, #2
        bl      sysconf
        vmov    s16, r0 @ int
        add     r0, sp, #16
        bl      times
        mov     r0, r5
        mov     r1, r4
        bl      CalculateIntegral
        vmov    r4, r5, d0
        mov     r0, sp
        bl      times
        mov     r2, r4
        mov     r3, r5
        movw    r0, #:lower16:.LC0
        movt    r0, #:upper16:.LC0
        bl      printf
        ldr     r3, [sp]
        ldr     r2, [sp, #16]
        subs    r3, r3, r2
        vmov    s0, r3  @ int
        vcvt.f64.s32    d0, s0
        vcvt.f64.s32    d8, s16
        vdiv.f64        d0, d0, d8
        add     sp, sp, #36
        vldm    sp!, {d8}
        pop     {r4, r5, pc}
MakeNMeasurementsAndPrint:
        push    {r3, lr}
        mov     r0, r1
        asrs    r1, r1, #31
        bl      MakeMeasurementAndGetTimeSec
        pop     {r3, pc}
main:
        push    {r3, lr}
        mov     r1, #17920
        movt    r1, 9155
        movs    r0, #1
        bl      MakeNMeasurementsAndPrint
        movs    r0, #0
        pop     {r3, pc}
kNFor40Secs:
        .word   600000000