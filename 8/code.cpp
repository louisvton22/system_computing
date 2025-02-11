#include "code.h"

/*
 TEMP VARIABLES
 R13: Used for pop operations
 R14: Local variables for VM functions
*/
std::string push();
std::string pop();
std::unordered_map<std::string, std::string> segments;
unsigned int call = 1;
std::string currentFunction = "";

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

    currentFunction = this->filename.stem().string();
}

// Finds command type and writes corresponding assembly code 
void Code::writeLine(Parser::COMMAND_TYPE ct, std::string command, std::string arg1, std::string arg2)
{
    switch(ct) {
        case (Parser::C_ARITHMETIC):
            writeArithmetic(command);
            break;
        case (Parser::C_PUSH):
            WritePushPop(ct, arg1, std::stoi(arg2));
            break;
        case (Parser::C_POP):
            WritePushPop(ct, arg1, std::stoi(arg2));
            break;
        case (Parser::C_CALL):
            writeCall(arg1, std::stoi(arg2));
            break;
        case (Parser::C_FUNCTION):
            writeFunction(arg1, std::stoi(arg2));
            break;
        case (Parser::C_GOTO):
            writeGoto(arg1);
            break;
        case (Parser::C_IF):
            writeIf(arg1);
            break;
        case (Parser::C_LABEL):
            writeLabel(arg1);
            break;
        case (Parser::C_RETURN):
            writeReturn();
            break;
    }
};



void Code::setFileName(std::string fileName) {
    this->outfile = std::ofstream(fileName);
    std::cout << "Parsing vm file: " << fileName << " has started" <<  std::endl;
    // initialize SP to 256m,
    // this->outfile << "@256\n"
    //               << "D=A\n"
    //               << "@SP\n"
    //               << "M=D\n"
    //               << "@300\n"
    //               << "D=A\n"
    //               << "@LCL\n"
    //               << "M=D\n"
    //               << "@400\n"
    //               << "D=A\n"
    //               << "@ARG\n"
    //               << "M=D\n"
    //               << "@3000\n"
    //               << "D=A\n"
    //               << "@THIS\n"
    //               << "M=D\n"
    //               << "@3010\n"
    //               << "D=A\n"
    //               << "@THAT\n"
    //               << "M=D\n";
}

void Code::writeArithmetic(std::string command) {
    std::string assemblyCommand;
    std::cout << "Writing Arithmetic" << std::endl;
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
                 << "@" << ((segment == "static") ? "0" : std::to_string(index)) << "\n" // set constant index
                 << "D=A\n"
                 << "@" << segmentReg << "\n" // go to segment base address
                 << "AD=D+" << ((segment == "static" || segment == "pointer") ? "A" : "M") << "\n"
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
                 << "D=D+" << ((segment == "static" || segment == "pointer") ? "A" : "M") << "\n" // index + segment
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




void Code::writeLabel(std::string label) {
    this->outfile << "(" << currentFunction << "$" << label <<  ")\n";
    
}

void Code::writeGoto(std::string label)
{
    this-> outfile << "@" << label << "\n" 
                   << "0;JEQ\n";
}

void Code::writeIf(std::string label)
{
    this->outfile << pop() // get top value
                  << "D=M\n" // store top value in register
                  << "@" << currentFunction << "$" << label << "\n"// store label name in register A
                  << "D;JNE\n"// Jump command
    ;
}

void Code::writeCall(std::string functionName, unsigned int numArgs) {
    this->outfile << "@" << functionName << ".return\n"
                  << "D=A\n" // set D to return address
                  << push()
                  << "@LCL\n" // go to local segment
                  << "D=M\n"  // store pointer 
                  << push() // push local pointer onto stack
                  << "@ARG\n" // go to argument segment
                  << "D=M\n"  // store pointer 
                  << push() // push argument pointer onto stack
                  << "@THIS\n" // go to this segment
                  << "D=M\n"  // store pointer 
                  << push() // push this pointer onto stack
                  << "@THAT\n" // go to that segment
                  << "D=M\n"  // store pointer 
                  << push() // push that pointer onto stack
                  << "@5\n"
                  << "D=A\n"
                  << "@" << numArgs <<"\n"
                  << "D=D-A\n" // d = -(5 + n)
                  << "@SP\n"
                  << "D=M+D\n" // d = SP - (5+n)
                  << "@ARG\n"
                  << "M=D\n" // arg = d
                  << "@SP\n"
                  << "D=M\n" // d = sp
                  << "@LCL\n"
                  << "M=D\n";// local = d
                  writeGoto(functionName);
    this->outfile << "(" << functionName << ".return)\n";
}

void Code::writeReturn() {
    currentFunction = "";
    this->outfile << "@LCL\n" //
                  << "D=M\n"
                  << "@R14\n" //temp
                  << "M=D\n" // temp = LCL
                  << "@5\n"
                  << "A=D-A\n"
                  << "D=M\n"
                  << "@R15\n"
                  << "M=D\n" // RET = temp - 5
                  << pop()
                  << "D=M\n" // D = top value of stack
                  << "@ARG\n" // go to position where return value will be
                  << "A=M\n"
                  << "M=D\n" // SP = return value
                  << "@ARG\n"
                  << "D=M\n"
                  << "@SP\n"
                  << "M=D+1\n" // SP = ARG + 1
                  << "@R14\n" // ram address of local
                  << "D=M\n"
                  << "@1\n"
                  << "A=D-A\n" // a = &temp - 1
                  << "D=M\n"  // d = &(&temp - 1)
                  << "@THAT\n"
                  << "M=D\n" // that = &(&temp - 1)
                  << "@R14\n" // ram address of local
                  << "D=M\n"
                  << "@2\n"
                  << "A=D-A\n" // a = &temp - 2
                  << "D=M\n"  // d = &(&temp - 2)
                  << "@THIS\n"
                  << "M=D\n" // this = &(&temp - 2)
                  << "@R14\n" // ram address of local
                  << "D=M\n"
                  << "@3\n"
                  << "A=D-A\n" // a = &temp - 3
                  << "D=M\n"  // d = &(&temp - 3)
                  << "@ARG\n"
                  << "M=D\n" // arg = &(&temp - 3)
                  << "@R14\n" // ram address of local
                  << "D=M\n"
                  << "@4\n"
                  << "A=D-A\n" // a = &temp - 4
                  << "D=M\n"  // d = &(&temp - 4)
                  << "@LCL\n"
                  << "M=D\n" // lcl = &(&temp - 4)
                  << "@R15\n"
                  << "A=M\n"
                  << "0;JEQ\n";
}

void Code::writeFunction(std::string functionName, unsigned int numLocals) {
    currentFunction = functionName;
    this->outfile << "(" << functionName << ")" << "\n" // set i to 0
                  << "@" << numLocals << "\n"
                  << "D=A\n" // store number of local vars
                  << "@R14\n"
                  << "M=D\n"
                  << "(" << functionName << ".loop" << ")\n" 
                  << "@0\n"
                  << "D=A\n"
                  << push()
                  << "@R14\n"
                  << "MD=M-1\n"
                  << "@" << functionName << ".loop" << "\n"
                  << "D;JEQ\n"; //
                  // ... rest of function parsed as normal
    ;
}