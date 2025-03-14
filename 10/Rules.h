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
        OCCURENCES optional;
        virtual void validate(stack<unique_ptr<Token>> stack, JackTokenizer* tk) const = 0;
        // virtual void add(stack<unique_ptr<Token>> stack)
        virtual ~Token() {}
        bool orType;
};

struct Terminal : Token {

    string literal;
    string tag;

    // vector<unique_ptr<Token>> validators;
    JackTokenizer::TOKEN_TYPE type;

    // moreToCompare: Used if token can be this | that. true indicates there's more values the token needs to compare
    // note: may not need tag
    //template<typename... Tokens>
    Terminal(OCCURENCES optional, JackTokenizer::TOKEN_TYPE type, string literal, bool orType)
            : literal(literal), type(type) {optional = optional; orType = orType;};
    Terminal(OCCURENCES optional, JackTokenizer::TOKEN_TYPE type, bool orType)
            : type(type), literal("") {Token::optional = optional; Token::orType = orType;};
    // need access to stack
    void validate(stack<unique_ptr<Token>> stack, JackTokenizer* tk) const override {
            if (literal == tk->currentToken) {
                // print <tag>
                cout << "<" << terminalTags[tk->getTokenType()] << ">" << endl;
                // print currentToken
                cout << tk->currentToken << endl;
                // print </tag>
                cout << "</" << terminalTags[tk->getTokenType()] << ">" << endl;
                // TODO: remove tokens until null it reached
                while (stack.top() != NULL) {
                    stack.pop();
                }
            } else {
                // handle occurences cases
                switch (optional) {
                    case(ONE):
                        // error
                        cerr << "An error occured" << endl;

                        
                }
                
            }
    }

};

// Handles the grouping of rules that the current token can be equal to
struct OrToken : NonTerminal {
    public:
        vector<unique_ptr<Token>> group;

        template<typename... Args>
        OrToken(Args... args) {
            (group.push_back(std::forward<Args>(args)), ...);
        }

        void validate(stack<unique_ptr<Token>> stack, JackTokenizer* tk) const override {
            NonTerminal::validate(stack, tk);
        }
};

struct NonTerminal : Token {
    public:
        
        string tag;
        vector<unique_ptr<Token>> children;

        // OCCURENCES occurences;
        NonTerminal(string tag, OCCURENCES optional, vector<unique_ptr<Token>> children, bool orType)
            : tag(tag), children(children) {Token::optional = optional; Token::orType = orType;};

        void validate(stack<unique_ptr<Token>> stack, JackTokenizer* tk) const override {
            // add a null token to separate rule
            for (const auto& child : children) {
                stack.push(child);
            }
        }

};

struct classRule : public NonTerminal {
    vector<unique_ptr<Token>> children = {
        make_unique<Token>(Terminal(ONE, JackTokenizer::KEYWORD, "class")),
        make_unique<Token>(classNameRule()),
        make_unique<Token>(Terminal(ONE, JackTokenizer::KEYWORD, "{")),

        };
    classRule() : NonTerminal("class", ONE, children, false) {
        // print <tag> 
        // call super 
        // print </tag>
    };
    void validate(stack<unique_ptr<Token>> stack, JackTokenizer* tk) const override{
        NonTerminal::validate(stack, tk);
    }

}; 

struct classNameRule : public NonTerminal {
    vector<unique_ptr<Token>> children = {make_unique<Token>(identifierRule())};
    classNameRule() : NonTerminal("className", false, children) {};
};

struct identifierRule : public Terminal {
    identifierRule() : Terminal(ONE, JackTokenizer::IDENTIFIER, false){};
    void validate(stack<unique_ptr<Token>> stack, JackTokenizer* tk) const override{

    }
};


#endif