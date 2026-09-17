#include "Parser.h"

Parser::Parser(const std::string &filename) : file(filename)
{
}

bool Parser::hasMoreLines()
{
    return file.peek() != std::char_traits<char>::eof();
}

// only call if hasMoreLines is true
void Parser::advance()
{
    do
    {

        std::getline(file, currInstruction);

        auto it = currInstruction.find("//");
        if (it != std::string::npos)
        {
            currInstruction.erase(it);
        }
        currInstruction.erase(std::remove(currInstruction.begin(), currInstruction.end(), ' '), currInstruction.end());
    } while (currInstruction.empty() && hasMoreLines());
}

std::string Parser::instructionType()
{
    if (currInstruction[0] == '@')
    {
        currInstructionType = "A_INSTRUCTION" return "A_INSTRUCTION";
    }
    else if (currInstruction[0] == '(')
    {
        currInstructionType = "L_INSTRUCTION" return "L_INSTRUCTION";
    }
    else
    {
        currInstructionType = "C_INSTRUCTION" return "C_INSTRUCTION";
    }
}

std::string Parser::symbol()
{
    std::string result;
    if (currInstructionType == "A_INSTRUCTION")
    {
        result = currInstruction.substr(1, currInstruction.length() - 1);
    }
    else
    {
        result = currInstruction.substr(1, currInstruction.length() - 2);
    }
    return result;
}

std::string Parser::dest()
{
    auto it = currInstruction.find("=");
    if (it == std::string::npos)
    {
        return null;
    }

    return currInstruction.substr(0, it);
}

std::string Parser::comp()
{
    auto startPos = currInstruction.find("=");
    auto endPos = currInstruction.find(";");

    size_t start;
    size_t end;
    if (startPos == std::string::npos)
    {
        start = 0;
    }
    else
    {
        start = startPos + 1;
    }

    if (endPos == std::string::npos)
    {
        // if no end cap found then just count till end of string
        end = currInstruction.length();
    }
    else
    {
        end = endPos;
    }

    return currInstruction.substr(start, end - start);
}

std::string Parser::jump()
{
    auto it = currInstruction.find(";");

    if (it == std::string::npos)
    {
        return "null"
    }
    return currInstruction.substr(it + 1);
}

~Parser::Parser()
{
    if (file.is_open())
    {
        file.close();
    }
}

int main()
{
    // Your code here
    return 0;
}
