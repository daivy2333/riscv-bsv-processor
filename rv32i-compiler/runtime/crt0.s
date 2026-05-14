    .text
    .globl _start
_start:
    # sp = 0x80000000 + 32KB - 4KB = 0x80007000
    # 栈在内存高端，向下增长，与代码/数据段分离
    lui sp, 0x80007
    # call main
    jal ra, main
    # tohost = a0
    lui t0, 0x80001
    sw a0, 0(t0)
loop:
    j loop
