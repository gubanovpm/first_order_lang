#include "../include/formula.hpp"
#include "../include/lexer.hpp"

first_order_language::Formula::Formula(const Lexer &lexems) {
    size_t state = 0;
    root_ = parse_expr(lexems, state);
    if (state != lexems.size()) { std::cout << "parse error" << std::endl; exit(1); }
}

first_order_language::ITreeNode *first_order_language::Formula::parse_term (const Lexer &lexems, size_t &state) {
    std::cout << "brand new term with state = " << state << "is " ; lexems[state]->show(); std::cout << std::endl;
    if (state > lexems.size())
        return nullptr;
    
    switch (lexems[state]->type()) {
        case LEX_BRACKET: {
            if (lexems[state]->kind() == LBRAC) ++state;
            else {std::cout << "pars error: unexpected bracket type" << std::endl; state = lexems.size() + 1; return nullptr; }

            ITreeNode *new_node = parse_expr(lexems, state);
            if (new_node != nullptr) new_node->setBrac(true);
            // std::cout << "out of parse (expr)" << std::endl;

            if (lexems[state]->kind() == RBRAC) ++state;
            else { std::cout << "pars error: expected \')\'" << std::endl; state = lexems.size() + 1; return nullptr; }

            break;
        }
        case LEX_OPERATION: {
            if (lexems[state]->kind() == OP_NOT) {
                TreeNodeO *new_node = new TreeNodeO (OP_NOT);
                ++state;
                
                new_node->left_ = parse_term(lexems, state);
                return new_node;
            }
            std::cout << "pars error: term operation not NOT )" << std::endl;
            state = lexems.size() + 1;
            return nullptr;
        }
        case LEX_QUANTIFIER: {
            ++state;
            if (lexems[state]->type() != LEX_FUNCT) { std::cout << "expected Quantifier Variable" << std::endl; state = lexems.size() + 1; return nullptr; }
            TreeNodeQ *new_node = new TreeNodeQ (quantifier_kind_t(lexems[state]->kind()), lexems[state]->name());
            ++state;
            new_node->left_ = parse_term(lexems, state);
            return new_node;
        }
        case LEX_FUNCT: {
            size_t number = 0;
            for (; number < __default_functions__.size(); ++number) {
                if (__default_functions__[number].getName() == lexems[state]->name()) break;
            }
            if (number < __default_functions__.size()) {
                ++state;
                if (lexems[state]->kind() != LBRAC) { std::cout << "parse error: after function name expected \'(\'"; state = lexems.size() + 1; return nullptr; }
                ++state;
                TreeNodeF *new_node = new TreeNodeF (&__default_functions__[number]);
                for (int i = 0; i < __default_functions__[number].getValence(); ++i) {
                    new_node->arguments_.push_back(parse_term(lexems, state));
                }
                if (lexems[state]->kind() != RBRAC) { std::cout << "parse error: at the end of argument list expected \')\'"; state = lexems.size() + 1; return nullptr; }
                ++state;
                return new_node;
            } else {
                for (number = 0; number < __default_predicates__.size(); ++number)
                    if (__default_predicates__[number].getName() == lexems[state]->name()) break;
                if (number < __default_predicates__.size()) {
                    ++state;
                    if (lexems[state]->kind() != LBRAC) { std::cout << "parse error: after function name expected \'(\'"; state = lexems.size() + 1; return nullptr; }
                    ++state;
                    TreeNodeP *new_node = new TreeNodeP (&__default_predicates__[number]);
                    for (int i = 0; i < __default_predicates__[number].getValence(); ++i) {
                        new_node->arguments_.push_back(parse_term(lexems, state));
                    }
                    if (lexems[state]->kind() != RBRAC) { std::cout << "parse error: at the end of argument list expected \')\'"; state = lexems.size() + 1; return nullptr; }
                    ++state;
                    return new_node;
                } else {
                    
                    TreeNodeV *new_node = new TreeNodeV(lexems[state]->name());
                    ++state;
                    return new_node;
                }
            }

            break;
        }

        default: { std::cout << "parse error 404" << std::endl; state = lexems.size() + 1; return nullptr; }
    }
    return nullptr;
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

void first_order_language::Formula::show() const {
    
}