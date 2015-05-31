#ifndef TKOM_MODULES_FILEREADER_HPP
#define TKOM_MODULES_FILEREADER_HPP

#include <fstream>
#include <string>

namespace tkom { namespace modules
{
    class FileReader
    {
    public:
        FileReader(const std::string& file);

        const char nextSign();
        void rewind();
        const bool hasFinished() const;
        const unsigned int& getCurrentLineNo() const;
        const unsigned int& getCurrentSignPos() const;
        const std::streampos getCurrentLinePos() const;
        const std::string getLine(const std::streampos& linePos);

    private:
        std::ifstream handler;

        unsigned int currentLineNo = 1;
        unsigned int currentSignPos = 0;
        std::streampos currentLinePos;
        char previousSign = 0;
    };
}}

#endif
