#ifndef PARSER_H
#define PARSER_H


#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>
class Parser
{
    
    public:
        enum COMMAND_TYPE {
                C_ARITHMETIC,
                C_PUSH,
                C_POP,
                C_LABEL,
                C_GOTO,
                C_IF,
                C_FUNCTION,
                C_RETURN,
                C_CALL
            };
        // Constructor opens file stream and prepares it for parsing
        Parser(std::string filename);
        // Checks if there are more commands in the input
        bool hasMoreCommands();
        // Reads the next command from the input only if hasMoreCommands() is true
        void advance();
        // Returns the first argument in the current VM command. Should not be called if command type is C_RETURN
        std::string arg1();
        // Returns the second argument in the current VM command. Only called on bionary commands (C_PUSH, C_POP, C_FUNCTION, C_CALL)
        std::string arg2();
        // Returns the type of the current command from enum COMMAND_TYPE
        COMMAND_TYPE commandType();

    private:
        std::ifstream file;
        std::string line;


};

#endif //PARSER_H