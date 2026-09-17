
class Parser
{

public:
    Parser(const std::string &filename);

    bool hasMoreLines();

    void advance();

    std::string instructionType();

    std::string symbol();

    std::string dest();

    std::string comp();

    std::string jump();

    ~Parser();

private:
    std::ifstream file;
    std::string currInstruction;
    std::string currInstructionType;
};