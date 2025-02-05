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
    private:
        std::ofstream outfile;
        std::filesystem::path filename;
};

#endif //CODE_H