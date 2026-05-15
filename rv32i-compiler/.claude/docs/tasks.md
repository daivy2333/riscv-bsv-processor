# 任务清单

> 最后更新：2026-05-15

## 进行中

- （无）

## 已完成

### 阶段 1-8 ✅（见 snapshot.md）

### 阶段 9：多文件与预处理器 ✅

- [x] 添加预处理器框架（pp_process 入口）
- [x] 添加 #include "file" 文件包含（递归、循环检测）
- [x] 添加 #define NAME VAL 常量宏替换
- [x] 添加 #ifdef/#ifndef/#endif 条件编译栈
- [x] 添加 #else/#elif 分支支持
- [x] 添加 extern 关键字（Lexer TOK_EXTERN + Parser parse_extern_decl）
- [x] 添加函数原型解析（int foo();）
- [x] 添加多文件编译（linker_link_multi）
- [x] 修复 extern 变量引用问题（la + lw，跳过 .data 生成）
- [x] 修复单文件模式汇编路径参数（argv[4]）
- [x] 验证: multifile + full_test 全部通过

## 待办

### 阶段 10：自举准备

- [ ] 添加 typedef 支持
- [ ] 添加 enum 支持
- [ ] 添加 volatile 支持
- [ ] 验证: 编译器编译自身

## 阻塞项

- （无）

## 下一步

- 开始阶段 10 规划