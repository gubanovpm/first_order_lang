#pragma once

#include <iostream>
#include <vector>
#include <unordered_set>

#include "./signature.hpp"
#include "./function.hpp"
#include "./predicate.hpp"
#include "./default.hpp"

namespace first_order_language {

class FiniteInterpretation {
private:
    inline static const size_t __MAX_COUNT__ = 2000;
    void recursive_cursed_function(std::unordered_set < SigEType > *, std::vector<SigEType> *, Function *, size_t);

public:
                  std::unordered_set < SigEType >   M_;
    std::vector < std::unordered_set < SigEType > > I_;

    FiniteInterpretation(Signature &signature);
};

}