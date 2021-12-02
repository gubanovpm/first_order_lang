#include <iostream>
#include <vector>

#include "../include/finite_interpretation.hpp"
#include "../include/signature.hpp"

first_order_language::FiniteInterpretation::FiniteInterpretation(Signature &signature) {
    for (int i = 0; i < signature.constants()->size(); ++i) {
        M_.insert(signature.constants()[0][i]);
    }
    std::vector<SigEType> arguments = {}; 
    size_t old_sz = 0, valence = 0;

    while (old_sz != M_.size()) {
        old_sz = M_.size();
        for (auto it = signature.functions()->begin(); it != signature.functions()->end(); ++it) {
            if (it->getName() == "+SM" || it->getName() == "+M" || it->getName() == "*M") {
                arguments.push_back(3);
                --valence;
            }
            recursive_cursed_function(&arguments, &(*it), 2);
            arguments.pop_back();
        }
    }

    std::cout << "interpretate body: " ;
    for (auto it = M_.begin(); it != M_.end(); ++it) {
        std::cout << *it << " " ;
    }
    std::cout << std::endl;
}

void first_order_language::FiniteInterpretation::recursive_cursed_function(std::vector<SigEType> *set, Function *maker, size_t last_var_count) {
    if (last_var_count == 0) { M_.insert(maker->execute(*set)); return; }
    if (M_.size() > __MAX_COUNT__ || last_var_count  < 0) return;
    // std::cout << "go deeeeeeep\n" ;
    int d = 0;
    for (auto it = M_.begin(); it != M_.end(); ++it, ++d) {
        --last_var_count; set->push_back(*it);
        // std::cout << "d = " << *it << std::endl ;
        recursive_cursed_function(set, maker, last_var_count);
        ++last_var_count; set->pop_back();
    }
    // std::cout << "goto up\n" ;
}