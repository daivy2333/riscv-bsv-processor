# 任务清单

> 最后更新：2026-05-15

## 进行中

- （无）

## 已完成

### 阶段 1-9 ✅（见 snapshot.md）

### 阶段 10：自举准备（volatile/const/void/typedef/static）✅

- [x] 添加 volatile 支持（Lexer TOK_VOLATILE + Type.is_volatile）
- [x] 添加 const 支持（Lexer TOK_CONST + Type.is_const）
- [x] 添加 void 支持（Lexer TOK_VOID + BaseType.TYPE_VOID + parse_type）
- [x] 添加 void(void) 参数语法
- [x] 添加空 return 语句支持（parse_return + codegen）
- [x] 添加隐式返回（函数结尾自动 jalr）
- [x] 添加 typedef 支持（Lexer TOK_TYPEDEF + typedef别名表）
- [x] 添加 static 支持（Lexer TOK_STATIC + AST.is_static + .Lstatic_标签）
- [x] 验证: volatile_test、const_test、void_test、typedef_test、static_test 全部通过
- [x] 验证: integration_test 综合测试通过

## 待办

### 预处理器增强

- [ ] 支持 `#include <file>` 系统头文件（需要头文件搜索路径）
- [ ] 实现完整自举（编译器编译自身）

### 运行时库

- [ ] 添加 printf 最小实现
- [ ] 添加 malloc/free 最小实现（用于编译器自举）

### 优化方向

- [ ] 添加更多错误处理和诊断信息
- [ ] 支持多级指针（当前仅一级）
- [ ] 添加 switch/case 支持

## 阻塞项

- 预处理器不支持 `#include <stdio.h>`，阻止完整自举

## 下一步

- 规划预处理器系统头文件支持方案