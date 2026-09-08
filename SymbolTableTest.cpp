#include <cassert>
#include <iostream>
#include "SymbolTable.h"

int main()
{
    SymbolTable table;

    // Test 1: predefined symbols exist after construction
    assert(table.contains("SP"));
    assert(table.getAddress("SP") == 0);
    assert(table.contains("SCREEN"));
    assert(table.getAddress("SCREEN") == 16384);

    // Test 2: a symbol that hasn't been added yet
    assert(!table.contains("myVar"));

    // Test 3: after adding, it should now exist
    table.addEntry("myVar", 16);
    assert(table.contains("myVar"));
    assert(table.getAddress("myVar") == 16);

    std::cout << "All SymbolTable tests passed!\n";
    return 0;
}