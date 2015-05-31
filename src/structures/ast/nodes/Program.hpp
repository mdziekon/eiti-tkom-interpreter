#ifndef TKOM_STRUCTURES_AST_NODES_PROGRAM_HPP
#define TKOM_STRUCTURES_AST_NODES_PROGRAM_HPP

#include "../AST.hpp"
#include <iostream>

using Node = tkom::structures::ast::Node;

namespace tkom { namespace structures { namespace ast
{
    class FunDefinition;

    class Program: public Node
    {
    public:
        void addFunction(const std::shared_ptr<FunDefinition>& function)
        {
            this->functions.push_back(function);
        }

    private:
        std::vector<std::shared_ptr<FunDefinition>> functions = {};
    };
}}}

#endif
