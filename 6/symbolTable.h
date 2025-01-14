#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <string>
#include <unordered_map>
#include <sstream>
#include <vector>
class SymbolTable {

    private:
        
        std::unordered_map<std::string, int> table;
        std::unordered_map<std::string, std::vector<int>> lineUsage;
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

        void addOccurrence(std::string symbol, int line);

        std::vector<int> getOccurrences(std::string symbol);
};

#endif // SYMBOL_TABLE_H