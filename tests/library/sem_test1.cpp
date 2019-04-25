/**
 * basic expression test
 */

#include <iostream>
#include <map>
#include <sstream>
#include <string>

#include "lex/Lex.hpp"
#include "lex/Token.hpp"
#include "syntax/Syntax.hpp"

std::map<std::string, std::pair<int, int> > tests{
    /* input value, return, testnumber */

    {"string foo(); int bar (int bar) {int baz; foo(bar,baz);}",
     //           ⬑--------- missing func body
     {SYNTAX_ERROR, 1}},

    {"string foo(){} int bar (int bar) {int baz; foo(bar,baz);}",
     //                                           ⬑-- too many params
     {SEMANTICS_ERROR, 2}},

    {"int foo(int a, float b){} int bar (int bag) {float baz; foo(bag, baz);}",
     {RET_OK, 3}},  // TODO void not working

    // {"int add(float a, float b){return a + b;} int bar (int bag) "
    //  "{float lol, sad ; add(bag, sad); return lol;}", {SEMANTICS_ERROR, 4}},
    //                   ⬑-------- missmatch int/float
    // should be SEMANTICS_ERROR maybe TODO ParseExpression(expType)
    // FIXME

    // {"int global(){} for(int zidan;( zidan <  motorko );"
    // //                                           ⬑-- not defined
    //  "zidan = zidan + 1 ){print(9);}", {SEMANTICS_ERROR, 5}},

    // {"int global(){} for(int zidan;( zidan <  motorko );"
    //  " zidan = zidan + 1 ){global(zidan);}", {SEMANTICS_ERROR, 6}},
    // //                              ⬑------ mismatch argc

    {"string }", {SYNTAX_ERROR, 7}},
    {"string a;", {RET_OK, 8}},
    {"string aa; string ret(string a ) {return a + aa;}", {RET_OK, 8}},

    // {"string a; ret(string a) {return a;}",
    //  //          ⬑---- ret not defined
    //  {SEMANTICS_ERROR, 9}},

    {"", {RET_OK, 10}},  // Note empty input

    {"int foo(int a, float b){} void bar (int bag) {float baz; foo(bag, baz); "
     "return;}",
     {RET_OK, 11}},

    // {"int global(){} for(int zidan;( zidan <  motorko ); zidan = zidan + 1
    // ){global(9);}", {SEMANTICS_ERROR, 12}},
    //  // ⬑-------------------┛ mismatch argc // FIXME 9 should not pass

};

int main() {
  int count = 0;

  for (auto t : tests) {
    std::cout << "Value: "
              << "\"" << t.first << "\"" << std::endl;
    std::string input(t.first);
    std::stringstream ss(input);
    RICC::Syntax syntax(ss);

    int rc = 0;
    rc = syntax.Parse();

    std::cout << "Testnumber: " << t.second.second << " Got: " << rc
              << " Expected: " << t.second.first << std::endl;

    if (rc != t.second.first) {
      std::cout << "ERROR! RC does not match" << std::endl;
      count++;
    }

    std::cout << std::endl;
  }

  return count;
}
