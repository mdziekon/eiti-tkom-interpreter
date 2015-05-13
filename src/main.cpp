#include <vector>
#include <string>

#include "Interpreter.hpp"

int main(int argc, char** argv)
{
    std::vector<std::string> arguments(argv + 1, argv + argc);

    tkom::Interpreter app(arguments);
}
