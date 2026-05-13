#ifndef CODEGEN_H
#define CODEGEN_H

#include "ast.h"

int codegen_gen(ASTNode *prog, const char *outfile);

#endif
