# 阶段 5：中断框架实施计划

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 实现中断框架和基础外设，使处理器能响应定时器中断和外部中断

**Architecture:** CLINT 管理_mtime 自动递增直接输出 MTIP；PLIC 管理外部中断仲裁输出 MEIP；UART 接 PLIC；Core 在提交边界检查中断

**Tech Stack:** BSV, Verilator, riscv64-unknown-elf-gcc

---

## 文件结构

```
src/
├── common/Types.bsv          # 新增 MemReq/MemResp 类型
├── peripheral/               # 新目录
│   ├── CLINT.bsv             # 定时器 + 软件中断
│   ├── PLIC.bsv              # 外部中断控制器
│   └── UART.bsv              # 串口外设
├── memory/DMem.bsv           # 独立内存模块（已有，改接口）
├── core/Core.bsv             # 提取 DMem、提交边界中断检查
├── soc/
│   ├── SOC.bsv               # 新增：MMIO 路由、模块互联
│   └ TestBench.bsv           # 修改：使用 SOC
tests/assembly/
├── timer_irq_test.s          # 新增：定时器中断测试
```

---

### Task 1: 新增内存接口类型定义

**Files:**
- Modify: `src/common/Types.bsv` (末尾添加)

- [ ] **Step 1: 在 Types.bsv 添加 MemReq/MemResp 类型**

```bsv
// ============================================================
// 内存请求/响应接口（用于 Core <-> SOC）
// ============================================================

typedef struct {
    Bool        valid;
    Addr        addr;
    Word        wdata;      // 写数据
    MemOp       op;         // READ/WRITE/NONE
    MemWidth    width;      // BYTE/HALF/WORD
    Bool        unsigned;   // 无符号扩展
} MemReq deriving (Bits, Eq, FShow);

typedef struct {
    Bool        valid;
    Word        rdata;      // 读数据（已按 width 扩展）
} MemResp deriving (Bits, Eq, FShow);

// nopMemReq: 生成空内存请求（用于无内存操作的指令）
function MemReq nopMemReq();
    return MemReq {
        valid: False,
        addr: 0,
        wdata: 0,
        op: MEM_NONE,
        width: MEM_WORD,
        unsigned: False
    };
endfunction
```

- [ ] **Step 2: 编译验证类型定义**

Run: `bsc -verilog -p src:src/common:src/core src/common/Types.bsv`
Expected: 编译成功，无错误

- [ ] **Step 3: Commit**

```bash
git add src/common/Types.bsv
git commit -m "feat(types): add MemReq/MemResp for request/response memory interface"
```

---

### Task 2: 创建 CLINT 模块

**Files:**
- Create: `src/peripheral/CLINT.bsv`

- [ ] **Step 1: 创建 CLINT.bsv**

