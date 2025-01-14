#include <iostream>
#include <filesystem>
#include "parser.h"
#include "code.h"
int main(int argc, char* argv[] ) {
    std::cout << "Beginning parsing" << std::endl;
    Parser parser = Parser(argv[1]);

    // std::ifstream file(argv[1]);
    // std::string line;
    // while(std::getline(file, line)) {
    //     std::cout << line << std::endl;
    // }

    std::filesystem::path fileName(argv[1]);
    std::ofstream outfile(fileName.stem().string() + ".txt");

    outfile << parser.parse();
    outfile.close();
    std::cout << "Input: " << fileName.filename().string() <<"\nOutput: " << fileName.stem().string() + ".txt" << " parsed into Hack binary." <<std::endl;
    return 0;
}
