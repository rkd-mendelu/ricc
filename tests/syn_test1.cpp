/**
 * basic expression test
 */

#include <iostream>
#include <string>
#include <sstream>
#include <map>

#include "lex/Token.hpp"
#include "lex/Lex.hpp"
#include "syntax/Syntax.hpp"

std::map < std::string, std::pair<int, int> > tests {
    /* input value, return, testnumber */

    {"int main () {}", {RET_OK, 1}},
    {"int main () {} int main () {}", {RET_OK, 2}},
    {"int foo () {return a;}", {RET_OK, 3}},
    {"int bar () {a=9;}", {RET_OK, 4}},
    {"int bar () {a=(;}", {EXPRESSION_ERROR, 5}},
    //               ⬑------------┛
    {"int bar () {foo();}", {RET_OK, 6}},
    {"int bar () {foo(bar);}", {RET_OK, 7}},
    {"int bar () {foo(bar,);}", {EXPRESSION_ERROR, 8}}, // FIXME WAS SYNTAX_ERROR now EXPRESSION_ERROR
    //                   ⬑------------┛
    {"int bar () {foo(bar,baz);}", {RET_OK, 9}},
    {"int bar () {foo(bar,baz); return a;}", {RET_OK, 10}},
    {"int bar () {foo(bar,baz); return a}", {SYNTAX_ERROR, 11}},
    //                                  ⬑------------┛
    {"int bar () {foo(bar,9); return a}", {SYNTAX_ERROR, 12}},
    //                                ⬑------------┛
    {"int bar () {foo(bar,9); return a;}", {RET_OK, 13}},
    {"int bar () {foo(bar=baz,9); return a;}", {RET_OK, 14}},
    {"int bar () {foo(bar=,9); return a;}", {EXPRESSION_ERROR, 15}},
    //                    ⬑-----------------------┛
    {"int bar () {foo(bar=baz,boo=9); return a;}", {RET_OK, 16}},
    {"int bar () {foo(bar=baz,200=9); return a;}", {RET_OK, 17}},
    {"int main (int argc) {foo(bar9); return a;}", {RET_OK, 18}},
    {"int main (int argc, string argv) {foo(bar9); return a;}", {RET_OK, 18}},
    {"int main (int argc, string ) {foo(bar9); return a;}", {SYNTAX_ERROR, 19}},
    //                          ⬑----------------------------------┛
    {"int main (int argc ;) {foo(bar9); return a;}", {SYNTAX_ERROR, 19}},
    //                   ⬑----------------------------------┛
    {"int main (int argc) {string candy; foo(bar9); return a;}", {RET_OK, 20}},
    {"int main (int argc) {string; foo(bar9); return a;}", {SYNTAX_ERROR, 21}},
    //                           ⬑--------------------------------┛
    {"int main (int argc) {string candy, shop; foo(bar9); return a;}", {RET_OK, 22}},
    {"int main (int argc) {string candy, shop;; foo(bar9); return a;}", {SYNTAX_ERROR, 23}},
    //                                        ⬑--------------------------------┛
    {"int main (int argc) {string candy=shop; foo(bar9); return a;}", {RET_OK, 24}},
    {"int main (int argc) {string candy=shop, asdf=\"Ahoj\"; foo(bar9); return a;}", {RET_OK, 25}},
    {"int main (int argc) {string candy=shop, asdf=\"Ahoj\" return a;}", {SYNTAX_ERROR, 26}},
    //                                                     ⬑--------------------┛
    {"int david () {if(zidan){print(9);} return sufurki;}", {RET_OK, 27}},
    {"int david () {if( ){print(9);} return sufurki;}", {EXPRESSION_ERROR, 28}},
    //                 ⬑-------------------------------------------┛
    {"int david () {if(zidan){print(9)} return sufurki;}", {SYNTAX_ERROR, 29}},
    //                               ⬑----------------------------┛
    {"int david () {if(zidan){print(9);}else{return sufurki;}}", {RET_OK, 30}},
    {"int david () {if(zidan){print(9);}else; return sufurki;}", {SYNTAX_ERROR, 31}},
    //                                      ⬑---------------------------┛
    {"int david () {if(zidan){print(9);}else{a=9} return sufurki;}", {SYNTAX_ERROR, 32}},
    //                                          ⬑---------------------------┛
    {"int david () {if(zidan){if(motorko){print(9);}else{}}else{return sufurki;}}", {RET_OK, 33}},
    {"int david () {while(zidan){if(motorko){print(9);}else{}}return sufurki;}", {RET_OK, 34}},
    {"int david () {while( ){if(motorko){print(9);}else{}}return sufurki;}", {EXPRESSION_ERROR, 35}},
    //                    ⬑---------------------------------------------------------┛
    {"int david () {while(zidan)if(motorko){print(9);}else{}}return sufurki;}", {SYNTAX_ERROR, 36}},
    //                          ⬑---------------------------------------------------------┛
    {"int david () {while(zidan){if(motorko){print(9);}else{zidan=motorko},}return sufurki;}", {SYNTAX_ERROR, 37}},
    //                                                                    ⬑----------------------------┛
    {"int zidan () {for(int zidan; zidan<motorko; motorko = zidan){print(9);}}", {RET_OK, 38}},
    {"int zidan () {for( ; zidan<motorko; motorko = zidan){print(9);}}", {SYNTAX_ERROR, 39}},
    //                  ⬑-------------------------------------------------------┛
    {"int zidan () {for(int zidan; ; motorko = zidan){print(9);}}", {EXPRESSION_ERROR, 40}},
    //                            ⬑--------------------------------------------┛
    {"int zidan () {for(int zidan;( zidan <  motorko ); ){print(9);}}", {SYNTAX_ERROR, 41}},
    //                                                 ⬑-----------------------┛
    {"int global(){} for(int zidan;( zidan <  motorko ); zidan = zidan + 1 ){print(9);}", {RET_OK, 42}},
    {"int global(){}; for(int zidan;( zidan <  motorko ); zidan = zidan + 1 ){print(9);}", {SYNTAX_ERROR, 42}},
    //              ⬑----------------------------------------------------------------------------┛ SEMICOLON without statement - Note func definition
};

int main()
{
    int count = 0;

    for (auto t: tests){

        std::cout << "Value: " << "\"" << t.first << "\"" << std::endl;
        std::string input(t.first);
        std::stringstream ss(input);
        TPJparser::Syntax syntax(ss);

        int rc = 0;
        syntax.setSemanticsCheck(false); // disable semantics checking
        rc = syntax.Parse();


        std::cout << "Testnumber: " << t.second.second << " Got: " << rc << " Expected: " <<  t.second.first << std::endl;

        if (rc != t.second.first) {
            std::cout << "ERROR! RC does not match" << std::endl;
            count++;
        }

        std::cout << std::endl;
    }

    return count;
}
