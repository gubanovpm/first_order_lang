#include "../include/signature.hpp"
#include "../include/default.hpp"
#include "../include/predicate.hpp"
#include "../include/function.hpp"

#include "../include/default.hpp"
#include "../include/global.hpp"

first_order_language::Signature::Signature() {
    std::cout << "Starting signature initialize...\nPlease, enter the signature fields : Constants Functions Predicates" << std::endl ;

    size_t c_count_, p_count_, f_count_;
    std::cin  >> c_count_ ; SigEType x;
    for (int i = 0; i < (int)c_count_ ; ++i) {
        std::cin >> x ; constants_.push_back(x);
    }

    std::cin >> f_count_ ; std::string temp_function_name = "" ;
    for (int i = 0 ; i < (int)f_count_; ++i) {
        std::cin >> temp_function_name;

        bool isExist = false;
        for (int j = 0; j < __default_functions__.size() ; ++j) {

            if (__default_functions__[j].getName() == temp_function_name) {
                if (temp_function_name == "+M" || temp_function_name == "*M" || temp_function_name == "+SM") {
                    int mod = 1;
                    std::cin >> mod ; 
                    if (mod == 0) { std::cout << "wrong modul operation with 0\n"; exit(1); } 
                    __default_functions__[j].getConsts()->push_back(mod);
                    // std::cout << "|" << __default_functions__[j].getName() << "|" << std::endl;
                    // std::cout << "cur size consts_ = " << __default_functions__[j].getConsts()->size() << std::endl;
                    functions_.push_back(__default_functions__[j]);
                } else
                    functions_.push_back(__default_functions__[j]);
                isExist = true;
                break;
            }
        }

        if (!isExist) { std::cout << "undefiend function " << temp_function_name << std::endl; exit(1); }
    }

    std::cin >> p_count_ ; std::string temp_predicate_name = "" ;
    for (int i = 0 ; i < (int)p_count_ ; ++i) {
        std::cin >> temp_predicate_name ; 

        bool isExist = false;
        for (int j = 0 ; j < first_order_language::__default_predicates__.size() ; ++j) {
            if (__default_predicates__[j].getName() == temp_predicate_name) {
                predicates_.push_back(first_order_language::__default_predicates__[j]);
                isExist = true;
                break;
            }
        }

        if (!isExist) { std::cout << "undefiend predicate " << temp_predicate_name << std::endl; exit(1); }
    }
}

void first_order_language::Signature::show() const{
    std::cout << "( " ;
    for (int i = 0; i < constants_.size() - 1; ++i) std::cout << constants_[i] << ", ";
    if (constants_.size() - 1 >= 0) std::cout << constants_[constants_.size() - 1]; std::cout << " ; " ;

    for (int i = 0; i < functions_.size() - 1; ++i) std::cout << functions_[i].getName() << ", ";
    if (functions_.size() - 1 >= 0) std::cout << functions_[functions_.size() - 1].getName(); std::cout << " ; " ;

    for (int i = 0; i < predicates_.size() - 1; ++i) std::cout << predicates_[i].getName() << ", ";
    if (predicates_.size() - 1 >= 0) std::cout << predicates_[predicates_.size() - 1].getName(); std::cout << " )" << std::endl ;
}