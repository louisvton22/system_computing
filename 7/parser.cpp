#include "parser.h"



Parser::Parser(std::string filename) {

    this->file = std::ifstream(filename);
}

bool Parser::hasMoreCommands() {
    
}

void Parser::advance() {
    while (getline(this->file, this->line))
    {
        
        // break if valid command found
    }
}

std::string Parser::arg1() {
    
}


std::string Parser::arg2() {}