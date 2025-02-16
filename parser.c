#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include <stdbool.h>

Parser parser;

void initParser(Token *tokens) {
    parser.tokens = tokens;
    parser.current = 0;
}

bool match(TokenType type) {
    if (parser.tokens[parser.current].type == type) {
        parser.current++;
        return true;
    }
    return false;
}

Token previous() {
    return parser.tokens[parser.current - 1];
}

Token advanceParser() {
    if (parser.tokens[parser.current].type != TOKEN_EOF) parser.current++;
    return previous();
}

Token peekParser() {
    return parser.tokens[parser.current];
}

Token consume(TokenType type, const char *message) {
    if (match(type)) return previous();
    fprintf(stderr, "Parse error: %s\n", message);
    exit(1);
}

Expr* primary() {
    if (match(TOKEN_NUMBER)) {
        Expr *expr = (Expr*)malloc(sizeof(Expr));
        expr->type = EXPR_LITERAL;
        expr->literal = previous();
        return expr;
    }
    if (match(TOKEN_IDENTIFIER)) {
        Expr *expr = (Expr*)malloc(sizeof(Expr));
        expr->type = EXPR_VARIABLE;
        expr->name = previous();
        return expr;
    }
    if (match(TOKEN_LPAREN)) {
        Expr *expr = expression();
        consume(TOKEN_RPAREN, "Expect ')' after expression.");
        return expr;
    }
    fprintf(stderr, "Parse error: Expect expression.\n");
    exit(1);
}

Expr* unary() {
    if (match(TOKEN_MINUS)) {
        Token operator = previous();
        Expr *right = unary();
        Expr *expr = (Expr*)malloc(sizeof(Expr));
        expr->type = EXPR_UNARY;
        expr->operator = operator;
        expr->right = right;
        return expr;
    }
    return primary();
}

Expr* factor() {
    Expr *expr = unary();
    while (match(TOKEN_STAR) || match(TOKEN_SLASH)) {
        Token operator = previous();
        Expr *right = unary();
        Expr *newExpr = (Expr*)malloc(sizeof(Expr));
        newExpr->type = EXPR_BINARY;
        newExpr->left = expr;
        newExpr->operator = operator;
        newExpr->right = right;
        expr = newExpr;
    }
    return expr;
}

Expr* term() {
    Expr *expr = factor();
    while (match(TOKEN_PLUS) || match(TOKEN_MINUS)) {
        Token operator = previous();
        Expr *right = factor();
        Expr *newExpr = (Expr*)malloc(sizeof(Expr));
        newExpr->type = EXPR_BINARY;
        newExpr->left = expr;
        newExpr->operator = operator;
        newExpr->right = right;
        expr = newExpr;
    }
    return expr;
}

Expr* assignment() {
    Expr *expr = expression();
    
    if (match(TOKEN_ASSIGN)) {
        Token equals = previous();
        Expr *value = assignment();
        
        if (expr->type == EXPR_VARIABLE) {
            Expr *newExpr = (Expr*)malloc(sizeof(Expr));
            newExpr->type = EXPR_ASSIGNMENT;
            newExpr->name = expr->name;
            newExpr->right = value;
            return newExpr;
        }

        fprintf(stderr, "Parse error: Invalid assignment target.\n");
        exit(1);
    }

    return expr;
}

Expr* expression() {
    return assignment();
}

void parse() {
    while (peekParser().type != TOKEN_EOF) {
        Expr *expr = expression();
        // Process the parsed expression (e.g., add to AST, etc.)
    }
}

   
