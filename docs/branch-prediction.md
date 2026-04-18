# 分支预测机制

## 组件

| 组件 | 说明 |
|------|------|
| BHT | 分支历史表，64 条目，2 位饱和计数器 |
| BTB | 分支目标缓冲区，64 条目，缓存跳转目标地址 |

## 预测流程

```
IF 阶段：
  1. BHT 查询 → 是否预测跳转
  2. BTB 查询 → 跳转目标地址
  3. 当前周期仍取原地址指令（不跳过）
  4. 预测只影响下一周期 PC

ID 阶段：
  1. 传递 predicted_taken/predicted_target 到 ID_EX_Packet

EX 阶段：
  1. 执行分支判断，得到实际 taken/not taken
  2. 检测 misprediction = (predicted_taken != branch_taken)
  3. 如果预测失败 → 冲刷流水线，重定向 PC

冲刷恢复期间：
  - 禁用预测（直到 branch_flush_done 清除）
```

## BHT 状态机

```
00 (强不跳转) → 实际跳转 → 01
01 (弱不跳转) → 实际跳转 → 10
10 (弱跳转)   → 实际跳转 → 11
11 (强跳转)   → 实际跳转 → 11

预测: state >= 10 → taken
```

## 更新时机

EX 阶段实际分支结果：
- 条件分支 → 更新 BHT + BTB
- JAL/JALR → 更新 BTB（总是跳转）

## 预测失败处理

| 场景 | 处理 |
|------|------|
| 预测 taken，实际 not taken | 冲刷流水线，PC 重定向到 PC+4 |
| 预测 not taken，实际 taken | 冲刷流水线，PC 重定向到分支目标 |
| BTB 未命中 | 顺序执行，无惩罚 |

**关键修复点**：
- 预测只影响下一周期 PC，当前指令必须正常进入流水线
- ID_EX_Packet 必须携带 predicted_taken/predicted_target 字段
- 冲刷恢复期间禁用预测，避免二次错误

## 分支冲刷

分支命中时：
```
1. 设置 branch_flush / no_pc_update 标志
2. 清空 if_id_reg / id_ex_reg 的 valid
3. 更新 PC 为实际目标
4. 下周期从新 PC 取指
```

## 索引方式

- PC[11:2] 作为索引（直接映射）
- 64 条目覆盖 256 字节对齐空间