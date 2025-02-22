#ifndef RULES_H
#define RULES_H

#include <string>
#include <vector>
#include "JackTokenizer.h"
#include <stack>
#include <unordered_map>
using namespace std;


char* terminalTags[] = {"keyword", "symbol", "identifier", "integerConst", "stringConst"};

enum OCCURENCES {
    ONE,
    ZERO_OR_ONE,
    ZERO_OR_MORE
};

class Token {
    public:
        virtual void validate(stack<unique_ptr<Token>> stack, JackTokenizer* tk) const = 0;
        // virtual void add(stack<unique_ptr<Token>> stack)
        virtual ~Token() {}
};

struct Terminal : Token {

    string literal;
    string tag;
    bool optional;
    bool moreToCompare;
    // vector<unique_ptr<Token>> validators;
    JackTokenizer::TOKEN_TYPE type;

    // moreToCompare: Used if token can be this | that. true indicates there's more values the token needs to compare
    // note: may not need tag
    //template<typename... Tokens>
    Terminal(bool optional, JackTokenizer::TOKEN_TYPE type, string literal, bool moreToCompare)
            : literal(literal), optional(optional), type(type), moreToCompare(moreToCompare) {};
    Terminal(bool optional, JackTokenizer::TOKEN_TYPE type, bool moreToCompare)
            : optional(optional), type(type), literal(""), moreToCompare(moreToCompare){};
    // need access to stack
    void validate(stack<unique_ptr<Token>> stack, JackTokenizer* tk) const override {
        tk->advance();
        if (literal == tk->currentToken) {
            // print <tag>
            cout << "<" << terminalTags[tk->getTokenType()] << ">" << endl;
            // print currentToken
            cout << tk->currentToken << endl;
            // print </tag>
            cout << "</" << terminalTags[tk->getTokenType()] << ">" << endl;
            // remove all uneeded tokens from stack
        } else if (!moreToCompare) {
            // error
            cerr << "An error occured" << endl;
        } else if (moreToCompare) {
            return;
        }
    }

};

struct OrToken : Terminal {

};

struct NonTerminal : Token {
    public:
        
        string tag;
        bool optional;
        vector<unique_ptr<Token>> children;
        // OCCURENCES occurences;
        NonTerminal(string tag, bool optional, vector<unique_ptr<Token>> children)
            : tag(tag), optional(optional), children(children) {};

        void validate(stack<unique_ptr<Token>> stack, JackTokenizer* tk) const override {
            // print <tag>
            // go through list of children and add them to stack, and call validate on them
            for (unsigned int i = children.size(); i >= 0 ; i--) {
                stack.push(children[i]);
            } 
            // print </tag>
        }
};

struct classRule : public NonTerminal {
    vector<unique_ptr<Token>> children = {
        make_unique<Token>(Terminal(false, JackTokenizer::KEYWORD, "class", false))
    
        };
    classRule() : NonTerminal("class", false, children) {
        
    }
}; 

struct classNameRule : public NonTerminal {
    vector<unique_ptr<Token>> children = {make_unique<Token>(identifierRule())};
    classNameRule() : NonTerminal("className", false, children) {};
};

struct identifierRule : public Terminal {
    identifierRule() : Terminal(false, JackTokenizer::IDENTIFIER, false){};
    void validate(stack<unique_ptr<Token>> stack, JackTokenizer* tk) const override{

    }
};


#endif