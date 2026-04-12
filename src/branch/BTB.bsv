// src/branch/BTB.bsv
package BTB;

import Types::*;
import Vector::*;

// 分支目标缓冲区接口
interface BTB;
    // 根据PC查找分支目标地址
    method Maybe#(Addr) lookup(Addr pc);

    // 更新BTB（条件更新）
    method Action update(Addr branch_pc, Addr target, Bool valid);
endinterface

// 64条目的BTB（直接映射）
module mkBTB(BTB);
    Vector#(64, Reg#(BTBEntry)) btbTable <- replicateM(mkReg(BTBEntry {
        branch_pc: 0,
        target_addr: 0,
        valid: False
    }));

    function Bit#(6) getIndex(Addr pc);
        return pc[7:2];
    endfunction

    method Maybe#(Addr) lookup(Addr pc);
        Bit#(6) index = getIndex(pc);
        BTBEntry entry = btbTable[index];
        if (entry.valid && entry.branch_pc == pc) begin
            return Valid(entry.target_addr);
        end else begin
            return Invalid;
        end
    endmethod

    method Action update(Addr branch_pc, Addr target, Bool valid);
        Bit#(6) index = getIndex(branch_pc);
        BTBEntry entry = btbTable[index];
        // 只在有效或PC匹配时更新
        if (valid || entry.branch_pc == branch_pc) begin
            BTBEntry newEntry = BTBEntry {
                branch_pc: branch_pc,
                target_addr: target,
                valid: valid
            };
            btbTable[index] <= newEntry;
        end
    endmethod
endmodule

endpackage