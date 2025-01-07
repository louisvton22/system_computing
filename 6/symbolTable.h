#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <string>
#include <unordered_map>
#include <sstream>
class SymbolTable {

    private:
        
        std::unordered_map<std::string, int> table;
        int size;
    public:
        SymbolTable();
        // Adds the pair:(symbol, address) to the symbol table
        void addEntry(std::string symbol, int address);
        // Checks if the symbol table contains symbol
        bool contains(std::string symbol);
        // Returns the address location associated with symbol
        int getAddress(std::string symbol);

        int getSize();

        std::string toString();
};

#endif // SYMBOL_TABLE_H