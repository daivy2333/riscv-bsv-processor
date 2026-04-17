// src/core/HazardUnit.bsv
package HazardUnit;

import Types::*;

interface HazardUnit;
    // 检测Load-Use冒险（支持EX和MEM阶段）
    method Bool detectLoadUseHazard(
        Bool ex_is_load,       // EX阶段是否是Load指令
        Bit#(5) ex_rd,         // EX阶段的目标寄存器
        Bool mem_is_load,      // MEM阶段是否是Load指令
        Bit#(5) mem_rd,        // MEM阶段的目标寄存器
        Bool id_use_rs1,       // ID阶段是否使用rs1
        Bit#(5) id_rs1,        // ID阶段的rs1编号
        Bool id_use_rs2,       // ID阶段是否使用rs2
        Bit#(5) id_rs2         // ID阶段的rs2编号
    );
endinterface

module mkHazardUnit(HazardUnit);
    method Bool detectLoadUseHazard(
        Bool ex_is_load,
        Bit#(5) ex_rd,
        Bool mem_is_load,
        Bit#(5) mem_rd,
        Bool id_use_rs1,
        Bit#(5) id_rs1,
        Bool id_use_rs2,
        Bit#(5) id_rs2
    );
        // 检测Load-Use冒险：
        // EX阶段Load → ID使用（停顿1周期）
        // MEM阶段Load → ID使用（停顿已发生，继续检测）

        Bool hazard = False;

        // EX阶段检测（Load在EX，ID要使用）
        if (ex_is_load && ex_rd != 0) begin
            if (id_use_rs1 && id_rs1 == ex_rd)
                hazard = True;
            if (id_use_rs2 && id_rs2 == ex_rd)
                hazard = True;
        end

        // MEM阶段检测（Load在MEM，ID要使用）
        if (mem_is_load && mem_rd != 0 && !hazard) begin
            if (id_use_rs1 && id_rs1 == mem_rd)
                hazard = True;
            if (id_use_rs2 && id_rs2 == mem_rd)
                hazard = True;
        end

        return hazard;
    endmethod
endmodule

endpackage