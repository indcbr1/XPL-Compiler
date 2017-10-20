// $Id: print_node.h,v 1.4 2017/05/21 23:47:58 ist181271 Exp $ -*- c++ -*-
#ifndef __XPL_PRINTNODE_H__
#define __XPL_PRINTNODE_H__

#include <cdk/ast/expression_node.h>
#include <cdk/ast/basic_node.h>


namespace xpl {

  /**
   * Class for describing print nodes.
   */
  class print_node: public cdk::basic_node {

  cdk::expression_node *_argument;
  bool _newline;
  public:
    inline print_node(int lineno, cdk::expression_node *argument, bool newline) :
        cdk::basic_node(lineno), _argument(argument), _newline(newline) {
    }

  public:
      
    inline bool newline(){
        return _newline;
    }
    
    inline cdk::expression_node *argument() {
      return _argument;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_print_node(this, level);
    }

  };

} // xpl

#endif
