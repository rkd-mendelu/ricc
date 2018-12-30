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

    {"string foo(); int bar (int bar) {int baz; foo(bar,baz);}", {SYNTAX_ERROR, 1}},
    //            ⬑------------------------------------------------------┛ missing func body
    {"string foo(){} int bar (int bar) {int baz; foo(bar,baz);}", {SEMANTICS_ERROR, 2}},
    //                                                ⬑--------------------┛ too many params
    {"int foo(int a, float b){} int bar (int bag) {float baz; foo(bag, baz);}", {RET_OK, 3}}, //TODO void not working
    // {"int add(float a, float b){return a + b;} int bar (int bag) {float lol, sad ; add(bag, sad); return lol;}", {SEMANTICS_ERROR, 4}}, // FIXME should be SEMANTICS_ERROR TODO ParseExpression(expType)
    // //                                                                                  ⬑---------------------------------┛ missmatch int/float
    {"int global(){} for(int zidan;( zidan <  motorko ); zidan = zidan + 1 ){print(9);}", {SEMANTICS_ERROR, 5}},
    //                                                                        ⬑-------------------┛ print not defined
    // {"int global(){} for(int zidan;( zidan <  motorko ); zidan = zidan + 1 ){global(9);}", {SEMANTICS_ERROR, 6}},
    // //                                                                              ⬑-------------------┛ mismatch argc // FIXME 9 should not pass
    {"int global(){} for(int zidan;( zidan <  motorko ); zidan = zidan + 1 ){global(zidan);}", {SEMANTICS_ERROR, 6}},
    //                                                                               ⬑-------------------┛ mismatch argc
    {"string }", {SYNTAX_ERROR, 7}},
    {"string a;", {RET_OK, 8}},
    {"string aa; string ret(string a ) {return a + aa;}", {RET_OK, 8}},
    {"string a; ret(string a) {return a;}", {SEMANTICS_ERROR, 9}},
    //           ⬑--------------------------------┛ ret not defined
    {"", {RET_OK, 10}}, // Note empty input




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
