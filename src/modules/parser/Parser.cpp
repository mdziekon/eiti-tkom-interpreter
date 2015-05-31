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
    this->tracer.reset();

    this->resetPreviousToken();

    Token token;

    bool finished = false;

    this->tracer.enter("Starting parser tracing...");
    do
    {
        finished = this->parseFunction();
    }
    while(!finished);
    this->tracer.leave("Trace ended...");
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
                .append("\n")
                .append(this->lexer.getLine(token.lineStart))
                .append("\n")
                .append(this->makeErrorMarker(token.pos))
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
            .append("\n")
            .append(this->lexer.getLine(token.lineStart))
            .append("\n")
            .append(this->makeErrorMarker(token.pos))
    );
}

const std::string Parser::makeErrorMarker(const unsigned int& pos)
{
    return std::string(pos, ' ').append("^");
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
    this->tracer.enter("Parsing function");

    auto tempToken = this->accept({ TokenType::Function, TokenType::EndOfFile });
    if (tempToken.type == TokenType::EndOfFile)
    {
        return false;
    }

    tempToken = this->accept({ TokenType::Identifier });
    this->parseParameters();
    this->parseStatementBlock();

    this->tracer.leave();

    return true;
}

void Parser::parseParameters()
{
    this->tracer.enter("Parsing parameters");

    Token tempToken;

    this->accept({ TokenType::ParenthOpen });

    tempToken = this->accept({ TokenType::ParenthClose, TokenType::Identifier });
    if (tempToken.type == TokenType::ParenthClose)
    {
        this->tracer.leave();
        return;
    }

    while (true)
    {
        tempToken = this->accept({ TokenType::ParenthClose, TokenType::Comma });
        if (tempToken.type == TokenType::ParenthClose)
        {
            this->tracer.leave();
            return;
        }
        tempToken = this->accept({ TokenType::Identifier });
    }
}

void Parser::parseStatementBlock()
{
    this->tracer.enter("Parsing statement block");

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

    this->tracer.leave();
}

void Parser::parseIfStatement()
{
    this->tracer.enter("Parsing if statement");

    this->accept({ TokenType::If });

    this->accept({ TokenType::ParenthOpen });
    this->parseCondition();
    this->accept({ TokenType::ParenthClose });

    this->parseStatementBlock();

    if (!this->peek({ TokenType::Else }))
    {
        this->tracer.leave();
        return;
    }

    this->accept({ TokenType::Else });
    this->parseStatementBlock();

    this->tracer.leave();
}

void Parser::parseWhileStatement()
{
    this->tracer.enter("Parsing while statement");

    this->accept({ TokenType::While });

    this->accept({ TokenType::ParenthOpen });
    this->parseCondition();
    this->accept({ TokenType::ParenthClose });

    this->parseStatementBlock();

    this->tracer.leave();
}

void Parser::parseReturnStatement()
{
    this->tracer.enter("Parsing return statement");

    this->accept({ TokenType::Return });
    this->parseAssignable();
    this->accept({ TokenType::Semicolon });

    this->tracer.leave();
}

void Parser::parseInitStatement()
{
    this->tracer.enter("Parsing init statement");

    this->accept({ TokenType::Var });
    this->accept({ TokenType::Identifier });

    if (this->peek({ TokenType::Assignment }))
    {
        this->accept({ TokenType::Assignment });
        this->parseAssignable();
    }

    this->accept({ TokenType::Semicolon });

    this->tracer.leave();
}

void Parser::parseAssignmentOrFunCall()
{
    this->tracer.enter("Parsing assignment or function call");

    this->accept({ TokenType::Identifier });

    if (!this->parseFunCall())
    {
        this->accept({ TokenType::Assignment });
        this->parseAssignable();
    }

    this->tracer.leave();
}

void Parser::parseAssignable()
{
    this->tracer.enter("Parsing assignable");

    if (this->peek({ TokenType::Identifier }))
    {
        auto tempToken = this->accept({ TokenType::Identifier });
        if (this->parseFunCall())
        {
            this->tracer.leave();
            return;
        }

        this->parseExpression(tempToken);
        this->tracer.leave();
        return;
    }

    this->parseExpression();

    this->tracer.leave();
}

