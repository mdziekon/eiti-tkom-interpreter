#include "Parser.hpp"

#include "../error-handler/ErrorHandler.hpp"
#include "../lexer/Lexer.hpp"

#include <iostream>

using Parser = tkom::modules::Parser;
using Lexer = tkom::modules::Lexer;

Parser::Parser(Lexer& lexer):
lexer(lexer)
{}

void Parser::parse()
{
    this->resetPreviousToken();

    Token token;

    bool finished = false;

    do
    {
        finished = this->parseFunction();
    }
    while(!finished);
}

bool Parser::isAcceptable(const Token& token, const std::initializer_list<TokenType>& acceptable) const
{
    for(auto& it: acceptable)
    {
        if (token.type == it)
        {
            return true;
        }
    }

    return false;
}

Token Parser::accept(const std::initializer_list<TokenType>& acceptable)
{
    Token token;

    if (this->hasBufferedToken())
    {
        token = this->previousToken;
        this->resetPreviousToken();
    }
    else
    {
        token = this->lexer.nextToken();
    }

    if (this->isAcceptable(token, acceptable))
    {
        return token;
    }
    else
    {
        ErrorHandler::error(
            std::string("Unexpected token: ")
                .append(tkom::modules::utils::getTokenTypeName(token.type))
                .append(" (Line: ")
                .append(std::to_string(token.line))
                .append(", Pos: ")
                .append(std::to_string(token.pos))
                .append(")")
        );
        return token;
    }
}

bool Parser::peek(const std::initializer_list<TokenType>& acceptable)
{
    if (!this->hasBufferedToken())
    {
        this->previousToken = this->lexer.nextToken();
    }

    return this->isAcceptable(this->previousToken, acceptable);
}

Token Parser::getPeeked()
{
    if (!this->hasBufferedToken())
    {
        ErrorHandler::debugFatal(std::string("Nothing peeked"));
    }

    return this->previousToken;
}

void Parser::peekFail()
{
    Token& token = this->previousToken;

    ErrorHandler::error(
        std::string("Unexpected token: ")
            .append(tkom::modules::utils::getTokenTypeName(token.type))
            .append(" (Line: ")
            .append(std::to_string(token.line))
            .append(", Pos: ")
            .append(std::to_string(token.pos))
            .append(")")
    );
}

bool Parser::hasBufferedToken() const
{
    return this->previousToken.type != TokenType::Undefined;
}

void Parser::resetPreviousToken()
{
    this->previousToken.type = TokenType::Undefined;
    this->previousToken.value = "";
    this->previousToken.line = 0;
    this->previousToken.pos = 0;
}

bool Parser::parseFunction()
{
    auto tempToken = this->accept({ TokenType::Function, TokenType::EndOfFile });
    if (tempToken.type == TokenType::EndOfFile)
    {
        return false;
    }

    tempToken = this->accept({ TokenType::Identifier });
    this->parseParameters();
    this->parseStatementBlock();

    return true;
}

void Parser::parseParameters()
{
    Token tempToken;

    this->accept({ TokenType::ParenthOpen });

    tempToken = this->accept({ TokenType::ParenthClose, TokenType::Identifier });
    if (tempToken.type == TokenType::ParenthClose)
    {
        return;
    }

    while (true)
    {
        tempToken = this->accept({ TokenType::ParenthClose, TokenType::Comma });
        if (tempToken.type == TokenType::ParenthClose)
        {
            return;
        }
        tempToken = this->accept({ TokenType::Identifier });
    }
}

