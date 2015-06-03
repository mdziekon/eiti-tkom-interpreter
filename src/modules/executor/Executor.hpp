#ifndef TKOM_MODULES_EXECUTOR_HPP
#define TKOM_MODULES_EXECUTOR_HPP

#include <unordered_map>
#include <string>
#include "../../structures/ir/Function.hpp"

namespace ir = tkom::structures::ir;

namespace tkom { namespace modules
{
    class Executor
    {
    public:
        void execute(const std::vector<std::shared_ptr<ir::Function>>& functions);
    };
}}

#endif