bool Parser::parseFunCall()
{
    this->tracer.enter("Parsing function call");

    if (!this->peek({ TokenType::ParenthOpen }))
    {
        this->tracer.leave("  - not a function call");
        return false;
    }

    this->accept({ TokenType::ParenthOpen });

    if (this->peek({ TokenType::ParenthClose }))
    {
        this->accept({ TokenType::ParenthClose });
        this->tracer.leave("  + function call");
        return true;
    }

    while (true)
    {
        this->parseAssignable();
        if (this->peek({ TokenType::ParenthClose }))
        {
            this->accept({ TokenType::ParenthClose });
            this->tracer.leave("  + function call");
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
    this->tracer.enter("Parsing variable");

    this->accept({ TokenType::Identifier });

    if (!this->peek({ TokenType::SquareBracketOpen }))
    {
        this->tracer.leave();
        return;
    }

    this->accept({ TokenType::SquareBracketOpen });
    this->parseAssignable();
    this->accept({ TokenType::SquareBracketClose });

    if (!this->peek({ TokenType::SquareBracketOpen }))
    {
        this->tracer.leave();
        return;
    }

    this->accept({ TokenType::SquareBracketOpen });
    this->parseAssignable();
    this->accept({ TokenType::SquareBracketClose });

    this->tracer.leave();
}

void Parser::parseLiteral()
{
    this->tracer.enter("Parsing literal");

    if (this->peek({ TokenType::SquareBracketOpen }))
    {
        this->parseMatrixLiteral();
        this->tracer.leave();
        return;
    }

    if (this->peek({ TokenType::Minus }))
    {
        this->accept({ TokenType::Minus });
    }

    this->accept({ TokenType::Infinity, TokenType::NumberLiteral });

    this->tracer.leave();
}

void Parser::parseMatrixLiteral()
{
    this->tracer.enter("Parsing matrix literal");

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

    this->tracer.leave();
}

void Parser::parseExpression(const Token& firstToken)
{
    this->tracer.enter("Parsing expression");

    this->parseMultiplicativeExpression(firstToken);

    while (this->peek({ TokenType::Plus, TokenType::Minus }))
    {
        this->accept({ TokenType::Plus, TokenType::Minus });
        this->parseMultiplicativeExpression();
    }

    this->tracer.leave();
}

void Parser::parseMultiplicativeExpression(const Token& firstToken)
{
    this->tracer.enter("Parsing multiplicative expression");

    this->parsePrimaryExpression(firstToken);

    while (this->peek({ TokenType::Multiply, TokenType::Divide, TokenType::Modulo }))
    {
        this->accept({ TokenType::Multiply, TokenType::Divide, TokenType::Modulo });
        this->parsePrimaryExpression();
    }

    this->tracer.leave();
}

void Parser::parsePrimaryExpression(const Token& firstToken)
{
    this->tracer.enter("Parsing primary expression");
    this->tracer.info(std::string("First Token type = ").append(tkom::modules::utils::getTokenTypeName(firstToken.type)));

    if (firstToken.type != TokenType::Undefined)
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

        this->tracer.leave();
        return;
    }

    if (this->peek({ TokenType::ParenthOpen }))
    {
        this->accept({ TokenType::ParenthOpen });
        this->parseExpression();
        this->accept({ TokenType::ParenthClose });

        this->tracer.leave();
        return;
    }

    if (this->peek({ TokenType::Identifier }))
    {
        this->parseVariable();

        this->tracer.leave();
        return;
    }

    this->parseLiteral();

    this->tracer.leave();
}

void Parser::parseCondition()
{
    this->tracer.enter("Parsing condition");

    this->parseAndCondition();

    while (this->peek({ TokenType::Or }))
    {
        this->accept({ TokenType::Or });
        this->parseAndCondition();
    }

    this->tracer.leave();
}

void Parser::parseAndCondition()
{
    this->tracer.enter("Parsing and condition");

    this->parseEqualityCondition();

    while (this->peek({ TokenType::And }))
    {
        this->accept({ TokenType::And });
        this->parseEqualityCondition();
    }

    this->tracer.leave();
}

void Parser::parseEqualityCondition()
{
    this->tracer.enter("Parsing equality condition");

    this->parseRelationalCondition();

    while (this->peek({ TokenType::Equality, TokenType::Inequality }))
    {
        this->accept({ TokenType::Equality, TokenType::Inequality });
        this->parseRelationalCondition();
    }

    this->tracer.leave();
}

void Parser::parseRelationalCondition()
{
    this->tracer.enter("Parsing relational condition");

    this->parsePrimaryCondition();

    while (this->peek({ TokenType::Less, TokenType::Greater, TokenType::LessOrEqual, TokenType::GreaterOrEqual }))
    {
        this->accept({ TokenType::Less, TokenType::Greater, TokenType::LessOrEqual, TokenType::GreaterOrEqual });
        this->parsePrimaryCondition();
    }

    this->tracer.leave();
}

void Parser::parsePrimaryCondition()
{
    this->tracer.enter("Parsing primary condition");

    if (this->peek({ TokenType::Negation }))
    {
        this->accept({ TokenType::Negation });
    }

    if (this->peek({ TokenType::ParenthOpen }))
    {
        this->accept({ TokenType::ParenthOpen });
        this->parseCondition();
        this->accept({ TokenType::ParenthClose });

        this->tracer.leave();
        return;
    }

    if (this->peek({ TokenType::Identifier }))
    {
        this->parseVariable();

        this->tracer.leave();
        return;
    }

    this->parseLiteral();

    this->tracer.leave();
}
