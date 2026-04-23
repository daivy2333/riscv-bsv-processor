// src/common/MemInterface.bsv - 内存通道接口定义
package MemInterface;

import Types::*;
import CSR::*;
import Vector::*;

// SOC 内存通道接口（Core 使用）
interface MemChannel;
    method Action sendMemReq(MemReq req);    // Core 发送请求
    method Bool hasMemResp();                 // 检查响应是否可用
    method MemResp peekMemResp();             // 读取响应（不出队）
    method Action deqMemResp();               // 出队响应
    // CSR 中断 Wire 输入（由 Core 每周期驱动）
    method Action timerIRQWire(Bool irq);
    method Action softwareIRQWire(Bool irq);
    method Action externalIRQWire(Bool irq);
    // 中断状态直接读取（Core 每周期调用）
    method Bool clintTimerIRQ();
    method Bool clintSoftwareIRQ();
    method Bool plicExternalIRQ();
    // UART RX 输入（仿真环境传入字符）
    method Action uartRXInput(Bit#(8) data, Bool valid);
    // 其他方法
    method Bool testDone();
    method Word tohostValue();
    // CSR 模块接口（Core 使用）
    method CSRs csrModule();
    // 程序加载方法（用于初始化 DMem）
    method Action loadProgram(Vector#(8192, Word) prog);
    // 调试方法：获取 mtime 和 mtimecmp
    method Bit#(64) getMtime();
    method Bit#(64) getMtimecmp();
    // 调试方法：获取 CSR 状态
    method Word getMStatus();
    method Word getMIE();
    method Word getMIP();
endinterface

endpackage