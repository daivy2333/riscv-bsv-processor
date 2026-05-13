    .text
    .globl __mulsi3
__mulsi3:
    # Multiply a0 (multiplicand) × a1 (multiplier) → a0 (product)
    # Uses shift-and-add algorithm
    mv t0, zero          # product = 0
    mv t1, a0            # multiplicand
    mv t2, a1            # multiplier
.Lmul_loop:
    beqz t2, .Lmul_done  # if multiplier == 0, done
    andi t3, t2, 1       # check LSB of multiplier
    beqz t3, .Lmul_skip  # if LSB == 0, skip addition
    add t0, t0, t1       # product += multiplicand
.Lmul_skip:
    slli t1, t1, 1       # multiplicand <<= 1
    srli t2, t2, 1       # multiplier >>= 1
    j .Lmul_loop
.Lmul_done:
    mv a0, t0            # return product
    ret

    .globl __udivsi3
__udivsi3:
    # Unsigned divide a0 (dividend) ÷ a1 (divisor) → a0 (quotient)
    # Returns 0 if divisor == 0
    beqz a1, .Ldiv_zero  # division by zero → return 0
    mv t0, zero          # quotient = 0
    mv t1, a0            # remainder
    mv t2, a1            # divisor
.Ldiv_loop:
    bltu t1, t2, .Ldiv_done   # if remainder < divisor, done
    sub t1, t1, t2            # remainder -= divisor
    addi t0, t0, 1            # quotient++
    j .Ldiv_loop
.Ldiv_done:
    mv a0, t0            # return quotient
    ret
.Ldiv_zero:
    mv a0, zero
    ret
