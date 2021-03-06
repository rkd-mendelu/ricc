#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include "SymbolTableItem.hpp"
#include "lex/Token.hpp"

namespace RICC {

class SymbolTable {
 public:
  SymbolTable();
  SymbolTable(long offset);

  std::shared_ptr<SymbolTableItem> defineVar(const std::string& name);
  std::shared_ptr<SymbolTableItem> defineFunc(const std::string& name);

  std::shared_ptr<SymbolTableItem> getItemByName(const std::string& name) const;
  bool isFuncDeclared(const std::string& name) const;
  bool isVarDeclared(const std::string& name) const;

  void printContent() const;

  long getNextOffset() const;

  void addContinue(long address);
  std::vector<long>& getContinues();
  void addBreak(long address);
  std::vector<long>& getBreaks();

  bool isFuncScope() const;
  void setBreakable();
  bool isBreakable() const;

 private:
  std::unordered_map<std::string, std::shared_ptr<SymbolTableItem> > _table;

  bool _func;
  long _nextOffset;
  bool _breakable;
  std::vector<long> _breaks;
  std::vector<long> _continues;
};
}  // namespace RICC
