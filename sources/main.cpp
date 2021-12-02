#include <iostream>

#include "../include/signature.hpp"
#include "../include/lexer.hpp"
#include "../include/formula.hpp"
#include "../include/finite_interpretation.hpp"

int main () {
  #if 1
  first_order_language::Signature sign = {};
  std::cout << "Current readed signature is: " ;
  sign.show();
  #endif

  #if 1
  std::string test_lexer;
  std::getline(std::cin, test_lexer); // to correct example reading
  std::getline(std::cin, test_lexer);
  first_order_language::Lexer lexems(test_lexer);
  // lexems.show();
  #endif

  #if 1
  first_order_language::Formula parser(test_lexer);
  parser.show();
  #endif

  #if 1
  first_order_language::FiniteInterpretation result(sign);
  
  #endif
  return 0;
}
