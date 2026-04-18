# tests/assembly/load_test.s
# Load 指令测试（无循环）

.section .text
.global _start

_start:
    # 设置数据地址
    li x6, 0x1000

    # Store 数据
    li x5, 70
    sw x5, 0(x6)

    # Load 数据并使用
    lw x7, 0(x6)       # x7 = 70
    add x8, x7, x1     # Load-Use 冒险：x8 = 70 + 10 = 80

    # 测试 li (在 Load 之后)
    li x10, 5          # x10 = 5
    li x11, 100        # x11 = 100

    # 写入 tohost 表示成功
    li x6, 0x80001000
    li x7, 1
    sw x7, 0(x6)

end:
    j end