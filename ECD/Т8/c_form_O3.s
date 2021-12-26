kNFor40Secs:
        .word   600000000
main:
        push    {r7, lr} @ r7 - сохраняет,т.к. будет использовать, link register - хранит адрес команды, на которую нужно вернуться.
        add     r7, sp, #0
        mov     r3, #17920 @ инструкции в 32 бита не позволяют сразу большое число положить.
        movt    r3, 9155 @ в инструкции 8 бит под числу, 4 бита под двойной сдвиг. r1 = kNFor40Secs
        mov     r1, r3
        movs    r0, #1  @ movs - то же, что и mov, но обновляет флаги.
        bl      MakeNMeasurementsAndPrint @ r0 =1, r1 = kNFor40Secs
        movs    r3, #0
        mov     r0, r3 @ return 0 через r0
        pop     {r7, pc}
MakeNMeasurementsAndPrint:
        push    {r7, lr}
        sub     sp, sp, #48 @ sp = r13, выделили 48 байт на стеке
        add     r7, sp, #0 
        str     r0, [r7, #4] :# в память загрузили int count_of_measurements = r7+4
        str     r1, [r7] :# в память загрузили int num_of_intervals = r7
        mov     r2, #0  :# step = 1 - IEEE754, step в r2 и r3 .
        mov     r3, #0
        movt    r3, 16368
        strd    r2, [r7, #32] @ r7+32 = step
        ldrd    r2, [r7, #32]
        strd    r2, [r7, #24] @ r7+24 = cur_stage
        vldr.64 d17, [r7, #32] @ NEON extension: d0-d31 x64 or Q0-Q15 x128
        vmov.f64        d18, #2.0e+0 @ d18 = 2
        vdiv.f64        d16, d17, d18 @ d16 = step / 2
        vmov.f64        d17, #1.0e+0 @ d17 = 1
        vadd.f64        d16, d16, d17 @ d16 = d16(step/2) + 1
        vstr.64 d16, [r7, #16] @ r7+16 = edge
        ldrd    r2, [r7, #24] 
        strd    r2, [r7, #40] @ r7+40 = coeff
        b       .L4
.L5:
        ldr     r3, [r7] @ num_of_intervals
        vmov    s15, r3 @ s15 - single precision register
        vcvt.f64.s32    d17, s15 @convert 
        vldr.64 d16, [r7, #40] @ d16 = coef
        vmul.f64        d16, d17, d16 @ d16 = coef*num_of_intervals
        vmov    r0, r1, d16 
        bl      __aeabi_d2lz @ double to long long C-style conversion
        mov     r2, r0
        mov     r3, r1
        mov     r0, r2
        mov     r1, r3
        bl      MakeMeasurementAndGetTimeSec @ call with arg long long
        vstr.64 d0, [r7, #8] @double time = d0
        vldr.64 d17, [r7, #40] @ coef
        vldr.64 d16, [r7, #32] @ step
        vadd.f64        d16, d17, d16 @coef + step
        vstr.64 d16, [r7, #40] @coef = coef+step
.L4:
        vldr.64 d17, [r7, #40] @ d17 = coef
        vldr.64 d16, [r7, #16] @ d16 = edge 
        vcmpe.f64       d17, d16 @ сравнить, 'e' - вызвать исключение, если Nan
        vmrs    APSR_nzcv, FPSCR @ Copy flags from FPSCR to flags in APSR
        bls     .L5 @ if coef < edge -> L5
        nop
        nop
        adds    r7, r7, #48
        mov     sp, r7
        pop     {r7, pc}
.LC0:
        .ascii  "%0.5lf\012\000"
MakeMeasurementAndGetTimeSec:
        push    {r4, r5, r7, r8, r9, lr}
        vpush.64        {d8}
        sub     sp, sp, #64
        add     r7, sp, #0
        strd    r0, [r7] @ [r7] = num_of_intervals
        movs    r0, #2
        bl      sysconf
        mov     r3, r0
        asrs    r2, r3, #31 @битовый сдвиг вправа на 31. Такая конвертация int в long long
        mov     r8, r3
        mov     r9, r2
        strd    r8, [r7, #56] @r7+56 = clocks_per_sec
        add     r3, r7, #24 @r7+24 = start
        mov     r0, r3
        bl      times
        ldrd    r0, [r7] 
        bl      CalculateIntegral
        vstr.64 d0, [r7, #48] @r7+48 = result
        add     r3, r7, #8 @r7+8 = end
        mov     r0, r3
        bl      times
        ldrd    r2, [r7, #48]
        movw    r0, #:lower16:.LC0 @relocation - адрес метки кладет в r0 двумя командами.
        movt    r0, #:upper16:.LC0
        bl      printf
        ldr     r2, [r7, #8]
        ldr     r3, [r7, #24]
        subs    r3, r2, r3 @ end - start и конвертация в long long
        asrs    r2, r3, #31
        mov     r4, r3
        mov     r5, r2
        strd    r4, [r7, #40] @r7+40 = clocks
        ldrd    r0, [r7, #40] @ return (double)clocks / clocks_per_sec; конвертации, ар. операции, выход из функции.
        bl      __aeabi_l2d
        vmov    d8, r0, r1 @d8 = (double)clocks
        ldrd    r0, [r7, #56]
        bl      __aeabi_l2d
        vmov    d17, r0, r1 @d17 = clocks_per_sec
        vdiv.f64        d16, d8, d17
        vmov.f64        d0, d16
        adds    r7, r7, #64
        mov     sp, r7
        vldm    sp!, {d8} @ дизассемблить будет в VPOP {d8}, ! показывает, что sp нужно обновить после pop
        pop     {r4, r5, r7, r8, r9, pc}
CalculateIntegral: @ до b       .L9 всё - просто инициализация переменных.
        push    {r4, r5, r7, lr}
        vpush.64        {d8}
        sub     sp, sp, #64
        add     r7, sp, #0
        strd    r0, [r7] @ r7 = num_of_intervals
        mov     r2, #0
        mov     r3, #0
        strd    r2, [r7, #32] @r7+32 = a
        adr     r3, .L12 @загружает адрес относительно PC. Ограничение - число 8 бит с двойным сдвигом
        ldrd    r2, [r3]
        strd    r2, [r7, #24] @r7+24 = b
        ldrd    r2, [r7, #32]
        strd    r2, [r7, #56] @r7+56 = x
        ldrd    r0, [r7]
        bl      __aeabi_l2d
        vmov    d18, r0, r1
        vldr.64 d17, .L12
        vdiv.f64        d16, d17, d18
        vstr.64 d16, [r7, #16] @r7+16 = step
        mov     r2, #0
        mov     r3, #0
        strd    r2, [r7, #48] @r7+48 = sum
        vldr.64 d17, [r7, #24]
        vldr.64 d16, [r7, #32]
        vsub.f64        d8, d17, d16
        ldrd    r0, [r7]
        bl      __aeabi_l2d
        vmov    d17, r0, r1
        vdiv.f64        d16, d8, d17
        vstr.64 d16, [r7, #8] @r7+8 = len_coef
        movs    r3, #0 @i = 0
        str     r3, [r7, #44] @r7+44 = i 
        b       .L9
.L10:
        vldr.64 d0, [r7, #56]
        bl      MathFunction
        vmov.f64        d8, d0 @d8 = MathFunction(x)
        vldr.64 d17, [r7, #56]
        vldr.64 d16, [r7, #16]
        vadd.f64        d16, d17, d16
        vmov.f64        d0, d16
        bl      MathFunction
        vmov.f64        d16, d0 @d16 = MathFunction(x + step)
        vadd.f64        d17, d8, d16 @d17 = MathFunction(x)+MathFunction(x+step)
        vmov.f64        d18, #2.0e+0
        vdiv.f64        d16, d17, d18 @d16 = (MathFunction(x)+MathFunction(x+step) )/ 2
        vldr.64 d17, [r7, #48]
        vadd.f64        d16, d17, d16 @sum+= (MathFunction(x)+MathFunction(x+step) )/ 2
        vstr.64 d16, [r7, #48] @сохранил Sum
        vldr.64 d17, [r7, #56]
        vldr.64 d16, [r7, #16]
        vadd.f64        d16, d17, d16
        vstr.64 d16, [r7, #56] @x = x+step
        ldr     r3, [r7, #44]
        adds    r3, r3, #1 @i++
        str     r3, [r7, #44]
.L9:
        ldr     r3, [r7, #44]
        asrs    r2, r3, #31 @конвертация i в long long
        mov     r4, r3
        mov     r5, r2
        ldrd    r2, [r7]
        cmp     r4, r2 @ сравнение i < num_of_intervals
        sbcs    r3, r5, r3
        blt     .L10
        vldr.64 d17, [r7, #48]
        vldr.64 d16, [r7, #8]
        vmul.f64        d16, d17, d16
        vmov.f64        d0, d16 @return sum*len_coef
        adds    r7, r7, #64
        mov     sp, r7
        vldm    sp!, {d8}
        pop     {r4, r5, r7, pc}
.L12:
        .word   1413754136
        .word   1074340347
MathFunction:
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