#ifndef PARSER_H
#define PARSER_H

#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <iostream>
#include "symbolTable.h"
#include <regex>
class Parser {

private:
    

public:

    enum COMMAND_TYPE {
        L_COMMAND, // Label/psuedo command
        A_COMMAND, // 
        C_COMMAND
    };

    Parser(char* filename);
    // Checks if there are more commands in the input
    bool hasMoreCommands();
    // Reads next command from the onput and makes it current command. Should only be called if hasMoreCommands() is true
    void advance();
    //Returns the type of the current command from enum COMMAND_TYPE
    COMMAND_TYPE commandType();
    // Returns the symbol or decimal Xxx of the current command. Called only if A_COMMAND or L_COMMAND
    std::string symbol();
    // Returns the dest mneumonic in the current C-Command. Only called if command type is C_COMMAND
    std::string dest();
    // Returns the comp mneumonic in the current C-Command. Only called if command type is C_COMMAND
    std::string comp();
    // Returns the jump mneumonic in the current C-Command. Only called if command type is C_COMMAND
    std::string jump();

    std::string toString();
};

#endif // PARSER_H