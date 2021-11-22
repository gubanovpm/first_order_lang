#include <iostream>

#include "../include/signature.hpp"
#include "../include/lexer.hpp"

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
  
  return 0;
}
