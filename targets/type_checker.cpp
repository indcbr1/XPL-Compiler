#include <string>
#include "targets/type_checker.h"
#include "ast/all.h"  // automatically generated

#define ASSERT_UNSPEC \
    { if (node->type() != nullptr && \
          node->type()->name() != basic_type::TYPE_UNSPEC) return; }

//---------------------------------------------------------------------------

void xpl::type_checker::do_integer_node(cdk::integer_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->type(new basic_type(4, basic_type::TYPE_INT));
}

void xpl::type_checker::do_string_node(cdk::string_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->type(new basic_type(4, basic_type::TYPE_STRING));
}

void xpl::type_checker::do_double_node(cdk::double_node * const node, int lvl) {
  ASSERT_UNSPEC;  
  node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
}

void xpl::type_checker::do_null_node(xpl::null_node * const node, int lvl){
 ASSERT_UNSPEC;
 node->type(new basic_type(4, basic_type::TYPE_POINTER));
}


//---------------------------------------------------------------------------

inline void xpl::type_checker::processUnaryExpression(cdk::unary_expression_node * const node, int lvl) {
  node->argument()->accept(this, lvl + 2);
  if (node->argument()->type()->name() != basic_type::TYPE_INT)
    throw std::string("wrong type in argument of unary expression");

  // in XPL, expressions are always int
  node->type(new basic_type(4, basic_type::TYPE_INT));
}

void xpl::type_checker::do_neg_node(cdk::neg_node * const node, int lvl) {
  processUnaryExpression(node, lvl);
}

void xpl::type_checker::do_not_node(cdk::not_node * const node, int lvl) {
    processUnaryExpression(node, lvl);
}

void xpl::type_checker::do_pratic1_node(xpl::pratic1_node * const node, int lvl){
     
}

//---------------------------------------------------------------------------
//this is an inclusive processor, and it will default to type A, which means type A will have to be double or pointer 
inline void xpl::type_checker::processBinaryExpressionI(cdk::binary_expression_node * const node, unsigned long int typeA, int typeASize, unsigned long int typeB, int typeBSize, int lvl){
    
    if(node->left()->type()->name()==typeA && node->right()->type()->name()==typeA)
        node->type(new basic_type(typeASize,typeA));
    else if(node->left()->type()->name()==typeA && node->right()->type()->name()==typeB)
        node->type(new basic_type(typeASize,typeA));
    else if(node->left()->type()->name()==typeB && node->right()->type()->name()==typeA)
        node->type(new basic_type(typeASize,typeA));
    else if(node->left()->type()->name()==typeB && node->right()->type()->name()==typeB)
        node->type(new basic_type(typeBSize,typeB));
}
//this is an exclusive processor, and it will default to type A and will clone the type of the part which is of type A (so that the subpointer does not get lost in translation), which means type A can and will be a pointer
inline void xpl::type_checker::processBinaryExpressionX(cdk::binary_expression_node * const node, unsigned long int typeA, int typeASize, unsigned long int typeB, int typeBSize, int lvl){
    
    if(node->left()->type()->name()==typeA && node->right()->type()->name()==typeB)
        node->type(clone_type(node->left()->type()));
    else if(node->left()->type()->name()==typeB && node->right()->type()->name()==typeA)
        node->type(clone_type(node->left()->type()));
}


inline void xpl::type_checker::processBinaryExpression(cdk::binary_expression_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->left()->accept(this, lvl + 2);
  if (node->left()->type()->name() != basic_type::TYPE_INT)
    throw std::string("wrong type in left argument of binary expression");

  node->right()->accept(this, lvl + 2);
  if (node->right()->type()->name() != basic_type::TYPE_INT)
    throw std::string("wrong type in right argument of binary expression");

  // in XPL, expressions are always int
  node->type(new basic_type(4, basic_type::TYPE_INT));
}

inline void xpl::type_checker::processMul(cdk::binary_expression_node * const node, int lvl){
  ASSERT_UNSPEC;
  node->left()->accept(this, lvl + 2);
  node->right()->accept(this, lvl + 2);
  processBinaryExpressionI(node,basic_type::TYPE_DOUBLE,8,basic_type::TYPE_INT,4, lvl);
  if(!node->type()){
      throw "undefined type";
  }
}