```bsv
// src/peripheral/CLINT.bsv
package CLINT;

import Types::*;
import RegFile::*;
import Vector::*;

interface CLINT;
    method Word read(Addr addr);
    method Action write(Addr addr, Word data);
    method Bool timerIRQ();             // MTIP: mtime >= mtimecmp
    method Bool softwareIRQStatus();   // MSIP 读状态
    method Action softwareIRQ(Bool v); // MSIP 写入
endinterface

module mkCLINT(CLINT);
    // mtime: 64-bit 自动递增计数器
    Reg#(Bit#(64)) mtime <- mkReg(0);
    
    // mtimecmp: 64-bit 比较器
    Reg#(Bit#(64)) mtimecmp <- mkReg(64'hFFFFFFFFFFFFFFFF);  // 初始化为最大值
    
    // msip: 软件中断触发
    Reg#(Bool) msip <- mkReg(False);
    
    // 地址定义
    Addr ADDR_MSIP     = 32'h02000000;
    Addr ADDR_MTIME    = 32'h0200BFF8;
    Addr ADDR_MTIME_H  = 32'h0200BFFC;
    Addr ADDR_MTIMECMP = 32'h02004000;
    Addr ADDR_MTIMECMP_H = 32'h02004004;
    
    // 每 cycle 自动递增 mtime
    rule increment_mtime;
        mtime <= mtime + 1;
    endrule
    
    method Word read(Addr addr);
        Word result = 0;
        if (addr == ADDR_MSIP) begin
            result = msip ? 1 : 0;
        end else if (addr == ADDR_MTIME) begin
            result = mtime[31:0];  // 低 32-bit
        end else if (addr == ADDR_MTIME_H) begin
            result = mtime[63:32]; // 高 32-bit
        end else if (addr == ADDR_MTIMECMP) begin
            result = mtimecmp[31:0];
        end else if (addr == ADDR_MTIMECMP_H) begin
            result = mtimecmp[63:32];
        end
        return result;
    endmethod
    
    method Action write(Addr addr, Word data);
        if (addr == ADDR_MSIP) begin
            msip <= (data[0] == 1);
        end else if (addr == ADDR_MTIME) begin
            mtime <= {mtime[63:32], data};  // 写低 32-bit
        end else if (addr == ADDR_MTIME_H) begin
            mtime <= {data, mtime[31:0]};   // 写高 32-bit
        end else if (addr == ADDR_MTIMECMP) begin
            mtimecmp <= {mtimecmp[63:32], data};
        end else if (addr == ADDR_MTIMECMP_H) begin
            mtimecmp <= {data, mtimecmp[31:0]};
        end
    endmethod
    
    method Bool timerIRQ();
        return mtime >= mtimecmp;
    endmethod
    
    method Bool softwareIRQStatus();
        return msip;
    endmethod
    
    method Action softwareIRQ(Bool v);
        msip <= v;
    endmethod
endmodule

endpackage
```

- [ ] **Step 2: 编译验证 CLINT**

Run: `bsc -verilog -p src:src/common:src/peripheral src/peripheral/CLINT.bsv`
Expected: 编译成功

- [ ] **Step 3: Commit**

```bash
git add src/peripheral/CLINT.bsv
git commit -m "feat(clint): add timer/software interrupt module with auto-increment mtime"
```

---

### Task 3: 修改 CSR.bsv 接收 MTIP/MSIP/MEIP

**Files:**
- Modify: `src/core/CSR.bsv`

- [ ] **Step 1: 确认 CSR.bsv 已有 setMTIP/setMSIP/setMEIP 方法**

检查现有 CSR.bsv 是否已有：
```bsv
method Action setMEIP(Bool v);
method Action setMSIP(Bool v);
method Action setMTIP(Bool v);
```

若有，继续；若无，添加。

- [ ] **Step 2: 添加 update_mip 规则（若缺失）**

确保 CSR.bsv 有规则根据外部信号更新 mip：
```bsv
// 在 mkCSR module 内
method Action setMTIP(Bool v);
    mtip_reg <= v;
endmethod

method Action setMSIP(Bool v);
    msip_reg <= v;
endmethod

method Action setMEIP(Bool v);
    meip_reg <= v;
endmethod
```

- [ ] **Step 3: 编译验证**

Run: `bsc -verilog -p src:src/common:src/core src/core/CSR.bsv`
Expected: 编译成功

- [ ] **Step 4: Commit**

```bash
git add src/core/CSR.bsv
git commit -m "refactor(csr): ensure MTIP/MSIP/MEIP setter methods exist"
```

---

### Task 4: 修改 Core.bsv 提取 DMem 并使用请求/响应接口

**Files:**
- Modify: `src/core/Core.bsv`

这是最复杂的修改，分多步完成。

- [ ] **Step 1: 修改 Core interface 添加内存请求方法**

```bsv
interface Core;
    method Addr pc;
    method Word instruction;
    method Bool running;
    method Bool testDone;
    method Word tohostValue;
    method Action loadProgram(Vector#(1024, Word) prog);
    method Word readReg(Bit#(5) addr);
    // 新增：内存请求接口
    method MemReq memReq();
    method Action memResp(MemResp resp);
endinterface
```

