#ifndef __XPL_FUNCTIONDEFINITIONNODE_H__
#define __XPL_FUNCTIONDEFINITIONNODE_H__


#include <cdk/ast/sequence_node.h>
#include <cdk/ast/basic_node.h>
#include <cdk/ast/expression_node.h>

namespace xpl {

  /**
   * Class for describing function definition nodes.
   */
  class function_definition_node: public cdk::basic_node {
    
  bool _qualpublic;
  basic_type* _returntype;
  std::string _name;
  cdk::sequence_node* _parameters;
  cdk::expression_node* _defaultreturn;
  block_node *_body;

  public:
    inline function_definition_node(int lineno, bool qualpublic, basic_type* returntype, std::string* name, cdk::sequence_node* parameters, cdk::expression_node* defaultreturn, block_node *body) :
        cdk::basic_node(lineno), _qualpublic(qualpublic), _returntype(returntype), _name(*name), _parameters(parameters), _defaultreturn(defaultreturn), _body(body) {
    }

  public:
      
    inline bool qualpublic(){
        return _qualpublic;
    }
    
    
    inline basic_type* returntype(){
        return _returntype;
    } 
    
    inline std::string name(){
        return _name;
    } 
    
    inline cdk::sequence_node* parameters(){
        return _parameters;
    }
    
    inline cdk::expression_node* defaultreturn(){
        return _defaultreturn;
    }
    
    inline block_node *body() {
      return _body;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_function_definition_node(this, level);
    }

  };

} // xpl

#endif
