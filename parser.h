#ifndef PARSER_H
#define PARSER_H

#include "token.h"

typedef struct {
    Token *tokens;
    int current;
} Parser;

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

void initParser(Token *tokens);
Expr* parse();

#endif // PARSER_H
