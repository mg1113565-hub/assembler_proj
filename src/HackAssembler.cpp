#include "../include/Code.h"
#include "../include/Parser.h"
#include "../include/SymbolTable.h"
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

  int romAddress = 0;

  // First pass: handling only label declarations
  while (parser.advance()) {
    std::string instructionType = parser.instructionType();
    if (instructionType == "L_INSTRUCTION") {
      symbolTable.addEntry(parser.symbol(), romAddress);
    } else {
      romAddress++;
    }
  }
  // reset file pointer to beginning of file for third pass
  parser.reset();

  // Second pass: handling A and C instructions
  int variableAddress =
      16; // Start allocating addresses for variables starting at 16
  while (parser.advance()) {
    std::cerr << parser.instructionType() << "  " << parser.symbol() << '\n';
    std::string instructionType = parser.instructionType();

    if (instructionType == "L_INSTRUCTION") {
      continue;
    }

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
    } else {
      // C_INSTRUCTION
      std::string dest = parser.dest();
      std::string comp = parser.comp();
      std::string jump = parser.jump();

      // Translate the C-instruction to binary
      binaryCode = "111" + code.comp(comp) + code.dest(dest) + code.jump(jump);
    }
    output << binaryCode << std::endl;
  }
}