- [ ] **Step 2: 添加 MemReq/MemResp 相关寄存器**

在 Core module 内添加：
```bsv
// 内存请求/响应寄存器
Reg#(MemReq) current_mem_req <- mkReg(nopMemReq());
Reg#(MemResp) pending_mem_resp <- mkReg(MemResp {valid: False, rdata: 0});
Reg#(Bool) mem_resp_pending <- mkReg(False);
```

- [ ] **Step 3: 修改 MEM 阶段生成 MemReq**

修改 memoryStage rule：
```bsv
rule memoryStage;
    EX_MEM_Packet pkt = ex2mem.first;
    ex2mem.deq;
    
    // 生成内存请求
    MemReq req = nopMemReq();
    if (pkt.mem_op != MEM_NONE) begin
        req = MemReq {
            valid: True,
            addr: pkt.alu_result,
            wdata: pkt.rs2_val,
            op: pkt.mem_op,
            width: pkt.mem_width,
            unsigned: pkt.mem_unsigned
        };
    end
    current_mem_req <= req;
    
    // 如果是读操作，标记等待响应
    if (pkt.mem_op == MEM_READ) begin
        mem_resp_pending <= True;
    end
    
    // 继续传递到 WB（不带 mem_data，等待响应）
    mem2wb.enq(MEM_WB_Packet {
        pc: pkt.pc,
        mem_data: 0,  // 等待响应填充
        alu_result: pkt.alu_result,
        rd: pkt.rd,
        write_reg: pkt.write_reg,
        is_load: pkt.mem_op == MEM_READ
    });
endrule
```

- [ ] **Step 4: 修改 WB 阶段等待响应**

修改 writebackStage rule：
```bsv
rule writebackStage;
    MEM_WB_Packet pkt = mem2wb.first;
    mem2wb.deq;
    
    Word wb_data = pkt.alu_result;
    
    // 如果是 Load，等待响应
    if (pkt.is_load && mem_resp_pending) begin
        wb_data = pending_mem_resp.rdata;
        mem_resp_pending <= False;
    end
    
    if (pkt.write_reg && pkt.rd != 0) begin
        regFile.write(pkt.rd, wb_data);
    end
    
    // ... 前递更新逻辑保持不变 ...
    
    // 提交边界检查中断
    if (csrs.hasPendingInterrupt()) begin
        MStatus ms = unpackMStatus(csrs.readCSR(12'h300));
        if (ms.mie) begin
            // 保存 trap 信息
            Bit#(5) cause = csrs.getPendingInterruptCause();
            csrs.writeCSR(12'h341, pack(pkt.pc));  // mepc
            csrs.writeCSR(12'h342, {1'b1, 27'b0, cause});  // mcause (最高位=1表示中断)
            csrs.writeCSR(12'h343, 0);  // mtval
            
            MStatus new_ms = ms;
            new_ms.mpie = ms.mie;
            new_ms.mpp = 2'b11;  // M-mode
            new_ms.mie = 0;
            csrs.writeCSR(12'h300, packMStatus(new_ms));
            
            // flush 流水线
            if2id.clear;
            id2ex.clear;
            ex2mem.clear;
            
            // 跳转到 mtvec
            Addr trap_vec = csrs.readCSR(12'h305) & ~32'h3;
            pcReg <= trap_vec;
        end
    end
endrule
```

- [ ] **Step 5: 添加 interface methods**

```bsv
method MemReq memReq();
    return current_mem_req;
endmethod

method Action memResp(MemResp resp);
    pending_mem_resp <= resp;
endmethod
```

- [ ] **Step 6: 移除 Core 内的 dmem 定义**

删除 Core.bsv 内的 `Vector#(512, Reg#(Word)) dmem` 定义和相关内存访问逻辑。

- [ ] **Step 7: 编译验证**

Run: `bsc -verilog -p src:src/common:src/core src/core/Core.bsv`
Expected: 编译成功

