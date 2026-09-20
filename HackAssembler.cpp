#include "Code.h"
#include "Parser.h"
#include "SymbolTable.h"
#include <iostream>

int main(int argc, char *argv[])
{

  if (argc != 2)
  {
    std::cerr << "Usage: HackAssembler <inputfile>" << std::endl;
    return 1;
  }

  std::string inputFile = argv[1];
  std::ifstream input(inputFile);
  if (!input.is_open())
  {
    std::cerr << "Error: Could not open input file " << inputFile << std::endl;
    return 1;
  }
  std::string outputFile =
      inputFile.substr(0, inputFile.find_last_not_of(".asm")) + ".hack";
  std::ofstream output(outputFile);
  if (!output.is_open())
  {
    std::cerr << "Error: Could not open output file " << outputFile
              << std::endl;
    return 1;
  }

  Parser parser(input);
  SymbolTable symbolTable;
  Code code;

  // First pass: get rid of the white space
  while (parser.hasMoreLines())
  {
    parser.advance();
  }

  // reset file pointer to beginning of file for second pass
  input.clear();
  input.seekg(0, std::ios::beg);

  int variableAddress = 16; // Start allocating addresses for variables at 16

  // Second pass: handling only label declarations
  while (parser.hasMoreLines())
  {
    std::string instructionType = parser.instructionType();
    if (instructionType == "L_INSTRUCTION")
    {
      std::string symbol = parser.symbol();
      symbolTable.addEntry(symbol, variableAddress);
    }
    parser.advance();
  }
  // reset file pointer to beginning of file for third pass
  input.clear();
  input.seekg(0, std::ios::beg);

  // Third pass: handling A and C instructions
  while (parser.hasMoreLines())
  {
    parser.advance();
    std::string instructionType = parser.instructionType();
    // translate A instructions
    if (instructionType == "A_INSTRUCTION")
    {
      std::string symbol = parser.symbol();
      int address;
      if (symbolTable.contains(symbol))
      {
        address = symbolTable.getAddress(symbol);
      }
      else
      {
        address = variableAddress;
        symbolTable.addEntry(symbol, variableAddress);
        variableAddress++;
      }
    }

    // translate C instructions
    if (instructionType == "C_INSTRUCTION")
    {
      std::string symbol = parser.symbol();
      int address;
      if (symbolTable.contains(symbol))
      {
        address = symbolTable.getAddress(symbol);
      }
      else
      {
        address = variableAddress;
        symbolTable.addEntry(symbol, variableAddress);
        variableAddress++;
      }
      std::string dest = dest();
      std::string comp = comp();
      std::string jump = jump();

      std::string bin = code.dest(dest);
      bin += code.comp(comp);
      bin += code.jump(jump);
    }
  }
