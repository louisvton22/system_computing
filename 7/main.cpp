
#include "parser.h"
#include "code.h"
#include <filesystem>
int main(int argc, char* argv[])
{
    std::string filename = argv[1];

    if(!std::filesystem::exists(filename)) {
        std::cerr << "File at " << filename <<" Not Found" << std::endl;
        return 1;
    }
    Parser p = Parser(filename);
    std::filesystem::path fileName(filename);
    Code c = Code(fileName.stem().string() + ".asm");
    while (p.hasMoreCommands()) {
        p.advance();
        if (p.commandType() == Parser::COMMAND_TYPE::C_ARITHMETIC){
            c.writeArithmetic(p.line);
        } else {
            c.WritePushPop(p.commandType(), p.arg1(), std::stoi(p.arg2()));
        }
    }
    c.Close();
    return 0;
}