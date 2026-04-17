#!/usr/bin/env python3
"""
在 BSV 生成的 Verilog 文件末尾注入 $readmemh 语句。

用法：
    python3 tools/inject_readmemh.py build/mkTestBench.v firmware/test.hex
"""
import sys

def inject_readmemh(verilog_file, hex_file):
    """在 Verilog 文件末尾注入 initial 块加载 hex"""
    with open(verilog_file, 'r') as f:
        content = f.read()
    
    # 在文件末尾添加 initial 块
    # 注意：需要使用数组语法，但 BSV Vector 生成单独的 reg
    # 解决方案：使用 Verilog 的 generate 或数组重构
    
    # 实际方案：创建一个数组别名
    inject_code = f'''
// Injected by inject_readmemh.py
// Create array alias for imem (BSV generates separate regs)
wire [31:0] core_imem_array [0:1023];
generate
    for (genvar i = 0; i < 1024; i = i + 1) begin: imem_gen
        assign core_imem_array[i] = core_imem_$i;
    end
endgenerate

initial begin
    // Load hex file (using workaround for non-array regs)
    $readmemh("{hex_file}", core_imem_array);
end
'''
    
    # 实际上 Verilog 不允许 assign 到 reg 数组
    # 使用更简单的方法：逐个赋值
    inject_code_simple = f'''
// Injected: Load hex file
integer idx;
reg [31:0] hex_data [0:1023];

initial begin
    $readmemh("{hex_file}", hex_data);
    for (idx = 0; idx < 1024; idx = idx + 1) begin
        case (idx)
            0: core_imem_0 = hex_data[0];
            1: core_imem_1 = hex_data[1];
            2: core_imem_2 = hex_data[2];
            // ... (需要生成更多)
        endcase
    end
end
'''
    
    # 这个方案太复杂。使用替代方案：直接修改 testbench
    # 让 TestBench 在 loadProgram 时加载程序
    
    print(f"Warning: Direct injection not practical for 1024 separate regs")
    print("Use TestBench.loadProgram() method instead")
    
    # 实际最佳方案：修改 Core.bsv 使用 Memory 类型
    # 或者使用 BSV 的 mkBRAM 或 mkMemory

if __name__ == "__main__":
    inject_readmemh(sys.argv[1], sys.argv[2])
