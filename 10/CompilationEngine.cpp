#include "CompilationEngine.h"
#include "Rules.h"



JackTokenizer tokenizer;
using namespace std;
CompilationEngine::CompilationEngine(std::string file) {
    tokenizer = JackTokenizer(file);
    this->output = std::ofstream(file);
    compileClass();
}

template<typename... Args>
void CompilationEngine::process(JackTokenizer::TOKEN_TYPE type, Args... args) {
    tokenizer.advance();
    std::string token = tokenizer.currentToken;
    
    if (tokenizer.getTokenType() == type) {
        if ((token == args) || ...) {
            this->output << token << endl;
        } else {
            cerr << "Error parsing" << endl;
        }
    } else {
        cerr << "Error parsing" << endl; 
    }

}

void CompilationEngine::compileClass()
{
    this->output << "<class>" << endl;
    process(JackTokenizer::KEYWORD, "class");
    process(JackTokenizer::IDENTIFIER);
    process(JackTokenizer::SYMBOL, "{");
    compileVarDec();
    compileSubroutine();
    process(JackTokenizer::SYMBOL, "}");
    this->output << "</class>" << endl;
}

void CompilationEngine::compileClassVarDec()
{
    this->output << "<classVarDec>" << endl;
    process(JackTokenizer::KEYWORD, "static", "field");
    // process type rule
    
    // process varName rule
    // process 0 or more varName rule
    this->output << "</classVarDec>" << endl;
}




stack<unique_ptr<Token>> compilationStack = stack<unique_ptr<Token>>();
void compile () {
    JackTokenizer tk = JackTokenizer("Square/Main.jack");
    compilationStack.push(make_unique<Token>(classRule()));
    
    while (!compilationStack.empty()) {
        auto &const currentRule = compilationStack.top();
        compilationStack.pop();
        currentRule->validate(compilationStack, &tk);
    }


}