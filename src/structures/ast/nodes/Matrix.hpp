#ifndef TKOM_STRUCTURES_AST_NODES_MATRIX_HPP
#define TKOM_STRUCTURES_AST_NODES_MATRIX_HPP

#include "../AST.hpp"

using Node = tkom::structures::ast::Node;

namespace tkom { namespace structures { namespace ast
{
    class Matrix: public Node
    {
    public:
        void pushValue(const double& value)
        {
            this->data.at(currentLevel).push_back(value);
        }
        void nextLevel()
        {
            this->data.push_back({});
            this->currentLevel++;
        }
        virtual Type getType()
        {
            return Node::Type::Matrix;
        }

        unsigned int currentLevel = 0;
        std::vector<std::vector<double>> data = {{}};
    };
}}}

#endif
