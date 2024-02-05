//
// Created by josh on 29/01/2024.
//

#ifndef LABB1_PARSER_H
#define LABB1_PARSER_H

#include <memory>
#include "Node.h"
#include "Lexer.h"

/*
<MATCH> -> <EXPR>
<EXPR> -> <LETTER> | <GROUP>
<LETTER> -> <MANY> | <DOT> | <CHAR>
<GROUP> -> (<LETTER>) | <OR>
<MANY> -> <CHAR><MANY>
<DOT> -> <DOT>{<CHAR>} | <DOT><MANY>
<OR> -> <CHAR> "+" <CHAR>
 */

Letter *parseLetter(IT &first, IT last);
Or* parseOR(IT& first, IT last);
Expression* parseExpr(IT& first, IT last);
Group* parseGroup(IT& first, IT last);

Char *parseCh(IT &first, IT last) {
    if (first == last) return nullptr;

    auto token = Lexer::find(first,last);
    if(token != Lexer::LETTER && token != Lexer::DOT && token != Lexer::MANY_OP){ return nullptr; }
    auto pChar = new Char;
    pChar->ch = *first;
    first++;
    return pChar;
}

Dot *parseDot(IT &first, IT last) {
    if (first == last || *first != '.') return nullptr;

    first++;

    auto Left_token = Lexer::find(first, last);
    if (Left_token != Lexer::LBRACKET) { return nullptr; }

    first--;
    Char* pChar = parseCh(first, last);
    first++;
    auto pDot = new Dot;
    pDot->add(pChar);
    int temp = std::stoi(&*first);
    pDot->steps = temp;
    first++;

    auto Right_token = Lexer::find(first, last);
    first++;
    if (Right_token != Lexer::RBRACKET){ return nullptr; }

    return pDot;
}

Many *parseMany(IT &first, IT last) {
    ASTNode* pLHS = parseCh(first, last);

    Many* pMany = new Many;
    pMany->add(pLHS);
    first++;

    auto token = Lexer::find(first, last);
    Letter* pRHS = nullptr;

    if (token != Lexer::LETTER && token != Lexer::DOT && token != Lexer::MANY_OP){
        pMany->add(pRHS);
        return pMany;
    }
    pRHS = parseLetter(first, last);
    pMany->add(pRHS);

    return pMany;
}

Letter *parseLetter(IT &first, IT last) {

    Letter* pLetter = new Letter;
    ASTNode* pLHS = nullptr;
    auto temp = first;
    bool consumed = false;
    auto Next_Token = Lexer::find(++temp, last);
    auto token = Lexer::find(first, last);

    if (Next_Token == Lexer::MANY_OP) {
        pLHS = parseMany(first, last);
        pLetter->add(pLHS);
    }
    if (Next_Token == Lexer::LBRACKET){
        pLHS = parseDot(first, last);
        pLetter->add(pLHS);
    }
    else {
        pLHS = parseCh(first, last);
        pLetter->add(pLHS);
    }

    token = Lexer::find(first, last);
    ASTNode* pRHS = nullptr;

    if (token != Lexer::LETTER && token != Lexer::DOT && token != Lexer::MANY_OP){
        pLetter->add(pRHS);
        return pLetter;
    }

    temp = first;
    Next_Token = Lexer::find(++temp, last);
    if (Next_Token == Lexer::MANY_OP) {
        pLHS = parseMany(first, last);
        pLetter->add(pLHS);
    } else{
        pRHS = parseLetter(first, last);
        pLetter->add(pRHS);
    }

    return pLetter;
}


Expression* parseExpr(IT& first, IT last) {
    auto pExpr = new Expression();
    ASTNode* node = nullptr;

    while (true) {
        auto token = Lexer::find(first, last);
        if(token == Lexer::END){
            return pExpr;
        }
        if (token == Lexer::LPAREN) {
            node = parseGroup(first, last);
        } else {
            node = parseLetter(first, last);
        }
        if (node) {
            pExpr->add(node);
        } else {
            break;
        }
    }

    return pExpr;
}

Match* parseMatch(IT& first, IT last) {

    auto pMatch = new Match();
    ASTNode* pNode = nullptr;
    pNode = parseExpr(first, last);
    pMatch->add(pNode);

    return pMatch;
}

Or* parseOR(IT& first, IT last){
    Letter* pLHS = parseLetter(first, last);
    first++;
    Letter* pRHS = parseLetter(first, last);
    first++;

    Or* pOr = new Or;
    pOr->add(pLHS);
    pOr->add(pRHS);

    return pOr;

}

Group* parseGroup(IT& first, IT last){
    if (first == last || *first != '(') return nullptr;
    first++;

    Group* pGroup = new Group();

    ASTNode* pLHS = parseLetter(first, last);
    if (first != last && *first == '+') {
        first++;
        ASTNode* pRHS = parseLetter(first, last);
        Or* orNode = new Or();
        orNode->add(pLHS);
        orNode->add(pRHS);
        pGroup->add(orNode);
    } else {
        pGroup->add(pLHS);
    }

    if (first == last || *first != ')') {
        delete pGroup;
        return nullptr;
    }
    first++;

    return pGroup;

}
#endif //LABB1_PARSER_H