#pragma once

#include <iostream>
#include <stack>

#include "SymbolTable.hpp"

namespace TPJparser {
    namespace Semantic {

        class Scope: public std::vector<SymbolTable> {
            public:
                std::shared_ptr<SymbolTableItem> define(const std::string& name, SymbolTableItem::Kind kind);
                std::shared_ptr<SymbolTableItem> getItemByName(const std::string& name) const;

                bool isDefined(const std::string& name, SymbolTableItem::Kind kind) const;
                void enterScope();
                void leaveScope();
        };

    }
}