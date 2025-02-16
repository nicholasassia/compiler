#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"
#include <stdbool.h>

// Global variables for lexer state
static const char *start;
static const char *current;

void initLexer(const char *source) {
    start = source;
    current = source;
}

static bool isAtEnd() {
    return *current == '\0';
}

static char advance() {
    current++;
    return current[-1];
}

static char peek() {
    return *current;
}

static char peekNext() {
    if (isAtEnd()) return '\0';
    return current[1];
}

static bool match(char expected) {
    if (isAtEnd()) return false;
    if (*current != expected) return false;
    current++;
    return true;
}

static Token makeToken(TokenType type) {
    Token token;
    token.type = type;
    token.lexeme = strndup(start, current - start);
    token.length = (int)(current - start);
    token.line = 1; // For simplicity, assuming single line
    return token;
}

static Token errorToken(const char *message) {
    Token token;
    token.type = TOKEN_ERROR;
    token.lexeme = strdup(message);
    token.length = (int)strlen(message);
    token.line = 1; // For simplicity, assuming single line
    return token;
}

static void skipWhitespace() {
    for (;;) {
        char c = peek();
        switch (c) {
            case ' ':
            case '\r':
            case '\t':
            case '\n':
                advance();
                break;
            default:
                return;
        }
    }
}

static TokenType checkKeyword(int start, int length, const char *rest, TokenType type) {
    if (current - start == length && memcmp(start + current, rest, length) == 0) {
        return type;
    }
    return TOKEN_IDENTIFIER;
}

static TokenType identifierType() {
    switch (start[0]) {
        case 'i':
            if (current - start > 1) {
                switch (start[1]) {
                    case 'f': return checkKeyword(2, 0, "", TOKEN_IF);
                    case 'n': return checkKeyword(2, 0, "", TOKEN_INT);
                }
            }
            break;
        case 'r':
            return checkKeyword(1, 5, "eturn", TOKEN_RETURN);
    }
    return TOKEN_IDENTIFIER;
}

static Token identifier() {
    while (isalnum(peek()) || peek() == '_') advance();
    return makeToken(identifierType());
}

static Token number() {
    while (isdigit(peek())) advance();
    return makeToken(TOKEN_NUMBER);
}

static Token string() {
    while (peek() != '"' && !isAtEnd()) {
        advance();
    }
    
    if (isAtEnd()) return errorToken("Unterminated string.");
    advance(); // Closing quote
    return makeToken(TOKEN_STRING);
}

Token scanToken() {
    skipWhitespace();
    start = current;

    if (isAtEnd()) return makeToken(TOKEN_EOF);

    char c = advance();

    if (isalpha(c)) return identifier();
    if (isdigit(c)) return number();

    switch (c) {
        case '(': return makeToken(TOKEN_LPAREN);
        case ')': return makeToken(TOKEN_RPAREN);
        case '{': return makeToken(TOKEN_LBRACE);
        case '}': return makeToken(TOKEN_RBRACE);
        case ';': return makeToken(TOKEN_SEMICOLON);
        case '+': return makeToken(TOKEN_PLUS);
        case '-': return makeToken(TOKEN_MINUS);
        case '*': return makeToken(TOKEN_STAR);
        case '/': return makeToken(TOKEN_SLASH);
        case '=': return makeToken(TOKEN_ASSIGN);
        case '"': return string();
    }

    return errorToken("Unexpected character.");
}
