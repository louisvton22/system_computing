#include <iostream>

#include "parser.h"
#include "symbolTable.h"
int main(int argc, char* argv[] ) {
    Parser parser = Parser(argv[1]);
    while (parser.hasMoreCommands())
    {
        parser.advance();
        //std::cout << parser.toString() << std::endl;
    }
    std::cout << parser.toString()<< std::endl;
}
