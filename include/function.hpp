#pragma once

#include <iostream>
#include "./default.hpp"

namespace first_order_language {

struct Function final{
private:
    std::string name_;
    size_t valence_;
    SigEType (* executor_)(std::vector <SigEType>);
public:
    Function(std::string name, size_t valence, SigEType (* executor)(std::vector <SigEType>)) :
        name_(name), 
        valence_(valence), 
        executor_(executor) {
    }

    SigEType execute(const std::vector <SigEType> &value);
    std::string getName() const;
    size_t getValence() const;
};

static std::vector < Function > __default_functions__ = { {"+"  ,  2, executeADD2 }, 
                                                                {"+S" ,  1, executeS1   }, 
                                                                {"+SM",  2, executeS1M  }, 
                                                                {"+M" ,  3, executeADD2M}, 
                                                                {"*"  ,  2, executeMUL2 }, 
                                                                {"*M" ,  3, executeMUL2M} };

}