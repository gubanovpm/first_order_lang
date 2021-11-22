#include <iostream>
#include <vector>

#include "./default.hpp"
#include "./function.hpp"
#include "./predicate.hpp"

namespace first_order_language {

struct ITerm {
protected:
    term_kind_t kind_;
public:
    term_kind_t getKind() const;
    virtual void show() const = 0;
    virtual ~ITerm() {}
};

struct TermC final : public ITerm {
private:
    SigEType value_;
public:
    void show() const override;
};

struct TermV : public ITerm {
protected:
    std::string name_;
public:
    void show() const override;
};

struct TermF final : public TermV {
private:
    Function *function_;
    std::vector< ITerm * > arguments_;
public: 
    void show() const override;
};

struct TermP final : public TermV {
private:
    Predicate *predicate_;
    std::vector< ITerm * > arguments_;
public:
    void show() const override;

};

}