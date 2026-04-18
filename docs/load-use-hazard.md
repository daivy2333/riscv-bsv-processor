# Load-Use 冒险检测

## 问题

Load 指令数据在 MEM 阶段才从内存读取，EX 阶段需要操作数时数据尚未可用。

## 检测位置

ID 阶段检测 EX 阶段的 Load 指令依赖。

## 检测逻辑

```
ID 阶段检查：
  if id_ex_reg.valid &&
     id_ex_reg.payload.mem_op == MEM_READ &&
     id_ex_reg.payload.rd != 0 &&
     (rs1 == rd || rs2 == rd):
    → 检测到 Load-Use 冒险
```

## 处理流程

| 周期 | Load 位置 | 使用指令 | 动作 |
|------|----------|---------|------|
| N | EX | ID 检测冒险 | stall=1, count=2, 插入气泡 |
| N+1 | MEM | ID 停顿 | count=1, 插入气泡 |
| N+2 | WB | ID 停顿 | count=0, stall=0 |
| N+3 | - | EX | Load 数据在 mem_wb_reg → WB→EX 前递可用 |

## 控制信号

```
stall > normal advance

stall 期间：
  - if_id_reg 保持不变
  - id_ex_reg.valid = False（气泡）
  - IF 阶段暂停
```

## 气泡包

```bsv
ID_EX_Packet {
    write_reg: False,  // 不写寄存器
    mem_op: MEM_NONE,  // 不访问内存
    is_branch: False,  // 不执行分支
    // 其他字段为 0
}
```

## 为什么不能前递

| 冒险类型 | 数据可用时机 | 解决方案 |
|----------|-------------|----------|
| ALU→ALU (非 Load) | MEM 阶段（同周期） | MEM→EX 前递 |
| Load→使用 | WB 阶段（下周期） | 必须停顿 |

**ex_mem_reg 对 Load 只有地址/控制信息，无数据**。