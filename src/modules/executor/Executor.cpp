#include "Executor.hpp"

#include "../stdlib/StdLib.hpp"

using Executor = tkom::modules::Executor;
using StdLib = tkom::modules::StdLib;

void Executor::execute(const std::vector<std::shared_ptr<ir::Function>>& functions)
{
    std::unordered_map<std::string, std::shared_ptr<ir::Function>> definedFunctions;
    for(auto& it: functions)
    {
        definedFunctions.insert({ { it->name, it } });
    }

    auto& main = definedFunctions.at("main");

    main->execute(nullptr, definedFunctions, {});

    // std::shared_ptr<Literal> lit = std::make_shared<Literal>();

    // lit->data = {
    //     { 1, 2, 3 },
    //     { 4, 5, 7}
    // };

    // StdLib::callFunction("print", { lit });

}
