#include <string>
#include "targets/xml_writer.h"
#include "targets/type_checker.h"
#include "ast/all.h"  // automatically generated

//---------------------------------------------------------------------------

void xpl::xml_writer::do_sequence_node(cdk::sequence_node * const node, int lvl) {
    os() << std::string(lvl, ' ') << "<sequence_node size='" << node->size() << "'>" << std::endl;
    for (size_t i = 0; i < node->size(); i++){
        node->node(i)->accept(this, lvl + 2);
    }
    closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void xpl::xml_writer::do_integer_node(cdk::integer_node * const node, int lvl) {
  process_literal(node, lvl);
}

//new
void xpl::xml_writer::do_double_node(cdk::double_node * const node, int lvl) {
  process_literal(node, lvl);
}

void xpl::xml_writer::do_string_node(cdk::string_node * const node, int lvl) {
  process_literal(node, lvl);
}
//---------------------------------------------------------------------------

inline void xpl::xml_writer::do_unary_expression(cdk::unary_expression_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  node->argument()->accept(this, lvl + 2);
  closeTag(node, lvl);
}

void xpl::xml_writer::do_neg_node(cdk::neg_node * const node, int lvl) {
  do_unary_expression(node, lvl);
}

//new
void xpl::xml_writer::do_identity_node(xpl::identity_node * const node, int lvl) {
  do_unary_expression(node, lvl);
}

//new
void xpl::xml_writer::do_address_of_node(xpl::address_of_node * const node, int lvl){
    do_unary_expression(node, lvl);
}

//new
void xpl::xml_writer::do_memory_reservation_node(xpl::memory_reservation_node * const node, int lvl){
    do_unary_expression(node, lvl);
}

void xpl::xml_writer::do_not_node(cdk::not_node * const node, int lvl){
    do_unary_expression(node, lvl);
}



//---------------------------------------------------------------------------

inline void xpl::xml_writer::do_binary_expression(cdk::binary_expression_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  node->left()->accept(this, lvl + 2);
  node->right()->accept(this, lvl + 2);
  closeTag(node, lvl);
}

void xpl::xml_writer::do_add_node(cdk::add_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void xpl::xml_writer::do_sub_node(cdk::sub_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void xpl::xml_writer::do_mul_node(cdk::mul_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void xpl::xml_writer::do_div_node(cdk::div_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void xpl::xml_writer::do_mod_node(cdk::mod_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void xpl::xml_writer::do_lt_node(cdk::lt_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void xpl::xml_writer::do_le_node(cdk::le_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void xpl::xml_writer::do_ge_node(cdk::ge_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void xpl::xml_writer::do_gt_node(cdk::gt_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void xpl::xml_writer::do_ne_node(cdk::ne_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void xpl::xml_writer::do_eq_node(cdk::eq_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}

//new
void xpl::xml_writer::do_and_node(cdk::and_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}

//new
void xpl::xml_writer::do_or_node(cdk::or_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}

//---------------------------------------------------------------------------

void xpl::xml_writer::do_identifier_node(cdk::identifier_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  os() << std::string(lvl, ' ') << "<" << node->label() << ">" << node->name() << "</" << node->label() << ">" << std::endl;
}

void xpl::xml_writer::do_rvalue_node(cdk::rvalue_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  node->lvalue()->accept(this, lvl + 4);
  closeTag(node, lvl);
}

void xpl::xml_writer::do_assignment_node(cdk::assignment_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);

  node->lvalue()->accept(this, lvl);
  //reset_new_symbol();

  node->rvalue()->accept(this, lvl + 4);
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

void xpl::xml_writer::do_evaluation_node(xpl::evaluation_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  node->argument()->accept(this, lvl + 2);
  closeTag(node, lvl);
}

void xpl::xml_writer::do_print_node(xpl::print_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  node->argument()->accept(this, lvl + 2);
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

void xpl::xml_writer::do_while_node(xpl::while_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  openTag("condition", lvl + 2);
  node->condition()->accept(this, lvl + 4);
  closeTag("condition", lvl + 2);
  openTag("block", lvl + 2);
  node->block()->accept(this, lvl + 4);
  closeTag("block", lvl + 2);
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void xpl::xml_writer::do_if_node(xpl::if_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  openTag("condition", lvl + 2);
  node->condition()->accept(this, lvl + 4);
  closeTag("condition", lvl + 2);
  openTag("then", lvl + 2);
  node->block()->accept(this, lvl + 4);
  closeTag("then", lvl + 2);
  closeTag(node, lvl);
}

void xpl::xml_writer::do_if_else_node(xpl::if_else_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  openTag("condition", lvl + 2);
  node->condition()->accept(this, lvl + 4);
  closeTag("condition", lvl + 2);
  openTag("then", lvl + 2);
  node->thenblock()->accept(this, lvl + 4);
  closeTag("then", lvl + 2);
  openTag("else", lvl + 2);
  node->elseblock()->accept(this, lvl + 4);
  closeTag("else", lvl + 2);
  closeTag(node, lvl);
}

void xpl::xml_writer::do_stop_node(xpl::stop_node * const node, int lvl){
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  closeTag(node, lvl);
}

void xpl::xml_writer::do_next_node(xpl::next_node * const node, int lvl){
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  closeTag(node, lvl);  
}

void xpl::xml_writer::do_return_node(xpl::return_node * const node, int lvl){
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  closeTag(node, lvl);
    
}



void xpl::xml_writer::do_variable_declaration_node(xpl::variable_declaration_node * const node, int lvl){
    
    //ASSERT_SAFE_EXPRESSIONS;
    openTag(node, lvl);
    openTag("qualifier", lvl+2);
    //provavelmente e melhor substituir por imprimir os booleans a balda, DUVIDA!!!!
    process_qualifier(node->qualpublic(),node->qualuse(),lvl+4);
    closeTag("qualifier", lvl+2);
    openTag("type", lvl+2);
    process_basic_type(node->type(),lvl+4);
    closeTag("type", lvl+2);
    openTag("name", lvl+2);
    os()<<std::string(lvl+4,' ')<<node->name()<<std::endl;
    closeTag("name", lvl+2);
    openTag("initvalue", lvl+2);
    if(node->initvalue()!=nullptr){
        node->initvalue()->accept(this,lvl+4);
    }
    closeTag("initvalue", lvl+2);
    closeTag(node, lvl);
    
}

void xpl::xml_writer::do_sweep_up_node(xpl::sweep_up_node * const node, int lvl){
    //ASSERT_SAFE_EXPRESSIONS;
    openTag(node, lvl);
    openTag("lvalue",lvl+2);
    node->lvalue()->accept(this,lvl+4);
    closeTag("lvalue",lvl+2);
    openTag("init",lvl+2);
    node->init()->accept(this,lvl+4);
    closeTag("init",lvl+2);
    openTag("cond",lvl+2);
    node->cond()->accept(this,lvl+4);
    closeTag("cond",lvl+2);
    openTag("step",lvl+2);
    node->step()->accept(this,lvl+4);
    closeTag("step",lvl+2);
    openTag("block",lvl+2);
    node->block()->accept(this,lvl+4);
    closeTag("block",lvl+2);
    closeTag(node, lvl);
    
}

void xpl::xml_writer::do_sweep_down_node(xpl::sweep_down_node * const node, int lvl){
    //ASSERT_SAFE_EXPRESSIONS;
    openTag(node, lvl);
    openTag("lvalue",lvl+2);
    node->lvalue()->accept(this,lvl+4);
    closeTag("lvalue",lvl+2);
    openTag("init",lvl+2);
    node->init()->accept(this,lvl+4);
    closeTag("init",lvl+2);
    openTag("cond",lvl+2);
    node->cond()->accept(this,lvl+4);
    closeTag("cond",lvl+2);
    openTag("step",lvl+2);
    node->step()->accept(this,lvl+4);
    closeTag("step",lvl+2);
    openTag("block",lvl+2);
    node->block()->accept(this,lvl+4);
    closeTag("block",lvl+2);
    closeTag(node, lvl);
    
}

void xpl::xml_writer::do_index_node(xpl::index_node * const node, int lvl){
    //ASSERT_SAFE_EXPRESSIONS;
    openTag(node, lvl);
    openTag("ptr", lvl+2);
    node->ptr()->accept(this,lvl+4);
    closeTag("ptr", lvl+2);
    openTag("offset", lvl+2);
    node->offset()->accept(this,lvl+4);
    closeTag("offset", lvl+2);
    closeTag(node, lvl);
}

void xpl::xml_writer::do_block_node(xpl::block_node * const node, int lvl){
    //ASSERT_SAFE_EXPRESSIONS;
    openTag(node, lvl);
    openTag("declarations",lvl+2);
    node->declarations()->accept(this,lvl+4);
    closeTag("declarations",lvl+2);
    openTag("instructions",lvl+2);
    node->instructions()->accept(this,lvl+4);
    closeTag("instructions",lvl+2);
    closeTag(node, lvl);
}

void xpl::xml_writer::do_function_declaration_node(xpl::function_declaration_node * const node, int lvl){
    //ASSERT_SAFE_EXPRESSIONS;
    openTag(node, lvl);
    openTag("qualifier", lvl+2);
    //provavelmente e melhor substituir por imprimir os booleans a balda, DUVIDA!!!!
    process_qualifier(node->qualpublic(),node->qualuse(),lvl+4);
    closeTag("qualifier", lvl+2);
    openTag("returntype", lvl+2);
    process_basic_type(node->returntype(),lvl+4);
    closeTag("returntype", lvl+2);
    openTag("name", lvl+2);
    os()<<std::string(lvl+4,' ')<<node->name()<<std::endl;
    closeTag("name", lvl+2);
    openTag("parameters",lvl+2);
    node->parameters()->accept(this,lvl+4);
    closeTag("parameters",lvl+2);
    closeTag(node, lvl);
}

void xpl::xml_writer::do_function_definition_node(xpl::function_definition_node * const node, int lvl){
    //ASSERT_SAFE_EXPRESSIONS;
    openTag(node, lvl);
    openTag("qualifier", lvl+2);
    //provavelmente e melhor substituir por imprimir os booleans a balda, DUVIDA!!!!
    process_qualifier(node->qualpublic(),false,lvl+4);
    closeTag("qualifier", lvl+2);
    openTag("returntype", lvl+2);
    process_basic_type(node->returntype(),lvl+4);
    closeTag("returntype", lvl+2);
    openTag("name", lvl+2);
    os()<<std::string(lvl+4,' ')<<node->name()<<std::endl;
    closeTag("name", lvl+2);
    openTag("parameters",lvl+2);
    node->parameters()->accept(this,lvl+4);
    closeTag("parameters",lvl+2);
    openTag("defaultreturn",lvl+2);
    if(node->defaultreturn()!=nullptr){
        node->defaultreturn()->accept(this,lvl+4);
    }
    closeTag("defaultreturn",lvl+2);
    openTag("body",lvl+2);
    node->body()->accept(this,lvl+4);
    closeTag("body",lvl+2);
    closeTag(node, lvl);
}

void xpl::xml_writer::do_function_call_node(xpl::function_call_node * const node, int lvl){
    //ASSERT_SAFE_EXPRESSIONS;
    openTag(node, lvl);
    openTag("name", lvl+2);
    os()<<std::string(lvl+4,' ')<<node->name()<<std::endl;
    closeTag("name", lvl+2);
    openTag("arguments",lvl+2);
    node->arguments()->accept(this,lvl+4);
    closeTag("arguments",lvl+2);
    closeTag(node, lvl);
}






void xpl::xml_writer::do_read_node(xpl::read_node * const node, int lvl){
    //ASSERT_SAFE_EXPRESSIONS;
    openTag(node, lvl);
    //E preciso por aqui alguma coisa? wtf
    closeTag(node, lvl);
}

void xpl::xml_writer::do_null_node(xpl::null_node * const node, int lvl){
    //ASSERT_SAFE_EXPRESSIONS;
    openTag(node, lvl);
    //E preciso por aqui alguma coisa? wtf
    closeTag(node, lvl);
}


void xpl::xml_writer::do_pratic1_node(xpl::pratic1_node * const node, int lvl){
    openTag(node, lvl);
    //E preciso por aqui alguma coisa? wtf
    closeTag(node, lvl);
}


