#include <string>
#include <unordered_map>

class Code {
public:
  std::string dest(std::string destInstr) const;

  std::string comp(std::string compInstr) const;

  std::string jump(std::string jumpInstr) const;

  Code();

private:
  std::unordered_map<std::string, std::string> compTbl;
  std::unordered_map<std::string, std::string> jumpTbl;
  std::unordered_map<std::string, std::string> destTbl;
};