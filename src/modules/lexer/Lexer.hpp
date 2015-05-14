#ifndef TKOM_MODULES_LEXER_HPP
#define TKOM_MODULES_LEXER_HPP

#include "../file-reader/FileReader.hpp"
#include "../utils/Token.hpp"

using Token = tkom::modules::utils::Token;

namespace tkom { namespace modules
{
    class Lexer
    {
    public:
        Lexer(const std::string& file);

        const Token nextToken();

    private:
        tkom::modules::FileReader reader;
    };
}}

#endif
