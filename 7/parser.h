#ifndef PARSER_H
#define PARSER_H


#include <string>
#include <fstream>
class Parser
{
    public:
        Parser(std::string filename);
        bool hasMoreCommands();
        void advance();
        std::string arg1();
        std::string arg2();
        

    private:
        std::ifstream file;
        std::string line;


};

#endif //PARSER_H