void xpl::type_checker::do_add_node(cdk::add_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->left()->accept(this, lvl + 2);
  node->right()->accept(this, lvl + 2);
  processBinaryExpressionI(node,basic_type::TYPE_DOUBLE,8,basic_type::TYPE_INT,4, lvl);
  processBinaryExpressionX(node,basic_type::TYPE_POINTER,4,basic_type::TYPE_INT,4, lvl);
  if(!node->type()){
      throw "undefined type";
  }
  
}
void xpl::type_checker::do_sub_node(cdk::sub_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->left()->accept(this, lvl + 2);
  node->right()->accept(this, lvl + 2);
  processBinaryExpressionI(node,basic_type::TYPE_DOUBLE,8,basic_type::TYPE_INT,4, lvl);
  processBinaryExpressionX(node,basic_type::TYPE_POINTER,4,basic_type::TYPE_INT,4, lvl);
  if(node->left()->type()->name()==basic_type::TYPE_POINTER &&node->right()->type()->name()==basic_type::TYPE_POINTER){
      node->type(new basic_type(4,basic_type::TYPE_INT));
}
  if(!node->type()){
      throw "undefined type";
  }
}
void xpl::type_checker::do_mul_node(cdk::mul_node * const node, int lvl) {
  processMul(node, lvl);
}
void xpl::type_checker::do_div_node(cdk::div_node * const node, int lvl) {
  processMul(node, lvl);
}
void xpl::type_checker::do_mod_node(cdk::mod_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void xpl::type_checker::do_lt_node(cdk::lt_node * const node, int lvl) {
  processMul(node, lvl);
}
void xpl::type_checker::do_le_node(cdk::le_node * const node, int lvl) {
  processMul(node, lvl);
}
void xpl::type_checker::do_ge_node(cdk::ge_node * const node, int lvl) {
  processMul(node, lvl);
}
void xpl::type_checker::do_gt_node(cdk::gt_node * const node, int lvl) {
  processMul(node, lvl);
}
void xpl::type_checker::do_ne_node(cdk::ne_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->left()->accept(this, lvl + 2);
  node->right()->accept(this, lvl + 2);
  processBinaryExpressionI(node,basic_type::TYPE_DOUBLE,8,basic_type::TYPE_INT,4, lvl);
  processBinaryExpressionI(node,basic_type::TYPE_POINTER,4,basic_type::TYPE_INT,4, lvl);
  if(!node->type()){
      throw "undefined type";
  }
}
void xpl::type_checker::do_eq_node(cdk::eq_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->left()->accept(this, lvl + 2);
  node->right()->accept(this, lvl + 2);
  processBinaryExpressionI(node,basic_type::TYPE_DOUBLE,8,basic_type::TYPE_INT,4, lvl);
  processBinaryExpressionI(node,basic_type::TYPE_POINTER,4,basic_type::TYPE_INT,4, lvl);
  if(!node->type()){
      throw "undefined type";
  }
}

void xpl::type_checker::do_and_node(cdk::and_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}

void xpl::type_checker::do_or_node(cdk::or_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}

//---------------------------------------------------------------------------

void xpl::type_checker::do_identifier_node(cdk::identifier_node * const node, int lvl) {
  const std::string &id = node->name();
  std::shared_ptr<xpl::symbol> symbol = _symtab.find(id);
    
  if (symbol != nullptr) {
    node->type(clone_type(symbol->type()));
  }
  else {
    throw id;
  }
  
}

void xpl::type_checker::do_rvalue_node(cdk::rvalue_node * const node, int lvl) {
  ASSERT_UNSPEC;
  try {
    node->lvalue()->accept(this, lvl);
    node->type(clone_type(node->lvalue()->type()));
  } catch (const std::string &id) {
    throw "undeclared variable '" + id + "'";
  }
}

void xpl::type_checker::do_assignment_node(cdk::assignment_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->lvalue()->accept(this, lvl);
  node->rvalue()->accept(this, lvl + 2);
    if(node->lvalue()->type()->name()==basic_type::TYPE_DOUBLE && node->rvalue()->type()->name()==basic_type::TYPE_DOUBLE)
        node->type(new basic_type(8,basic_type::TYPE_DOUBLE));
    else if(node->lvalue()->type()->name()==basic_type::TYPE_DOUBLE && node->rvalue()->type()->name()==basic_type::TYPE_INT)
        node->type(new basic_type(8,basic_type::TYPE_DOUBLE));
    else if(node->lvalue()->type()->name()==basic_type::TYPE_INT && node->rvalue()->type()->name()==basic_type::TYPE_INT)
        node->type(new basic_type(4,basic_type::TYPE_INT));
    
    else if(node->lvalue()->type()->name()==basic_type::TYPE_POINTER && node->rvalue()->type()->name()==basic_type::TYPE_POINTER){
        node->type(new basic_type(4,basic_type::TYPE_POINTER));
        //adding verification for memory reservation
        if(node->rvalue()->type()->subtype()==nullptr){
            node->rvalue()->type()->_subtype=node->lvalue()->type()->subtype();
        }
    }
    
    else if(node->lvalue()->type()->name()==basic_type::TYPE_POINTER && node->rvalue()->type()->name()==basic_type::TYPE_INT)
        node->type(new basic_type(4,basic_type::TYPE_POINTER));
    else if(node->lvalue()->type()->name()==basic_type::TYPE_INT && node->rvalue()->type()->name()==basic_type::TYPE_POINTER)
        node->type(new basic_type(4,basic_type::TYPE_POINTER));
    else if(node->lvalue()->type()->name()==basic_type::TYPE_INT && node->rvalue()->type()->name()==basic_type::TYPE_INT)
        node->type(new basic_type(4,basic_type::TYPE_INT));
    else if(node->lvalue()->type()->name()==basic_type::TYPE_STRING && node->rvalue()->type()->name()==basic_type::TYPE_STRING)
        node->type(new basic_type(4,basic_type::TYPE_STRING));
    //for read node
    else if(node->lvalue()->type()->name()==basic_type::TYPE_INT && node->rvalue()->type()->name()==basic_type::TYPE_VOID){
        node->type(new basic_type(4,basic_type::TYPE_INT));
        node->rvalue()->type(new basic_type(4,basic_type::TYPE_INT));
    }
    else if(node->lvalue()->type()->name()==basic_type::TYPE_DOUBLE && node->rvalue()->type()->name()==basic_type::TYPE_VOID){
        node->type(new basic_type(4,basic_type::TYPE_DOUBLE));
        node->rvalue()->type(new basic_type(4,basic_type::TYPE_DOUBLE));
    }
        
    else
        throw "unexpected error in assignment";
    
}

//---------------------------------------------------------------------------

void xpl::type_checker::do_evaluation_node(xpl::evaluation_node * const node, int lvl) {
  node->argument()->accept(this, lvl + 2);
}

void xpl::type_checker::do_print_node(xpl::print_node * const node, int lvl) {
  node->argument()->accept(this, lvl + 2);
  //for read node
  if(node->argument()->type()->name()==basic_type::TYPE_VOID){
    node->argument()->type(new basic_type(4,basic_type::TYPE_INT));
  }
}

//---------------------------------------------------------------------------

void xpl::type_checker::do_while_node(xpl::while_node * const node, int lvl) {
  node->condition()->accept(this, lvl + 4);
}

//---------------------------------------------------------------------------

void xpl::type_checker::do_if_node(xpl::if_node * const node, int lvl) {
  node->condition()->accept(this, lvl + 4);
}

void xpl::type_checker::do_if_else_node(xpl::if_else_node * const node, int lvl) {
  node->condition()->accept(this, lvl + 4);
}

void xpl::type_checker::do_stop_node(xpl::stop_node * const node, int lvl){
    
}

void xpl::type_checker::do_next_node(xpl::next_node * const node, int lvl){
    
}

void xpl::type_checker::do_return_node(xpl::return_node * const node, int lvl){
    
}

void xpl::type_checker::do_variable_declaration_node(xpl::variable_declaration_node * const node, int lvl){
  if (node->initvalue()) {
    node->initvalue()->accept(this, lvl+2);
    //for read
    if((node->type()->name()==basic_type::TYPE_INT || node->type()->name()==basic_type::TYPE_DOUBLE || node->type()->name()==basic_type::TYPE_STRING) && node->initvalue()->type()->name()==basic_type::TYPE_VOID){
         node->initvalue()->type(clone_type(node->type()));
    } 
    else if (node->type()->name() != node->initvalue()->type()->name() && !(node->type()->name()==basic_type::TYPE_DOUBLE && node->initvalue()->type()->name()==basic_type::TYPE_INT))
        throw std::string("wrong type for initvalue");
     
  }
  
  std::string id = node->name();
  std::shared_ptr<xpl::symbol> symbol = std::make_shared<xpl::symbol>(clone_type(node->type()), id, 0, false,false,node->qualuse());
  if (!_symtab.insert(id, symbol)){
    throw id + " redeclared";
  }
        

}


void xpl::type_checker::do_sweep_up_node(xpl::sweep_up_node * const node, int lvl){
     node->lvalue()->accept(this, lvl + 4);
     if(node->lvalue()->type()->name()!=basic_type::TYPE_INT && node->lvalue()->type()->name()!=basic_type::TYPE_DOUBLE){
         throw std::string("wrong type for sweep lvalue");
     }
     node->init()->accept(this, lvl + 4);
     cdk::assignment_node* assign = new cdk::assignment_node(node->lineno(),node->lvalue(),node->init());
     assign->accept(this,lvl);
     node->cond()->accept(this, lvl + 4);
     cdk::le_node* le = new cdk::le_node(node->lineno(),node->init(),node->cond());
     le->accept(this,lvl);
     node->step()->accept(this, lvl + 4);
     cdk::add_node* add = new cdk::add_node(node->lineno(),node->lvalue(),node->step());
     add->accept(this,lvl);
     cdk::assignment_node* inc = new cdk::assignment_node(node->lineno(),node->lvalue(),add);
     inc->accept(this,lvl);
}


void xpl::type_checker::do_sweep_down_node(xpl::sweep_down_node * const node, int lvl){
     node->lvalue()->accept(this, lvl + 4);
     if(node->lvalue()->type()->name()!=basic_type::TYPE_INT && node->lvalue()->type()->name()!=basic_type::TYPE_DOUBLE){
         throw std::string("wrong type for sweep lvalue");
     }
     node->init()->accept(this, lvl + 4);
     cdk::assignment_node* assign = new cdk::assignment_node(node->lineno(),node->lvalue(),node->init());
     assign->accept(this,lvl);
     node->cond()->accept(this, lvl + 4);
     cdk::ge_node* ge = new cdk::ge_node(node->lineno(),node->init(),node->cond());
     ge->accept(this,lvl);
     node->step()->accept(this, lvl + 4);
     cdk::sub_node* sub = new cdk::sub_node(node->lineno(),node->lvalue(),node->step());
     sub->accept(this,lvl);
     cdk::assignment_node* inc = new cdk::assignment_node(node->lineno(),node->lvalue(),sub);
     inc->accept(this,lvl);
     
}

void xpl::type_checker::do_index_node(xpl::index_node * const node, int lvl){
    ASSERT_UNSPEC;
    node->offset()->accept(this,lvl);
    if(node->offset()->type()->name()!=basic_type::TYPE_INT){
        throw "wrong offset type";
    }
    node->ptr()->accept(this,lvl);
    if(node->ptr()->type()->name()!=basic_type::TYPE_POINTER ){
        throw std::string("ptr type is not pointer");
    }
    if(node->ptr()->type()->subtype()==nullptr)
        throw std::string("ptr does not have a subtype");
    node->type(clone_type(node->ptr()->type()->subtype()));
}

void xpl::type_checker::do_block_node(xpl::block_node * const node, int lvl){
    
}

void xpl::type_checker::do_function_declaration_node(xpl::function_declaration_node * const node, int lvl){
    bool dif_args=false;
    const std::string &id = node->name();
    std::shared_ptr<xpl::symbol> symbol = _symtab.find(id);
    if(symbol){
      for(size_t i = 0;i<symbol->parvec().size();i++){
        xpl::variable_declaration_node* a = dynamic_cast<xpl::variable_declaration_node*> (node->parameters()->node(i));
        if(symbol->parvec()[i]->name()!=a->type()->name()){
            dif_args=true;
        }
      }
    }
    if(!symbol || dif_args){
      std::vector<basic_type*> parvec;
      for(size_t i=0;i<node->parameters()->size();i++){
          xpl::variable_declaration_node* p = dynamic_cast<xpl::variable_declaration_node*> (node->parameters()->node(i));
          parvec.push_back(p->type());
      }
      symbol =  std::make_shared<xpl::symbol>(node->returntype(), id, 0, true, true,true);
      symbol->parvec(parvec);
      _symtab.insert(id,symbol);
    }
    else if(!symbol->func()){
      throw "cannot redefine var"+id+"as function";
    }
    else{
        throw "already declared";
    }
    
}

void xpl::type_checker::do_function_definition_node(xpl::function_definition_node * const node, int lvl){
  bool dif_args=false;
  const std::string &id = node->name();
  std::shared_ptr<xpl::symbol> symbol = _symtab.find(id);
  
  if(symbol){
      for(size_t i = 0;i<symbol->parvec().size();i++){
        xpl::variable_declaration_node* a = dynamic_cast<xpl::variable_declaration_node*> (node->parameters()->node(i));
        if(symbol->parvec()[i]->name()!=a->type()->name()){
            dif_args=true;
        }
      }
  }

  if(!symbol || dif_args){
      if(id=="argc"||id=="argv"){
          throw "cannot define argc/argv";
      }
      std::vector<basic_type*> parvec;
      for(size_t i=0;i<node->parameters()->size();i++){
          xpl::variable_declaration_node* p = dynamic_cast<xpl::variable_declaration_node*> (node->parameters()->node(i));
          parvec.push_back(clone_type(p->type()));
      }
      symbol =  std::make_shared<xpl::symbol>(node->returntype(), id, 0, true, true,false);
      symbol->parvec(parvec);
      _symtab.insert(id,symbol);
  }
  else if(!symbol->func()){
      throw "cannot redefine var"+id+"as function";
  }
}

void xpl::type_checker::do_function_call_node(xpl::function_call_node * const node, int lvl){
    ASSERT_UNSPEC;
    //this is all very optimistic, gotta change it
    const std::string &id = node->name();
    std::shared_ptr<xpl::symbol> symbol = _symtab.find(id);
    node->type(clone_type(symbol->type()));
    for(size_t i = 0;i<symbol->parvec().size();i++){
        cdk::expression_node* a = dynamic_cast<cdk::expression_node*> (node->arguments()->node(i));
        a->accept(this,lvl);
        //for read node
        if((symbol->parvec()[i]->name()==basic_type::TYPE_INT || symbol->parvec()[i]->name()==basic_type::TYPE_DOUBLE) && a->type()->name()==basic_type::TYPE_VOID){
            a->type(clone_type(symbol->parvec()[i]));
        }
        else if(symbol->parvec()[i]->name()!=a->type()->name() && !(symbol->parvec()[i]->name()==basic_type::TYPE_DOUBLE && a->type()->name()==basic_type::TYPE_INT)){
            throw std::string("arguments do not match parameters");
        }
    }
}



void xpl::type_checker::do_address_of_node(xpl::address_of_node * const node, int lvl){
    ASSERT_UNSPEC;
    node->argument()->accept(this,lvl);
    node->type(new basic_type(4,basic_type::TYPE_POINTER));
    node->type()->_subtype=clone_type(node->argument()->type());
}

void xpl::type_checker::do_memory_reservation_node(xpl::memory_reservation_node * const node, int lvl){
    ASSERT_UNSPEC;
    node->argument()->accept(this,lvl);
    if(node->argument()->type()->name()!=basic_type::TYPE_INT){
        throw "wrong argument type";
    }
    node->type(new basic_type(4,basic_type::TYPE_POINTER));
}

void xpl::type_checker::do_read_node(xpl::read_node * const node, int lvl){
    ASSERT_UNSPEC;
    //just declaring the type as void so that we then recognize it and can replace it based on context
    node->type(new basic_type(0,basic_type::TYPE_VOID));
}

void xpl::type_checker::do_identity_node(xpl::identity_node * const node, int lvl){
    processUnaryExpression(node, lvl);
    
}

