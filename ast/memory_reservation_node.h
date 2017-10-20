 
#ifndef __XPL_MEMORYRESERVATIONNODE_H__
#define __XPL_MEMORYRESERVATIONNODE_H__

#include <cdk/basic_type.h>

#include <cdk/ast/unary_expression_node.h>
#include <cdk/ast/expression_node.h>

namespace xpl {

  /**
   * Class for describing memory reservation nodes.
   */
  class memory_reservation_node: public cdk::unary_expression_node {

  public:
    inline memory_reservation_node(int lineno, cdk::expression_node* argument) :
        cdk::unary_expression_node(lineno,argument) {
    }

  public:

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_memory_reservation_node(this, level);
    }

  };

} // xpl

#endif