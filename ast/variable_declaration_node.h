#ifndef __XPL_VARIABLEDECLARATIONNODE_H__
#define __XPL_VARIABLEDECLARATIONNODE_H__

#include <string>
#include <cdk/basic_type.h>
#include <cdk/ast/basic_node.h>
#include <cdk/ast/expression_node.h>

namespace xpl {

  /**
   * Class for describing variable declaration nodes.
   */
  class variable_declaration_node: public cdk::basic_node {
 
  bool _qualpublic;
  bool _qualuse;
  basic_type* _type;
  std::string _name;
  cdk::expression_node * _initvalue;
  
  public:
    inline variable_declaration_node(int lineno,bool qualpublic, bool qualuse,  basic_type* type, std::string* name, cdk::expression_node * initvalue ) :
        cdk::basic_node(lineno), _qualpublic(qualpublic), _qualuse(qualuse), _type(type), _name(*name), _initvalue(initvalue){
    }

  public:
   
    inline bool qualpublic(){
        return _qualpublic;
    }
    
    inline bool qualuse(){
        return _qualuse;
    }
    
    inline basic_type* type(){
        return _type;
    } 
    
    inline std::string name(){
        return _name;
    } 
    
    inline cdk::expression_node* initvalue(){
        return _initvalue;
    }
   

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_variable_declaration_node(this, level);
    }

  };

} // xpl

#endif