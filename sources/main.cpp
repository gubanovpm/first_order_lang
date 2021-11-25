#include <iostream>

#include "../include/signature.hpp"
#include "../include/lexer.hpp"
#include "../include/formula.hpp"

int main () {
  #if 0
  first_order_language::Signature sign = {};
  sign.show();
  #endif

  #if 1
  std::string test_lexer;
  std::getline(std::cin, test_lexer);
  first_order_language::Lexer lexems(test_lexer);
  lexems.show();
  #endif

  #if 1
  first_order_language::Formula parser(test_lexer);
  parser.show();
  #endif
  
  return 0;
}
