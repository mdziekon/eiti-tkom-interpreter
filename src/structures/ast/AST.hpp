#ifndef TKOM_STRUCTURES_AST_HPP
#define TKOM_STRUCTURES_AST_HPP

#include <memory>

namespace tkom { namespace structures { namespace ast
{
    class Node
    {
    protected:
        std::weak_ptr<Node> parent;

    public:
        enum class Type {
            Assignment,
            Call,
            Condition,
            Expression,
            FunDefinition,
            IfStatement,
            LoopJump,
            Matrix,
            Program,
            ReturnStatement,
            StatementBlock,
            VarDeclaration,
            Variable,
            WhileStatement
        };

        virtual Type getType() = 0;
    };

    typedef std::shared_ptr<Node> NodePtr;
}}}

#include "nodes/Assignable.hpp"
#include "nodes/Assignment.hpp"
#include "nodes/Call.hpp"
#include "nodes/Condition.hpp"
#include "nodes/Expression.hpp"
#include "nodes/FunDefinition.hpp"
#include "nodes/IfStatement.hpp"
#include "nodes/LoopJump.hpp"
#include "nodes/Matrix.hpp"
#include "nodes/Program.hpp"
#include "nodes/ReturnStatement.hpp"
#include "nodes/StatementBlock.hpp"
#include "nodes/VarDeclaration.hpp"
#include "nodes/Variable.hpp"
#include "nodes/WhileStatement.hpp"

#endif
