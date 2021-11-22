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
    ITreeNode *left;
    ITreeNode *right;
    bool isBrac = false;
public:
    virtual ~ITreeNode() {}
};

struct TreeNodeQ final : public ITreeNode {
private:
    quantifier_kind_t kind_;
public:

};

struct TreeNodeV final : public ITreeNode {
private:
    std::string name_;
public:

};

struct TreeNodeF final : public ITreeNode {
private:
    Function *function_;
public:

};

struct TreeNodeP final : public ITreeNode {
private:
    Predicate *predicate_;
public:

};

struct TreeNodeO final : public ITreeNode {
private:
    operation_kind_t kind_;
public:
    
};

struct Formula final {
private:
    ITreeNode root_;

    ITreeNode *parse_expr (const Lexer &lexems, size_t &state);
    ITreeNode *parse_conj (const Lexer &lexems, size_t &state);
    ITreeNode *parse_disj (const Lexer &lexems, size_t &state);
    ITreeNode *parse_term (const Lexer &lexems, size_t &state);
public:
    Formula(const Lexer &lex_array);
};

}