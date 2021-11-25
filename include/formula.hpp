#pragma once

#include <iostream>
#include <vector>

#include "./lexer.hpp"
#include "./default.hpp"
#include "./function.hpp"
#include "./predicate.hpp"

namespace first_order_language {

enum node_kind_t {NODE_Q = 101, NODE_V, NODE_F, NODE_P, NODE_O};

struct ITreeNode {
protected:
    node_kind_t type_;
    bool isBrac = false;
public:
    ITreeNode   *left_;
    ITreeNode   *right_;

    void setBrac(bool x) { isBrac = x; }
    ITreeNode(node_kind_t type, ITreeNode *left = nullptr, ITreeNode * right = nullptr) :
        type_(type), 
        left_(left),
        right_(right) {} 
    virtual ~ITreeNode() {}
};

struct TreeNodeQ final : public ITreeNode {
private:
    quantifier_kind_t kind_;
    std::string name_;
public:
    TreeNodeQ(quantifier_kind_t kind, std::string name) : 
        ITreeNode(NODE_Q),
        kind_(kind), 
        name_(name) {}
};

struct TreeNodeV final : public ITreeNode {
private:
    std::string name_;
public:
    TreeNodeV(std::string name) :
        ITreeNode(NODE_V), 
        name_(name) {}
};

struct TreeNodeF final : public ITreeNode {
private:
    const Function  *function_;
public:
    std::vector <ITreeNode *> arguments_;
    TreeNodeF(Function *function) :
        ITreeNode(NODE_F), 
        function_(function) {}


    TreeNodeF(const Function *function) :
        ITreeNode(NODE_F), 
        function_(function) {}
};

struct TreeNodeP final : public ITreeNode {
private:
    Predicate *predicate_;
public:
    std::vector <ITreeNode *> arguments_;
    TreeNodeP(Predicate *predicate) : 
        ITreeNode(NODE_P), 
        predicate_(predicate_) {}

    TreeNodeP(const Predicate *predicate) : 
        ITreeNode(NODE_P), 
        predicate_(predicate_) {}
};

struct TreeNodeO final : public ITreeNode {
private:
    operation_kind_t kind_;
public:
    TreeNodeO(operation_kind_t kind) : 
        ITreeNode(NODE_O), 
        kind_(kind) {}

};

struct Formula final {
private:
    ITreeNode *root_;

    ITreeNode *parse_expr (const Lexer &lexems, size_t &state);
    ITreeNode *parse_conj (const Lexer &lexems, size_t &state);
    ITreeNode *parse_disj (const Lexer &lexems, size_t &state);
    ITreeNode *parse_term (const Lexer &lexems, size_t &state);
public:
    Formula(const Lexer &lex_array);
    void show() const;
    ~Formula() {};
};

}