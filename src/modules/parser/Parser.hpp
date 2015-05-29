#ifndef TKOM_MODULES_PARSER_HPP
#define TKOM_MODULES_PARSER_HPP

#include <initializer_list>

#include "../utils/Token.hpp"
#include "../utils/TokenType.hpp"

#include "../tracer/Tracer.hpp"

using Token = tkom::modules::utils::Token;
using TokenType = tkom::modules::utils::TokenType;

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

        bool hasBufferedToken() const;
        void resetPreviousToken();

        // Decomposition procedures
        bool parseFunction();
        void parseParameters();
        void parseStatementBlock();

        void parseIfStatement();
        void parseWhileStatement();
        void parseReturnStatement();
        void parseInitStatement();
        void parseAssignmentOrFunCall();

        void parseAssignable();
        bool parseFunCall();
        void parseVariable();
        void parseLiteral();
        void parseMatrixLiteral();

        void parseExpression(const Token& firstToken = Token(TokenType::Undefined));
        void parseMultiplicativeExpression(const Token& firstToken = Token(TokenType::Undefined));
        void parsePrimaryExpression(const Token& firstToken = Token(TokenType::Undefined));

        void parseCondition();
        void parseAndCondition();
        void parseEqualityCondition();
        void parseRelationalCondition();
        void parsePrimaryCondition();
    };
}}

#endif
