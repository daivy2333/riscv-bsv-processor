// src/core/ForwardUnit.bsv
package ForwardUnit;

import Types::*;

// 前递来源类型
typedef enum {
    NO_FORWARD,     // 不需要前递，使用RegFile值
    FORWARD_EX,     // 从EX阶段前递（ALU结果）
    FORWARD_MEM,    // 从MEM阶段前递（ALU结果）
    FORWARD_WB      // 从WB阶段前递（最终结果）
} ForwardSource deriving (Bits, Eq, FShow);

// 前递控制信号
typedef struct {
    ForwardSource rs1_forward;
    ForwardSource rs2_forward;
} ForwardControl deriving (Bits, Eq, FShow);

interface ForwardUnit;
    method ForwardControl checkForward(
        Bit#(5) rs1,            // ID阶段rs1编号
        Bit#(5) rs2,            // ID阶段rs2编号
        Bit#(5) ex_rd,          // EX阶段rd
        Bool ex_write_reg,      // EX阶段是否写寄存器
        Bit#(5) mem_rd,         // MEM阶段rd
        Bool mem_write_reg,     // MEM阶段是否写寄存器
        Bool mem_is_load,       // MEM阶段是否是Load
        Bit#(5) wb_rd,          // WB阶段rd
        Bool wb_write_reg       // WB阶段是否写寄存器
    );
endinterface

module mkForwardUnit(ForwardUnit);
    method ForwardControl checkForward(
        Bit#(5) rs1,
        Bit#(5) rs2,
        Bit#(5) ex_rd,
        Bool ex_write_reg,
        Bit#(5) mem_rd,
        Bool mem_write_reg,
        Bool mem_is_load,
        Bit#(5) wb_rd,
        Bool wb_write_reg
    );

        ForwardSource rs1_forward = NO_FORWARD;
        ForwardSource rs2_forward = NO_FORWARD;

        // 检查rs1前递需求
        // WB阶段最近，优先级最高
        if (wb_write_reg && wb_rd != 0 && wb_rd == rs1) begin
            rs1_forward = FORWARD_WB;
        end
        // MEM阶段
        else if (mem_write_reg && mem_rd != 0 && mem_rd == rs1) begin
            rs1_forward = FORWARD_MEM;
        end
        // EX阶段（注意：Load指令需要暂停，不能前递）
        else if (ex_write_reg && ex_rd != 0 && ex_rd == rs1) begin
            // EX阶段的ALU结果可以直接前递
            rs1_forward = FORWARD_EX;
        end

        // 检查rs2前递需求（同样逻辑）
        if (wb_write_reg && wb_rd != 0 && wb_rd == rs2) begin
            rs2_forward = FORWARD_WB;
        end
        else if (mem_write_reg && mem_rd != 0 && mem_rd == rs2) begin
            rs2_forward = FORWARD_MEM;
        end
        else if (ex_write_reg && ex_rd != 0 && ex_rd == rs2) begin
            rs2_forward = FORWARD_EX;
        end

        return ForwardControl {
            rs1_forward: rs1_forward,
            rs2_forward: rs2_forward
        };
    endmethod
endmodule

endpackage