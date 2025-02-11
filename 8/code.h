#ifndef CODE_H
#define CODE_H

#include <fstream>
#include "parser.h"
#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <filesystem>
class Code {
    public:
        Code(std::string fileName);
        //Informs the code writer that the translation of a VM file has started
        void setFileName(std::string fileName);
        //Writes the assembly code for an arithmetic command
        void writeArithmetic(std::string command);
        //Writes the assembly code of the given command, where command is PUSH or POP
        void WritePushPop(Parser::COMMAND_TYPE c, std::string segment, int index);
        //Closes the output file;
        void Close();
        // writes bootstrap code to initialize VM
        void writeInit();

        // writes assembly code that effects the label command
        void writeLabel(std::string label);

        // writes assembly code that effects the goto command
        void writeGoto(std::string label);

        // writes assembly code that effects the if-goto command
        void writeIf(std::string label);

        // writes assembly code that effects the call command
        void writeCall(std::string functionName, unsigned int numArgs);

        // writes assembly code that effects the return command
        void writeReturn();

        // writes assembly code that effects the function command.
        void writeFunction(std::string functionName, unsigned int numLocals);


        // Identifies command type and calls corresponding assembly code writing function
        void writeLine(Parser::COMMAND_TYPE ct, std::string command, std::string arg1, std::string arg2);

    private:
        std::ofstream outfile;
        std::filesystem::path filename;
};

#endif //CODE_H