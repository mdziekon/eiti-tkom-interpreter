#ifndef TKOM_STRUCTURES_AST_NODES_IFSTATEMENT_HPP
#define TKOM_STRUCTURES_AST_NODES_IFSTATEMENT_HPP

#include "../AST.hpp"

using Node = tkom::structures::ast::Node;

namespace tkom { namespace structures { namespace ast
{
    class StatementBlock;

    class IfStatement: public Node
    {
    public:
        void setCondition(const std::shared_ptr<Condition>& conditionNode)
        {
            this->conditionNode = conditionNode;
        }
        void setTrueBlock(const std::shared_ptr<StatementBlock>& trueBlockNode)
        {
            this->trueBlockNode = trueBlockNode;
        }
        void setFalseBlock(const std::shared_ptr<StatementBlock>& falseBlockNode)
        {
            this->falseBlockNode = falseBlockNode;
        }

    private:
        std::shared_ptr<Condition> conditionNode;
        std::shared_ptr<StatementBlock> trueBlockNode;
        std::shared_ptr<StatementBlock> falseBlockNode;
    };
}}}

#endif
