#pragma once

#include <iostream>
#include <vector>

#include "./default.hpp"
#include "./term.hpp"

namespace first_order_language {

enum lexem_kind_t      {LEX_BRACKET = 11, LEX_OPERATION, LEX_VARIABLE, LEX_CONSTS, LEX_QUANTIFIER};
enum bracket_kind_t    {LBRAC = 21, RBRAC};
enum operation_kind_t  {OP_OR = 31, OP_AND, OP_IMPL, OP_NOT};
enum quantifier_kind_t {QUANTIFIER_ANY = 41, QUANTIFIER_EXIST};

struct ILexem {
protected:
    lexem_kind_t kind_;
public:
    virtual void show() const = 0;
    virtual ~ILexem() {}
};

struct LexemB final : public ILexem {
private:

public:

};


struct Lexer{
private:
    std::vector < ITerm * > lexems_;
public:
    Lexer(std::string buffer);
    ~Lexer();

};

}