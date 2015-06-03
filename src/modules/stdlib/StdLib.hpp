#ifndef TKOM_MODULES_STDLIB_HPP
#define TKOM_MODULES_STDLIB_HPP

#include <unordered_map>
#include <string>
#include <functional>
#include <memory>
#include <vector>
#include <utility>

#include "../../structures/ir/Literal.hpp"

using Literal = tkom::structures::ir::Literal;

namespace tkom { namespace modules
{
    struct StdLib
    {
        typedef const std::vector<std::shared_ptr<Literal>> ArgVec;
        typedef std::function<std::shared_ptr<Literal>(ArgVec&)> StdFun;

        static const std::unordered_map<std::string, std::pair<unsigned int, StdFun>>& getStandardFunctions();
        static const StdFun& getStandardFunction(const std::string& name);
        static unsigned int getFunctionParamsCount(const std::string& name);
        static bool hasFunction(const std::string& name);
        static std::shared_ptr<Literal> callFunction(const std::string& name, ArgVec& arguments);

    private:
        static std::shared_ptr<Literal> funPrint(ArgVec& arguments);
        static std::shared_ptr<Literal> funPrintEmpty(ArgVec& arguments);
        static std::shared_ptr<Literal> funGenerate(ArgVec& arguments);
        static std::shared_ptr<Literal> funResize(ArgVec& arguments);
        static std::shared_ptr<Literal> funSize(ArgVec& arguments);
        static std::shared_ptr<Literal> funTranspose(ArgVec& arguments);
    };
}}

#endif
