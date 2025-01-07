#include "parser.h"


std::string line;
std::ifstream file;
SymbolTable st;
unsigned int lineCount;

Parser::Parser(char* filename) {
    file = std::ifstream(filename);
    st = SymbolTable();
}


bool Parser::hasMoreCommands() {
    std::streampos current = file.tellg();
    char c = file.peek();
    if (c == EOF) {
        return false;
    }
    file.clear();
    file.seekg(current);
    return true;
}

void Parser::advance() {

    do {
        if (hasMoreCommands()) {
            std::getline(file, line);
            line.erase(
                std::remove_if(line.begin(), line.end(),
                                [](unsigned char c){return std::isspace(c); }), line.end()
            );
        }
        // check if we come across loop label, find next valid instruction and store in symbol table
       
    } while (line.substr(0,2) == "//" || line.empty());
    lineCount++;
    // check if loop command or symbol then update symbol table
    std::cout << line << std::endl;
    //std::cout << commandType() << std::endl << "\n";
    if (commandType() == Parser::L_COMMAND) {
        if (!st.contains(line.substr(1,line.length()-2))) {
            st.addEntry(line.substr(1,line.length()-2), lineCount);
        } else {
            std::cout << "ERROR:: loop label already defined" << std::endl;
        }
    } else if (commandType() == Parser::A_COMMAND && std::regex_match(line.substr(1), std::regex (R"(^[a-zA-Z][a-zA-Z0-9]*$)"))) {
        if (!st.contains(line.substr(1))) {
            st.addEntry(line.substr(1), st.getSize());
        }
    }
}

Parser::COMMAND_TYPE Parser::commandType() {
    std::string command = line;
    // if starts with @ could be A or L command
    // A command if numbers passed after @ 
    // L command if Xxx label passed after @

    std::regex pattern(R"(\((.*)\))");
    std::smatch match;
    if (command[0] == '@')
    {
        return Parser::A_COMMAND;
    } else if (std::regex_search(line, match, pattern)) {
        return Parser::L_COMMAND;
    } else {
        return Parser::C_COMMAND;
    }
        

}

std::string Parser::symbol() {
    if (commandType() == Parser::COMMAND_TYPE::A_COMMAND || commandType() == Parser::COMMAND_TYPE::L_COMMAND)
    {
        return line.substr(1);
    }
    return "null";
}

std::string Parser::dest() {
    if (commandType() == Parser::COMMAND_TYPE::C_COMMAND)
    {
        auto index = line.find('=');
        if (index != std::string::npos) {
            return line.substr(0,index);
        }
    }
    return "None";
}

std::string Parser::jump() {
    if (commandType() == Parser::COMMAND_TYPE::C_COMMAND)
    {
        // find mneumonic after ";", ignore if there's no ";" meaning no jump condition given in line
        auto index = line.find(';');
        if (index != std::string::npos) {
            return line.substr(index+1);
        } 
    }
    return "null";
};

std::string Parser::comp() {
    if (commandType() == Parser::COMMAND_TYPE::C_COMMAND)
    {
        auto index = line.find('=');
        if (index != std::string::npos) {
            return line.substr(index+1);
        } else {
            // if only a comp value exists, it's a jump command;
            index = line.find(";");
            return line.substr(0, index);
        }
    }
    return "null";
}

std::string Parser::toString() {
    std::string str = "";
    str += line + '\n';
    str += "Command Type: " + std::to_string(static_cast<int>(commandType())) + "\n";
    str += "Destination: " + dest() + '\n';
    str += "Compute: " + comp() + '\n';
    str += "Jump: " + jump() + '\n';
    str += st.toString();
    return str;
}





