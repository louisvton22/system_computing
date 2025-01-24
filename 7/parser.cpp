#include "parser.h"



std::unordered_map<std::string, Parser::COMMAND_TYPE> commandWords = {
    {"add", Parser::C_ARITHMETIC},
    {"sub", Parser::C_ARITHMETIC},
    {"neg", Parser::C_ARITHMETIC},
    {"eq", Parser::C_ARITHMETIC},
    {"gt", Parser::C_ARITHMETIC},
    {"lt", Parser::C_ARITHMETIC},
    {"and", Parser::C_ARITHMETIC},
    {"or", Parser::C_ARITHMETIC},
    {"not", Parser::C_ARITHMETIC},
    {"push", Parser::C_PUSH},
    {"pop", Parser::C_POP},
    {"label", Parser::C_LABEL},
    {"goto", Parser::C_GOTO},
    {"if", Parser::C_IF},
    {"function", Parser::C_FUNCTION},
    {"return", Parser::C_RETURN},
    {"call", Parser::C_CALL}
};
Parser::Parser(std::string filename) {

    this->file = std::ifstream(filename);
}

bool Parser::hasMoreCommands() {
    char c = this->file.peek();
    return c != EOF;
}

void Parser::advance() {

    if (hasMoreCommands) {
        while (getline(this->file, this->line))
        {   
            // continue if empty line or comment found
            if (this->line.substr(0, 2) == "//" || this->line.empty()) {
                continue;
            } else {
            // break if valid command found
                break;
            }
        }
    }

}

Parser::COMMAND_TYPE Parser::commandType() {}

std::string Parser::arg1() {
    if (commandType() != Parser::C_RETURN)
    {
        return this->line.substr(0, this->line.find(' '));
    }
}


std::string Parser::arg2() {
    std::vector<Parser::COMMAND_TYPE> binary = {
        Parser::C_PUSH,
        Parser::C_POP,
        Parser::C_FUNCTION,
        Parser::C_CALL
    };

    if (std::find(binary.begin(), binary.end(), commandType()) != binary.end())
    {
        // +2 to account for space between arg1 and arg2
        return this->line.substr(arg1().length() + 2);
    }
}