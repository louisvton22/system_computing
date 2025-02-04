#include "parser.h"




std::smatch tokens;
std::string calculate(std::string val);

std::unordered_map<std::string, Parser::COMMAND_TYPE> commandWords = {
    {"add", Parser::COMMAND_TYPE::C_ARITHMETIC},
    {"sub", Parser::COMMAND_TYPE::C_ARITHMETIC},
    {"neg", Parser::COMMAND_TYPE::C_ARITHMETIC},
    {"eq", Parser::COMMAND_TYPE::C_ARITHMETIC},
    {"gt", Parser::COMMAND_TYPE::C_ARITHMETIC},
    {"lt", Parser::COMMAND_TYPE::C_ARITHMETIC},
    {"and", Parser::COMMAND_TYPE::C_ARITHMETIC},
    {"or", Parser::COMMAND_TYPE::C_ARITHMETIC},
    {"not", Parser::COMMAND_TYPE::C_ARITHMETIC},
    {"push", Parser::COMMAND_TYPE::C_PUSH},
    {"pop", Parser::COMMAND_TYPE::C_POP},
    {"label", Parser::COMMAND_TYPE::C_LABEL},
    {"goto", Parser::COMMAND_TYPE::C_GOTO},
    {"if", Parser::COMMAND_TYPE::C_IF},
    {"function", Parser::COMMAND_TYPE::C_FUNCTION},
    {"return", Parser::COMMAND_TYPE::C_RETURN},
    {"call", Parser::COMMAND_TYPE::C_CALL}
};
Parser::Parser(std::string filename) {

    this->file = std::ifstream(filename);
    std::cout << "Parsing: " << filename << std::endl;
}

bool Parser::hasMoreCommands() {
    while (isspace(this->file.peek())) {
        this->file.get(); // Consume the whitespace character
    }
    
    // Check if we have reached the end of the file
    return this->file.peek() != EOF;
}

void Parser::advance() {

        std::cout << "Getting next line" << std::endl;
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
        std::regex pattern(R"(^(\S*)\s?(\S*)\s?(\S*)$)");
        std::regex_search(line,tokens,pattern);
        std::cout << line << std::endl;

}

Parser::COMMAND_TYPE Parser::commandType() {
    // find keyword and refer to map to determine type
    // std::string command = 
    Parser::COMMAND_TYPE command = commandWords.at(tokens.str(1));
    //std::cout << "Command Type: " << tokens.str(1) << std::endl;
    return command;
}

std::string Parser::arg1() {
    if (commandType() != Parser::C_RETURN)
    {
        return tokens.str(2);
    }
    return "";
}


std::string Parser::arg2() {
    std::vector<Parser::COMMAND_TYPE> binary = {
        Parser::C_PUSH,
        Parser::C_POP,
        Parser::C_FUNCTION,
    };

    if (std::find(binary.begin(), binary.end(), commandType()) != binary.end())
    {
        // +2 to account for space between arg1 and arg2
        return tokens.str(3);
    }
    return "";
}

