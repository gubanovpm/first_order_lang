#include "../include/term.hpp"
#include "../include/lexer.hpp"
#include "../include/predicate.hpp"
#include "../include/function.hpp"

void first_order_language::TermC::show() const {
    std::cout << value_ ;
}

void first_order_language::TermV::show() const {
    std::cout << name_ ;
}

void first_order_language::TermF::show() const {
    std::cout << name_ << "(" ;
    for (int i = 0; i < function_->getValence() - 1; ++i) {
        arguments_[i]->show(); std::cout << ", " ;
    }
    if (function_->getValence() - 1 >= 0) arguments_[function_->getValence() - 1]->show(); 
    std::cout << ")" ;
}

void first_order_language::TermP::show() const {
    std::cout << name_ << "(" ;
    for (int i = 0; i < predicate_->getValence() - 1; ++i) {
        arguments_[i]->show(); std::cout << ", " ;
    }
    if (predicate_->getValence() - 1 >= 0) arguments_[predicate_->getValence() - 1]->show(); 
    std::cout << ")" ;
}

first_order_language::term_kind_t first_order_language::ITerm::getKind() const {
    return kind_;
}

first_order_language::ITerm *first_order_language::read_term(std::string buffer, size_t &state) {
    Lexer lexems(buffer);
    size_t number = 0;
    for (; number < __default_functions__.size(); ++number) {
        if (lexems[state]->name() == __default_functions__[number].getName()) break;
    }
    if (number < __default_functions__.size()) {
        ++state;
            if (lexems[state]->kind() != LBRAC) {std::cout << "read term: error\n"; exit(1); }
            TermP *new_term = new TermP();
            for (int i = 0; i < __default_predicates__[number].getValence(); ++i) {
                new_term->arguments_.push_back(read_term(buffer, state));
            }
            ++state;
            if (lexems[state]->kind() != RBRAC) {std::cout << "read term: error\n"; exit(1); }
            return new_term;
    } else {
        number = 0;
        for (; number < __default_predicates__.size(); ++number)
            if (lexems[state]->name() == __default_predicates__[number].getName()) break;
        if (number < __default_predicates__.size()) {
            ++state;
            if (lexems[state]->kind() != LBRAC) {std::cout << "read term: error\n"; exit(1); }
            TermP *new_term = new TermP();
            for (int i = 0; i < __default_predicates__[number].getValence(); ++i) {
                new_term->arguments_.push_back(read_term(buffer, state));
            }
            ++state;
            if (lexems[state]->kind() != RBRAC) {std::cout << "read term: error\n"; exit(1); }
            return new_term;
        } else {
            if (isdigit(lexems[state]->name()[0])) {
                TermC *new_term = new TermC();
                SigEType res = std::atoi(lexems[state]->name().data());
                new_term->set_value(res);
                ++state;
                return new_term;
            } else {
                TermV *new_term = new TermV();
                new_term->set_name(lexems[state]->name());
                ++state;
                return new_term;
            }
        }
    }
}