#ifndef TKOM_STRUCTURES_AST_NODES_LOOPJUMP_HPP
#define TKOM_STRUCTURES_AST_NODES_LOOPJUMP_HPP

#include "../AST.hpp"

using Node = tkom::structures::ast::Node;

namespace tkom { namespace structures { namespace ast
{
    class LoopJump: public Node
    {
    public:
        void setType(const TokenType& type)
        {
            if (type == TokenType::Break)
            {
                this->isBreak = true;
                return;
            }
            this->isBreak = false;
        }

    private:
        bool isBreak;
    };
}}}

#endif
