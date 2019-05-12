/**
 * Library interface
 */

#pragma once

#include <iostream>
#include <memory>

namespace RICC {

class ParserPrivate;
class Parser {
 public:
  Parser(std::istream& stream);
  ~Parser();
  int Parse();
  int Run();
  int SetServerDetails(const std::string& url, const std::string& port);

 private:
  std::unique_ptr<ParserPrivate> _d_pointer;
};

}  // namespace RICC
