#include "Code.h"

Code::Code()
{

    compTbl["0"] = "0101010";
    compTbl["1"] = "0111111";
    compTbl["-1"] = "0111010";
    compTbl["D"] = "0001100";
    compTbl["A"] = "0110000";
    compTbl["!D"] = "0001101";
    compTbl["!A"] = "0110001";
    compTbl["-D"] = "0001111";
    compTbl["-A"] = "0110011";
    compTbl["D+1"] = "0011111";
    compTbl["A+1"] = "0110111";
    compTbl["D-1"] = "0001110";
    compTbl["A-1"] = "0110010";
    compTbl["D+A"] = "0000010";
    compTbl["D-A"] = "0010011";
    compTbl["A-D"] = "0000111";
    compTbl["D&A"] = "0000000";
    compTbl["D|A"] = "0010101";
    compTbl["M"] = "1110000";
    compTbl["!M"] = "1110001";
    compTbl["-M"] = "1110011";
    compTbl["M+1"] = "1110111";
    compTbl["M-1"] = "1110010";
    compTbl["D+M"] = "1000010";
    compTbl["D-M"] = "1010011";
    compTbl["M-D"] = "1000111";
    compTbl["D&M"] = "1000000";
    compTbl["D|M"] = "1010101";

    jumpTbl["null"] = "000";
    jumpTbl["JGT"] = "001";
    jumpTbl["JEQ"] = "010";
    jumpTbl["JGE"] = "011";
    jumpTbl["JLT"] = "100";
    jumpTbl["JNE"] = "101";
    jumpTbl["JLE"] = "110";
    jumpTbl["JMP"] = "111";

    destTbl["null"] = "000";
    destTbl["M"] = "001";
    destTbl["D"] = "010";
    destTbl["DM"] = "011";
    destTbl["A"] = "100";
    destTbl["AM"] = "101";
    destTbl["AD"] = "110";
    destTbl["ADM"] = "101";
}

std::string Code::dest(std::string destInstr)
{
    return destTbl[destInstr];
}

std::string Code::comp(std::string compInstr)
{
    return compTbl[compInstr];
}

std::string Code::jump(std::string jumpInstr)
{
    return jumpTbl[jumpInstr];
}