#include <fstream>
#include <iostream>
#include <sstream>

#include <unistd.h>

#include <ricc/ricc-parser.hpp>

int main(int argc, char** argv) {
  int rc = 0;
  if (argc < 2 || argc > 7) {
    std::cerr << "Bad arguments" << std::endl;
    return 1;
  }

  int c = 0;
  std::string address;
  std::string port = "80";
  std::string file;
  std::ifstream ff;

  while ((c = getopt(argc, argv, "f:u:p:")) != -1) {
    switch (c) {
      case 'u':
        address = optarg;
        break;
      case 'p':
        port = optarg;
        break;
      case 'f':
        file = optarg;
        break;
      case '?':
        std::cerr << "Unexpected argument!" << std::endl
                  << argv[optind] << std::endl;
        return 1;
        break;
      default:
        break;
    }
  }

  if (file != "") {
    ff.open(file);
    if (!ff.is_open()) {
      std::cerr << "File: " << file << " does not exist!" << std::endl;
      return 1;
    }
  }

  RICC::Parser parser(file != "" ? ff : std::cin);
  parser.SetServerDetails(address, port);
  rc = parser.Parse();
  if (rc) {
    std::cerr << "Cannot parse input" << std::endl;
    goto BAD;
  }

  rc = parser.Run();
  if (rc) {
    std::cerr << "Interpret error" << std::endl;
    goto BAD;
  }

  if (file != "") {
    ff.close();
  }
  return 0;

BAD:
  if (file != "") {
    ff.close();
  }
  return rc;
}
