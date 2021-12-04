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

  std::string test_lexer;
  std::getline(std::cin, test_lexer); // to correct example reading
  std::getline(std::cin, test_lexer);
  first_order_language::Lexer lexems(test_lexer);
  #if 0
  lexems.show();
  #endif

  #if 1
  first_order_language::FiniteInterpretation result(sign);
  #endif

  #if 1
  first_order_language::Formula parser(test_lexer, &result);
  parser.show();
  std::cout << "Models result : " << parser.models() << std::endl;
  #endif

  return 0;
}
