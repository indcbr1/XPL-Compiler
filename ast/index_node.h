
#ifndef __XPL_INDEXNODE_H__
#define __XPL_INDEXNODE_H__

#include <cdk/ast/lvalue_node.h>
#include <cdk/ast/expression_node.h>

namespace xpl {

  /**
   * Class for describing return nodes.
   */
  class index_node: public cdk::lvalue_node {

  cdk::expression_node* _ptr;
  cdk::expression_node* _offset;
  
  public:
    inline index_node(int lineno, cdk::expression_node* ptr, cdk::expression_node* offset ) :
        cdk::lvalue_node(lineno), _ptr(ptr), _offset(offset) {
    }

  public:
      
    inline cdk::expression_node* ptr(){
        return _ptr;
        
    }
    
    inline cdk::expression_node* offset(){
        return _offset;
        
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_index_node(this, level);
    }

  };

} // xpl

#endif