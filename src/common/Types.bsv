// src/common/Types.bsv
package Types;

typedef 32 DataSz;      // 数据总线宽度
typedef 32 AddrSz;      // 地址总线宽度  
typedef Bit#(DataSz) Word;
typedef Bit#(AddrSz) Addr;

// RISC-V指令格式
typedef struct {
    Bit#(7) opcode;
    Bit#(5) rd;
    Bit#(3) funct3;
    Bit#(5) rs1;
    Bit#(5) rs2;
    Bit#(7) funct7;
} InstrFormat deriving (Bits, Eq, FShow);

// 处理器状态
typedef enum {
    RUNNING,
    HALTED,
    TRAPPED
} ProcessorState deriving (Bits, Eq, FShow);

endpackage