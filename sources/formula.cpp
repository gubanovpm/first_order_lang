#include "../include/formula.hpp"
#include "../include/lexer.hpp"
#include "../include/default.hpp"
#include "../include/function.hpp"
#include "../include/predicate.hpp"
#include "../include/finite_interpretation.hpp"

first_order_language::Formula::Formula(const Lexer &lexems, FiniteInterpretation *interpretation) :
    interpretation_(interpretation) {
    size_t state = 0;
    root_ = parse_expr(lexems, state);
    if (state != lexems.size()) { std::cout << "parse error" << std::endl; exit(1); }
}

first_order_language::ITreeNode *first_order_language::Formula::parse_term (const Lexer &lexems, size_t &state) {
    // std::cout << "brand new term with state = " << state << " and kind = " << lexems[state]->kind() << " is " ; lexems[state]->show(); std::cout << std::endl;
    if (state > lexems.size())
        return nullptr;
    
    switch (lexems[state]->type()) {
        case LEX_BRACKET: {
            // std::cout << "is it brac?\n" ;
            if (lexems[state]->kind() == LBRAC) ++state;
            else {std::cout << "pars error: unexpected bracket type" << std::endl; state = lexems.size() + 1; return nullptr; }

            ITreeNode *new_node = parse_expr(lexems, state);
            if (new_node != nullptr) new_node->setBrac(true);

            if (lexems[state]->kind() == RBRAC) ++state;
            else { std::cout << "pars error: expected \')\'" << std::endl; state = lexems.size() + 1; return nullptr; }

            return new_node;
        }
        case LEX_OPERATION: {
            // std::cout << "is it oper?\n" ;
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
            // std::cout << "is it quantifier?\n" ;
            ++state;
            if (lexems[state]->type() != LEX_FUNCT) { std::cout << "expected Quantifier Variable" << std::endl; state = lexems.size() + 1; return nullptr; }
            TreeNodeQ *new_node = new TreeNodeQ (quantifier_kind_t(lexems[state - 1]->kind()), lexems[state]->name());
            ++state;
            new_node->left_ = parse_term(lexems, state);
            return new_node;
        }
        case LEX_FUNCT: {
            // std::cout << "is it var/funct/pred?\n" ;
            size_t number = 0;
            for (; number < __default_functions__.size(); ++number) {
                if (__default_functions__[number].getName() == lexems[state]->name()) break;
            }
            if (number < __default_functions__.size()) {
                ++state;
                if (lexems[state]->kind() != LBRAC) { std::cout << "parse error: after function name expected \'(\'"; state = lexems.size() + 1; return nullptr; }
                ++state;
                TreeNodeF *new_node = new TreeNodeF (&(__default_functions__[number]));
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
                    if (lexems[state]->kind() != LBRAC) { std::cout << "parse error: after predicate name expected \'(\'"; state = lexems.size() + 1; return nullptr; }
                    ++state;
                    TreeNodeP *new_node = new TreeNodeP (&(__default_predicates__[number]));
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

        default: { std::cout << "parse error 404: unknown lexem type" << std::endl; state = lexems.size() + 1; return nullptr; }
    }
    printf("a kak?\n"); std::cout << state << " is " ; lexems[state]->show();
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
    if (root_ != nullptr) root_->show();
    std::cout << std::endl;
}

void first_order_language::TreeNodeO::show() const {
    if (kind_ == OP_NOT) { std::cout << "~" ; left_->show() ; return; }
    
    left_->show();
    switch (kind_) {
        case OP_AND  : std::cout << "& "  ; break;
        case OP_OR   : std::cout << "| "  ; break;
        case OP_IMPL : std::cout << "-> " ; break;
    }
    right_->show();
}

void first_order_language::TreeNodeV::show() const {
    std::cout << name_ ;
}

void first_order_language::TreeNodeP::show() const {
    std::cout << predicate_->getName() << "(" ;
    for (int i = 0; i < arguments_.size() - 1; ++i) {
        arguments_[i]->show(); std::cout << ", ";
    }
    if (arguments_.size() - 1 >= 0) arguments_[arguments_.size() - 1]->show();
    std::cout << ") " ;
}

void first_order_language::TreeNodeF::show() const {
    std::cout << function_->getName() << "(" ;
    for (int i = 0; i < arguments_.size() - 1; ++i) {
        arguments_[i]->show(); std::cout << ", " ;
    }
    if (arguments_.size() - 1 >= 0) arguments_[arguments_.size() - 1]->show();
    std::cout << ") " ;
}

void first_order_language::TreeNodeQ::show() const {
    switch (kind_) {
        case QUANTIFIER_ANY   : std::cout << "!A" ; break;
        case QUANTIFIER_EXIST : std::cout << "!E" ; break;
        default: std::cout << "my kind is = " << kind_ ; break;
    }
    std::cout << "< " << name_ << " >: " ;
    left_->show();
}

first_order_language::Formula::~Formula() {
    root_->destroy_subtree();
}

void first_order_language::ITreeNode::destroy_subtree() {
    if (left_  != nullptr) left_->destroy_subtree();
    if (right_ != nullptr) right_->destroy_subtree();

    delete this;
}

void first_order_language::TreeNodeP::destroy_subtree() {
    for (int i = 0; i < predicate_->getValence(); ++i)
        arguments_[i]->destroy_subtree();

    delete this;
}

void first_order_language::TreeNodeF::destroy_subtree() {
    for (int i = 0; i < function_->getValence(); ++i)
        arguments_[i]->destroy_subtree();

    delete this;
}

std::pair< bool, SigEType > first_order_language::TreeNodeV::eval(std::unordered_map < std::string, SigEType > *variables, FiniteInterpretation *interpretation) const {
    if (std::isdigit(name_[0])) return { true, std::atoi(name_.data()) };
    
    if (variables->find(name_) == variables->end()) return {false, 0};
    SigEType result = (*variables)[name_];
    return {true, result};
}

std::pair< bool, SigEType > first_order_language::TreeNodeP::eval(std::unordered_map < std::string, SigEType > *variables, FiniteInterpretation *interpretation) const {
    std::pair < bool, SigEType > result;
    std::vector < SigEType > arguments = {} ;
    for (int i = 0; i < predicate_->getValence(); ++i) {
        result = arguments_[i]->eval(variables, interpretation);
        if (!result.first) return { false, 0 };
        arguments.push_back(result.second);
    }
    return {true, predicate_->execute(arguments)} ;
}

std::pair< bool, SigEType > first_order_language::TreeNodeF::eval(std::unordered_map < std::string, SigEType > *variables, FiniteInterpretation *interpretation) const {
    std::pair < bool, SigEType > result;
    std::vector < SigEType > arguments = {};
    for (int i = 0 ; i < function_->getConsts()->size(); ++i) {
        arguments.push_back((*function_->getConsts())[i]);
    }
    for (int i = 0; i < function_->getValence(); ++i) {
        result = arguments_[i]->eval(variables, interpretation);
        if (!result.first) return { false, 0 } ;
        arguments.push_back(result.second);
    }
    return {true, function_->execute(arguments)};
}

std::pair< bool, SigEType > first_order_language::TreeNodeO::eval(std::unordered_map < std::string, SigEType > *variables, FiniteInterpretation *interpretation) const {
    switch (kind_) {
        case OP_AND: {
            bool fl1, fl2 ;
            std::pair < bool, SigEType > result ;
            
            result = left_->eval(variables, interpretation) ; fl1 = result.first ;
            if (!fl1) return { false, 0 } ;
            if (!result.second) return {true, false};
            
            result = right_->eval(variables, interpretation); fl2 = result.second;
            if (!fl2) return { false, 0 } ;
            if (!result.second) return {true, false};
            return {true, true};
        }
        case OP_OR: {
            bool fl1, fl2 ;
            std::pair < bool, SigEType > result ;
            
            result = left_->eval(variables, interpretation) ; fl1 = result.first ;
            if (!fl1) return { false, 0 } ;
            
            result = right_->eval(variables, interpretation); fl2 = result.second;
            if (!fl2) return { false, 0 } ;

            return {true, fl1 || fl2};
        }
        case OP_IMPL: {
            bool fl1, fl2;
            std::pair < bool, SigEType > result ;

            result = left_->eval(variables, interpretation) ; fl1 = result.first ;
            if (!fl1) return { false, 0 } ;
            
            result = right_->eval(variables, interpretation); fl2 = result.second;
            if (!fl2) return { false, 0 } ;

            return {true, !fl1 || fl2};
        }
        case OP_NOT: {
            std::pair < bool, SigEType > result ;
            result = left_->eval(variables, interpretation) ;
            if (!result.first) return { false, 0 } ;
            return {true, !result.second} ;
        }
        default: { std::cout << "eval_op: unknown eval construction" << std::endl; exit(1); }
    }
}

std::pair< bool, SigEType > first_order_language::TreeNodeQ::eval(std::unordered_map < std::string, SigEType > *variables, FiniteInterpretation *interpretation) const {
    switch (kind_) {
        case QUANTIFIER_ANY:   {
            std::pair < bool, SigEType > result;
            for (auto it = interpretation->M_.begin(); it != interpretation->M_.end(); ++it) {
                (*variables)[name_] = *it;
                result = left_->eval(variables, interpretation);
                if (!result.first) return  {false, 0}   ;
                if (!result.second) return {true, false};
            }
            return {true, true};
        }
        case QUANTIFIER_EXIST: {
            std::pair < bool, SigEType > result;
            for (auto it = interpretation->M_.begin(); it != interpretation->M_.end(); ++it) {
                (*variables)[name_] = *it;
                result = left_->eval(variables, interpretation);
                if (!result.first) return {false, 0}  ;
                if (result.second) return {true, true};
            }
            return {true, false};
        } 
        default: { std::cout << "eval_q: unknown eval construction" << std::endl; exit(1); }
    }
}

void first_order_language::Formula::__get_all_variables__(std::vector < std::string > &var_names) const {
    root_->get_all_variables(var_names);
}

void first_order_language::TreeNodeV::get_all_variables(std::vector < std::string > &var_names) const {
    if (left_  != nullptr) left_ ->get_all_variables(var_names);
    if (right_ != nullptr) right_->get_all_variables(var_names);

    if (!std::isdigit(name_[0])) var_names.push_back(name_);
}

void first_order_language::TreeNodeQ::get_all_variables(std::vector < std::string > &var_names) const {
    if (left_  != nullptr) left_ ->get_all_variables(var_names);
    if (right_ != nullptr) right_->get_all_variables(var_names);

    if (!std::isdigit(name_[0])) var_names.push_back(name_);
}

void first_order_language::TreeNodeP::get_all_variables(std::vector < std::string > &var_names) const {
    if (left_  != nullptr) left_ ->get_all_variables(var_names);
    if (right_ != nullptr) right_->get_all_variables(var_names);

    for (int i = 0; i < arguments_.size(); ++i) {
        arguments_[i]->get_all_variables(var_names);
    }
}

void first_order_language::TreeNodeF::get_all_variables(std::vector < std::string > &var_names) const {
    if (left_  != nullptr) left_ ->get_all_variables(var_names);
    if (right_ != nullptr) right_->get_all_variables(var_names);

    for (int i = 0; i < arguments_.size(); ++i) {
        arguments_[i]->get_all_variables(var_names);
    }
}

SigEType first_order_language::Formula::models() const {
    std::vector < std::string > var_names;
    __get_all_variables__(var_names);

    std::unordered_map < std::string, SigEType > variables;
    for (int i = 0; i < var_names.size(); ++i) {
        variables[var_names[i]] = 0xDEADFA11;   // POISON
    }
    
    std::pair < bool, SigEType > result = root_->eval(&variables, interpretation_);

    #if 0
    for (auto it = variables.begin(); it != variables.end(); ++it) {
        std::cout << it->first << " = " << it->second << std::endl;
    }
    #endif

    return result.second;
}