
#include "parser.h"
#include "code.h"
#include <filesystem>
int main(int argc, char* argv[])
{
    std::string filepath = argv[1];
    std::filesystem::recursive_directory_iterator directory(filepath);

    try {
        for (const auto& filename : directory) {
            if (filename.path().extension() == ".vm") {
                Parser p = Parser(filename.path().string());
                std::filesystem::path fileName(filename);
                Code c = Code(filename.path().parent_path().string() + "/" + filename.path().stem().string() + ".asm");
                while (p.hasMoreCommands()) {
                p.advance();
                if (p.commandType() == Parser::COMMAND_TYPE::C_ARITHMETIC){
                    c.writeArithmetic(p.line);
                } else {
                    c.WritePushPop(p.commandType(), p.arg1(), std::stoi(p.arg2()));
                }
                }
                c.Close();
            }
        }
    } catch ( const std::filesystem::filesystem_error e) {
        std::cerr << "Filesystem error " << e.what() << std::endl;
    }
    
    return 0;
}