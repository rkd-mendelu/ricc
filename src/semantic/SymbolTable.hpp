#pragma once

#include <vector>
#include <memory>
#include <unordered_map>

#include "SymbolTableItem.hpp"
#include "lex/Token.hpp"

namespace TPJparser {

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

            void addBreak(long address);
            std::vector<long>& getBreaks();
            bool isFuncScope() const;
            void setBreakable();
            bool isBreakable() const;
        private:
            std::unordered_map<
                std::string,
                std::shared_ptr<SymbolTableItem>
            > _table;

            bool _func;
            long _nextOffset;
            bool _breakable;
            std::vector<long> _breaks;
    };
}
