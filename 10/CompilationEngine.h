#ifndef COMPILATION_ENGINE_H
#define COMPILATION_ENGINE_H

#include <fstream>
class CompilationEngine {
    private:
        
        // Gets its input from a JackTokenizer and emits its output to and output
        // file, using a set of parsing routines.
        CompilationEngine(std::ifstream input, std::ofstream output);

        // Compiles a complete class
        void compileClass();

        // Compiles a static variable declari
        void compileClassVarDec();

        // Compiles a comeplete method, function, or constructor
        void compileSubroutine();

        // Compiles a (possibly empty) parameter list. Does not handle the enclosing parentheses tokens ( and )
        void compileParameterList();

        // Compiles a subroutine's body
        void compileSubroutineBody();

        // Compiles a var declaration
        void compileVarDec();

        // Compiles a sequence of statements, Does not handle the enclosign curly bracket tokens { and }.
        void compileStatements();

        // Compiles a let statements
        void compileLet();

        // Compiles an if statement, possibly with an else statement
        void compileIf();

        // Compiles a while statement
        void compileWhile();

        // Compiles a do statement
        void compileDo();

        // Compiles a return statement
        void compileReturn();

        // Compiles an expression
        void compileExpression();

        // Compiles a term. If the current token is an identifier, the routine must
        // resolve it into a variable, an array entry, or a subroutine call. A single
        // look ahead token, which may be [, (, or ., suffices to distinguish between
        // possibilities. Any other token is not art of this term and should not be
        // advanced over.
        void compileTerm();

        // Compiles a (possibly empty) comma-separated list of expressions, Returns
        // the # of expressions in the list
        int compileExpressionList();

    public:


};

#endif // CompilationEngine.h