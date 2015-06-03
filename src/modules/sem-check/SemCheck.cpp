#include "SemCheck.hpp"

#include "../error-handler/ErrorHandler.hpp"
#include "../stdlib/StdLib.hpp"

#include "../../structures/ir/includes.hpp"

using ErrorHandler = tkom::modules::ErrorHandler;
using SemCheck = tkom::modules::SemCheck;
using StdLib = tkom::modules::StdLib;
namespace ir = tkom::structures::ir;
namespace ast = tkom::structures::ast;

std::vector<std::shared_ptr<ir::Function>> SemCheck::check(const std::shared_ptr<ast::Program>& syntaxTree)
{
    this->syntaxTree = syntaxTree.get();
    this->definedFunctions.clear();

    this->scanFunctionDefinitions();
    this->checkMain();

    return this->traverseTree();
}

void SemCheck::scanFunctionDefinitions()
{
    for(auto& functionNode: this->syntaxTree->functions)
    {
        if (StdLib::hasFunction(functionNode->name))
        {
            ErrorHandler::error(
                std::string("Redefinition of Standard Lib function: ")
                    .append(functionNode->name)
            );
            return;
        }

        if (this->definedFunctions.count(functionNode->name) == 1)
        {
            ErrorHandler::error(
                std::string("Duplicated definition of function: ")
                    .append(functionNode->name)
            );
            return;
        }

        this->definedFunctions.insert({ { functionNode->name, std::make_shared<ir::Function>() } });
        auto& fun = this->definedFunctions.at(functionNode->name);
        fun->name = functionNode->name;

        for(auto& variable: functionNode->parameters)
        {
            if (!fun->scopeProto.addVariable(variable))
            {
                ErrorHandler::error(
                    std::string("Duplicated definition of parameter \"")
                        .append(variable)
                        .append("\" of function \"")
                        .append(functionNode->name)
                        .append("\"")
                );
                return;
            }
            fun->scopeProto.setVariableDefined(variable);
        }
    }
}

void SemCheck::checkMain()
{
    if (this->definedFunctions.count("main") == 0)
    {
        ErrorHandler::error(
            std::string("No entry point (a.k.a. \"main\" function) defined")
        );
        return;
    }
    if (this->definedFunctions.at("main")->scopeProto.variables.size() != 0)
    {
        ErrorHandler::error(
            std::string("\"main\" function should not have parameters")
        );
        return;
    }
}

std::vector<std::shared_ptr<ir::Function>> SemCheck::traverseTree()
{
    std::vector<std::shared_ptr<ir::Function>> functions;

    for(auto& function: this->syntaxTree->functions)
    {
        functions.push_back(this->checkFunction(*function));
    }

    return functions;
}

std::shared_ptr<ir::Function> SemCheck::checkFunction(ast::FunDefinition& functionDef)
{
    auto& function = this->definedFunctions.at(functionDef.name);

    function->instructions.push_back(this->checkBlock(function->scopeProto, *(functionDef.blockNode)));

    return function;
}

