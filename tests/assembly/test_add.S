# RISC-V 汇编测试程序
# 测试基本的算术运算和内存访问

.globl _start

_start:
    # 初始化寄存器
    li x1, 10      # x1 = 10
    li x2, 20      # x2 = 20
    li x3, 30      # x3 = 30

    # 算术运算
    add x4, x1, x2 # x4 = x1 + x2 = 30
    add x5, x4, x3 # x5 = x4 + x3 = 60

    # 存储到内存
    lui x6, 0x1    # x6 = 0x1000 (4096)
    sw x5, 0(x6)   # mem[0] = x5 = 60

    # 从内存加载
    lw x7, 0(x6)   # x7 = mem[0] = 60

    # 使用加载的值
    add x8, x7, x1 # x8 = x7 + x1 = 70

    # 无限循环
loop:
    j loop
