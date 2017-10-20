 
#ifndef __XPL_PRATIC1NODE_H__
#define __XPL_PRATIC1NODE_H__

#include <cdk/ast/basic_node.h>


namespace xpl {

  /**
   * Class for describing return nodes.
   */
  class pratic1_node: public cdk::basic_node {

 cdk::expression_node* _low;
 cdk::expression_node* _high;
 std::string _func;
 std::string _vec;
  public:
    inline pratic1_node(int lineno, cdk::expression_node* low, cdk::expression_node* high, std::string* func, std::string* vec) :
        cdk::basic_node(lineno), _low(low), _high(high), _func(*func), _vec(*vec) {
    }
    
  cdk::expression_node* low(){
      return _low;
}

cdk::expression_node* high(){
    return _high;
}

std::string func(){
    return _func;
}

std::string vec(){
    return _vec;
}
  public:

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_pratic1_node(this, level);
    }

  };

} // xpl

#endif 
