#ifndef CODE_H
#define CODE_H

#include <bitset>
#include <string>
#include <unordered_map>
class Code {

    public:
        Code();

        // Returns the binary copde of the dest mneumonic
        std::bitset<3> dest(std::string mneumonic);
        // Returns the binary copde of the comp mneumonic
        std::bitset<7> comp(std::string mneumonic);
        // Returns the binary copde of the jump mneumonic
        std::bitset<3> jump(std::string mneumonic);

};

#endif // CODE_H
