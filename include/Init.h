#include "Parser.h"
#include "SymbolTable.h"
#include "./Code.h"
#include <bitset>

class Init {
  public:
    Init(std::istream& inStream, std::ostream& outStream) : parser_{inStream}, outStream_{outStream} {};

    void execute();
  private:
    Parser parser_;
    SymbolTable symbolTable_;
    Code code_;
    std::ostream& outStream_;

    void parseLabels();
    void generateBinaryCodeOutput();
    std::bitset<16> getCurrCmdAsBinaryCode();
};