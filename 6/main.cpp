#include <iostream>

#include "parser.h"
#include "code.h"
int main(int argc, char* argv[] ) {
    Parser parser = Parser(argv[1]);
    Code coder = Code();
    while (parser.hasMoreCommands())
    {
        parser.advance();
        std::string binaryCommand;
        
        if (parser.commandType() == Parser::A_COMMAND)
        {
            // A instruction bit
            binaryCommand += "0";

            // take symbol and convert to integer then binary
            binaryCommand += std::bitset<15>(parser.aValue()).to_string();
        } else {

            // C instruction bit
            binaryCommand += "1";
            // get comp binary translation
            binaryCommand += coder.comp(parser.comp()).to_string();

            // get binary destination only if "=" exists in mneumonic
            binaryCommand += parser.comp().find('=') == std::string::npos ? "000" : coder.dest(parser.dest()).to_string();
            binaryCommand += coder.jump(parser.jump()).to_string();
        }
        std::cout << binaryCommand << std::endl;
        std::cout << parser.toString() << std::endl;
    }

    // std::ifstream file(argv[1]);
    // std::string line;
    // while(std::getline(file, line)) {
    //     std::cout << line << std::endl;
    // }
    return 0;
}
