#ifndef code_h
#define code_h
#include <string>
#include <bitset>

using namespace std;

class Code {
  public:
    Code();
    std::bitset<3> dest(const std::string& mnemonic);
    std::bitset<7> comp(const std::string& mnemonic);
    std::bitset<3> jump(const std::string& mnemonic);
};

#endif