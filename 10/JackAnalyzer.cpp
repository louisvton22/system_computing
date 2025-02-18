

#include <iostream>
#include <fstream>
#include <filesystem>
#include "JackTokenizer.h"
#include "CompilationEngine.h"


int main(int argc, char* argv[]) {
    std::filesystem::path filename(argv[1]);

    JackTokenizer tokenizer = JackTokenizer(filename.string());

    while (tokenizer.hasMoreTokens()) {
        tokenizer.advance();
    }

    
} 