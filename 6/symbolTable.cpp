#include "symbolTable.h"

#include <vector>

SymbolTable::SymbolTable() {
    this->size = 16;
    // initial labels
    this->table["SP"] = 0;
    this->table["LCL"] = 1;
    this->table["ARG"] = 2;
    this->table["THIS"] = 3;
    this->table["THAT"] = 4;
    this->table["SCREEN"] = 16384;
    this->table["KEYBOARD"] = 24576;
    std::string reg = "R";
    for (int i = 0; i < 16; i++) {
        this->table[reg + std::to_string(i)] = i;
    }
}


void SymbolTable::addEntry(std::string symbol, int address) {
    this->table[symbol] = address;
    size++;
    // figure out error handling if we've initialized too many variables;
}

bool SymbolTable::contains(std::string symbol) {
    return this->table.find(symbol) != this->table.end();
}

int SymbolTable::getAddress(std::string symbol) {
    if (this->contains(symbol))
    {
        return this->table[symbol];
    }
    return -1;
}

int SymbolTable::getSize() {
    return this->size;
}


std::string SymbolTable::toString() {
    std::stringstream ss; // Use stringstream to construct the string

    ss << "{ ";
    for (const auto& pair : this->table) {
        ss << pair.first << ": " << pair.second << ", "; // Format each key-value pair
    }
    std::string result = ss.str(); // Get the string from stringstream

    // Remove the trailing comma and space, if present
    if (result.size() > 2) {
        result.pop_back();
        result.pop_back();
    }
    result += " }";

    return result;
}

void SymbolTable::addOccurrence(std::string symbol, int line) {
    this->lineUsage[symbol].push_back(line);
}

std::vector<int> SymbolTable::getOccurrences(std::string symbol) {
    return this->lineUsage[symbol];
}