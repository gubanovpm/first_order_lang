#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

#include "./lexer.hpp"
#include "./default.hpp"
#include "./function.hpp"
#include "./predicate.hpp"
#include "./finite_interpretation.hpp"

namespace first_order_language {

enum node_kind_t {NODE_Q = 101, NODE_V, NODE_F, NODE_P, NODE_O};

struct ITreeNode {
protected:
    node_kind_t type_;
    bool isBrac = false;
public:
    ITreeNode   *left_;
    ITreeNode   *right_;
    virtual void destroy_subtree();

    void setBrac(bool x) { isBrac = x; }
    ITreeNode(node_kind_t type, ITreeNode *left = nullptr, ITreeNode * right = nullptr) :
        type_(type), 
        left_(left),
        right_(right) {} 
    virtual ~ITreeNode() {};

    virtual std::string name() const { return "__unnamed__"; }
    virtual void show() const = 0;
    virtual void get_all_variables(std::vector < std::string > &var_names) const {}
    virtual std::pair< bool, SigEType > eval(std::unordered_map < std::string, SigEType > *variables, FiniteInterpretation *interpretation) const = 0;
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
    void show() const override;

    virtual void get_all_variables(std::vector < std::string > &var_names) const override;
    std::pair< bool, SigEType > eval(std::unordered_map < std::string, SigEType > *variables, FiniteInterpretation *interpretation) const override;
};

struct TreeNodeV final : public ITreeNode {
private:
    std::string name_;
public:
    TreeNodeV(std::string name) :
        ITreeNode(NODE_V), 
        name_(name) {}
    void show() const override;

    virtual void get_all_variables(std::vector < std::string > &var_names) const override;
    std::string name() const override { return name_; }
    std::pair< bool, SigEType > eval(std::unordered_map < std::string, SigEType > *variables, FiniteInterpretation *interpretation) const override;
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
    void show() const override;
    void destroy_subtree() override;
    
    virtual void get_all_variables(std::vector < std::string > &var_names) const override;
    std::pair< bool, SigEType > eval(std::unordered_map < std::string, SigEType > *variables, FiniteInterpretation *interpretation) const override;
};

struct TreeNodeP final : public ITreeNode {
private:
    Predicate *predicate_;
public:
    std::vector <ITreeNode *> arguments_;
    TreeNodeP(Predicate *predicate) : 
        ITreeNode(NODE_P), 
        predicate_(predicate) {}

    void show() const override;
    void destroy_subtree() override;
    
    virtual void get_all_variables(std::vector < std::string > &var_names) const override;
    std::pair< bool, SigEType > eval(std::unordered_map < std::string, SigEType > *variables, FiniteInterpretation *interpretation) const override;
};

struct TreeNodeO final : public ITreeNode {
private:
    operation_kind_t kind_;
public:
    TreeNodeO(operation_kind_t kind) : 
        ITreeNode(NODE_O), 
        kind_(kind) {}

    void show() const override;
    std::pair< bool, SigEType > eval(std::unordered_map < std::string, SigEType > *variables, FiniteInterpretation *interpretation) const override;
};

struct Formula final {
private:
    ITreeNode *root_;
    FiniteInterpretation *interpretation_;
    void __get_all_variables__(std::vector < std::string > &var_names) const;

    ITreeNode *parse_expr (const Lexer &lexems, size_t &state);
    ITreeNode *parse_conj (const Lexer &lexems, size_t &state);
    ITreeNode *parse_disj (const Lexer &lexems, size_t &state);
    ITreeNode *parse_term (const Lexer &lexems, size_t &state);
public:
    Formula(const Lexer &lex_array, FiniteInterpretation *interpretation_);
    void show() const;
    SigEType models() const;
    ~Formula();
};

}