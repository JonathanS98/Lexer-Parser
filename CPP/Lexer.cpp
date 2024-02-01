//
// Created by josh on 29/01/2024.
//

#include "../Header/Lexer.h"

std::vector<std::pair<Lexer::Tokenizer, IT>> Tokens;
Lexer::Tokenizer Lexer::find(IT first, IT last) {

    if (first == last) {
        return END;
    }

    Tokenizer tokenType;

    switch (*first) {
        case '(': tokenType = LPAREN; break;
        case ')': tokenType = RPAREN; break;
        case '{': tokenType = LBRACKET; break;
        case '}': tokenType = RBRACKET; break;
        case '+': tokenType = OR_OP; break;
        case '*': tokenType = MANY_OP; break;
        case '.': tokenType = DOT; break;
        case '\\':
            first++;
            if (*first == 'I') {
                first++;
                tokenType = IGNORE_OP;
                break;
            }else if(*first == 'O'){
                first++;
                tokenType = GROUP_OP;
                break;
            }
        default:
            tokenType = UNKNOWN;
            break;
    }

    if (std::isdigit(*first)) {
        tokenType = DIGIT;
    } else if (*first >= 'A' && *first <= 'z' || isspace(*first)) {
        tokenType = LETTER;
    }

    Tokens.emplace_back(tokenType, first);
    return tokenType;
}