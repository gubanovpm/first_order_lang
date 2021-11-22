#include <iostream>
#include <vector>

#include "../include/default.hpp"
#include "../include/function.hpp"

SigEType first_order_language::Function::execute(const std::vector <SigEType> &value) {
    return executor_(value);
}

std::string first_order_language::Function::getName() const{
    return name_;
}

size_t first_order_language::Function::getValence() const {
    return valence_;
}