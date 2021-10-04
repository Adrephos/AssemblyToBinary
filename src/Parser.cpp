#include <iostream>
#include "../include/Parser.h"
#include <fstream>
#include <string>
#include <regex>
#include <algorithm>

using namespace std;
using std::string;
using std::remove;

const regex A_CMD_PATTERN{R"(^@([[:alpha:]_:\.\$][:\w\.\$]*|[[:digit:]]+)$)", regex::nosubs | regex::optimize};
const regex L_CMD_PATTERN{R"(^\([[:alpha:]_:\.\$][:\w\.\$]*\)$)", regex::nosubs | regex::optimize};
const regex C_CMD_PATTERN{"^((M|D|MD|A|AM|AD|AMD)=(0|-?1|[-!]?[ADM]|D[+-][1AM]|D[\\|&][AM]|[AM][+-]1|[AM]-D)(;(JGT|JEQ|JGE|JLT|JNE|JLE|JMP))?|""(0|-?1|[-!]?[ADM]|D[+-][1AM]|D[\\|&][AM]|[AM][+-]1|[AM]-D);(JGT|JEQ|JGE|JLT|JNE|JLE|JMP))$", regex::nosubs | regex::optimize};

void removeWhitespaceAndComments(string& line) {
  auto isSpace = [](const unsigned char c) 
  {
      return std::isspace(c);
  };

  line.erase(remove_if(line.begin(), line.end(), isSpace), line.end());
  line = line.substr(0, line.find("//"));
}

bool hasValidCmdSyntax(const string& line) {
  return regex_match(line, A_CMD_PATTERN) || regex_match(line, L_CMD_PATTERN) || regex_match(line, C_CMD_PATTERN);
}

void Parser::updateNextCommand() {
        string line;
        
        while(inStream_ && line.empty()) {
            getline(inStream_, line);
            removeWhitespaceAndComments(line);
            ++currLineNr_;
        }

        nextCmd_ = line;
    }


void Parser::advance(){
  currCmd_ = nextCmd_;
  
  if (syntaxChecking_ && !hasValidCmdSyntax(currCmd_)) {
    throw runtime_error("Invalid syntax in line" + to_string(currLineNr_) + ": " + currCmd_);
  }

  updateNextCommand();
}

void Parser::reset() {
  inStream_.clear();
  inStream_.seekg(0, ios::beg);
  currCmd_.clear();
  currLineNr_ = 0;
  syntaxChecking_ = true;
  updateNextCommand();
}

Parser::CommandType Parser::commandType() const {
  switch(currCmd_.front()) {
    case '@':
      return CommandType::A;
    case '(':
      return CommandType::L;
    default:
      return CommandType::C;
  }
}

string Parser::symbol() const {
  if (commandType() == CommandType::A) {
    return currCmd_.substr(1);
  }

  return currCmd_.substr(1, currCmd_.size() - 2);
}

string Parser::dest() const {
  const auto eqIndex = currCmd_.find('=');
  return eqIndex != string::npos ? currCmd_.substr(0, eqIndex) : "null";
}

string Parser::comp() const {
  const auto eqIndex = currCmd_.find('=');
  const auto startIndex = eqIndex != string::npos ? eqIndex + 1 : 0;

  const auto semiColIndex = currCmd_.find(';');
  const auto compLength = semiColIndex != string::npos ? semiColIndex - startIndex : string::npos;

  return currCmd_.substr(startIndex, compLength);
}

string Parser::jump() const { 
  const auto semiColIndex = currCmd_.find(';');
  return semiColIndex != string::npos ? currCmd_.substr(semiColIndex + 1) : "null";
}