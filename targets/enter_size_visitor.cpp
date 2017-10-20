#include "targets/enter_size_visitor.h"
//DESCONTADO POR ISTO?
#include "ast/all.h"

//interesting nodes
void xpl::enter_size_visitor::do_sequence_node(cdk::sequence_node * const node, int lvl){
    for (size_t i = 0; i < node->size(); i++) {
    node->node(i)->accept(this, lvl);
  }
}

void xpl::enter_size_visitor::do_block_node(xpl::block_node * const node, int lvl){
    node->declarations()->accept(this,lvl);
    node->instructions()->accept(this,lvl);
}

void xpl::enter_size_visitor::do_variable_declaration_node(xpl::variable_declaration_node * const node, int lvl){
    _totalsize+=node->type()->size();
}

void xpl::enter_size_visitor::do_function_call_node(xpl::function_call_node * const node, int lvl){
    node->arguments()->accept(this,lvl);
}
//kinda unnecessary
void xpl::enter_size_visitor::do_function_definition_node(xpl::function_definition_node * const node, int lvl){
    node->body()->accept(this,lvl);
}


//essentially garbage: do nothing
void xpl::enter_size_visitor::do_integer_node(cdk::integer_node * const node, int lvl){}
void xpl::enter_size_visitor::do_string_node(cdk::string_node * const node, int lvl){}
void xpl::enter_size_visitor::do_double_node(cdk::double_node * const node, int lvl){}

  
void xpl::enter_size_visitor::do_neg_node(cdk::neg_node * const node, int lvl){}
void xpl::enter_size_visitor::do_not_node(cdk::not_node * const node, int lvl){}


void xpl::enter_size_visitor::do_add_node(cdk::add_node * const node, int lvl){}
void xpl::enter_size_visitor::do_sub_node(cdk::sub_node * const node, int lvl){}
void xpl::enter_size_visitor::do_mul_node(cdk::mul_node * const node, int lvl){}
void xpl::enter_size_visitor::do_div_node(cdk::div_node * const node, int lvl){}
void xpl::enter_size_visitor::do_mod_node(cdk::mod_node * const node, int lvl){}
void xpl::enter_size_visitor::do_lt_node(cdk::lt_node * const node, int lvl){}
void xpl::enter_size_visitor::do_le_node(cdk::le_node * const node, int lvl){}
void xpl::enter_size_visitor::do_ge_node(cdk::ge_node * const node, int lvl){}
void xpl::enter_size_visitor::do_gt_node(cdk::gt_node * const node, int lvl){}
void xpl::enter_size_visitor::do_ne_node(cdk::ne_node * const node, int lvl){}
void xpl::enter_size_visitor::do_eq_node(cdk::eq_node * const node, int lvl){}
void xpl::enter_size_visitor::do_and_node(cdk::and_node * const node, int lvl){}
void xpl::enter_size_visitor::do_or_node(cdk::or_node * const node, int lvl){}


void xpl::enter_size_visitor::do_identifier_node(cdk::identifier_node * const node, int lvl){}
void xpl::enter_size_visitor::do_rvalue_node(cdk::rvalue_node * const node, int lvl){}
void xpl::enter_size_visitor::do_assignment_node(cdk::assignment_node * const node, int lvl){}

void xpl::enter_size_visitor::do_evaluation_node(xpl::evaluation_node * const node, int lvl){}
void xpl::enter_size_visitor::do_print_node(xpl::print_node * const node, int lvl){}
void xpl::enter_size_visitor::do_read_node(xpl::read_node * const node, int lvl){}


void xpl::enter_size_visitor::do_while_node(xpl::while_node * const node, int lvl){}
void xpl::enter_size_visitor::do_if_node(xpl::if_node * const node, int lvl){}//visitar o bloco do if
void xpl::enter_size_visitor::do_if_else_node(xpl::if_else_node * const node, int lvl){}

void xpl::enter_size_visitor::do_stop_node(xpl::stop_node * const node, int lvl){}
void xpl::enter_size_visitor::do_next_node(xpl::next_node * const node, int lvl){}
void xpl::enter_size_visitor::do_return_node(xpl::return_node * const node, int lvl){}

void xpl::enter_size_visitor::do_sweep_up_node(xpl::sweep_up_node * const node, int lvl){}
void xpl::enter_size_visitor::do_sweep_down_node(xpl::sweep_down_node * const node, int lvl){}

void xpl::enter_size_visitor::do_index_node(xpl::index_node * const node, int lvl){}
void xpl::enter_size_visitor::do_function_declaration_node(xpl::function_declaration_node * const node, int lvl){}

void xpl::enter_size_visitor::do_null_node(xpl::null_node * const node, int lvl){}
void xpl::enter_size_visitor::do_address_of_node(xpl::address_of_node * const node, int lvl){}
void xpl::enter_size_visitor::do_memory_reservation_node(xpl::memory_reservation_node * const node, int lvl){}

void xpl::enter_size_visitor::do_identity_node(xpl::identity_node * const node, int lvl){}

void xpl::enter_size_visitor::do_pratic1_node(xpl::pratic1_node * const node, int lvl){
    _totalsize+=4;
}
