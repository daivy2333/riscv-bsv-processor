// src/common/Types.bsv
package Types;

import Vector::*;

// ============================================================
// 基本数据类型
// ============================================================

typedef 32 DataSz;      // 数据总线宽度
typedef 32 AddrSz;      // 地址总线宽度
typedef Bit#(DataSz) Word;
typedef Bit#(AddrSz) Addr;

// ============================================================
// RISC-V指令格式（原始位域）
// ============================================================

typedef struct {
    Bit#(7) opcode;     // 7位操作码
    Bit#(5) rd;         // 5位目标寄存器
    Bit#(3) funct3;     // 3位功能码
    Bit#(5) rs1;        // 5位源寄存器1
    Bit#(5) rs2;        // 5位源寄存器2
    Bit#(7) funct7;     // 7位功能码7
} InstrFormat deriving (Bits, Eq, FShow);

// ============================================================
// 指令类型枚举
// ============================================================

typedef enum {
    R_TYPE,     // 寄存器-寄存器操作 (ADD, SUB, AND, OR, XOR, SLL, SRL, SRA, SLT, SLTU)
    I_TYPE,     // 立即数操作 (ADDI, ANDI, ORI, XORI, SLTI, SLTIU, SLLI, SRLI, SRAI)
    S_TYPE,     // 存储操作 (SB, SH, SW)
    B_TYPE,     // 分支操作 (BEQ, BNE, BLT, BGE, BLTU, BGEU)
    U_TYPE,     // 大立即数操作 (LUI, AUIPC)
    J_TYPE,     // 跳转操作 (JAL, JALR)
    L_TYPE      // 加载操作 (LB, LH, LW, LBU, LHU)
} InstrType deriving (Bits, Eq, FShow);

// ============================================================
// ALU操作码
// ============================================================

typedef enum {
    ALU_ADD,
    ALU_SUB,
    ALU_SLL,
    ALU_SLT,
    ALU_SLTU,
    ALU_XOR,
    ALU_SRL,
    ALU_SRA,
    ALU_OR,
    ALU_AND,
    ALU_PASS,   // 直接传递operand1 (用于LUI等)
    ALU_PC      // 使用PC (用于AUIPC等)
} ALUOp deriving (Bits, Eq, FShow);

// ============================================================
// 分支条件类型
// ============================================================

typedef enum {
    BR_EQ,      // BEQ
    BR_NE,      // BNE
    BR_LT,      // BLT
    BR_GE,      // BGE
    BR_LTU,     // BLTU
    BR_GEU,     // BGEU
    BR_NONE     // 无分支
} BranchCond deriving (Bits, Eq, FShow);

// ============================================================
// 内存操作类型
// ============================================================

typedef enum {
    MEM_NONE,   // 无内存操作
    MEM_READ,   // Load
    MEM_WRITE   // Store
} MemOp deriving (Bits, Eq, FShow);

// ============================================================
// 内存访问宽度
// ============================================================

typedef enum {
    MEM_BYTE,   // LB/LBU/SB - 8位
    MEM_HALF,   // LH/LHU/SH - 16位
    MEM_WORD    // LW/SW - 32位
} MemWidth deriving (Bits, Eq, FShow);

// ============================================================
// 处理器状态
// ============================================================

typedef enum {
    RUNNING,
    HALTED,
    TRAPPED
} ProcessorState deriving (Bits, Eq, FShow);

// ============================================================
// 流水线数据包定义
// ============================================================

// IF → ID 阶段数据包
typedef struct {
    Addr    pc;             // 当前指令PC
    Word    instruction;    // 取到的指令
    Addr    predicted_pc;  // 预测的PC（顺序执行的PC）
    Bool    predicted_taken;// 是否预测分支命中
} IF_ID_Packet deriving (Bits, Eq, FShow);

// ID → EX 阶段数据包
typedef struct {
    Addr        pc;
    Word        instruction;
    Word        rs1_val;        // 源寄存器1的值
    Word        rs2_val;        // 源寄存器2的值
    Word        imm;            // 立即数（已扩展）
    Bit#(5)     rs1;            // 源寄存器1编号（用于前递）
    Bit#(5)     rs2;            // 源寄存器2编号（用于前递）
    Bit#(5)     rd;             // 目标寄存器号
    ALUOp       alu_op;         // ALU操作码
    BranchCond  branch_cond;    // 分支条件
    MemOp       mem_op;         // 内存操作类型
    Bool        is_branch;      // 是否是分支指令
    Bool        is_jump;        // 是否是跳转指令(JAL/JALR)
    Bool        write_reg;      // 是否写寄存器
    Bool        use_imm;        // 是否使用立即数作为ALU第二个操作数
} ID_EX_Packet deriving (Bits, Eq, FShow);

