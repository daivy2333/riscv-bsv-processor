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
    // CSR 中断 Wire 输入（由 SOC 内部驱动）
    method Action timerIRQWire(Bool irq);
    method Action softwareIRQWire(Bool irq);
    method Action externalIRQWire(Bool irq);
    // 其他方法
    method Bool testDone();
    method Word tohostValue();
    // CSR 模块接口（Core 使用）
    method CSRs csrModule();
endinterface

endpackage