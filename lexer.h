#ifndef LEXER_H
#define LEXER_H

#include "token.h"

void initLexer(const char *source);
Token scanToken();

#endif // LEXER_H
