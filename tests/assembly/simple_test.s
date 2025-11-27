# tests/assembly/simple_test.s
.section .text
.global _start

_start:
    # 测试加法
    li a0, 10          # a0 = 10
    li a1, 20          # a1 = 20  
    add a2, a0, a1     # a2 = a0 + a1 (应该得到30)
    
    # 测试存储器访问
    li a3, 0x1000      # 存储地址
    sw a2, 0(a3)       # 存储结果
    lw a4, 0(a3)       # 加载回来
    
    # 简单循环测试
    li t0, 5           # 循环计数器
loop:
    addi t0, t0, -1    # 递减
    bnez t0, loop      # 如果非零则继续循环
    
    # 退出
    li a7, 93          # 退出系统调用
    li a0, 0           # 退出码0
    ecall