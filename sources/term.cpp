#include "../include/term.hpp"
#include "../include/lexer.hpp"

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