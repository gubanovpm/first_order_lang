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
            valence  = it->getValence();

            for (int i = 0; i < it->getConsts()->size(); ++i)
                arguments.push_back((*it->getConsts())[i]);

            recursive_cursed_function(&M_, &arguments, &(*it), valence);
            arguments.pop_back();
        }
    }
    // created M_, now we want to get I_

    for (int i = 0; i < M_.size(); ++i) {
        std::unordered_set < SigEType > temp_set = {};
        for (auto it = signature.functions()->begin(); it != signature.functions()->end(); ++it) {
            valence  = it->getValence();

            for (int i = 0; i < it->getConsts()->size(); ++i)
                arguments.push_back((*it->getConsts())[i]);

            recursive_cursed_function(&temp_set, &arguments, &(*it), valence);
            arguments.pop_back();
        }
        I_.push_back(temp_set);
    }

    std::cout << "Interpretate body (M): " ;
    for (auto it = M_.begin(); it != M_.end(); ++it) {
        std::cout << *it << " " ;
    } 
    std::cout << std::endl;

    std::cout << "for every elements (I):" << std::endl ;
    auto iter = M_.begin();
    for (auto it1 = I_.begin(); it1 != I_.end(); ++it1, ++iter) {
        std::cout << *iter << ": " ;
        for (auto it2 = it1->begin(); it2 != it1->end(); ++it2) {
            std::cout << *it2 << " ";
        }
        std::cout << std::endl;
    }
}

void first_order_language::FiniteInterpretation::recursive_cursed_function(std::unordered_set < SigEType > *where, std::vector<SigEType> *set, Function *maker, size_t last_var_count) {
    if (last_var_count == 0) { where->insert(maker->execute(*set)); return; }
    if (M_.size() > __MAX_COUNT__ || last_var_count  < 0) return;
    // std::cout << "go deep\n" ;
    int d = 0;
    for (auto it = M_.begin(); it != M_.end(); ++it, ++d) {
        --last_var_count; set->push_back(*it);
        // std::cout << "d = " << *it << std::endl ;
        recursive_cursed_function(where, set, maker, last_var_count);
        ++last_var_count; set->pop_back();
    }
    // std::cout << "go up\n" ;
}