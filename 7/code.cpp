#include "code.h"

std::string push();
std::string pop();
std::unordered_map<std::string, std::string> segments;
unsigned int call = 1;
Code::Code(std::string fileName) {
    this->filename = std::filesystem::path(fileName);
    setFileName(fileName);

    segments = {
    {"local", "LCL"},
    {"argument", "ARG"},
    {"this", "THIS"},
    {"that", "THAT"},
    {"temp", "R5"},
    {"pointer", "R3"}
    };
}


void Code::setFileName(std::string fileName) {
    this->outfile = std::ofstream(fileName);
    std::cout << "Parsing vm file: " << fileName << " has started" <<  std::endl;
    // initialize SP to 256m,
    this->outfile << "@256\n"
                  << "D=A\n"
                  << "@SP\n"
                  << "M=D\n"
                  << "@300\n"
                  << "D=A\n"
                  << "@LCL\n"
                  << "M=D\n"
                  << "@400\n"
                  << "D=A\n"
                  << "@ARG\n"
                  << "M=D\n"
                  << "@3000\n"
                  << "D=A\n"
                  << "@THIS\n"
                  << "M=D\n"
                  << "@3010\n"
                  << "D=A\n"
                  << "@THAT\n"
                  << "M=D\n";
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
    } else if (command == "lt") {
        this->outfile << pop()
                      << "D=M\n"
                      << pop()
                      << "D=D-M\n"
                      << "@Great." << call << "\n"
                      << "D;JGE\n"
                      << "@0\n"
                      << "D=A\n"
                      << "@ENDIF" << call << "\n"
                      << "0;JEQ\n"
                      << "(Great." << call << ")\n"
                      << "@1\n"
                      << "D=-A\n"
                      << "(ENDIF" << call << ")\n"
                      << push();
        call++;
    } else if (command == "gt") {
        this->outfile << pop()
                      << "D=M\n"
                      << pop()
                      << "D=D-M\n"
                      << "@Great." << call << "\n"
                      << "D;JGT\n"
                      << "@0\n"
                      << "D=A\n"
                      << "@ENDIF" << call << "\n"
                      << "0;JEQ\n"
                      << "(Great." << call << ")\n"
                      << "@1\n"
                      << "D=-A\n"
                      << "(ENDIF" << call << ")\n"
                      << push();
        call++;
    } else if (command == "eq") {
        this->outfile << pop()
                      << "D=M\n"
                      << pop()
                      << "D=D-M\n"
                      << "@Not_Equal" << call << "\n"
                      << "D;JNE\n"
                      << "@1\n"
                      << "D=-A\n"
                      << "@ENDIF" << call << "\n"
                      << "0;JEQ\n"
                      << "(Not_Equal" << call << ")\n"
                      << "@0\n"
                      << "D=A\n"
                      << "(ENDIF" << call << ")\n"
                      << push();
        call++;
    } else if (command == "and") {
            this->outfile << pop()
                          << "D=M\n"
                          << pop()
                          << "D=D&M\n"
                          << "@and.t" << call << "\n"
                          << "D;JGT\n"
                          << "@and.f" << call << "\n"
                          << "D;JLE\n"
                          << "(and.t" << call << ")\n"
                          << "@1\n"
                          << "D=-A\n"
                          << "@END" << call << "\n"
                          << "0;JEQ\n"
                          << "(and.f" << call << ")\n"
                          << "@0\n"
                          << "D=A\n"
                          << "(END" << call<< ")\n"
                          << push();
        call++;
    } else if (command == "or") {
        this->outfile << pop()
                          << "D=M\n"
                          << pop()
                          << "D=D|M\n"
                          << "@and.t" << call << "\n"
                          << "D;JGT\n"
                          << "@and.f" << call<< "\n"
                          << "D;JLE\n"
                          << "(and.t" << call<< ")\n"
                          << "@1\n"
                          << "D=-A\n"
                          << "@END" << call << "\n"
                          << "0;JEQ\n"
                          << "(and.f" << call<< ")\n"
                          << "@0\n"
                          << "D=A\n"
                          << "(END" << call<< ")\n"
                          << push();
    call++;
    } else if (command == "not") {
        this->outfile << pop()
                      << "D=!M\n"
                      << push();
    }
}


void Code::WritePushPop(Parser::COMMAND_TYPE c, std::string segment, int index) {
    std::ostringstream command;
    std::string segmentReg;
    if (segment == "constant") {
        command << "@" << index << "\n"
        << "D=A\n"
        << push();
        this->outfile << command.str();
        return;
    } else if (segment == "static") {
        segmentReg = this->filename.stem().string() + "." + std::to_string(index);
    } else {
        segmentReg = segments.find(segment)->second;
    }
    switch(c) {
        case(Parser::C_PUSH): {
            
            // push segment[index] onto the stack
            command 
                 << "@" << ((segment == "static ") ? "0" : std::to_string(index)) << "\n" // set constant index
                 << "D=A\n"
                 << "@" << segmentReg << "\n" // go to segment base address
                 << "A=M\n" // go to segment virtual address
                 << "A=D+A\n" // segment + index
                 << "D=M\n"
                 << "@SP\n" // go to stack pointer
                 << "A=M\n"
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
                 << "@" << ((segment == "static") ? "0" : std::to_string(index)) << "\n" // set constant index
                 << "D=A\n"
                 << "@" << segmentReg << "\n"
                 << "D=D+" << ((segment == "static") ? "A" : "M") << "\n" // index + segment
                 << "@R13\n" // store segment index in temp
                 << "M=D\n" //
                 << "@SP\n" // go to stack pointer
                 << "AM=M-1\n" // go to top of stack address
                 << "D=M\n" // store value on stack in D
                 << "@R13\n"
                 << "A=M\n"
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
             <<  "A=M\n" // go to top of stack
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
             << "A=M\n"; // go to top stack memory address
    return assembly.str();
}

void Code::Close()
{   
    std::cout << "Closing file" << std::endl;
    // end program with infinite loop
    this->outfile << "(END)\n"
                  << "@END\n"
                  << "0;JEQ\n";
    this->outfile.close();
}