// EX → MEM 阶段数据包
typedef struct {
    Addr        pc;
    Word        alu_result;     // ALU计算结果 / 分支目标地址
    Word        rs2_val;        // Store指令的数据
    Bit#(5)     rd;
    MemOp       mem_op;
    Bool        is_branch;
    Bool        branch_taken;   // 分支是否命中（实际判断结果）
    Bool        predicted_taken;// 分支预测结果
    Bool        write_reg;
    Bool        is_load;        // 是否是Load指令
} EX_MEM_Packet deriving (Bits, Eq, FShow);

// MEM → WB 阶段数据包
typedef struct {
    Addr        pc;
    Word        mem_data;       // 内存读取的数据（Load指令）
    Word        alu_result;     // ALU结果（非Load指令）
    Bit#(5)     rd;
    Bool        write_reg;
    Bool        is_load;
} MEM_WB_Packet deriving (Bits, Eq, FShow);

// ============================================================
// BHT状态（2位饱和计数器）
// ============================================================

typedef Bit#(2) BHTState;

// ============================================================
// BTB条目
// ============================================================

typedef struct {
    Addr    branch_pc;       // 分支指令地址（用于匹配）
    Addr    target_addr;     // 分支目标地址
    Bool    valid;           // 条目是否有效
} BTBEntry deriving (Bits, Eq, FShow);

// ============================================================
// 辅助函数
// ============================================================

// 从指令中提取opcode
function Bit#(7) getOpcode(Word instr);
    return instr[6:0];
endfunction

// 从指令中提取rd
function Bit#(5) getRd(Word instr);
    return instr[11:7];
endfunction

// 从指令中提取funct3
function Bit#(3) getFunct3(Word instr);
    return instr[14:12];
endfunction

// 从指令中提取rs1
function Bit#(5) getRs1(Word instr);
    return instr[19:15];
endfunction

// 从指令中提取rs2
function Bit#(5) getRs2(Word instr);
    return instr[24:20];
endfunction

// 从指令中提取funct7
function Bit#(7) getFunct7(Word instr);
    return instr[31:25];
endfunction

// I-type立即数提取（12位有符号扩展）
function Word signExtendI(Word instr);
    Bit#(12) imm12 = instr[31:20];
    return signExtend(imm12);
endfunction

// S-type立即数提取
function Word signExtendS(Word instr);
    Bit#(7) imm7 = instr[31:25];
    Bit#(5) imm5 = instr[11:7];
    Bit#(12) imm12 = {imm7, imm5};
    return signExtend(imm12);
endfunction

// B-type立即数提取
function Word signExtendB(Word instr);
    Bit#(1) imm12 = instr[31];
    Bit#(6) imm10_5 = instr[30:25];
    Bit#(4) imm4_1 = instr[11:8];
    Bit#(1) imm11 = instr[7];
    Bit#(13) imm13 = {imm12, imm11, imm10_5, imm4_1, 1'b0};
    return signExtend(imm13);
endfunction

// U-type立即数提取（20位左移12位）
function Word getUImm(Word instr);
    Bit#(20) imm20 = instr[31:12];
    return {imm20, 12'b0};
endfunction

// J-type立即数提取
function Word signExtendJ(Word instr);
    Bit#(1) imm20 = instr[31];
    Bit#(10) imm10_1 = instr[30:21];
    Bit#(1) imm11 = instr[20];
    Bit#(8) imm19_12 = instr[19:12];
    Bit#(21) imm21 = {imm20, imm19_12, imm11, imm10_1, 1'b0};
    return signExtend(imm21);
endfunction

// BHT预测函数
function Bool bhtPredict(BHTState state);
    return (state >= 2'b10);
endfunction

// BHT状态更新函数
function BHTState bhtUpdate(BHTState state, Bool taken);
    case (state)
        2'b00: return taken ? 2'b01 : 2'b00;
        2'b01: return taken ? 2'b10 : 2'b00;
        2'b10: return taken ? 2'b11 : 2'b01;
        2'b11: return taken ? 2'b11 : 2'b10;
        default: return 2'b01;
    endcase
endfunction

endpackage