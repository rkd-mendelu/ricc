#include <memory>

#include "SymbolTable.hpp"
#include "util/Logger.hpp"

namespace TPJparser {

    SymbolTable::SymbolTable()
      : _func(true)
      ,  _nextOffset(0)
      , _breakable(-1)
    {}

    SymbolTable::SymbolTable(long offset)
      : _func(false)
      , _nextOffset(offset)
      , _breakable(-1)
    {}

    long SymbolTable::getNextOffset() const {
        return this->_nextOffset;
    }

    std::shared_ptr<SymbolTableItem> SymbolTable::defineVar(const std::string& name) {
        if (this->_table.count(name) == 0) {
            auto item = std::make_shared<SymbolTableItem>
                    (name, SymbolTableItem::Kind::VARIABLE);
            item->setOffset(this->_nextOffset);
            this->_nextOffset++;
            return this->_table[name] = item;
        }

        return nullptr;
    }

    std::shared_ptr<SymbolTableItem> SymbolTable::defineFunc(const std::string& name) {
        if (this->_table.count(name) == 0)
            return this->_table[name] =
                std::make_shared<SymbolTableItem>
                    (name, SymbolTableItem::Kind::FUNCTION);

        return nullptr;
    }

    std::shared_ptr<SymbolTableItem> SymbolTable::getItemByName(const std::string& name) const {
        if (this->_table.count(name) == 0)
            return nullptr;

        return this->_table.at(name);
    }

    bool SymbolTable::isFuncDeclared(const std::string& name) const {
        const auto item = this->getItemByName(name);

        if (item.get() != nullptr) {
            if (item.get()->isFunc())
                return true;
        }
        return false;
    }

    bool SymbolTable::isVarDeclared(const std::string& name) const {
        const auto item = this->getItemByName(name);

        if (item.get() != nullptr) {
            if (item.get()->isVar())
                return true;
        }
        return false;
    }

    void SymbolTable::printContent() const {
      DEBUG("isFunc: " << this->_func);
      DEBUG("nextOffset: " << this->_nextOffset);
      DEBUG("breakable: " << this->_breakable);

        DEBUG("Breaks:");
        for (auto& item: this->_breaks) {
          DEBUG(item);
        }

        for (auto& item: this->_table) {
          item.second->print();
        }
    }

    bool SymbolTable::isFuncScope() const {
        return this->_func;
    }

    void SymbolTable::setBreakable() {
        this->_breakable = true;
    }

    bool SymbolTable::isBreakable() const {
        return this->_breakable > 0;
    }

    void SymbolTable::addBreak(long address) {
        this->_breaks.push_back(address);
    }

    std::vector<long>& SymbolTable::getBreaks() {
      return this->_breaks;
    }

    void SymbolTable::addContinue(long address) {
        this->_continues.push_back(address);
    }

    std::vector<long>& SymbolTable::getContinues() {
        return this->_continues;
    }

}
