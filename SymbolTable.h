#include <string>
#include <unordered_map>

class SymbolTable
{
public:
    SymbolTable();

    // Adds <symbol, address> to the table
    void addEntry(std::string symbol, int address);

    // checks if symbol exists in the table
    bool contains(std::string symbol);

    // Returns the adderss associated with symbol
    int getAddress(std::string symbol);

private:
    std::unordered_map<std::string, int> table;
}