 
#ifndef __XPL_SWEEPDOWNNODE_H__
#define __XPL_SWEEPDOWNNODE_H__

#include <cdk/ast/expression_node.h>
#include <cdk/ast/lvalue_node.h>
#include <cdk/ast/basic_node.h>


namespace xpl {

  /**
   * Class for describing sweep up nodes.
   */
  class sweep_down_node: public cdk::basic_node {
  
  cdk::lvalue_node* _lvalue;
  cdk::expression_node* _init;
  cdk::expression_node* _cond;
  cdk::expression_node* _step;
  cdk::basic_node* _block;
      
  public:
    inline sweep_down_node(int lineno, cdk::lvalue_node* lvalue, cdk::expression_node* init, cdk::expression_node* cond, cdk::expression_node* step, cdk::basic_node* block) :
        cdk::basic_node(lineno), _lvalue(lvalue), _init(init), _cond(cond), _step(step), _block(block) {
    }
    

  public:
      
    inline cdk::lvalue_node* lvalue(){
        return _lvalue;
    }
    
    inline cdk::expression_node* init(){
        return _init;
    }
    
    inline cdk::expression_node* cond(){
        return _cond;
    }
    inline cdk::expression_node* step(){
        return _step;
    }
    
    inline cdk::basic_node* block(){
        return _block;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_sweep_down_node(this, level);
    }

  };

} // xpl

#endif