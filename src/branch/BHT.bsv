// src/branch/BHT.bsv
package BHT;

import Types::*;
import Vector::*;

// 分支历史表接口
interface BHT;
    // 根据PC预测分支是否命中
    method Bool predict(Addr pc);

    // 更新分支历史（根据实际命中结果）
    method Action update(Addr pc, Bool taken);
endinterface

// 64条目的BHT（使用2位饱和计数器）
module mkBHT(BHT);
    // 64条目，每条目2位饱和计数器
    Vector#(64, Reg#(BHTState)) bhtTable <- replicateM(mkReg(2'b01));

    // 使用PC低位作为索引（直接映射）
    function Bit#(6) getIndex(Addr pc);
        return pc[7:2];  // 使用PC[7:2]，忽略最低2位（字对齐）
    endfunction

    method Bool predict(Addr pc);
        Bit#(6) index = getIndex(pc);
        BHTState state = bhtTable[index];
        return bhtPredict(state);
    endmethod

    method Action update(Addr pc, Bool taken);
        Bit#(6) index = getIndex(pc);
        BHTState oldState = bhtTable[index];
        BHTState newState = bhtUpdate(oldState, taken);
        bhtTable[index] <= newState;
    endmethod
endmodule

endpackage