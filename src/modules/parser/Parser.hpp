#ifndef TKOM_MODULES_PARSER_HPP
#define TKOM_MODULES_PARSER_HPP

#include <initializer_list>

#include "../utils/Token.hpp"
#include "../utils/TokenType.hpp"

#include "../tracer/Tracer.hpp"

#include "../../structures/ast/AST.hpp"

using Token = tkom::modules::utils::Token;
using TokenType = tkom::modules::utils::TokenType;
namespace ast = tkom::structures::ast;

namespace tkom { namespace modules
{
    class Lexer;

    class Parser
    {
    public:
        Parser(Lexer& lexer);

        void parse();

    private:
        Tracer tracer = Tracer(true);

        Lexer& lexer;
        Token previousToken;

        bool isAcceptable(const Token& token, const std::initializer_list<TokenType>& acceptable) const;
        Token accept(const std::initializer_list<TokenType>& acceptable);
        bool peek(const std::initializer_list<TokenType>& acceptable);
        Token getPeeked();
        void peekFail();
        const std::string makeErrorMarker(const unsigned int& pos);

        bool hasBufferedToken() const;
        void resetPreviousToken();

        // Decomposition procedures
        std::shared_ptr<ast::FunDefinition> parseFunction();
        std::vector<std::string> parseParameters();
        std::shared_ptr<ast::StatementBlock> parseStatementBlock();

        std::shared_ptr<ast::IfStatement> parseIfStatement();
        std::shared_ptr<ast::WhileStatement> parseWhileStatement();
        std::shared_ptr<ast::ReturnStatement> parseReturnStatement();
        std::shared_ptr<ast::VarDeclaration> parseInitStatement();
        ast::NodePtr parseAssignmentOrFunCall();
        std::shared_ptr<ast::LoopJump> parseLoopJump();

        std::shared_ptr<ast::Assignable> parseAssignable();
        std::shared_ptr<ast::Call> parseFunCall(const std::string& identifier);
        std::shared_ptr<ast::Variable> parseVariable(const Token& firstToken = Token(TokenType::Undefined));
        std::shared_ptr<ast::Matrix> parseLiteral();
        double parseNumberLiteral();
        std::shared_ptr<ast::Matrix> parseMatrixLiteral();

        std::shared_ptr<ast::Expression> parseExpression(const Token& firstToken = Token(TokenType::Undefined));
        std::shared_ptr<ast::Expression> parseMultiplicativeExpression(const Token& firstToken = Token(TokenType::Undefined));
        ast::NodePtr parsePrimaryExpression(const Token& firstToken = Token(TokenType::Undefined));

        std::shared_ptr<ast::Condition> parseCondition();
        std::shared_ptr<ast::Condition> parseAndCondition();
        std::shared_ptr<ast::Condition> parseEqualityCondition();
        std::shared_ptr<ast::Condition> parseRelationalCondition();
        ast::NodePtr parsePrimaryCondition();
    };
}}

#endif
