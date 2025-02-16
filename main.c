#include <stdio.h>
#include <stdlib.h>
#include "token.h"
#include "lexer.h"
#include "parser.h"
#include "semantic.h"
#include "codegen.h"
#include "expr.h"

int main() {
    const char *source = "int main() { return 42; }";
    initLexer(source);

    Token tokens[256];
    int tokenCount = 0;

    Token token;
    do {
        token = scanToken();
        tokens[tokenCount++] = token;
    } while (token.type != TOKEN_EOF);

    initParser(tokens);

    while (peekParser().type != TOKEN_EOF) {
        Expr *expr = expression();
        analyze(expr);
        generateCode(expr);
        freeExpr(expr); // Free the expression tree
    }

    // Free tokens
    for (int i = 0; i < tokenCount; i++) {
        free(tokens[i].lexeme);
    }

    return 0;
}