std::shared_ptr<ir::Block> SemCheck::checkBlock(ir::ScopeProto& scopeProto, ast::StatementBlock& blockNode)
{
    std::shared_ptr<ir::Block> block = std::make_shared<ir::Block>();
    block->scopeProto.upperScope = &scopeProto;

    for(auto& instruction: blockNode.instructions)
    {
        switch(instruction->getType())
        {
            case ast::Node::Type::VarDeclaration:
            {
                auto node = static_cast<ast::VarDeclaration*>(instruction.get());
                this->checkVarDeclaration(block->scopeProto, node->name);

                if (node->assignableNode)
                {
                    block->instructions.push_back(this->checkAssignment(block->scopeProto, node->name, *(node->assignableNode)));
                }
                break;
            }
            case ast::Node::Type::Assignment:
            {
                auto node = static_cast<ast::Assignment*>(instruction.get());
                block->instructions.push_back(this->checkAssignment(block->scopeProto, *(node->variable), *(node->value)));
                break;
            }
            case ast::Node::Type::ReturnStatement:
            {
                auto node = static_cast<ast::ReturnStatement*>(instruction.get());
                block->instructions.push_back(this->checkReturnStatement(block->scopeProto, *(node->assignableNode)));
                break;
            }
            case ast::Node::Type::Call:
            {
                auto node = static_cast<ast::Call*>(instruction.get());
                block->instructions.push_back(this->checkFunctionCall(block->scopeProto, *node));
                break;
            }
            case ast::Node::Type::StatementBlock:
            {
                auto node = static_cast<ast::StatementBlock*>(instruction.get());
                block->instructions.push_back(this->checkBlock(block->scopeProto, *node));
                break;
            }
            case ast::Node::Type::IfStatement:
            {
                auto node = static_cast<ast::IfStatement*>(instruction.get());
                block->instructions.push_back(this->checkIfStatement(block->scopeProto, *node));
                break;
            }
            case ast::Node::Type::WhileStatement:
            {
                auto node = static_cast<ast::WhileStatement*>(instruction.get());
                block->instructions.push_back(this->checkWhileStatement(block->scopeProto, *node));
                break;
            }
            case ast::Node::Type::LoopJump:
            {
                auto node = std::make_shared<ir::instructions::LoopJump>();
                node->isBreak = (static_cast<ast::LoopJump*>(instruction.get()))->isBreak;
                block->instructions.push_back(node);
                break;
            }
            default:
            {
                ErrorHandler::error(
                    std::string("Invalid instruction node type")
                );
            }
        }
    }

    return block;
}

void SemCheck::checkVarDeclaration(ir::ScopeProto& scopeProto, const std::string& name)
{
    if (!scopeProto.addVariable(name))
    {
        ErrorHandler::error(
            std::string("Redeclaration of variable: ")
                .append(name)
        );
    }
}

std::shared_ptr<ir::instructions::Assignment> SemCheck::checkAssignment(ir::ScopeProto& scopeProto, const std::string& variable, ast::Assignable& assignable)
{
    std::shared_ptr<ir::instructions::Assignment> node = std::make_shared<ir::instructions::Assignment>();

    if (!scopeProto.hasVariable(variable))
    {
        ErrorHandler::error(
            std::string("Assignment to undefined variable: ")
                .append(variable)
        );

        return nullptr;
    }

    node->variable->name = variable;
    node->value = this->checkAssignable(scopeProto, assignable);

    scopeProto.setVariableDefined(variable);

    return node;
}


std::shared_ptr<ir::instructions::Assignment> SemCheck::checkAssignment(ir::ScopeProto& scopeProto, ast::Variable& variable, ast::Assignable& assignable)
{
    std::shared_ptr<ir::instructions::Assignment> node = std::make_shared<ir::instructions::Assignment>();

    if (!scopeProto.hasVariable(variable.variableName))
    {
        ErrorHandler::error(
            std::string("Assignment to undefined variable: ")
                .append(variable.variableName)
        );

        return nullptr;
    }

    if (variable.indexArg1 && !scopeProto.isVariableDefined(variable.variableName))
    {
        ErrorHandler::error(
            std::string("Indexed assignment to empty variable: ")
                .append(variable.variableName)
        );

        return nullptr;
    }

    node->variable->name = variable.variableName;
    if (variable.indexArg1)
    {
        if (variable.indexArg1->getType() == ast::Node::Type::Call)
        {
            node->variable->indexArg1 = this->checkFunctionCall(scopeProto, *(static_cast<ast::Call*>(variable.indexArg1.get())));
        }
        else if (variable.indexArg1->getType() == ast::Node::Type::Expression)
        {
            node->variable->indexArg1 = this->checkExpression(scopeProto, *(static_cast<ast::Expression*>(variable.indexArg1.get())));
        }
        else
        {
            ErrorHandler::error(
                std::string("Invalid assignable value")
            );
        }
    }
    if (variable.indexArg2)
    {
        if (variable.indexArg2->getType() == ast::Node::Type::Call)
        {
            node->variable->indexArg2 = this->checkFunctionCall(scopeProto, *(static_cast<ast::Call*>(variable.indexArg2.get())));
        }
        else if (variable.indexArg2->getType() == ast::Node::Type::Expression)
        {
            node->variable->indexArg2 = this->checkExpression(scopeProto, *(static_cast<ast::Expression*>(variable.indexArg2.get())));
        }
        else
        {
            ErrorHandler::error(
                std::string("Invalid assignable value")
            );
        }
    }
    node->value = this->checkAssignable(scopeProto, assignable);

    scopeProto.setVariableDefined(variable.variableName);

    return node;
}

