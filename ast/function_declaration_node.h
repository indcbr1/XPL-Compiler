#ifndef __XPL_FUNCTIONDECLARATIONNODE_H__
#define __XPL_FUNCTIONDECLARATIONNODE_H__

#include <string>
#include <cdk/basic_type.h>
#include <cdk/ast/sequence_node.h>
#include <cdk/ast/basic_node.h>


namespace xpl {

  /**
   * Class for describing function declaration nodes.
   */
  class function_declaration_node: public cdk::basic_node {

  bool _qualpublic,_qualuse;
  basic_type* _returntype;
  std::string _name;
  cdk::sequence_node* _parameters;
  
  public:
    inline function_declaration_node(int lineno, bool qualpublic, bool qualuse, basic_type* returntype, std::string* name, cdk::sequence_node* parameters ) :
        cdk::basic_node(lineno), _qualpublic(qualpublic), _qualuse(qualuse), _returntype(returntype), _name(*name), _parameters(parameters) {
     }

  public:
      
    inline bool qualpublic(){
        return _qualpublic;
    }
    
    inline bool qualuse(){
        return _qualuse;
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
   

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_function_declaration_node(this, level);
    }

  };

} // xpl

#endif