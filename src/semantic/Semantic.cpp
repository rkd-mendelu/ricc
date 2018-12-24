
#include "util/Logger.hpp"
#include "Semantic.hpp"

namespace TPJparser {
    namespace Semantic {

            std::shared_ptr<SymbolTableItem> Scope::define(const std::string& name, SymbolTableItem::Kind kind) {
                auto& table = this->back();

                switch(kind) {
                    case SymbolTableItem::Kind::FUNCTION:
                        return table.defineFunc(name);

                    case SymbolTableItem::Kind::VARIABLE:
                        return table.defineVar(name);

                    default:
                        DEBUG("Default branch: should never happen!");
                        return nullptr;
                }
            }

            std::shared_ptr<SymbolTableItem> Scope::getItemByName(const std::string& name) const {
                for (auto i = this->rbegin() ; i != this->rend() ; ++i) {
                    auto ptr = i->getItemByName(name);
                    if (ptr.get() != nullptr) {
                        return ptr;
                    }
                }
                return nullptr;
            }

            bool Scope::isDefined(const std::string& name, SymbolTableItem::Kind kind) const {
                bool defined = false;
                for (vector<SymbolTable>::const_reverse_iterator table = this->crbegin(); table != this->crend(); ++table ) {
                    if (defined) break;
                    switch(kind) {
                        case SymbolTableItem::Kind::FUNCTION:
                            defined = table->isFuncDeclared(name);
                            break;

                        case SymbolTableItem::Kind::VARIABLE:
                            defined = table->isVarDeclared(name);
                            break;

                        default:
                            DEBUG("Default branch: should never happen!");
                            defined = false;
                            break;
                    }
                }
                return defined;

            }

            void Scope::enterScope() {
                this->push_back(SymbolTable());
            }

            void Scope::leaveScope() {
                this->pop_back();
            }

            void Scope::printScope() const {
                this->back().printContent();
            }

    } // Semanctic
}
