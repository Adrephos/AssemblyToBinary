#include "../include/Init.h"
#include <bitset>
#include <string>
#include <iostream>
#include "../include/Code.h"

using std::string;
using std::bitset;

bool isInteger(string& input) {
  auto isDigit = [](const unsigned char c) {
    return std::isdigit(c);
  };

  return all_of(input.cbegin(), input.cend(), isDigit);
}

template<size_t L1, size_t L2>
void setBitSetAt(std::bitset<L1>& input, size_t startPos, const bitset<L2>& val) {
  const auto end = std::min<size_t>(L1, L2 + startPos);

  for(int i = startPos; i < end; ++i) {
    input[i] = val[i - startPos];
  }
}

void Init::execute() {
  parseLabels();
  parser_.reset();
  parser_.setSyntaxChecking(false);
  generateBinaryCodeOutput();
}

void Init::parseLabels() {
  unsigned programCounter{};

  while(parser_.hasMoreCommands()) {
    parser_.advance();
    
    if(parser_.commandType() == Parser::CommandType::L) {
      symbolTable_.addEntry(parser_.symbol(), programCounter);
    } else {
      ++programCounter;
    }
  }
}

void Init::generateBinaryCodeOutput() {
  while(parser_.hasMoreCommands()) {
    parser_.advance();
    if(parser_.commandType() != Parser::CommandType::L) {
      outStream_ << getCurrCmdAsBinaryCode() << '\n';
    }
  }
}

bitset<16> Init::getCurrCmdAsBinaryCode() {
  bitset<16> result;

  if(parser_.commandType() == Parser::CommandType::A) {
    string currSymbol = parser_.symbol();

    if(symbolTable_.contains(currSymbol)) {
      result = {symbolTable_.GetAddress(currSymbol)};
    } else if(isInteger(currSymbol)) {
      result= {stoul(currSymbol)};
    } else {
      symbolTable_.addVarSymbol(currSymbol);
      result = {symbolTable_.GetAddress(currSymbol)};
    }
  } else {
    result.set();
    setBitSetAt(result, 0, code_.jump(parser_.jump()));
    setBitSetAt(result, 3, code_.dest(parser_.dest()));
    setBitSetAt(result, 6, code_.comp(parser_.comp()));
  }
  return result;
}
