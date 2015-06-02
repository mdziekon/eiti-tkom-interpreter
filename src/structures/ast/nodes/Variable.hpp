#ifndef TKOM_STRUCTURES_AST_NODES_VARIABLE_HPP
#define TKOM_STRUCTURES_AST_NODES_VARIABLE_HPP

#include "../AST.hpp"

using Node = tkom::structures::ast::Node;

namespace tkom { namespace structures { namespace ast
{
    class Variable: public Node
    {
    public:
        void setName(const std::string& name)
        {
            this->variableName = name;
        }

        void setIndexArg(
            const unsigned int& indexNo,
            const std::shared_ptr<Assignable>& argument
        )
        {
            if (indexNo == 1)
            {
                this->indexArg1 = argument;
            }
            else if (indexNo == 2)
            {
                this->indexArg2 = argument;
            }
            else
            {
                // error
            }
        }
        virtual Type getType()
        {
            return Node::Type::Variable;
        }

        std::string variableName;
        std::shared_ptr<Assignable> indexArg1;
        std::shared_ptr<Assignable> indexArg2;
    };
}}}

#endif
