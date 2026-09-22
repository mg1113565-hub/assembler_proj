#include "Code.h"
#include "Parser.h"
#include "SymbolTable.h"
#include <bitset>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

int main(int argc, char *argv[]) {

  if (argc != 2) {
    std::cerr << "Usage: HackAssembler <inputfile>" << std::endl;
    return 1;
  }

  std::string inputFile = argv[1];

  std::string outputFile =
      inputFile.substr(0, inputFile.rfind(".asm")) + ".hack";
  std::ofstream output(outputFile);
  if (!output.is_open()) {
    std::cerr << "Error: Could not open output file " << outputFile
              << std::endl;
    return 1;
  }

  Parser parser(inputFile);
  SymbolTable symbolTable;
  Code code;

  // First pass: get rid of the white space
  while (parser.hasMoreLines()) {
    parser.advance();
  }

  // reset file pointer to beginning of file for second pass
  parser.reset();

  int variableAddress = 16; // Start allocating addresses for variables at 16

  // Second pass: handling only label declarations
  while (parser.hasMoreLines()) {
    std::string instructionType = parser.instructionType();
    if (instructionType == "L_INSTRUCTION") {
      std::string symbol = parser.symbol();
      symbolTable.addEntry(symbol, variableAddress);
      variableAddress++; // Increment variableAddress for the next available
                         // address
    }
    parser.advance();
  }
  // reset file pointer to beginning of file for third pass
  parser.reset();

  // Third pass: handling A and C instructions
  while (parser.hasMoreLines()) {
    std::string instructionType = parser.instructionType();
    std::string binaryCode;

    if (instructionType == "A_INSTRUCTION") {
      std::string symbol = parser.symbol();
      int address = 0;
      if (symbolTable.contains(symbol)) {
        address = symbolTable.getAddress(symbol);
      } else {
        if (isdigit(symbol[0])) {
          address = std::stoi(symbol);
        } else {
          address = variableAddress;
          symbolTable.addEntry(symbol, variableAddress);
          variableAddress++;
        }
      }
      std::bitset<16> code(address);
      // translate the A-instruction to binary
      binaryCode = code.to_string();
      parser.advance();
    }

    // translate C instructions
    if (instructionType == "C_INSTRUCTION") {
      std::string dest = parser.dest();
      std::string comp = parser.comp();
      std::string jump = parser.jump();

      // Translate the C-instruction to binary
      binaryCode = "111" + code.comp(comp) + code.dest(dest) + code.jump(jump);
      std::cout << binaryCode << std::endl;
      parser.advance();
    }
    output << binaryCode << std::endl;
  }
}
