
#include "parser.h"
#include "code.h"
#include <filesystem>
int main(int argc, char* argv[])
{
    std::string filepath = argv[1];
    std::filesystem::recursive_directory_iterator directory(filepath);

    try {
        std::cout << "Getting Sys.vm " << std::endl;
        Parser p = Parser(filepath + "/Sys.vm");
        std::filesystem::path dirPath(filepath);
        Code c = Code(dirPath.string() + "/" + dirPath.stem().string() + ".asm");
        while (p.hasMoreCommands()) {
                    p.advance();
                    std::cout << "Command type: " << p.commandType() << std::endl;
                    c.writeLine(p.commandType(), p.tokens[1], p.arg1(), p.arg2());
                }
        for (const auto& filename : directory) {
            if (filename.path().extension() == ".vm" && filename.path().string().find("Sys.vm") == std::string::npos ) {
                p = Parser(filename.path().string());
                while (p.hasMoreCommands()) {
                    p.advance();
                    std::cout << "Command type: " << p.commandType() << std::endl;
                    c.setFileName(filename.path());
                    c.writeLine(p.commandType(), p.tokens[1], p.arg1(), p.arg2());
                }
            }
        }
        c.Close();
    } catch ( const std::filesystem::filesystem_error e) {
        std::cerr << "Filesystem error " << e.what() << std::endl;
    }
    
    return 0;
}