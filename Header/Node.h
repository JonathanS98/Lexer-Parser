//
// Created by josh on 29/01/2024.
//

#ifndef LABB1_NODE_H
#define LABB1_NODE_H

#include "Lexer.h"
#include <vector>
#include <string>
#include <iterator>

std::string result;

struct ASTNode {
    virtual bool evaluate(IT &first, IT last) = 0;
    virtual std::string id() = 0;
    std::vector<ASTNode*> children;
    void add(ASTNode* child) {
        if(child != nullptr){
            children.push_back(child);
        }
    }

};

struct Char : ASTNode{
    char ch;
    bool evaluate(IT &first, IT last) override{
        if(ch == *first || ch == '.'){
            result.push_back(*first);
            return true;
        }
        result.clear();
        return false;
    }

    std::string id() override {
        return std::string(1, ch);
    }
};

struct Dot : ASTNode {
    int steps;
    bool evaluate(IT &first, IT last) override{
        bool lhs;

        for(int i = 0; i < steps; i++){
            lhs = children[0]->evaluate(first, last);
            first++;
        }
        first--;

        return lhs;
    }

    std::string id() override{
        std::string StepsToString = std::to_string(steps);
        return "Steps (" + StepsToString + ")";
    }
};

struct Many : ASTNode {
    bool evaluate(IT &first, IT last) override{
        bool lhs = false;
        std::string temp;

        while(children[0]->evaluate(first, last) && first != last){
            temp = result;
            first++;
            lhs = true;
        }

        result = temp;
        first--;

        bool rhs = true;
        if (!lhs) { return false; }
        if (children.size() == 2){
            rhs = children[1]->evaluate(++first, last);
        }

        return lhs & rhs;
    }

    std::string id() override {
        return "MANY";
    }
};

struct Or : ASTNode{
    bool evaluate(IT &first, IT last) override{
        auto temp = result;
        bool lhs = children[0]->evaluate(first,last);
        if (lhs) return true;
        result = temp;
        return children[1]->evaluate(first, last);
    }

    std::string id() override {
        return "OR";
    }
};

struct Letter : ASTNode{
    bool evaluate(IT &first, IT last) override{
        bool rhs = true;
        bool lhs = children[0]->evaluate(first, last);

        if (!lhs) { return false; }
        if (children.size() == 2){
            rhs = children[1]->evaluate(++first, last);
        }

        return lhs && rhs;
    }

    std::string id() override {
        return "LETTER";
    }
};

struct Match : ASTNode {
    bool evaluate(IT &first, IT last) override{
        while (first != last) {
            IT temp = first;
            if (children[0]->evaluate(temp, last)) {
                first = temp;
                std::cout << result;
                return true;
            }
            ++first;
        }
        return false;
    }

    std::string id() override{
        return "MATCH";
    }
};

struct Expression : ASTNode {
    bool evaluate(IT &first, IT last) override{
        for (auto letter : children) {
            if (!letter->evaluate(first, last)) {
                return false;
            }
        }
        return true;
    }

    std::string id() override{
        return "EXPR";
    }
};


#endif //LABB1_NODE_H
