#ifndef __XPL_SEMANTICS_POSTFIX_WRITER_H__
#define __XPL_SEMANTICS_POSTFIX_WRITER_H__

#include <string>
#include <iostream>
#include <vector>
#include <cdk/symbol_table.h>
#include <cdk/emitters/basic_postfix_emitter.h>
#include "targets/basic_ast_visitor.h"
#include "targets/symbol.h"

#include <stack>

namespace xpl {

  //!
  //! Traverse syntax tree and generate the corresponding assembly code.
  //!
  class postfix_writer: public basic_ast_visitor {
    cdk::symbol_table<xpl::symbol> &_symtab;
    cdk::basic_postfix_emitter &_pf;
    int _lbl;
    std::stack<int> _nextlbls;
    std::stack<int> _stoplbls;
    int _declbl = 0;
    int _retlbl;
    int _rel_sp=0;
    int _arg_sp=0;
    bool _arg_def=false;
    bool _glb=true;
    bool _dec_conv=false;
    std::string _func_name;
    std::vector<std::string> _externs;

  public:
    postfix_writer(std::shared_ptr<cdk::compiler> compiler, cdk::symbol_table<xpl::symbol> &symtab,
                   cdk::basic_postfix_emitter &pf) :
        basic_ast_visitor(compiler), _symtab(symtab), _pf(pf), _lbl(0) {
    }
    
    std::vector<std::string> externs(){
        return _externs;
    }
    void writeExterns(){
        for(size_t i=0; i<_externs.size();i++){
            _pf.EXTERN(_externs[i]);
        }
    }
    
    basic_type* clone_type(basic_type* t){
        basic_type* result = new basic_type(t->size(),t->name());
        if(t->subtype()!=nullptr){
            result->_subtype=clone_type(t->subtype());
        }
        return result;
    }
  public:
    ~postfix_writer() {
      os().flush();
    }

  private:
    /** Method used to generate sequential labels. */
    inline std::string mklbl(int lbl) {
      std::ostringstream oss;
      if (lbl < 0)
        oss << ".L" << -lbl;
      else
        oss << "_L" << lbl;
      return oss.str();
    }
    
    inline void removeExtern(std::string name){
        for(size_t i = 0; i< _externs.size();i++){
            if(_externs[i]==name)
                _externs.erase(_externs.begin()+i);
        }
    }

  public:
    void do_sequence_node(cdk::sequence_node * const node, int lvl);

  public:
    void do_integer_node(cdk::integer_node * const node, int lvl);
    void do_string_node(cdk::string_node * const node, int lvl);
    void do_double_node(cdk::double_node * const node, int lvl);

  public:
    void do_neg_node(cdk::neg_node * const node, int lvl);
    void do_not_node(cdk::not_node * const node, int lvl);

  public:
    void do_add_node(cdk::add_node * const node, int lvl);
    void do_sub_node(cdk::sub_node * const node, int lvl);
    void do_mul_node(cdk::mul_node * const node, int lvl);
    void do_div_node(cdk::div_node * const node, int lvl);
    void do_mod_node(cdk::mod_node * const node, int lvl);
    void do_lt_node(cdk::lt_node * const node, int lvl);
    void do_le_node(cdk::le_node * const node, int lvl);
    void do_ge_node(cdk::ge_node * const node, int lvl);
    void do_gt_node(cdk::gt_node * const node, int lvl);
    void do_ne_node(cdk::ne_node * const node, int lvl);
    void do_eq_node(cdk::eq_node * const node, int lvl);
    void do_and_node(cdk::and_node * const node, int lvl);
    void do_or_node(cdk::or_node * const node, int lvl);
    
  public:
    void do_identifier_node(cdk::identifier_node * const node, int lvl);
    void do_rvalue_node(cdk::rvalue_node * const node, int lvl);
    void do_assignment_node(cdk::assignment_node * const node, int lvl);

  public:
    void do_evaluation_node(xpl::evaluation_node * const node, int lvl);
    void do_print_node(xpl::print_node * const node, int lvl);
    void do_read_node(xpl::read_node * const node, int lvl);

  public:
    void do_while_node(xpl::while_node * const node, int lvl);
    void do_if_node(xpl::if_node * const node, int lvl);
    void do_if_else_node(xpl::if_else_node * const node, int lvl);
    
    void do_stop_node(xpl::stop_node * const node, int lvl);
    void do_next_node(xpl::next_node * const node, int lvl);
    void do_return_node(xpl::return_node * const node, int lvl);
    
    void do_variable_declaration_node(xpl::variable_declaration_node * const node, int lvl);
    void do_sweep_up_node(xpl::sweep_up_node * const node, int lvl);
    void do_sweep_down_node(xpl::sweep_down_node * const node, int lvl);
    
    void do_index_node(xpl::index_node * const node, int lvl);
    void do_block_node(xpl::block_node * const node, int lvl);
    void do_function_declaration_node(xpl::function_declaration_node * const node, int lvl);
    void do_function_definition_node(xpl::function_definition_node * const node, int lvl);
    void do_function_call_node(xpl::function_call_node * const node, int lvl);
    
    void do_null_node(xpl::null_node * const node, int lvl);
    void do_address_of_node(xpl::address_of_node * const node, int lvl);
    void do_memory_reservation_node(xpl::memory_reservation_node * const node, int lvl);
    
    void do_identity_node(xpl::identity_node * const node, int lvl);
    
    void process_add(cdk::binary_expression_node * const node, int lvl);
    void process_mul(cdk::binary_expression_node * const node, int lvl);
    void process_cmp(cdk::binary_expression_node * const node, int lvl);
    
    void do_pratic1_node(xpl::pratic1_node* const node, int lvl);
    
    
  };

} // xpl

#endif
