#include "../include/formula.hpp"
#include "../include/lexer.hpp"

first_order_language::Formula::Formula(const Lexer &lexems) {
    size_t state = 0;
    root_ = parse_expr(lexems, state);
    if (state < lexems.size()) { std::cout << "parse error" << std::endl; exit(1); }
}

first_order_language::ITreeNode *first_order_language::Formula::parse_term (const Lexer &lexems, size_t &state) {
    
}

first_order_language::ITreeNode *first_order_language::Formula::parse_disj (const Lexer &lexems, size_t &state) {
    ITreeNode *new_node = nullptr;

    new_node = parse_term(lexems, state);
    if (state >= lexems.size() || (lexems[state]->kind() != OP_AND)) {
        return new_node;
    }

    ITreeNode *temp = new TreeNodeO(OP_AND);
    temp->left_  = new_node;
    ++state;
    temp->right_ = parse_disj(lexems, state);

    return temp;
}

first_order_language::ITreeNode *first_order_language::Formula::parse_conj (const Lexer &lexems, size_t &state) {
	ITreeNode *new_node = nullptr;

	new_node = parse_disj(lexems, state);
	if (state >= lexems.size() || lexems[state]->kind() != OP_OR) {
		return new_node;
	}

	ITreeNode *temp = new TreeNodeO(OP_OR) ;
	temp->left_ = new_node;
	++state; 
	temp->right_ = parse_conj(lexems, state);

	return temp;
}

first_order_language::ITreeNode *first_order_language::Formula::parse_expr (const Lexer &lexems, size_t &state) {
	ITreeNode *new_node = nullptr;

	new_node = parse_conj(lexems, state);
	if (state >= lexems.size() || lexems[state]->kind() != OP_IMPL) {
		return new_node;
	}

	ITreeNode *temp = new TreeNodeO(OP_IMPL);	
	temp->left_ = new_node;
	++state; 
	temp->right_ = parse_expr(lexems, state);

	return temp;
}