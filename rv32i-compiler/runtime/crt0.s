    .text
    .globl _start
_start:
    # sp = 0x80001000 - 4096
    lui sp, 0x80001
    addi sp, sp, -4096
    # call main
    jal ra, main
    # tohost = a0
    lui t0, 0x80001
    sw a0, 0(t0)
loop:
    j loop
