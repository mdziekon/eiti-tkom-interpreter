#include "FileReader.hpp"

#include "../error-handler/ErrorHandler.hpp"

using ErrorHandler = tkom::modules::ErrorHandler;
using FileReader = tkom::modules::FileReader;

FileReader::FileReader(const std::string& file):
handler(file)
{
    if (this->handler.fail())
    {
        ErrorHandler::error(std::string("Failed to open file: ").append(file));
    }

    this->currentLinePos = this->handler.tellg();
}

const char FileReader::nextSign()
{
    char sign;

    while (true)
    {
        sign = this->handler.get();

        if (sign == '\n' || sign == '\r')
        {
            if (this->previousSign != sign &&
                (this->previousSign == '\n' || this->previousSign == '\r')
            )
            {
                // CRLF or LFCR, just skip it
            }
            else
            {
                this->currentLineNo++;
                this->currentSignPos = 0;
                this->currentLinePos = this->handler.tellg();
            }

            this->previousSign = sign;
            continue;
        }

        this->previousSign = sign;
        this->currentSignPos++;

        return sign;
    }
}

void FileReader::rewind()
{
    this->handler.unget().unget();

    this->previousSign = this->handler.get();
    auto peek = this->handler.peek();

    if (peek == '\n' || peek == '\r')
    {
        this->previousSign = this->handler.get();
        return;
    }

    this->currentSignPos--;
}

const bool FileReader::hasFinished() const
{
    return this->handler.eof();
}

const unsigned int& FileReader::getCurrentLineNo() const
{
    return this->currentLineNo;
}

const unsigned int& FileReader::getCurrentSignPos() const
{
    return this->currentSignPos;
}

const std::streampos FileReader::getCurrentLinePos() const
{
    return this->currentLinePos;
}

const std::string FileReader::getLine(const std::streampos& linePos)
{
    const std::streampos currentPos = this->handler.tellg();
    std::string line;

    this->handler.seekg(linePos);

    std::getline(this->handler, line);

    this->handler.seekg(currentPos);

    return line;
}
