#include <iostream>
#include "Header/Lexer.h"
#include "Header/Parser.h"
#include "Header/Node.h"

void printTree(const std::string& prefix, ASTNode *node, bool isLeft)
{
    if (node != nullptr)
    {
        std::cout << prefix;
        std::cout << (isLeft ? "|--" : "L__" );
        std::cout << node->id() << std::endl;
        for (size_t i = 0; i < node->children.size(); ++i)
        {
            if (i < node->children.size() - 1)
            {
                printTree(prefix + (isLeft ? "|   " : "    "), node->children[i], true);
            }
            else
            {
                printTree(prefix + (isLeft ? "|   " : "    "), node->children[i], false);
            }
        }
    }
}

void printTree(ASTNode* node)
{
    printTree("", node, false);
}

int main() {
    std::string input = "(love+hate)";
    auto start = input.begin();
    auto end = input.end();

    std::string txt = "Waterloo I was defeated, you won the war Waterloo promise to love you for ever more Waterloo couldn't escape if I wanted to Waterloo knowing my fate is to be with you Waterloo finally facing my Waterloo";

    IT txtFirst = txt.begin();
    IT txtEnd = txt.end();

    auto res = parseMatch(start, end);

    if(res->evaluate(txtFirst, txtEnd)){
        std::cout << " MATCH";
    } else {
        std::cout << "NO MATCH";
    }

    std::cout << "\n";
    printTree(res);

    return 0;
}