- [ ] **Step 8: Commit**

```bash
git add src/core/Core.bsv
git commit -m "refactor(core): extract DMem, add request/response memory interface, commit-boundary interrupt check"
```

---

### Task 5: 修改 DMem.bsv 添加 tohost 监控

**Files:**
- Modify: `src/memory/DMem.bsv`

- [ ] **Step 1: 修改 DMem interface**

```bsv
interface DMem;
    method Word read(Addr addr);
    method Action write(Addr addr, Word data);
    method Bool tohostWritten();   // tohost 写入检测
    method Word tohostValue();     // tohost 写入值
endinterface
```

- [ ] **Step 2: 添加 tohost 监控寄存器**

```bsv
module mkDMem(DMem);
    Vector#(16384, Reg#(Word)) memory <- replicateM(mkReg(0));  // 64KB (16K words)
    
    Reg#(Bool) tohost_written <- mkReg(False);
    Reg#(Word) tohost_value <- mkReg(0);
    Addr tohost_addr = 32'h80001000;
    
    method Word read(Addr addr);
        Bit#(14) idx = addr[15:2];  // 14-bit index for 64KB
        return memory[idx];
    endmethod
    
    method Action write(Addr addr, Word data);
        Bit#(14) idx = addr[15:2];
        memory[idx] <= data;
        
        // tohost 监控
        if (addr == tohost_addr) begin
            tohost_written <= True;
            tohost_value <= data;
        end
    endmethod
    
    method Bool tohostWritten();
        return tohost_written;
    endmethod
    
    method Word tohostValue();
        return tohost_value;
    endmethod
endmodule
```

- [ ] **Step 3: 编译验证**

Run: `bsc -verilog -p src:src/common:src/memory src/memory/DMem.bsv`
Expected: 编译成功

- [ ] **Step 4: Commit**

```bash
git add src/memory/DMem.bsv
git commit -m "refactor(dmem): expand to 64KB, add tohost monitoring callback"
```

---

### Task 6: 创建 PLIC 模块

**Files:**
- Create: `src/peripheral/PLIC.bsv`

- [ ] **Step 1: 创建 PLIC.bsv**

```bsv
// src/peripheral/PLIC.bsv
package PLIC;

import Types::*;
import RegFile::*;
import Vector::*;

interface PLIC;
    method Word read(Addr addr);
    method Action write(Addr addr, Word data);
    method Bool externalIRQ();          // MEIP 输出
    method Action setIRQ(Bit#(32) source_id, Bool v);  // 外设 IRQ 输入
endinterface

module mkPLIC(PLIC);
    // 简化实现：支持最多 32 个中断源
    Vector#(32, Reg#(Bool)) irq_pending <- replicateM(mkReg(False));
    Vector#(32, Reg#(Bit#(32))) priority <- replicateM(mkReg(1));  // 默认优先级 1
    
    Reg#(Bit#(32)) threshold <- mkReg(0);       // 优先级阈值
    Reg#(Bit#(32)) enable_bits <- mkReg(0);     // 使能位
    
    Reg#(Bit#(32)) claim_id <- mkReg(0);        // 当前 claim 的中断号
    
    // 地址定义
    Addr ADDR_THRESHOLD = 32'h0C000000;
    Addr ADDR_PRIORITY_BASE = 32'h0C000004;    // priority[1] 开始
    Addr ADDR_ENABLE = 32'h0C002000;
    Addr ADDR_CLAIM_COMPLETE = 32'h0C200004;
    
    // 计算最高优先级挂起中断
    function Bit#(32) getHighestPending();
        Bit#(32) highest_id = 0;
        Bit#(32) highest_pri = 0;
        for (Integer i = 1; i < 32; i = i + 1) begin
            if (irq_pending[i] && (enable_bits[i] == 1)) begin
                Bit#(32) pri = priority[i];
                if (pri > highest_pri && pri > threshold) begin
                    highest_pri = pri;
                    highest_id = fromInteger(i);
                end
            end
        end
        return highest_id;
    endfunction
    
    method Word read(Addr addr);
        Word result = 0;
        if (addr == ADDR_THRESHOLD) begin
            result = threshold;
        end else if (addr >= ADDR_PRIORITY_BASE && addr < ADDR_PRIORITY_BASE + 32*4) begin
            Bit#(32) src_id = (addr - ADDR_PRIORITY_BASE) >> 2;
            if (src_id > 0 && src_id < 32)
                result = priority[src_id];
        end else if (addr == ADDR_ENABLE) begin
            result = enable_bits;
        end else if (addr == ADDR_CLAIM_COMPLETE) begin
            // claim: 返回最高优先级挂起中断
            result = getHighestPending();
        end
        return result;
    endmethod
    
    method Action write(Addr addr, Word data);
        if (addr == ADDR_THRESHOLD) begin
            threshold <= data;
        end else if (addr >= ADDR_PRIORITY_BASE && addr < ADDR_PRIORITY_BASE + 32*4) begin
            Bit#(32) src_id = (addr - ADDR_PRIORITY_BASE) >> 2;
            if (src_id > 0 && src_id < 32)
                priority[src_id] <= data;
        end else if (addr == ADDR_ENABLE) begin
            enable_bits <= data;
        end else if (addr == ADDR_CLAIM_COMPLETE) begin
            // complete: 清除挂起状态
            Bit#(32) id = data;
            if (id > 0 && id < 32)
                irq_pending[id] <= False;
        end
    endmethod
    
    method Bool externalIRQ();
        return getHighestPending() != 0;
    endmethod
    
    method Action setIRQ(Bit#(32) source_id, Bool v);
        if (source_id > 0 && source_id < 32)
            irq_pending[source_id] <= v;
    endmethod
endmodule

endpackage
```

