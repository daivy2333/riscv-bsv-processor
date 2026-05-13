#include "ast.h"
#include <stdlib.h>

ASTNode *ast_new(ASTNodeType type)
{
    ASTNode *n = calloc(1, sizeof(ASTNode));
    if (!n) return NULL;
    n->type = type;
    return n;
}

void ast_free_all(ASTNode *head)
{
    while (head) {
        ASTNode *next = head->next;
        if (head->type == AST_FUNC_DEF && head->body)
            ast_free_all(head->body);
        if (head->type == AST_BIN_OP) {
            if (head->left) ast_free_all(head->left);
            if (head->right) ast_free_all(head->right);
        }
        if (head->type == AST_VAR_DECL) {
            if (head->init) ast_free_all(head->init);
        }
        if (head->type == AST_ASSIGN) {
            if (head->expr) ast_free_all(head->expr);
        }
        if (head->type == AST_IF) {
            if (head->left)  ast_free_all(head->left);
            if (head->body)  ast_free_all(head->body);
            if (head->right) ast_free_all(head->right);
        }
        if (head->type == AST_WHILE) {
            if (head->left)  ast_free_all(head->left);
            if (head->body)  ast_free_all(head->body);
        }
        if (head->type == AST_FUNC_CALL) {
            if (head->left)  ast_free_all(head->left);
        }
        free(head->func_name);
        free(head->name);
        free(head);
        head = next;
    }
}
