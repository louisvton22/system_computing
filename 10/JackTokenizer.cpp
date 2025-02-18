#include "JackTokenizer.h"



std::string token;

std::set<unsigned char> symbolSet = std::set<unsigned char>(
    {'{','}', '(', ')', '[', ']', '.', ',', ';', '+', '-', '*', '/', '&', '|',
    '<', '>', '=', '~'}
);

JackTokenizer::JackTokenizer(std::string input) {
    this->stream = std::ifstream(input);
}

bool JackTokenizer::hasMoreTokens()
{
    char c = this->stream.peek();
    return (c != EOF);
}

void JackTokenizer::advance()
{   char buffer;
    currentToken = "";
    std::string line;
    while (hasMoreTokens()) {
        this->stream.get(buffer);
        // if buffer is symbol, update current Token and break
        if (symbolSet.find(buffer) != symbolSet.end())
        {   
            // handles if we deduce line is non-programmatic
            if (currentToken.size() > 0)
            {   
                // fast-forward stream position to next line
                if (currentToken + buffer == "//" || currentToken + buffer == "/*" || currentToken + buffer == "*/") {
                    std::cout << "Non-program line found, skipping line" << std::endl;
                    this->stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    currentToken = "";
                    continue;
                }
                // End current token 
                this->stream.unget();
                break;
            } else {
                // add symbol to current token to check for comment line
                currentToken += buffer;
                if (buffer != '/') {
                    break;
                }
            }
        }
        // if buffer is character, determine if identifier or string constnat
        else if (std::isalpha(buffer)) {
            currentToken += buffer;
        } 
        // if buffer is digit, continue adding to token
        else if (std::isdigit(buffer)) {
            currentToken += buffer;
        }
        // if whitespace after nonwhitespace, complete token, otherwise continue
        // until nonwhitespace encountered
        else if (std::iswspace(buffer)) {
            if (currentToken.size() > 0) {
                break;
            } else {
                continue;
            }
        }

        
        // currentToken += buffer;
        //std::cout << "current token: " << currentToken << std::endl;
        // if buffer is number, go until whitespace
    }
    std::cout << "final token: " << currentToken << std::endl;

}

char JackTokenizer::symbol()
{
    return 0;
}

std::string JackTokenizer::identifier()
{
    return std::string();
}

int JackTokenizer::intVal()
{
    return 0;
}

std::string JackTokenizer::stringVal()
{
    return std::string();
}

bool isSymbol() {
   

    
}