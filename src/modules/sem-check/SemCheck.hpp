#ifndef TKOM_MODULES_SEMCHECK_HPP
#define TKOM_MODULES_SEMCHECK_HPP

#include "../parser/Parser.hpp"
#include "../executor/Executor.hpp"
#include "../../structures/ir/includes.hpp"

namespace ir = tkom::structures::ir;
namespace ast = tkom::structures::ast;

namespace tkom { namespace modules {
    class SemCheck
    {
    public:
        std::vector<std::shared_ptr<ir::Function>> check(const std::shared_ptr<ast::Program>& syntaxTree, tkom::modules::Executor& executor);

    private:
        tkom::modules::Executor* executor;
        ast::Program* syntaxTree;
        std::unordered_map<std::string, std::shared_ptr<ir::Function>> definedFunctions;

        void scanFunctionDefinitions();
        void checkMain();
        std::vector<std::shared_ptr<ir::Function>> traverseTree();
        std::shared_ptr<ir::Function> checkFunction(ast::FunDefinition& functionDef);
        std::shared_ptr<ir::Block> checkBlock(ir::ScopeProto& scopeProto, ast::StatementBlock& blockNode);

        void checkVarDeclaration(ir::ScopeProto& scopeProto, const std::string& name);
        std::shared_ptr<ir::instructions::Assignment> checkAssignment(ir::ScopeProto& scopeProto, const std::string& variable, ast::Assignable& assignable);
        std::shared_ptr<ir::instructions::Assignment> checkAssignment(ir::ScopeProto& scopeProto, ast::Variable& variable, ast::Assignable& assignable);
        std::shared_ptr<ir::Assignable> checkAssignable(ir::ScopeProto& scopeProto, ast::Assignable& assignable);
        std::shared_ptr<ir::instructions::Call> checkFunctionCall(ir::ScopeProto& scopeProto, ast::Call& call);
        std::shared_ptr<ir::Expression> checkExpression(ir::ScopeProto& scopeProto, ast::Expression& call);
        std::shared_ptr<ir::Variable> checkVariable(ir::ScopeProto& scopeProto, ast::Variable& variable);
        std::shared_ptr<ir::instructions::Return> checkReturnStatement(ir::ScopeProto& scopeProto, ast::Assignable& assignable);
        std::shared_ptr<ir::instructions::IfStatement> checkIfStatement(ir::ScopeProto& scopeProto, ast::IfStatement& stmt);
        std::shared_ptr<ir::instructions::WhileStatement> checkWhileStatement(ir::ScopeProto& scopeProto, ast::WhileStatement& stmt);
        std::shared_ptr<ir::Condition> checkCondition(ir::ScopeProto& scopeProto, ast::Condition& condition);
        std::shared_ptr<ir::Literal> checkMatrixLiteral(ast::Matrix& matrixLiteral);
    };
}}

#endif
