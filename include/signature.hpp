#pragma once
#include <iostream>
#include <vector>

#include "./default.hpp"
#include "./predicate.hpp"
#include "./function.hpp"

namespace first_order_language {

struct Signature final{
private:
    std::vector < SigEType  > constants_  = {};
    std::vector < Predicate > predicates_ = {};
    std::vector < Function  > functions_  = {};
public:
    Signature();
    Signature(const Signature &other) = delete;
    Signature(Signature &&other) = delete;

    Signature &operator=(const Signature &other) = delete;
    Signature &operator=(Signature &&other) = delete;

    ~Signature() = default;

    std::vector < SigEType  > *constants () { return &constants_ ; }
    std::vector < Predicate > *predicates() { return &predicates_; }
    std::vector < Function  > *functions () { return &functions_ ; }

    void show() const;
};

}
