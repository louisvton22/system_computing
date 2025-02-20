#include "CompilationEngine.h"


JackTokenizer tokenizer;
using namespace std;
CompilationEngine::CompilationEngine(std::string file) {
    tokenizer = JackTokenizer(file);
    this->output = std::ofstream(file);
    compileClass();
}


void CompilationEngine::process(std::string expectedToken) {
    tokenizer.advance();
    std::string token = tokenizer.currentToken;

    if (token == expectedToken) {
        this->output << token << endl;
    } else {
        cerr << "Error parsing" << endl; 
    }
}

void CompilationEngine::compileClass()
{
    this->output << "<class>" << endl;
    process("class")
    verifyToken("identitfier");
    process("{");
    compileVarDec();
    compileSubroutine();
    process("}");
    this->output << "</class>" << endl;
}

void CompilationEngine::compileClassVarDec()
{

}

void CompilationEngine::compileSubroutine()
{
}

void CompilationEngine::compileParameterList()
{
}

void CompilationEngine::compileSubroutineBody()
{
}

void CompilationEngine::compileVarDec()
{
}

void CompilationEngine::compileStatements()
{
}

void CompilationEngine::compileLet()
{
}

void CompilationEngine::compileIf()
{
}

void CompilationEngine::compileWhile()
{
}

void CompilationEngine::compileDo()
{
}

void CompilationEngine::compileReturn()
{
}

void CompilationEngine::compileExpression()
{
}

void CompilationEngine::compileTerm()
{
}

int CompilationEngine::compileExpressionList()
{
    return 0;
}
