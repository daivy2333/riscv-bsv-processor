// src/core/HazardUnit.bsv
package HazardUnit;

import Types::*;

interface HazardUnit;
    // 检测Load-Use冒险
    method Bool detectLoadUseHazard(
        Bool ex_is_load,        // EX阶段是否是Load指令
        Bit#(5) ex_rd,          // EX阶段的目标寄存器
        Bool id_use_rs1,        // ID阶段是否使用rs1
        Bit#(5) id_rs1,         // ID阶段的rs1编号
        Bool id_use_rs2,        // ID阶段是否使用rs2
        Bit#(5) id_rs2          // ID阶段的rs2编号
    );
endinterface

module mkHazardUnit(HazardUnit);
    method Bool detectLoadUseHazard(
        Bool ex_is_load,
        Bit#(5) ex_rd,
        Bool id_use_rs1,
        Bit#(5) id_rs1,
        Bool id_use_rs2,
        Bit#(5) id_rs2
    );
        // 检测Load-Use冒险：
        // 上一条指令是Load，当前指令要使用其结果
        // 此时需要暂停一个周期

        Bool hazard = False;

        if (ex_is_load && ex_rd != 0) begin
            // 检查ID阶段是否需要Load的结果
            if (id_use_rs1 && id_rs1 == ex_rd) begin
                hazard = True;
            end
            if (id_use_rs2 && id_rs2 == ex_rd) begin
                hazard = True;
            end
        end

        return hazard;
    endmethod
endmodule

endpackage