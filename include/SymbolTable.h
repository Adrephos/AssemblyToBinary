#ifndef symboltable_h
#define symboltable_h

#include <unordered_map>
#include <string>

using namespace std;

class SymbolTable {
  private:
    unordered_map<std::string, int> table_;
    int currNewVarAddr_{16}; //mapa no ordenado

  public:
    
    SymbolTable(); 
    
    /**
     * \brief Añade una nueva entrada a la tabla o actualiza si ya existe
     * \param symbol string, map key
     * \param address int, key value
     * \return void
     */
    void addEntry(string symbol, int address) { 
      auto it = table_.find(symbol);

      if(it != table_.end()) {
        it->second = address;
      } else {
        table_.insert({symbol, address});
      }
    }

    bool contains(string symbol) { return table_.find(symbol) != table_.cend(); }
    
    unsigned GetAddress(string symbol) { return table_.at(symbol); }

    void addVarSymbol( const std::string& name) { table_.emplace(name, currNewVarAddr_++); }
};

#endif
