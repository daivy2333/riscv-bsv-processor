#ifndef PARSER_H
#define PARSER_H

#include "ast.h"
#include "lexer.h"

ASTNode *parse(Token *tokens);

#endif
