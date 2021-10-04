#include <iostream>
#include "../include/Code.h"
#include <string>
#include <unordered_map>
#include <bitset>

using namespace std;

Code::Code(){ 

}

std::bitset<3> Code::dest(const string& mnemonic){
  const unordered_map<string, bitset<3>> destMnemonicList{
    {"null",  bitset<3>{0b000}},
    { "M",    bitset<3>{0b001} },
    { "D",    bitset<3>{0b010} },
    { "MD",   bitset<3>{0b011} },
    { "A",    bitset<3>{0b100} },
    { "AM",   bitset<3>{0b101} },
    { "AD",   bitset<3>{0b110} },
    { "AMD",  bitset<3>{0b111} }
  };

  return destMnemonicList.at(mnemonic);
}

std::bitset<7> Code::comp(const string& mnemonic){
  const unordered_map<string, bitset<7>> compMnemonicList{
    { "0",   bitset<7>{0b0101010} },
    { "1",   bitset<7>{0b0111111} },
    { "-1",  bitset<7>{0b0111010} },
    { "D",   bitset<7>{0b0001100} },
    { "A",   bitset<7>{0b0110000} },
    { "!D",  bitset<7>{0b0001101} },
    { "!A",  bitset<7>{0b0110001} },
    { "-D",  bitset<7>{0b0001111} },
    { "-A",  bitset<7>{0b0110011} },
    { "D+1", bitset<7>{0b0011111} },
    { "A+1", bitset<7>{0b0110111} },
    { "D-1", bitset<7>{0b0001110} },
    { "A-1", bitset<7>{0b0110010} },
    { "D+A", bitset<7>{0b0000010} },
    { "D-A", bitset<7>{0b0010011} },
    { "A-D", bitset<7>{0b0000111} },
    { "D&A", bitset<7>{0b0000000} },
    { "D|A", bitset<7>{0b0010101} },
    { "M",   bitset<7>{0b1110000} },
    { "!M",  bitset<7>{0b1110001} },
    { "-M",  bitset<7>{0b1110011} },
    { "M+1", bitset<7>{0b1110111} },
    { "M-1", bitset<7>{0b1110010} },
    { "D+M", bitset<7>{0b1000010} },
    { "D-M", bitset<7>{0b1010011} },
    { "M-D", bitset<7>{0b1000111} },
    { "D&M", bitset<7>{0b1000000} },
    { "D|M", bitset<7>{0b1010101} }
  };

  return compMnemonicList.at(mnemonic);
}

std::bitset<3> Code::jump(const string& mnemonic){
  const unordered_map<string, bitset<3>> jumpMnemonicList{
    { "null", bitset<3>{0b000} },
    { "JGT",  bitset<3>{0b001} },
    { "JEQ",  bitset<3>{0b010} },
    { "JGE",  bitset<3>{0b011} },
    { "JLT",  bitset<3>{0b100} },
    { "JNE",  bitset<3>{0b101} },
    { "JLE",  bitset<3>{0b110} },
    { "JMP",  bitset<3>{0b111} }
  };

  return jumpMnemonicList.at(mnemonic);
}