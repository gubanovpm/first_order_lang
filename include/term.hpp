#pragma once
#include <iostream>
#include <vector>

#include "./default.hpp"
#include "./function.hpp"
#include "./predicate.hpp"

namespace first_order_language {

// for the future - idk for what we needed this class

struct ITerm {
protected:
    term_kind_t kind_;
public:
    ITerm(term_kind_t kind) : kind_(kind) {}
    term_kind_t getKind() const;
    virtual void show() const = 0;
    virtual ~ITerm() {}
};

struct TermC final : public ITerm {
private:
    SigEType value_;
public:
    TermC() : ITerm(TERM_C) {}
    void set_value(SigEType value) {value_ = value;}
    void show() const override;
};

struct TermV : public ITerm {
protected:
    std::string name_;
public:
    TermV(term_kind_t kind = TERM_V) : ITerm(kind) {}
    void set_name(std::string name) { name_ = name; }
    void show() const override;
};

struct TermF final : public TermV {
private:
    Function *function_;
public: 
    std::vector< ITerm * > arguments_;
    
    TermF(): TermV(TERM_F) {}
    void show() const override;
};

struct TermP final : public TermV {
private:
    Predicate *predicate_;
public:
    std::vector< ITerm * > arguments_;

    TermP() : TermV(TERM_P) {}
    void show() const override;

};

ITerm *read_term(std::string buffer, size_t &state);

}