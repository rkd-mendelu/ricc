#pragma once

#include <iostream>
#include <vector>
#include <memory>

#include "SymbolTable.hpp"

namespace RICC {
    namespace Semantic {

        class Scope: public std::vector<std::shared_ptr<SymbolTable>> {
            public:
                std::shared_ptr<SymbolTableItem> define(const std::string& name, SymbolTableItem::Kind kind);
                std::shared_ptr<SymbolTableItem> getItemByName(const std::string& name) const;

                bool isDefined(const std::string& name, SymbolTableItem::Kind kind) const;
                std::shared_ptr<SymbolTable> getBreakScope();

                void enterScope(bool function);
                void leaveScope();

                std::shared_ptr<SymbolTable> getScope();
                void printScope() const;
        };

    }
}