void Parser::parseStatementBlock()
{
    this->accept({ TokenType::BracketOpen });

    Token tempToken;

    while (true)
    {
        if (!this->peek({
            TokenType::If,
            TokenType::While,
            TokenType::Return,
            TokenType::Var,
            TokenType::BracketOpen,
            TokenType::Identifier,
            TokenType::Continue,
            TokenType::Break
        }))
        {
            break;
        }

        tempToken = this->getPeeked();

        switch (tempToken.type)
        {
            case TokenType::If:
                this->parseIfStatement();
                break;
            case TokenType::While:
                this->parseWhileStatement();
                break;
            case TokenType::Return:
                this->parseReturnStatement();
                break;
            case TokenType::Var:
                this->parseInitStatement();
                break;
            case TokenType::BracketOpen:
                this->parseStatementBlock();
                break;
            case TokenType::Identifier:
                this->parseAssignmentOrFunCall();
                break;
            case TokenType::Continue:
            case TokenType::Break:
                this->accept({ TokenType::Continue, TokenType::Break });
                break;
        }
    }

    this->accept({ TokenType::BracketClose });
}

void Parser::parseIfStatement()
{
    this->accept({ TokenType::If });

    this->accept({ TokenType::ParenthOpen });
    this->parseCondition();
    this->accept({ TokenType::ParenthClose });

    this->parseStatementBlock();

    if (!this->peek({ TokenType::Else }))
    {
        return;
    }

    this->accept({ TokenType::Else });
    this->parseStatementBlock();
}

void Parser::parseWhileStatement()
{
    this->accept({ TokenType::While });

    this->accept({ TokenType::ParenthOpen });
    this->parseCondition();
    this->accept({ TokenType::ParenthClose });

    this->parseStatementBlock();
}

void Parser::parseReturnStatement()
{
    this->accept({ TokenType::Return });
    this->parseAssignable();
    this->accept({ TokenType::Semicolon });
}

void Parser::parseInitStatement()
{
    this->accept({ TokenType::Var });
    this->accept({ TokenType::Identifier });

    if (this->peek({ TokenType::Assignment }))
    {
        this->accept({ TokenType::Assignment });
        this->parseAssignable();
    }

    this->accept({ TokenType::Semicolon });
}

void Parser::parseAssignmentOrFunCall()
{
    this->accept({ TokenType::Identifier });

    if (!this->parseFunCall())
    {
        this->accept({ TokenType::Assignment });
        this->parseAssignable();
    }
}

void Parser::parseAssignable()
{
    if (this->peek({ TokenType::Identifier }))
    {
        auto tempToken = this->accept({ TokenType::Identifier });
        if (this->parseFunCall())
        {
            return;
        }

        this->parseExpression(tempToken);
        return;
    }

    this->parseExpression();
}

bool Parser::parseFunCall()
{
    if (!this->peek({ TokenType::ParenthOpen }))
    {
        return false;
    }

    this->accept({ TokenType::ParenthOpen });

    if (this->peek({ TokenType::ParenthClose }))
    {
        this->accept({ TokenType::ParenthClose });
        return true;
    }

    while (true)
    {
        this->parseAssignable();
        if (this->peek({ TokenType::ParenthClose }))
        {
            this->accept({ TokenType::ParenthClose });
            return true;
        }
        if (this->peek({ TokenType::Comma }))
        {
            this->accept({ TokenType::Comma });
            continue;
        }

        this->peekFail();
    }
}

void Parser::parseVariable()
{
    this->accept({ TokenType::Identifier });

    if (!this->peek({ TokenType::SquareBracketOpen }))
    {
        return;
    }

    this->accept({ TokenType::SquareBracketOpen });
    this->parseAssignable();
    this->accept({ TokenType::SquareBracketClose });

    if (!this->peek({ TokenType::SquareBracketOpen }))
    {
        return;
    }

    this->accept({ TokenType::SquareBracketOpen });
    this->parseAssignable();
    this->accept({ TokenType::SquareBracketClose });
}

void Parser::parseLiteral()
{
    if (this->peek({ TokenType::SquareBracketOpen }))
    {
        this->parseMatrixLiteral();
        return;
    }

    if (this->peek({ TokenType::Minus }))
    {
        this->accept({ TokenType::Minus });
    }

    this->accept({ TokenType::Infinity, TokenType::NumberLiteral });
}

void Parser::parseMatrixLiteral()
{
    this->accept({ TokenType::SquareBracketOpen });
    this->accept({ TokenType::NumberLiteral });

    while (!this->peek({ TokenType::SquareBracketClose }))
    {
        while (!this->peek({ TokenType::Semicolon }))
        {
            this->accept({ TokenType::Comma });
            this->accept({ TokenType::NumberLiteral });
        }

        this->accept({ TokenType::NumberLiteral });
    }
}

