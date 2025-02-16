#include <stdlib.h>
#include "expr.h"

void freeExpr(Expr *expr) {
    if (expr == NULL) return;
    
    switch (expr->type) {
        case EXPR_LITERAL:
            free(expr->literal.lexeme);
            break;
        case EXPR_VARIABLE:
            free(expr->name.lexeme);
            break;
        case EXPR_ASSIGNMENT:
            freeExpr(expr->right);
            free(expr->name.lexeme);
            break;
        case EXPR_BINARY:
            freeExpr(expr->left);
            freeExpr(expr->right);
            free(expr->operator.lexeme);
            break;
        case EXPR_UNARY:
            freeExpr(expr->right);
            free(expr->operator.lexeme);
            break;
        case EXPR_GROUPING:
            freeExpr(expr->left);
            break;
    }
    
    free(expr);
}
