#include "code.h"


Code::Code() {

}


void Code::setFileName(std::string fileName) {
    this->outfile = std::ofstream(fileName);
    std::cout << "Parsing vm file: " << fileName << " has started" <<  std::endl;
}

void Code::writeArithmetic(std::string command) {
    
}