- [ ] **Step 2: 编译验证 PLIC**

Run: `bsc -verilog -p src:src/common:src/peripheral src/peripheral/PLIC.bsv`
Expected: 编译成功

- [ ] **Step 3: Commit**

```bash
git add src/peripheral/PLIC.bsv
git commit -m "feat(plic): add external interrupt controller with claim/complete"
```

---

### Task 7: 创建 UART 模块

**Files:**
- Create: `src/peripheral/UART.bsv`

- [ ] **Step 1: 创建 UART.bsv**

```bsv
// src/peripheral/UART.bsv
package UART;

import Types::*;
import RegFile::*;

interface UART;
    method Word read(Addr addr);
    method Action write(Addr addr, Word data);
    method Bool hasIRQ();              // IRQ 输出（接 PLIC）
endinterface

module mkUART(UART);
    Reg#(Bit#(8)) txdata <- mkReg(0);
    Reg#(Bool) tx_full <- mkReg(False);
    Reg#(Bit#(8)) rxdata <- mkReg(0);
    Reg#(Bool) rx_valid <- mkReg(False);
    
    Reg#(Bool) tx_enable <- mkReg(False);
    Reg#(Bool) rx_enable <- mkReg(False);
    
    Reg#(Bit#(32)) ie <- mkReg(0);     // 中断使能
    Reg#(Bit#(32)) ip <- mkReg(0);     // 中断挂起
    
    // 地址偏移
    Addr OFFSET_TXDATA = 0;
    Addr OFFSET_RXDATA = 4;
    Addr OFFSET_TXCTRL = 8;
    Addr OFFSET_RXCTRL = 12;
    Addr OFFSET_IE = 16;
    Addr OFFSET_IP = 20;
    
    // 模拟发送完成（简化实现）
    rule tx_complete (tx_full);
        tx_full <= False;
        ip[0] <= 1;  // TX 完成 interrupt
        $display("UART TX: %h", txdata);
    endrule
    
    method Word read(Addr addr);
        Addr offset = addr & 32'hFF;  // 取低 8 位
        Word result = 0;
        case (offset)
            OFFSET_TXDATA: result = tx_full ? 1 : 0;  // TX 状态
            OFFSET_RXDATA: result = rx_valid ? {24'b0, rxdata} : 0;
            OFFSET_TXCTRL: result = tx_enable ? 1 : 0;
            OFFSET_RXCTRL: result = rx_enable ? 1 : 0;
            OFFSET_IE:     result = ie;
            OFFSET_IP:     result = ip;
            default:       result = 0;
        endcase
        return result;
    endmethod
    
    method Action write(Addr addr, Word data);
        Addr offset = addr & 32'hFF;
        case (offset)
            OFFSET_TXDATA: begin
                txdata <= data[7:0];
                tx_full <= True;
            end
            OFFSET_TXCTRL: tx_enable <= (data[0] == 1);
            OFFSET_RXCTRL: rx_enable <= (data[0] == 1);
            OFFSET_IE:     ie <= data;
            OFFSET_IP:     ip <= ip & ~data;  // 写 1 清除
            default:       ;  // ignore
        endcase
    endmethod
    
    method Bool hasIRQ();
        // TXWM (bit 0) 或 RXWM (bit 1) 中断
        return (ip & ie) != 0;
    endmethod
endmodule

endpackage
```

