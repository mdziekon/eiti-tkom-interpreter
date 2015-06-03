#include "StdLib.hpp"

#include <iostream>

using StdLib = tkom::modules::StdLib;

const std::unordered_map<std::string, std::pair<unsigned int, StdLib::StdFun>>&
StdLib::getStandardFunctions()
{
    static const std::unordered_map<std::string, std::pair<unsigned int, StdLib::StdFun>> list = {
        { "generate", { 3, StdLib::StdFun(&StdLib::funGenerate) } },
        { "resize", { 4, StdLib::StdFun(&StdLib::funResize) } },
        { "size", { 1, StdLib::StdFun(&StdLib::funSize) } },
        { "print", { 1, StdLib::StdFun(&StdLib::funPrint) } },
        { "printEmpty", {0, StdLib::StdFun(&StdLib::funPrintEmpty) } },
        { "transpose", { 1, StdLib::StdFun(&StdLib::funTranspose) } }
    };

    return list;
}

const StdLib::StdFun&
StdLib::getStandardFunction(const std::string& name)
{
    return (StdLib::getStandardFunctions()).at(name).second;
}

bool
StdLib::hasFunction(const std::string& name)
{
    return (StdLib::getStandardFunctions()).count(name) == 1;
}

unsigned int
StdLib::getFunctionParamsCount(const std::string& name)
{
    return (StdLib::getStandardFunctions()).at(name).first;
}

std::shared_ptr<Literal>
StdLib::callFunction(const std::string& name, ArgVec& arguments)
{
    return ((StdLib::getStandardFunction(name))(arguments));
}

std::shared_ptr<Literal>
StdLib::funGenerate(ArgVec& arguments)
{
    // arg[0] - width
    // arg[1] - height
    // arg[2] - filling

    // Check variables

    auto result = std::make_shared<Literal>();
    result->data.clear();
    for(auto y = 0; y < arguments.at(1)->data.at(0).at(0); ++y)
    {
        result->data.push_back({});
        for(auto x = 0; x < arguments.at(0)->data.at(0).at(0); ++x)
        {
            result->data.at(y).push_back(arguments.at(2)->data.at(0).at(0));
        }
    }
    return result;
}

std::shared_ptr<Literal>
StdLib::funResize(ArgVec& arguments)
{
    // arg[0] - matrix
    // arg[1] - width
    // arg[2] - height
    // arg[3] - filling

    // Check variables

    auto prevSize = arguments.at(0)->getSize();

    auto result = std::make_shared<Literal>();
    result->data.clear();
    for(auto y = 0; y < arguments.at(2)->data.at(0).at(0); ++y)
    {
        result->data.push_back({});
        for(auto x = 0; x < arguments.at(1)->data.at(0).at(0); ++x)
        {
            if (x < prevSize.second && y < prevSize.first)
            {
                result->data.at(y).push_back(arguments.at(0)->data.at(y).at(x));
            }
            else
            {
                result->data.at(y).push_back(arguments.at(3)->data.at(0).at(0));
            }
        }
    }
    return result;
}

std::shared_ptr<Literal>
StdLib::funSize(ArgVec& arguments)
{
    // arg[0] - matrix

    // Check variables

    auto size = arguments.at(0)->getSize();

    auto result = std::make_shared<Literal>();
    result->data.clear();

    result->data.push_back( { size.second + 0.0, size.first + 0.0 } );

    return result;
}

std::shared_ptr<Literal>
StdLib::funPrint(ArgVec& arguments)
{
    // arg[0] - matrix to display

    for(auto& it: arguments.at(0)->data)
    {
        for(auto& rowIt: it)
        {
            std::cout << rowIt << " ";
        }
        std::cout << std::endl;
    }

    auto result = std::make_shared<Literal>();
    result->data = { { 1 } };
    return result;
}

std::shared_ptr<Literal>
StdLib::funPrintEmpty(ArgVec& arguments)
{
    std::cout << std::endl;

    auto result = std::make_shared<Literal>();
    result->data = { { 1 } };
    return result;
}

std::shared_ptr<Literal>
StdLib::funTranspose(ArgVec& arguments)
{
    // arg[0] - matrix

    auto prevSize = arguments.at(0)->getSize();

    auto result = std::make_shared<Literal>();
    result->data.clear();
    for(auto y = 0; y < prevSize.second; ++y)
    {
        result->data.push_back({});
        for(auto x = 0; x < prevSize.first; ++x)
        {
            result->data.at(y).push_back(arguments.at(0)->data.at(x).at(y));
        }
    }
    return result;
}
