#include <iostream>
#include <vector>

#include "../include/predicate.hpp"
#include "../include/default.hpp"

bool first_order_language::Predicate::execute(const std::vector <SigEType> &value) {
    return executor_(value);
}

std::string first_order_language::Predicate::getName() const{
    return name_;
}