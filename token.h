#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
    TOKEN_LPAREN,     // (
    TOKEN_RPAREN,    // )
    TOKEN_LBRACE,     // {
    TOKEN_RBRACE,    // }
    TOKEN_COMMA,          // ,
    TOKEN_DOT,            // .
    TOKEN_MINUS,          // -
    TOKEN_PLUS,           // +
    TOKEN_SEMICOLON,      // ;
    TOKEN_SLASH,          // /
    TOKEN_STAR,           // *
    TOKEN_BANG,           // !
    TOKEN_BANG_EQUAL,     // !=
    TOKEN_ASSIGN,         // =
    TOKEN_EQUAL,          // ==
    TOKEN_GREATER,        // >
    TOKEN_GREATER_EQUAL,  // >=
    TOKEN_LESS,           // <
    TOKEN_LESS_EQUAL,     // <=
    TOKEN_IDENTIFIER,     // Identifiers (e.g., variable names)
    TOKEN_STRING,         // String literals
    TOKEN_NUMBER,         // Number literals
    TOKEN_AND,            // and
    TOKEN_CLASS,          // class
    TOKEN_ELSE,           // else
    TOKEN_FALSE,          // false
    TOKEN_FOR,            // for
    TOKEN_FUN,            // fun
    TOKEN_IF,             // if
    TOKEN_NIL,            // nil
    TOKEN_OR,             // or
    TOKEN_PRINT,          // print
    TOKEN_RETURN,         // return
    TOKEN_SUPER,          // super
    TOKEN_THIS,           // this
    TOKEN_TRUE,           // true
    TOKEN_VAR,            // var
    TOKEN_WHILE,          // while
    TOKEN_INT,            // int (keyword)
    TOKEN_ERROR,          // Error token
    TOKEN_EOF             // End of file
} TokenType;

typedef struct {
    TokenType type;
    const char* lexeme;
    int length;
    int line;
} Token;

#endif // TOKEN_H
