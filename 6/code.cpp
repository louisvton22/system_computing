#include "code.h"
#include <iostream>
const std::unordered_map<std::string, std::bitset<3>> dests = {
    {"null", std::bitset<3>("000")},
    {"M", std::bitset<3>("001")},
    {"D", std::bitset<3>("010")},
    {"MD", std::bitset<3>("011")},
    {"A", std::bitset<3>("100")},
    {"AM", std::bitset<3>("101")},
    {"AD", std::bitset<3>("110")},
    {"AMD", std::bitset<3>("111")},
};

const std::unordered_map<std::string, std::bitset<6>> comps = {
    {"0", std::bitset<6>("101010")},
    {"1", std::bitset<6>("111111")},
    {"-1", std::bitset<6>("111010")},
    {"D", std::bitset<6>("001100")},
    {"!D", std::bitset<6>("001101")},
    {"-D", std::bitset<6>("001111")},
    {"D+1", std::bitset<6>("011111")},
    {"D-1", std::bitset<6>("001110")},
    {"A", std::bitset<6>("110000")},
    {"!A", std::bitset<6>("110001")},
    {"-A", std::bitset<6>("110011")},
    {"A+1", std::bitset<6>("110111")},
    {"A-1", std::bitset<6>("110010")},
    {"D+A", std::bitset<6>("000010")},
    {"D-A", std::bitset<6>("010011")},
    {"A-D", std::bitset<6>("000111")},
    {"D&A", std::bitset<6>("000000")},
    {"D|A", std::bitset<6>("010101")},
    {"M", std::bitset<6>("110000")},
    {"!M", std::bitset<6>("110001")},
    {"-M", std::bitset<6>("110011")},
    {"M+1", std::bitset<6>("110111")},
    {"M-1", std::bitset<6>("110010")},
    {"D+M", std::bitset<6>("000010")},
    {"D-M", std::bitset<6>("010011")},
    {"M-D", std::bitset<6>("000111")},
    {"D&M", std::bitset<6>("000000")},
    {"D|M", std::bitset<6>("010101")},
};
const std::unordered_map<std::string, std::bitset<3>> jumps = {
    {"null", std::bitset<3>("000")},
    {"JGT", std::bitset<3>("001")},
    {"JEQ", std::bitset<3>("010")},
    {"JGE", std::bitset<3>("011")},
    {"JLT", std::bitset<3>("100")},
    {"JNE", std::bitset<3>("101")},
    {"JLE", std::bitset<3>("110")},
    {"JMP", std::bitset<3>("111")},
};
Code::Code() {
    
}



std::bitset<3> Code::dest(std::string mneumonic) {
    return dests.at(mneumonic);
}

std::bitset<7> Code::comp(std::string mneumonic) {
    std::bitset<7> compset;
    if ( mneumonic.find("A") == std::string::npos)
    {
        // operation doesn't use A, "a" bit set to 0
        compset.set(0);
    }
    return compset | std::bitset<compset.size()>(comps.at(mneumonic).to_ullong());
}

std::bitset<3> Code::jump(std::string mneumonic) {
    std::cout << mneumonic << std::endl;
    return jumps.at(mneumonic);
}