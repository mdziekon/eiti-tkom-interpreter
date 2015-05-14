#ifndef TKOM_MODULES_PARSER_HPP
#define TKOM_MODULES_PARSER_HPP

namespace tkom { namespace modules
{
    class Lexer;

    class Parser
    {
    public:
        Parser(Lexer& lexer);

        void parse();

    private:
        Lexer& lexer;
    };
}}

#endif