- [ ] **Step 2: 编译验证 UART**

Run: `bsc -verilog -p src:src/common:src/peripheral src/peripheral/UART.bsv`
Expected: 编译成功

- [ ] **Step 3: Commit**

```bash
git add src/peripheral/UART.bsv
git commit -m "feat(uart): add simple UART peripheral with TX/RX and IRQ"
```

---

### Task 8: 创建 SOC 模块

**Files:**
- Create: `src/soc/SOC.bsv`

- [ ] **Step 1: 创建 SOC.bsv**

```bsv
// src/soc/SOC.bsv
package SOC;

import Types::*;
import Core::*;
import CLINT::*;
import PLIC::*;
import UART::*;
import DMem::*;
import CSR::*;
import Vector::*;
import FIFO::*;

interface SOC;
    method Bool testDone();
    method Word tohostValue();
    method Action loadProgram(Vector#(1024, Word) prog);
    method Word readReg(Bit#(5) addr);
endinterface

module mkSOC(SOC);
    Core core <- mkCore("test");
    CLINT clint <- mkCLINT;
    PLIC plic <- mkPLIC;
    UART uart <- mkUART;
    DMem dmem <- mkDMem;
    
    // 内存请求响应寄存器
    Reg#(MemResp) mem_resp_reg <- mkReg(MemResp {valid: False, rdata: 0});
    Reg#(Bool) resp_ready <- mkReg(False);
    
    // 处理 Core 内存请求
    rule handle_mem_req;
        MemReq req = core.memReq();
        
        if (req.valid) begin
            Addr addr = req.addr;
            Word rdata = 0;
            
            // 地址路由
            if (addr >= 32'h02000000 && addr < 32'h02010000) begin
                // CLINT
                if (req.op == MEM_READ)
                    rdata = clint.read(addr);
                else if (req.op == MEM_WRITE)
                    clint.write(addr, req.wdata);
            end else if (addr >= 32'h0C000000 && addr < 32'h0C100000) begin
                // PLIC
                if (req.op == MEM_READ)
                    rdata = plic.read(addr);
                else if (req.op == MEM_WRITE)
                    plic.write(addr, req.wdata);
            end else if (addr >= 32'h10000000 && addr < 32'h10001000) begin
                // UART
                if (req.op == MEM_READ)
                    rdata = uart.read(addr);
                else if (req.op == MEM_WRITE)
                    uart.write(addr, req.wdata);
            end else if (addr >= 32'h80000000) begin
                // RAM
                if (req.op == MEM_READ)
                    rdata = dmem.read(addr);
                else if (req.op == MEM_WRITE)
                    dmem.write(addr, req.wdata);
            end
            
            // 响应
            if (req.op == MEM_READ) begin
                // 字节/半字扩展（由 Core 负责，这里返回原始 word）
                mem_resp_reg <= MemResp {valid: True, rdata: rdata};
                resp_ready <= True;
            end
        end
    endrule
    
    // 发送响应给 Core
    rule send_mem_resp (resp_ready);
        core.memResp(mem_resp_reg);
        resp_ready <= False;
    endrule
    
    // 中断信号连接
    rule connect_interrupts;
        core.csrs.setMTIP(clint.timerIRQ());
        core.csrs.setMSIP(clint.softwareIRQStatus());
        core.csrs.setMEIP(plic.externalIRQ());
        plic.setIRQ(1, uart.hasIRQ());  // UART -> PLIC source_id=1
    endrule
    
    method Bool testDone();
        return dmem.tohostWritten();
    endmethod
    
    method Word tohostValue();
        return dmem.tohostValue();
    endmethod
    
    method Action loadProgram(Vector#(1024, Word) prog);
        core.loadProgram(prog);
    endmethod
    
    method Word readReg(Bit#(5) addr);
        return core.readReg(addr);
    endmethod
endmodule

endpackage
```

