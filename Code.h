
class Code
{
public:
    std::string dest(std::string destInstr);

    std::string comp(std::string compInstr);

    std::string jump(std::string jumpInstr);

    Code();
    Code ~;

private:
    std::unordered_map<std::string, std::string> compTbl;
    std::unordered_map<std::string, std::string> jumpTbl;
    std::unordered_map<std::string, std::string> destTbl;
};