#include <stdio.h>
#include "semantic.h"

void analyze(Expr *expr) {
    switch (expr->type) {
        case EXPR_LITERAL:
            break;
        case EXPR_VARIABLE:
            if (expr->name.lexeme == NULL) {
                fprintf(stderr, "Semantic error: Undeclared variable.\n");
            } else {
                fprintf(stderr, "Semantic error: Undeclared variable '%s'.\n", expr->name.lexeme);
            }
            break;
        case EXPR_ASSIGNMENT:
            if (expr->right->type != EXPR_VARIABLE) {
                fprintf(stderr, "Semantic error: Invalid assignment target.\n");
            }
            analyze(expr->right);
            break;
        case EXPR_BINARY:
        case EXPR_UNARY:
            analyze(expr->left);
            analyze(expr->right);
            break;
        case EXPR_GROUPING:
            analyze(expr->left);
            break;
    }
}
