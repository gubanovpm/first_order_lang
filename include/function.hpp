#pragma once

#include <iostream>
#include <vector>
#include "./default.hpp"

namespace first_order_language {

struct Function final{
private:
    std::string name_;
    size_t valence_;
    SigEType (* executor_)(std::vector <SigEType>);
    std::vector < SigEType > consts_;
public:
    Function(std::string name, size_t valence, SigEType (* executor)(std::vector <SigEType>)) :
        name_(name), 
        valence_(valence), 
        executor_(executor) {
    }

    SigEType execute(const std::vector <SigEType> &value);
    std::string getName() const;
    size_t getValence() const;
    std::vector < SigEType > *getConsts(); 
};

}

static std::vector < first_order_language::Function > __default_functions__ = { {"+"  ,  2, first_order_language::executeADD2 }, 
                                                          {"+S" ,  1, first_order_language::executeS1   }, 
                                                          {"+SM",  1, first_order_language::executeS1M  }, 
                                                          {"+M" ,  2, first_order_language::executeADD2M}, 
                                                          {"*"  ,  2, first_order_language::executeMUL2 }, 
                                                          {"*M" ,  2, first_order_language::executeMUL2M} };