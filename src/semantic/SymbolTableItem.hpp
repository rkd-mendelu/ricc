#pragma once

#include <vector>
#include <memory>
#include <map>
#include <unordered_map>
#include "lex/Token.hpp"

namespace TPJparser {

    class SymbolTableItem {
        public:

            enum Kind {
                UNKNOWN,
                VARIABLE,
                FUNCTION,
            };

            enum Type {
                INT = Token::KW_INT,
                BOOL = Token::KW_BOOL,
                FLOAT = Token::KW_FLOAT,
                VOID = Token::KW_VOID,
                STRING = Token::KW_STRING,
            };

            static const std::map<Type, std::string> TypeMap;

            SymbolTableItem(std::string key, Kind kind);

            void setType(Type t);
            Type getType() const;

            void setOffset(long offset);
            long getOffset() const;

            bool isFunc() const;
            bool isVar() const;

            void addArg(Type t, std::string &name);
            std::vector<std::pair<Type, std::string>>& getArgs();

            void print() const;

        private:
            std::string _key;
            Kind _itemKind;
            Type _type;
            std::vector<std::pair<Type, std::string>> _args;

            long _offset;
    };

}