std::shared_ptr<ir::Assignable> SemCheck::checkAssignable(ir::ScopeProto& scopeProto, ast::Assignable& assignable)
{
    if (assignable.getType() == ast::Node::Type::Call)
    {
        return this->checkFunctionCall(scopeProto, *(static_cast<ast::Call*>(&assignable)));
    }
    else if (assignable.getType() == ast::Node::Type::Expression)
    {
        return this->checkExpression(scopeProto, *(static_cast<ast::Expression*>(&assignable)));
    }

    ErrorHandler::error(
        std::string("Invalid assignable value")
    );

    return nullptr;
}

std::shared_ptr<ir::instructions::Call> SemCheck::checkFunctionCall(ir::ScopeProto& scopeProto, ast::Call& call)
{
    if (this->definedFunctions.count(call.name) == 0 && !StdLib::hasFunction(call.name))
    {
        ErrorHandler::error(
            std::string("Call to undefined function: ")
                .append(call.name)
        );
        return nullptr;
    }

    if (this->definedFunctions.count(call.name) == 1)
    {
        auto &functionDef = this->definedFunctions.at(call.name);
        if (functionDef->scopeProto.variables.size() != call.arguments.size())
        {
            ErrorHandler::error(
                std::string("Invalid arguments count for function \"")
                    .append(call.name)
                    .append("\", expected ")
                    .append(std::to_string(functionDef->scopeProto.variables.size()))
                    .append(", got ")
                    .append(std::to_string(call.arguments.size()))
            );
            return nullptr;
        }
    }
    else
    {
        unsigned int requiredArgs = StdLib::getFunctionParamsCount(call.name);
        if (requiredArgs != call.arguments.size())
        {
            ErrorHandler::error(
                std::string("Invalid arguments count for function \"")
                    .append(call.name)
                    .append("\", expected ")
                    .append(std::to_string(requiredArgs))
                    .append(", got ")
                    .append(std::to_string(call.arguments.size()))
            );
            return nullptr;
        }
    }

    std::shared_ptr<ir::instructions::Call> obj = std::make_shared<ir::instructions::Call>();
    obj->name = call.name;

    for(auto& argument: call.arguments)
    {
        obj->arguments.push_back(this->checkAssignable(scopeProto, *argument));
    }

    return obj;
}

std::shared_ptr<ir::Expression> SemCheck::checkExpression(ir::ScopeProto& scopeProto, ast::Expression& expression)
{
    std::shared_ptr<ir::Expression> obj = std::make_shared<ir::Expression>();

    obj->operations = expression.operations;

    for(auto& operand: expression.operands)
    {
        if (operand->getType() == ast::Node::Type::Matrix)
        {
            obj->operands.push_back(this->checkMatrixLiteral(*(static_cast<ast::Matrix*>(operand.get()))));
        }
        else if (operand->getType() == ast::Node::Type::Expression)
        {
            obj->operands.push_back(this->checkExpression(scopeProto, *(static_cast<ast::Expression*>(operand.get()))));
        }
        else if (operand->getType() == ast::Node::Type::Variable)
        {
            obj->operands.push_back(this->checkVariable(scopeProto, *(static_cast<ast::Variable*>(operand.get()))));
        }
        else
        {
            ErrorHandler::error(
                std::string("Invalid expression operand")
            );
        }
    }

    return obj;
}

