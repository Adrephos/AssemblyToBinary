#ifndef parser_h
#define parser_h

#include <string>
#include <istream>
#include <regex>

using namespace std;using std::string;


class Parser {
    public:

      enum class CommandType { A, C, L };
 
      explicit Parser(std::istream& inStream) : inStream_{inStream} { updateNextCommand(); }


      bool hasMoreCommands() const noexcept { return !nextCmd_.empty(); };

      void advance();

      void reset();

      void ReadFile();

      CommandType commandType() const;

      string symbol() const;

      string dest() const; 

      string comp() const;

      string jump() const;

      void setSyntaxChecking(bool value) { syntaxChecking_ = value; }

      bool isSyntaxChecking() const { return syntaxChecking_; }

    private:
      std::istream& inStream_;
      std::string currCmd_;
      std::string nextCmd_;
      size_t currLineNr_{};
      bool syntaxChecking_{true};

      void updateNextCommand();
};

#endif