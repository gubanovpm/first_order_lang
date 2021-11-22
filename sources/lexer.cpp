#include "../include/lexer.hpp"

void first_order_language::LexemB::show()  const {
    if (kind_ == LBRAC) std::cout << "(" ;
    else std::cout << ")";
}

void first_order_language::LexemOP::show() const {
    switch (kind_) {
        case OP_NOT : std::cout << "~"  ; break;
        case OP_AND : std::cout << "&"  ; break;
        case OP_IMPL: std::cout << "->" ; break;
        case OP_OR  : std::cout << "|"  ; break;
        default: std::cout << "Unknown lexem operation type :(\n" ; exit(1);
    }
}

void first_order_language::LexemF::show()  const {
    std::cout << name_;
}

void first_order_language::LexemQ::show() const {
    if (kind_ == QUANTIFIER_ANY) std::cout << "!A" ;
    else std::cout << "!E" ;
}

void first_order_language::Lexer::show() const {
    std::cout << "Lexer result is : " ;
    for (int i = 0; i < lexems_.size(); ++i) {
        std::cout << "< " ;
        lexems_[i]->show();
        std::cout << " >   " ;
    }
    std::cout << std::endl;
}

first_order_language::Lexer::~Lexer () {
    for (int i = 0; i < lexems_.size(); ++i) delete lexems_[i];
}

bool first_order_language::isFunction(char c) {
    return (c == '<' || c == '>' || c == '*' || c == '+' || c == ':' || c == '=');
}

first_order_language::Lexer::Lexer(std::string buffer) {
    size_t state = 0;
    while (state < buffer.size()) {
        while (isspace(buffer[state]) && state < buffer.size())
            ++state;

        switch (buffer[state]) {
            case '(' : lexems_.push_back(new LexemB (LEX_BRACKET, LBRAC)); break;
            case ')' : { lexems_.push_back(new LexemB (LEX_BRACKET, RBRAC)); break; }
            case '&' : { lexems_.push_back(new LexemOP(LEX_OPERATION, OP_AND)); break; }
            case '|' : { lexems_.push_back(new LexemOP(LEX_OPERATION, OP_OR)); break; }
            case '~' : { lexems_.push_back(new LexemOP(LEX_OPERATION, OP_NOT)); break; }
            case '-' : {
                ++state;
                if (buffer[state] == '>') { lexems_.push_back(new LexemOP(LEX_OPERATION, OP_IMPL)); break; }
                else { std::cout << state << ": <" << buffer[state] << ">" << std::endl; std::cout << "unknown logical operation - "; exit(1); }
            }
            case '!': {
                ++state;
                if (buffer[state] == 'A') { lexems_.push_back(new LexemQ(LEX_QUANTIFIER, QUANTIFIER_ANY)); break; }
                if (buffer[state] == 'E') { lexems_.push_back(new LexemQ(LEX_QUANTIFIER, QUANTIFIER_EXIST)); break; }
                std::cout << state << ": <" << buffer[state] << ">" << std::endl;
                std::cout << "unknown quantifier" << std::endl ; exit(1) ;
            }
            case ',' : { break; }

            default: {
                if (isalpha(buffer[state]) || isdigit(buffer[state]) || isFunction(buffer[state])) {
                    std::string name = "" ;
                    while (isalpha(buffer[state]) || isdigit(buffer[state]) || isFunction(buffer[state])) {
                        name += buffer[state]; 
                        ++state;
                    }
                    --state;
                    lexems_.push_back(new LexemF(LEX_FUNCT, name));
                    break;
                }
                std::cout << state << ": <" << buffer[state] << ">" << std::endl;
                std::cout << "uncorrect name" << std::endl;
                exit(1);
            }
        }

        ++state;
    }
}