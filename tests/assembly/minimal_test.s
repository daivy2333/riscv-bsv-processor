# Minimal test: just write to tohost and halt
.section .text
.global _start
_start:
    li x6, 0x80001000
    li x7, 1
    sw x7, 0(x6)
end:
    j end
