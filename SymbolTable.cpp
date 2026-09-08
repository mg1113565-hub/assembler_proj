#include "SymbolTable.h"

SymbolTable::SymbolTable()
{
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

    if (!((*this).contains(symbol)))
    {
        result = table[symbol];
    }

    // returning 0 is the flag for not valid since we cant assign any labels or variable to 0
    return result;
}