void Parser::parseExpression()
{
    this->parseMultiplicativeExpression();

    while (this->peek({ TokenType::Plus, TokenType::Minus }))
    {
        this->accept({ TokenType::Plus, TokenType::Minus });
        this->parseMultiplicativeExpression();
    }
}

void Parser::parseMultiplicativeExpression()
{
    this->parsePrimaryExpression();

    while (this->peek({ TokenType::Multiply, TokenType::Divide, TokenType::Modulo }))
    {
        this->accept({ TokenType::Multiply, TokenType::Divide, TokenType::Modulo });
        this->parsePrimaryExpression();
    }
}

void Parser::parsePrimaryExpression()
{
    if (this->peek({ TokenType::ParenthOpen }))
    {
        this->accept({ TokenType::ParenthOpen });
        this->parseExpression();
        this->accept({ TokenType::ParenthClose });

        return;
    }

    if (this->peek({ TokenType::Identifier }))
    {
        this->parseVariable();

        return;
    }

    this->parseLiteral();
}

void Parser::parseExpression(const Token& firstToken)
{
    this->parseMultiplicativeExpression(firstToken);

    while (this->peek({ TokenType::Plus, TokenType::Minus }))
    {
        this->accept({ TokenType::Plus, TokenType::Minus });
        this->parseMultiplicativeExpression();
    }
}

void Parser::parseMultiplicativeExpression(const Token& firstToken)
{
    this->parsePrimaryExpression(firstToken);

    while (this->peek({ TokenType::Multiply, TokenType::Divide, TokenType::Modulo }))
    {
        this->accept({ TokenType::Multiply, TokenType::Divide, TokenType::Modulo });
        this->parsePrimaryExpression();
    }
}

void Parser::parsePrimaryExpression(const Token& firstToken)
{
    if (!this->isAcceptable(firstToken, { TokenType::Identifier }))
    {
        ErrorHandler::error(
            std::string("Unexpected token: ")
                .append(tkom::modules::utils::getTokenTypeName(firstToken.type))
                .append(" (Line: ")
                .append(std::to_string(firstToken.line))
                .append(", Pos: ")
                .append(std::to_string(firstToken.pos))
                .append(")")
        );
    }
}

void Parser::parseCondition()
{
    this->parseAndCondition();

    while (this->peek({ TokenType::Or }))
    {
        this->accept({ TokenType::Or });
        this->parseAndCondition();
    }
}

void Parser::parseAndCondition()
{
    this->parseEqualityCondition();

    while (this->peek({ TokenType::And }))
    {
        this->accept({ TokenType::And });
        this->parseEqualityCondition();
    }
}

void Parser::parseEqualityCondition()
{
    this->parseRelationalCondition();

    while (this->peek({ TokenType::Equality, TokenType::Inequality }))
    {
        this->accept({ TokenType::Equality, TokenType::Inequality });
        this->parseRelationalCondition();
    }
}

void Parser::parseRelationalCondition()
{
    this->parsePrimaryCondition();

    while (this->peek({ TokenType::Less, TokenType::Greater, TokenType::LessOrEqual, TokenType::GreaterOrEqual }))
    {
        this->accept({ TokenType::Less, TokenType::Greater, TokenType::LessOrEqual, TokenType::GreaterOrEqual });
        this->parsePrimaryCondition();
    }
}

void Parser::parsePrimaryCondition()
{
    if (this->peek({ TokenType::Negation }))
    {
        this->accept({ TokenType::Negation });
    }

    if (this->peek({ TokenType::ParenthOpen }))
    {
        this->accept({ TokenType::ParenthOpen });
        this->parseCondition();
        this->accept({ TokenType::ParenthClose });

        return;
    }

    if (this->peek({ TokenType::Identifier }))
    {
        this->parseVariable();

        return;
    }

    this->parseLiteral();
}
