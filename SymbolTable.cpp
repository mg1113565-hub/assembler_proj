#include "SymbolTable.h"
#include <iostream>

SymbolTable::SymbolTable()
{
    std::string base = "R";
    for (int i = 0; i < 16; ++i)
    {
        base += std::to_string(i);
        (*this).addEntry(base, i);
        std::cout << base << " " << i << '\n';
        base.erase(1);
        i++;
    }

    (*this).addEntry("SCREEN", 16384);
    (*this).addEntry("KBD", 24576);
    (*this).addEntry("SP", 0);
    (*this).addEntry("LCL", 1);
    (*this).addEntry("ARG", 2);
    (*this).addEntry("THIS", 3);
    (*this).addEntry("THAT", 4);
}

bool SymbolTable::contains(std::string symbol)
{

    if (table.find(symbol) != table.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}

void SymbolTable::addEntry(std::string symbol, int address)
{
    if (!((*this).contains(symbol)))
    {
        table[symbol] = address;
    }
    // do nothing if entry already exists
}

// defo need to check contains before calling this
int SymbolTable::getAddress(std::string symbol)
{
    int result{};

    if ((*this).contains(symbol))
    {
        result = table[symbol];
    }

    // returning 0 is the flag for not valid since we cant assign any labels or variable to 0
    return result;
}