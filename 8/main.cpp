
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
                    std::cout << "Command type: " << p.commandType() << std::endl;
                    c.writeLine(p.commandType(), p.tokens[1], p.arg1(), p.arg2());
                }
                c.Close();
            }
        }
    } catch ( const std::filesystem::filesystem_error e) {
        std::cerr << "Filesystem error " << e.what() << std::endl;
    }
    
    return 0;
}