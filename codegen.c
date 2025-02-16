#include <stdio.h>
#include "codegen.h"

void generateCode(Expr *expr) {
    switch (expr->type) {
        case EXPR_LITERAL:
            printf("PUSH %s\n", expr->literal.lexeme);
            break;
        case EXPR_VARIABLE:
            printf("PUSH [%s]\n", expr->name.lexeme);
            break;
        case EXPR_ASSIGNMENT:
            generateCode(expr->right);
            printf("POP [%s]\n", expr->name.lexeme);
            break;
        case EXPR_BINARY:
            generateCode(expr->left);
            generateCode(expr->right);
            switch (expr->operator.type) {
                case TOKEN_PLUS: printf("ADD\n"); break;
                case TOKEN_MINUS: printf("SUB\n"); break;
                case TOKEN_STAR: printf("MUL\n"); break;
                case TOKEN_SLASH: printf("DIV\n"); break;
            }
            break;
        case EXPR_UNARY:
            generateCode(expr->right);
            switch (expr->operator.type) {
                case TOKEN_MINUS: printf("NEG\n"); break;
            }
            break;
        case EXPR_GROUPING:
            generateCode(expr->left);
            break;
    }
}