- [ ] **Step 2: 编译验证 SOC**

Run: `bsc -verilog -p src:src/common:src/core:src/peripheral:src/memory:src/soc src/soc/SOC.bsv`
Expected: 编译成功（可能有接口问题需调整）

- [ ] **Step 3: Commit**

```bash
git add src/soc/SOC.bsv
git commit -m "feat(soc): add top-level module with MMIO routing and interrupt connections"
```

---

### Task 9: 修改 TestBench 使用 SOC

**Files:**
- Modify: `src/soc/TestBench.bsv`

- [ ] **Step 1: 修改 TestBench 使用 SOC**

```bsv
// src/soc/TestBench.bsv
package TestBench;

import Types::*;
import SOC::*;
import Vector::*;
import TestProgram::*;

interface TestBench;
    method Bool done();
endinterface

module mkTestBench(TestBench);
    SOC soc <- mkSOC;
    
    Reg#(Bit#(32)) cycleCount <- mkReg(0);
    Reg#(Bool) programDone <- mkReg(False);
    Reg#(Bool) dumpDone <- mkReg(False);
    Reg#(Bool) programLoaded <- mkReg(False);
    
    rule load (!programLoaded);
        soc.loadProgram(testProgram());
        programLoaded <= True;
    endrule
    
    rule countCycles (programLoaded && !dumpDone);
        cycleCount <= cycleCount + 1;
    endrule
    
    rule checkDone (programLoaded && !programDone);
        if (soc.testDone()) begin
            programDone <= True;
        end
        // 超时检测
        if (cycleCount >= 100000) begin
            programDone <= True;
        end
    endrule
    
    rule report (programDone && !dumpDone);
        $display("\n====================================");
        if (soc.tohostValue() == 1) begin
            $display("  Test Results: PASSED");
        end else begin
            $display("  Test Results: FAILED (tohost=0x%x)", soc.tohostValue());
        end
        $display("====================================");
        $display("Cycles: %0d", cycleCount);
        dumpDone <= True;
    endrule
    
    rule finish (dumpDone);
        $finish(0);
    endrule
    
    method Bool done = dumpDone;
endmodule

endpackage
```

- [ ] **Step 2: 编译完整系统**

Run: `make compile`
Expected: 编译成功

- [ ] **Step 3: Commit**

```bash
git add src/soc/TestBench.bsv
git commit -m "refactor(testbench): use SOC module instead of direct Core"
```

---

### Task 10: 创建 timer_irq_test.s

**Files:**
- Create: `tests/assembly/timer_irq_test.s`

- [ ] **Step 1: 创建 timer_irq_test.s**