std::shared_ptr<ir::Variable> SemCheck::checkVariable(ir::ScopeProto& scopeProto, ast::Variable& variable)
{
    std::shared_ptr<ir::Variable> obj = std::make_shared<ir::Variable>();

    if (!scopeProto.hasVariable(variable.variableName))
    {
        ErrorHandler::error(
            std::string("Usage of undefined variable: ")
                .append(variable.variableName)
        );

        return nullptr;
    }

    if (!scopeProto.isVariableDefined(variable.variableName))
    {
        ErrorHandler::error(
            std::string("Usage of empty variable: ")
                .append(variable.variableName)
        );

        return nullptr;
    }

    if (variable.indexArg1 && !scopeProto.isVariableDefined(variable.variableName))
    {
        ErrorHandler::error(
            std::string("Indexed usage of empty variable: ")
                .append(variable.variableName)
        );

        return nullptr;
    }

    obj->name = variable.variableName;
    if (variable.indexArg1)
    {
        obj->indexArg1 = this->checkAssignable(scopeProto, *(variable.indexArg1));
    }
    if (variable.indexArg2)
    {
        obj->indexArg2 = this->checkAssignable(scopeProto, *(variable.indexArg2));
    }

    return obj;
}

std::shared_ptr<ir::instructions::Return> SemCheck::checkReturnStatement(ir::ScopeProto& scopeProto, ast::Assignable& assignable)
{
    std::shared_ptr<ir::instructions::Return> obj = std::make_shared<ir::instructions::Return>();

    obj->value = this->checkAssignable(scopeProto, assignable);

    return obj;
}

std::shared_ptr<ir::instructions::IfStatement> SemCheck::checkIfStatement(ir::ScopeProto& scopeProto, ast::IfStatement& stmt)
{
    std::shared_ptr<ir::instructions::IfStatement> obj = std::make_shared<ir::instructions::IfStatement>();

    obj->condition = this->checkCondition(scopeProto, *(stmt.conditionNode));

    obj->trueBlock = this->checkBlock(scopeProto, *(stmt.trueBlockNode));
    if (stmt.falseBlockNode)
    {
        obj->falseBlock = this->checkBlock(scopeProto, *(stmt.falseBlockNode));
    }

    return obj;
}

std::shared_ptr<ir::instructions::WhileStatement> SemCheck::checkWhileStatement(ir::ScopeProto& scopeProto, ast::WhileStatement& stmt)
{
    std::shared_ptr<ir::instructions::WhileStatement> obj = std::make_shared<ir::instructions::WhileStatement>();

    obj->condition = this->checkCondition(scopeProto, *(stmt.conditionNode));

    obj->block = this->checkBlock(scopeProto, *(stmt.blockNode));

    return obj;
}

std::shared_ptr<ir::Condition> SemCheck::checkCondition(ir::ScopeProto& scopeProto, ast::Condition& condition)
{
    std::shared_ptr<ir::Condition> obj = std::make_shared<ir::Condition>();

    obj->operation = condition.operation;
    obj->negated = condition.negated;

    for(auto& operand: condition.operands)
    {
        if (operand->getType() == ast::Node::Type::Matrix)
        {
            obj->operands.push_back(this->checkMatrixLiteral(*(static_cast<ast::Matrix*>(operand.get()))));
        }
        else if (operand->getType() == ast::Node::Type::Condition)
        {
            obj->operands.push_back(this->checkCondition(scopeProto, *(static_cast<ast::Condition*>(operand.get()))));
        }
        else if (operand->getType() == ast::Node::Type::Variable)
        {
            obj->operands.push_back(this->checkVariable(scopeProto, *(static_cast<ast::Variable*>(operand.get()))));
        }
        else
        {
            ErrorHandler::error(
                std::string("Invalid condition operand")
            );
        }
    }

    return obj;
}

std::shared_ptr<ir::Literal> SemCheck::checkMatrixLiteral(ast::Matrix& matrixLiteral)
{
    std::shared_ptr<ir::Literal> obj = std::make_shared<ir::Literal>();

    unsigned int lastRowSize = matrixLiteral.data.at(0).size();

    for(auto it = matrixLiteral.data.begin() + 1; it != matrixLiteral.data.end(); ++it)
    {
        if (it->size() != lastRowSize)
        {
            ErrorHandler::error(
                std::string("Invalid matrix literal definition")
            );
        }
    }

    obj->data = matrixLiteral.data;

    return obj;
}
