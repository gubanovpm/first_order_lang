#pragma once

#include <iostream>
#include <vector>

#include "./default.hpp"

namespace first_order_language {

bool isFunction(char c);

enum lexem_kind_t      {LEX_BRACKET = 11, LEX_OPERATION, LEX_FUNCT, LEX_QUANTIFIER};
enum bracket_kind_t    {LBRAC = 21, RBRAC};
enum operation_kind_t  {OP_OR = 31, OP_AND, OP_IMPL, OP_NOT};
enum quantifier_kind_t {QUANTIFIER_ANY = 41, QUANTIFIER_EXIST};

struct ILexem {
protected:
    lexem_kind_t type_;
public:
    ILexem(lexem_kind_t type) :
        type_(type) {}
    virtual void show() const = 0;
    lexem_kind_t getType() const { return type_; }
    virtual int kind() const = 0;
    virtual ~ILexem() {}
};

struct LexemB final : public ILexem {
private:
    bracket_kind_t kind_;
public:
    LexemB(lexem_kind_t type, bracket_kind_t kind) :
        ILexem(type), kind_(kind) {}
    void show() const override;
    int kind() const override;
    ~LexemB() {}
};

struct LexemOP final : public ILexem {
private:
    operation_kind_t kind_;
public:
    LexemOP(lexem_kind_t type, operation_kind_t kind) :
        ILexem(type), kind_(kind) {}
    void show() const override;
    int kind() const override;
};

struct LexemF final : public ILexem {
private:
    std::string name_;
public:
    LexemF(lexem_kind_t type, std::string name) :
        ILexem(type), name_(name) {}
    void show() const override;
    int kind() const override;
};

struct LexemQ final : public ILexem {
private:
    quantifier_kind_t kind_;
public:
    LexemQ(lexem_kind_t type, quantifier_kind_t kind) :
        ILexem(type), kind_(kind) {}
    void show() const override;
    int kind() const override;
};

struct Lexer {
private:
    std::vector < ILexem * > lexems_;
public:

    Lexer(std::string buffer = "");
    size_t size() const { return lexems_.size(); }
    ILexem *operator[](size_t number) const{ return lexems_[number]; }
    void show() const;
    virtual ~Lexer();

//rule of five
    Lexer(const Lexer &other) = delete;
    Lexer(Lexer &&other) = delete;
    Lexer &operator= (const Lexer &other) = delete;
    Lexer &operator= (Lexer &&other) = delete;

};

}