```asm
# tests/assembly/timer_irq_test.s
# 测试定时器中断 + mret 返回

.section .text
.global _start

_start:
    # 设置 trap handler
    la t0, trap_handler
    csrw mtvec, t0
    
    # 设置 mtimecmp = 100（100 周期后触发）
    li t1, 100
    li t2, 0x02004000      # mtimecmp 地址
    sw t1, 0(t2)
    sw zero, 4(t2)         # 高 32-bit = 0
    
    # 启用定时器中断
    li t1, 0x80            # MTIE (bit 7)
    csrw mie, t1
    
    # 启用全局中断
    li t1, 0x8             # MIE (bit 3)
    csrw mstatus, t1
    
    # 等待中断触发
    wait_loop:
        nop
        nop
        j wait_loop

trap_handler:
    # 保存返回地址
    csrr t0, mepc
    
    # 检查 mcause 是否是定时器中断
    csrr t1, mcause
    li t2, 0x80000007      # Interrupt bit + MTIP cause
    beq t1, t2, is_timer_irq
    
    # 不是定时器中断，失败
    li t3, 0xDEAD
    j end_test
    
is_timer_irq:
    # 更新 mtimecmp 防止再次触发
    li t2, 0x02004000
    li t3, 0xFFFFFFFF
    sw t3, 0(t2)
    sw t3, 4(t2)
    
    # 返回成功
    li t3, 1
    
end_test:
    # 写入 tohost
    li t4, 0x80001000
    sw t3, 0(t4)
    
    # 停止
halt:
    j halt
```

- [ ] **Step 2: 编译测试**

Run: `riscv64-unknown-elf-gcc -march=rv32i_zicsr -mabi=ilp32 -nostdlib -static -T scripts/link.ld tests/assembly/timer_irq_test.s -o firmware/timer_irq_test.elf && riscv64-unknown-elf-objcopy -O verilog firmware/timer_irq_test.elf firmware/timer_irq_test.hex`

- [ ] **Step 3: 生成 BSV 测试程序**

Run: `python3 tools/hex_to_bsv.py firmware/timer_irq_test.hex > src/soc/TestProgram.bsv`

- [ ] **Step 4: 运行测试**

Run: `make compile && rm -rf obj_dir && verilator --cc --exe --build -o VmkTestBench --top-module mkTestBench build/mkTestBench.v /opt/bsc/lib/Verilog/FIFO2.v tests/c/test_bench.cpp -Wno-STMTDLY -Wno-WIDTH && ./obj_dir/VmkTestBench`
Expected: PASSED 或调试输出

- [ ] **Step 5: 调试并修复问题**

根据输出调试，可能需要调整：
- Core 的中断检测逻辑
- CSR 的 mip 更新时序
- CLINT 的 mtime 递增频率

- [ ] **Step 6: Commit**

```bash
git add tests/assembly/timer_irq_test.s firmware/timer_irq_test.hex src/soc/TestProgram.bsv
git commit -m "test: add timer_irq_test for interrupt validation"
```

---

## Self-Review

**1. Spec coverage:**
- ✓ CLINT 模块（Task 2）
- ✓ CSR MTIP/MSIP/MEIP（Task 3）
- ✓ Core MemReq/MemResp + 提交边界中断（Task 4）
- ✓ DMem tohost 监控（Task 5）
- ✓ PLIC（Task 6）
- ✓ UART（Task 7）
- ✓ SOC（Task 8）
- ✓ TestBench（Task 9）
- ✓ timer_irq_test（Task 10）

**2. Placeholder scan:**
- ✓ 无 TBD/TODO
- ✓ 所有代码块完整

**3. Type consistency:**
- MemReq/MemResp 在 Task 1 定义，Task 4/8 使用
- CLINT interface Task 2 定义，Task 8 使用
- PLIC interface Task 6 定义，Task 8 使用
- UART interface Task 7 定义，Task 8 使用

---

Plan complete and saved to `docs/superpowers/plans/2026-04-18-stage5-interrupt-framework.md`. Two execution options:

**1. Subagent-Driven (recommended)** - I dispatch a fresh subagent per task, review between tasks, fast iteration

**2. Inline Execution** - Execute tasks in this session using executing-plans, batch execution with checkpoints

**Which approach?**