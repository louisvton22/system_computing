#include "code.h"

std::string push();
std::string pop();
std::unordered_map<std::string, std::string> segments = {
    {"local", "LCL"},
    {"argument", "ARG"},
    {"this", "THIS"},
    {"that", "THAT"},
    {"temp", "R5"},
    {"pointer", "R3"}
};
Code::Code(std::string fileName) {
    setFileName(fileName);
}


void Code::setFileName(std::string fileName) {
    this->outfile = std::ofstream(fileName);
    std::cout << "Parsing vm file: " << fileName << " has started" <<  std::endl;
}

void Code::writeArithmetic(std::string command) {
    std::string assemblyCommand;
    if (command == "add")
    {
        this-> outfile << pop()
                       << "D=M\n"
                       << pop()
                       << "D=D+M\n"
                       << push();
    } else if (command == "sub") {
        this->outfile << pop()
                      << "D=-M\n"
                      << pop()
                      << "D=D+M\n"
                      << push();
    } else if (command == "neg") {
        this->outfile << pop()
                      << "D=-D\n"
                      << push();    
    } else if (command == "eq") {
        this->outfile << pop()
                      << "D=M\n"
                      << pop()
                      << "D=D-M\n"
                      << push();
    } else if (command == "lt") {
        this->outfile << pop()
                      << "D=M\n"
                      << pop()
                      << "D=D-M\n"
                      << "@Less\n"
                      << "D;JLT\n"
                      << "@Great\n"
                      << "D;JGE\n"
                      << "(Less)\n"
                      << "@1\n"
                      << "D=-A\n"
                      << push()
                      << "@END\n"
                      << "0;JEQ\n"
                      << "(Great)\n"
                      << "@0\n"
                      << "D=A\n"
                      << "(END)\n"
                      << push();


    } else if (command == "gt") {
        this->outfile << pop()
                      << "D=M\n"
                      << pop()
                      << "D=D-M\n"
                      << "@Less\n"
                      << "D;JLE\n"
                      << "@Great\n"
                      << "D;JGT\n"
                      << "(Less)\n"
                      << "@0\n"
                      << "D=A\n"
                      << "@END\n"
                      << "0;JEQ\n"
                      << "(Great\n)"
                      << "@1\n"
                      << "D=-A\n"
                      << "(END)\n"
                      << push();
    } else if (command == "eq") {
        this->outfile << pop()
                      << "D=M\n"
                      << pop()
                      << "D=D-M\n"
                      << "@Not_Equal\n"
                      << "D;NEQ\n"
                      << "@Equal\n"
                      << "D;JEQ\n"
                      << "(Not_Equal)\n"
                      << "@0\n"
                      << "D=A\n"
                      << "@END\n"
                      << "0;JEQ\n"
                      << "(Equal)\n"
                      << "@1\n"
                      << "D=-A\n"
                      << "(END)\n"
                      << push();
    } else if (command == "and") {
            this->outfile << pop()
                          << "D=M\n"
                          << pop()
                          << "D=D&M\n"
                          << "@and.t\n"
                          << "D;JGT\n"
                          << "@and.f\n"
                          << "D;JLE\n"
                          << "(and.t\n)"
                          << "@1\n"
                          << "D=-A\n"
                          << "(and.f)\n"
                          << "@0\n"
                          << "D=A\n"
                          << push();
    } else if (command == "or") {
        this->outfile << pop()
                          << "D=M\n"
                          << pop()
                          << "D=D|M\n"
                          << "@and.t\n"
                          << "D;JGT\n"
                          << "@and.f\n"
                          << "D;JLE\n"
                          << "(and.t)\n"
                          << "@1\n"
                          << "D=-A\n"
                          << "(and.f)\n"
                          << "@0\n"
                          << "D=A\n"
                          << push();
    } else if (command == "not") {
        this->outfile << pop()
                      << "D=!M\n"
                      << push();
    }
}


void Code::WritePushPop(Parser::COMMAND_TYPE c, std::string segment, int index) {
    std::ostringstream command;
    auto segmentReg = segments.find(segment);
    switch(c) {
        case(Parser::C_PUSH): {
            if (segment == "constant")
            {
                command << "@" << index << "\n"
                << "D=A\n"
                << push();
                this->outfile << command.str();
                break;
            }
            // push segment[index] onto the stack
            command 
                 << "@" << index << "\n" // set constant index
                 << "D=A\n"
                 << "M=D\n"
                 << "@" << segmentReg->second << "\n"
                 << "D=D+M\n" // segment + index
                 << "@D\n" // go to segment + index
                 << "D=M\n"   // store segment + index value
                 << "@SP\n" // go to stack pointer
                 << "M=D\n" // set value to D
                 << "D=A+1\n" // increment stack value
                 << "@SP\n" // go to stack pointer
                 << "M=D\n"; // update stack pointer index
            this->outfile << command.str();
            break;
        }
        case(Parser::C_POP): {
            // pop off the stack and put in segment[index]
            command 
                 << "@" << index << "\n" // set constant index
                 << "D=A\n"
                 << "@" << segmentReg->second << "\n"
                 << "D=D+A\n" // index + segment
                 << "@R13\n"
                 << "M=D\n"
                 << "@SP\n"
                 << "M=M-1\n"
                 << "@M\n"
                 << "D=M\n"
                 << "@R13\n"
                 << "@M\n"
                 << "M=D\n";
            this->outfile << command.str();
            break;
        }
    };
}

// pushes a constant stored in D onto the stack
std::string push()
{
    std::ostringstream assembly;
    assembly << "@SP\n" // go to register 0
             <<  "@M\n" // go to top of stack
             <<   "M=D\n" // set top of stack to D
             <<   "@SP\n"
             <<   "M=M+1\n";
    return assembly.str();
}

// moves stack pointer 1 back and sets Register A to memory address of current top of stack
std::string pop()
{
    std::ostringstream assembly;
    assembly << "@SP\n" // go to stack pointer
             << "M=M-1\n" // decrease stack pointer
             << "@M\n"; // go to top stack memory address
    return assembly.str();
}

void Code::Close()
{   
    std::cout << "Closing file" << std::endl;
    this->outfile.close();
}