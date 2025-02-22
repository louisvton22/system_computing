#ifndef JACK_TOKENIZER_H
#define JACK_TOKENIZER_H

#include <fstream>
#include <set>
#include <cctype>
#include <iostream>
class JackTokenizer {
    

    enum KEYWORD {
        CLASS,
        METHOD,
        FUNCTION,
        CONSTRUCTOR,
        INT,
        BOOLEAN,
        CHAR,
        VOID,
        VAR,
        STATIC,
        FIELD,
        LET,
        DO,
        IF,
        ELSE,
        WHILE,
        RETURN,
        TRUE,
        FALSE,
        NULL_VALUE,
        THIS
    };

    public:

        // Provides routines that skip comments and white space, get the next token, and advance
        // the input exactly beyond it. Other routines return the type of the current token, and its value.
        JackTokenizer(std::string input);

        // Are there more tokens in the input?
        bool hasMoreTokens();

        void advance();

        char symbol();

        std::string identifier();

        int intVal();

        std::string stringVal();

        std::ifstream stream;

        std::string currentToken;

        enum TOKEN_TYPE{
        KEYWORD,
        SYMBOL,
        IDENTIFIER,
        INT_CONST,
        STRING_CONST    
        };

        TOKEN_TYPE getTokenType();

    private:


};


#endif