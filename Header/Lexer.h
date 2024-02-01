//
// Created by josh on 29/01/2024.
//

#ifndef LABB1_LEXER_H
#define LABB1_LEXER_H

#include <iostream>
#include <vector>
#include <algorithm>

using IT = std::string::iterator;

class Lexer{
public:
    enum Tokenizer{
        DIGIT,
        LETTER,
        LPAREN,
        RPAREN,
        LBRACKET,
        RBRACKET,
        OR_OP,
        MANY_OP,
        DOT,
        IGNORE_OP,
        GROUP_OP,
        UNKNOWN,
        END,
    };

    static Tokenizer GetNextToken(IT& first, IT& last);
    static Tokenizer GetCurrentToken(IT& first, IT& last);

    static Tokenizer find(IT first, IT last);

private:
    static Tokenizer current_char;

};

#endif //LABB1_LEXER_H
