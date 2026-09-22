#include <fstream>
#include <iostream>
#include <string>

class Parser {

public:
  Parser(const std::string &filename);

  void reset();

  bool hasMoreLines();

  bool advance();

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