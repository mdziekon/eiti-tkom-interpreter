#ifndef TKOM_STRUCTURES_AST_NODES_FUNDEFINITION_HPP
#define TKOM_STRUCTURES_AST_NODES_FUNDEFINITION_HPP

#include "../AST.hpp"

#include <vector>
#include <string>

using Node = tkom::structures::ast::Node;

namespace tkom { namespace structures { namespace ast
{
    class StatementBlock;

    class FunDefinition: public Node
    {
    public:
        void setParameters(const std::vector<std::string> parameters)
        {
            this->parameters = parameters;
        }
        void setBlock(const std::shared_ptr<StatementBlock>& blockNode)
        {
            this->blockNode = blockNode;
        }

    private:
        std::vector<std::string> parameters;
        std::shared_ptr<StatementBlock> blockNode;
    };
}}}

#endif
