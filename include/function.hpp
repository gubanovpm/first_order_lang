#pragma once

namespace first_order_language {

struct Function {
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
};

static const std::vector < Function > __default_functions__ = { {"+",  2, executeADD2 }, 
                                                                {"S",  1, executeS1   }, 
                                                                {"SM", 1, executeS1M  }, 
                                                                {"+M", 2, executeADD2M}, 
                                                                {"*",  2, executeMUL2 }, 
                                                                {"*M", 2, executeMUL2M} };

}