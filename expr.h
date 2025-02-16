#ifndef EXPR_H
#define EXPR_H

#include "token.h"

typedef enum {
    EXPR_LITERAL,
    EXPR_BINARY,
    EXPR_UNARY,
    EXPR_GROUPING,
    EXPR_VARIABLE,
    EXPR_ASSIGNMENT
} ExprType;

typedef struct Expr {
    ExprType type;
    struct Expr *left;
    struct Expr *right;
    Token operator;
    Token literal;
    Token name;
} Expr;

void freeExpr(Expr *expr);

#endif // EXPR_H
