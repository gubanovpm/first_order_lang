#pragma once

#include "./default.hpp"

namespace first_order_language {

struct Predicate final{
private:
    std::string name_;
    size_t valence_;
    bool (* executor_)(std::vector <SigEType>);
public:
    Predicate(std::string name, size_t valence, bool (* executor)(std::vector <SigEType>)) :
        name_(name), 
        valence_(valence), 
        executor_(executor) {
    };

    std::string getName() const;
    size_t getValence() const;
    bool execute(const std::vector <SigEType> &value);

};

static std::vector <Predicate> __default_predicates__ = { {"<" , 2, executeLess2  }, 
                                                                {">" , 2, executeMore2  }, 
                                                                {"=" , 2, executeEqual2 },
                                                                {"<>", 2, executeNEqual2}, 
                                                                {"<=", 2, executeLessEq2}, 
                                                                {">=", 2, executeMoreEq2} };

}

