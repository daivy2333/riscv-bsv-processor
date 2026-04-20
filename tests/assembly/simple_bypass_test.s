# tests/assembly/simple_bypass_test.s
# WB bypass 测试（无 load）

.section .text
.global _start

_start:
    # 简单的 bypass 测试
    li x5, 100       # x5 = 100
    li x6, 0x80001000  # tohost address
    li x7, 1         # x7 = 1
    sw x7, 0(x6)     # write tohost = 1 (x7 应该立即可用)

end:
    j end