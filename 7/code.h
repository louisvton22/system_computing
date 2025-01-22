#ifndef CODE_H
#define CODE_H

#include <fstream>

class Code {
    enum COMMAND {
        PUSH,
        POP
    };
    public:
        Code(std::ofstream output);
        //Informs the code writer that the translation of a VM file has started
        void setFileName(std::string fileName);
        //Writes the aseembly code for an arithmetic command
        void writeArithmetic(std::string command);
        //Writes the assembly code of the given command, where command is PUSH or POP
        void WritePushPop(COMMAND c, std::string segment, int index);

        //Closes the output file;
        void Close();
    private:
        std::ofstream outfile;
};

#endif //CODE_H