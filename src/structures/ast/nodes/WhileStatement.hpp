#ifndef TKOM_STRUCTURES_AST_NODES_WHILESTATEMENT_HPP
#define TKOM_STRUCTURES_AST_NODES_WHILESTATEMENT_HPP

#include "../AST.hpp"

using Node = tkom::structures::ast::Node;

namespace tkom { namespace structures { namespace ast
{
    class WhileStatement: public Node
    {
    public:
        void setCondition(const std::shared_ptr<Condition>& conditionNode)
        {
            this->conditionNode = conditionNode;
        }
        void setBlock(const std::shared_ptr<StatementBlock>& blockNode)
        {
            this->blockNode = blockNode;
        }

    private:
        std::shared_ptr<Condition> conditionNode;
        std::shared_ptr<StatementBlock> blockNode;
    };
}}}

#endif
