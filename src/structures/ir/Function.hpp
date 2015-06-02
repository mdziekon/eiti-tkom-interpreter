#ifndef TKOM_STRUCTURES_IR_FUNCTION_HPP
#define TKOM_STRUCTURES_IR_FUNCTION_HPP

#include <vector>
#include <memory>

#include "Block.hpp"

namespace tkom { namespace structures { namespace ir
{
    struct Function: public Block
    {
        typedef std::shared_ptr<Function> ptr;

        unsigned int parameters = 0;
    };
}}}

#endif
