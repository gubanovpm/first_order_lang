#include "../include/formula.hpp"
#include "../include/lexer.hpp"

first_order_language::Formula::Formula(const Lexer &lexems) {
    size_t state = 0;
    root_ = parse_expr(lexems, state);
    if (state < lexems.size()) { std::cout << "parse error" << std::endl; exit(1); }
     
}