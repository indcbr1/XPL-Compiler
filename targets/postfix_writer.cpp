#include <string>
#include <sstream>
#include "targets/type_checker.h"
#include "targets/postfix_writer.h"
#include "ast/all.h"  // all.h is automatically generated

#include "targets/enter_size_visitor.h"
//---------------------------------------------------------------------------

void xpl::postfix_writer::do_sequence_node(cdk::sequence_node * const node, int lvl) {
  for (size_t i = 0; i < node->size(); i++) {
    node->node(i)->accept(this, lvl);
  }
}

//---------------------------------------------------------------------------

void xpl::postfix_writer::do_integer_node(cdk::integer_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  if(_glb){
      if(_dec_conv)
        _pf.DOUBLE(node->value());
      else
        _pf.CONST(node->value());
  }
  else{
    _pf.INT(node->value()); // push an integer
  }
}

void xpl::postfix_writer::do_string_node(cdk::string_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  int lbl1;

  /* generate the string */
  _pf.RODATA(); // strings are DATA readonly
  _pf.ALIGN(); // make sure we are aligned
  _pf.LABEL(mklbl(lbl1 = ++_lbl)); // give the string a name
  _pf.STR(node->value()); // output string characters
  if(!_glb){
    /* leave the address on the stack */
    _pf.TEXT(); // return to the TEXT segment
    _pf.ADDR(mklbl(lbl1)); // the string to be printed
    }
  else{
    _declbl=lbl1;
  }
}

void xpl::postfix_writer::do_double_node(cdk::double_node * const node, int lvl) {
    ASSERT_SAFE_EXPRESSIONS;
    if(_glb){
        _pf.DOUBLE(node->value());
    }
    else{
        int lbl1;
        /* generate the double */
        _pf.RODATA(); 
        _pf.ALIGN(); 
        _pf.LABEL(mklbl(lbl1 = ++_lbl)); // give the double a name
        _pf.DOUBLE(node->value()); // output double
        _pf.TEXT();
        _pf.ADDR(mklbl(lbl1));
        _pf.DLOAD();
    }
}

void xpl::postfix_writer::do_null_node(xpl::null_node * const node, int lvl){
  ASSERT_SAFE_EXPRESSIONS;
  if(_glb){
    _pf.CONST(0);
  }
  else{
    _pf.INT(0); // push an integer
  }
}


//---------------------------------------------------------------------------

void xpl::postfix_writer::do_neg_node(cdk::neg_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->argument()->accept(this, lvl);// determine the value
  if(node->type()->name()==basic_type::TYPE_DOUBLE)
    _pf.DNEG(); // 2-complement
  else
    _pf.NEG();
}

void xpl::postfix_writer::do_not_node(cdk::not_node * const node, int lvl) {
    ASSERT_SAFE_EXPRESSIONS;
    node->argument()->accept(this,lvl);
    _pf.NOT();
}

//---------------------------------------------------------------------------

void xpl::postfix_writer::process_add(cdk::binary_expression_node * const node, int lvl){
    //check if either side differs
  node->left()->accept(this, lvl);
  if(node->left()->type()->name()==basic_type::TYPE_INT && node->right()->type()->name()==basic_type::TYPE_DOUBLE ){
      _pf.I2D();
  }
  else if(node->left()->type()->name()==basic_type::TYPE_INT && node->right()->type()->name()==basic_type::TYPE_POINTER ){
      _pf.INT(node->right()->type()->subtype()->size());
      _pf.MUL();
  }
  
  node->right()->accept(this, lvl);
  if(node->right()->type()->name()==basic_type::TYPE_INT && node->left()->type()->name()==basic_type::TYPE_DOUBLE ){
      _pf.I2D();
  }
  else if(node->right()->type()->name()==basic_type::TYPE_INT && node->left()->type()->name()==basic_type::TYPE_POINTER ){
      _pf.INT(node->left()->type()->subtype()->size());
      _pf.MUL();
  }
}

void xpl::postfix_writer::process_mul(cdk::binary_expression_node * const node, int lvl){
    //check if either side differs
  node->left()->accept(this, lvl);
  if(node->left()->type()->name()==basic_type::TYPE_INT && node->right()->type()->name()==basic_type::TYPE_DOUBLE )
      _pf.I2D();
  
  node->right()->accept(this, lvl);
  if(node->right()->type()->name()==basic_type::TYPE_INT && node->left()->type()->name()==basic_type::TYPE_DOUBLE )
      _pf.I2D();
}

void xpl::postfix_writer::process_cmp(cdk::binary_expression_node * const node, int lvl){
  process_mul(node, lvl);
  //gotta manually attribute int, because it is always integer
  node->type(new basic_type(4,basic_type::TYPE_INT));
  if(node->left()->type()->name()==basic_type::TYPE_DOUBLE || node->right()->type()->name()==basic_type::TYPE_DOUBLE){
    _pf.DCMP();
    _pf.INT(0);
  }
}



void xpl::postfix_writer::do_add_node(cdk::add_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  process_add(node,lvl);
  //check if result is gonna be double or not
  if(node->type()->name()==basic_type::TYPE_DOUBLE){
    _pf.DADD();
  }
  else{
    _pf.ADD();
  }
    
}


void xpl::postfix_writer::do_sub_node(cdk::sub_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  //check if either side differs
  process_add(node,lvl);
  //check if result is gonna be double or not
  if(node->type()->name()==basic_type::TYPE_DOUBLE)
    _pf.DSUB();
  else
    _pf.SUB();
  //check if difference between pointers, gotta reduce difference to actual difference of sizes
  if(node->right()->type()->name()==basic_type::TYPE_POINTER && node->left()->type()->name()==basic_type::TYPE_POINTER ){
    _pf.INT(node->left()->type()->subtype()->size());
    _pf.DIV();
  }
}
void xpl::postfix_writer::do_mul_node(cdk::mul_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  process_mul(node, lvl);
  if(node->type()->name()==basic_type::TYPE_DOUBLE)
    _pf.DMUL();
  else 
    _pf.MUL();
}
void xpl::postfix_writer::do_div_node(cdk::div_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  process_mul(node, lvl);
  if(node->type()->name()==basic_type::TYPE_DOUBLE)
    _pf.DDIV();
  else
    _pf.DIV();
}
void xpl::postfix_writer::do_mod_node(cdk::mod_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.MOD();
}




void xpl::postfix_writer::do_lt_node(cdk::lt_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  process_cmp( node, lvl);
  _pf.LT();
}
void xpl::postfix_writer::do_le_node(cdk::le_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  process_cmp( node, lvl);
  _pf.LE();
}
void xpl::postfix_writer::do_ge_node(cdk::ge_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  process_cmp( node, lvl);
  _pf.GE();
}
void xpl::postfix_writer::do_gt_node(cdk::gt_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  process_cmp( node, lvl);
  _pf.GT();
}
void xpl::postfix_writer::do_ne_node(cdk::ne_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  process_cmp( node, lvl);
  _pf.NE();
}
void xpl::postfix_writer::do_eq_node(cdk::eq_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  process_cmp( node, lvl);
  _pf.EQ();
}

void xpl::postfix_writer::do_and_node(cdk::and_node * const node, int lvl) {
    ASSERT_SAFE_EXPRESSIONS;
    int lbl1;
    node->left()->accept(this, lvl);
    //this dup is necessary because the jump consumes the top of the stack and we gotta have something when we return 
    _pf.DUP();
    _pf.JZ(mklbl(lbl1 = ++_lbl));
    //we dont need the dup
    _pf.TRASH(4);
    node->right()->accept(this,lvl);
    //its not a logical and so we dont have to call AND!
    _pf.LABEL(mklbl(lbl1));
}

void xpl::postfix_writer::do_or_node(cdk::or_node * const node, int lvl) {
    ASSERT_SAFE_EXPRESSIONS;
    int lbl1;
    node->left()->accept(this, lvl);
    //this dup is necessary because the jump consumes the top of the stack and we gotta have something when we return 
    _pf.DUP();
    _pf.JNZ(mklbl(lbl1 = ++_lbl));
    //we dont need the dup
    _pf.TRASH(4);
    node->right()->accept(this,lvl);
    //its not a logical or so we dont have to call OR!
    _pf.LABEL(mklbl(lbl1));
}



//---------------------------------------------------------------------------

void xpl::postfix_writer::do_identifier_node(cdk::identifier_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  // simplified generation: all variables are global
  const std::string &id = node->name();
  std::shared_ptr<xpl::symbol> symbol = _symtab.find(id);
  int pos_size,neg_size; 
  if(node->name()==_func_name){
    pos_size=symbol->type()->size();
    neg_size=-pos_size;
    _pf.LOCAL(neg_size);   
  }
  else if(symbol->global()){
    _pf.ADDR(symbol->name());
  }
  else{
    _pf.LOCAL(symbol->offset());
}
  
}

void xpl::postfix_writer::do_rvalue_node(cdk::rvalue_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->lvalue()->accept(this, lvl);
  if(node->type()->name()==basic_type::TYPE_DOUBLE){
   _pf.DLOAD();   
  }
  else{
  _pf.LOAD(); // depends on type size
  }
      
}

void xpl::postfix_writer::do_assignment_node(cdk::assignment_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->rvalue()->accept(this, lvl); // determine the new value
  //gotta check if we can actualy convert it. Any other types require no conversion whatsoever
  if(node->lvalue()->type()->name()==basic_type::TYPE_DOUBLE && node->rvalue()->type()->name()==basic_type::TYPE_INT){
      _pf.I2D();
  }
  else if(node->lvalue()->type()->name()==basic_type::TYPE_INT && node->rvalue()->type()->name()==basic_type::TYPE_DOUBLE){
      throw "cannot assign double value to integer lvalue";
  }
  if(node->type()->name()==basic_type::TYPE_DOUBLE){
    _pf.DDUP();
    node->lvalue()->accept(this, lvl); // where to store the value
    _pf.DSTORE();
  }
  else{
  _pf.DUP();
  node->lvalue()->accept(this, lvl); // where to store the value
  _pf.STORE(); // store the value at address
  }
      
}


//---------------------------------------------------------------------------

void xpl::postfix_writer::do_evaluation_node(xpl::evaluation_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->argument()->accept(this, lvl); // determine the value
  if (node->argument()->type()->name() == basic_type::TYPE_INT) {
    _pf.TRASH(4); // delete the evaluated value
  } else if (node->argument()->type()->name() == basic_type::TYPE_STRING) {
    _pf.TRASH(4); // delete the evaluated value's address
  } else if(node->argument()->type()->name() == basic_type::TYPE_DOUBLE){
    _pf.TRASH(8);
  } else if (node->argument()->type()->name() == basic_type::TYPE_POINTER){
      _pf.TRASH(4);
  }
  else if (node->argument()->type()->name() == basic_type::TYPE_VOID){
      //do nothing, trash nothing
  }
  else{
    std::cerr << "ERROR: CANNOT HAPPEN!" << std::endl;
    exit(1);
  }
}

void xpl::postfix_writer::do_print_node(xpl::print_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->argument()->accept(this, lvl); // determine the value to print
  if (node->argument()->type()->name() == basic_type::TYPE_INT) {
    _pf.CALL("printi");
    _pf.TRASH(4); // delete the printed value
  } else if (node->argument()->type()->name() == basic_type::TYPE_STRING) {
    _pf.CALL("prints");
    _pf.TRASH(4); // delete the printed value's address
  } else if (node->argument()->type()->name() == basic_type::TYPE_DOUBLE) {
    _pf.CALL("printd");
    _pf.TRASH(8);
  }
    else {
    std::cerr << "ERROR: CANNOT HAPPEN!" << std::endl;
    exit(1);
  }
  if(node->newline()){
    _pf.CALL("println"); // print a newline
  }
      
}

//---------------------------------------------------------------------------

void xpl::postfix_writer::do_while_node(xpl::while_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  int lbl1, lbl2;
  _nextlbls.push(lbl1=++_lbl);
  _stoplbls.push(lbl2=++_lbl);
  _pf.LABEL(mklbl(lbl1));
  node->condition()->accept(this, lvl);
  _pf.JZ(mklbl(lbl2));
  node->block()->accept(this, lvl + 2);
  _pf.JMP(mklbl(lbl1));
  _pf.LABEL(mklbl(lbl2));
}

//---------------------------------------------------------------------------

void xpl::postfix_writer::do_if_node(xpl::if_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  int lbl1;
  node->condition()->accept(this, lvl);
  _pf.JZ(mklbl(lbl1 = ++_lbl));
  node->block()->accept(this, lvl + 2);
  _pf.LABEL(mklbl(lbl1));
}

//---------------------------------------------------------------------------

void xpl::postfix_writer::do_if_else_node(xpl::if_else_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  int lbl1, lbl2;
  node->condition()->accept(this, lvl);
  _pf.JZ(mklbl(lbl1 = ++_lbl));
  node->thenblock()->accept(this, lvl + 2);
  _pf.JMP(mklbl(lbl2 = ++_lbl));
  _pf.LABEL(mklbl(lbl1));
  node->elseblock()->accept(this, lvl + 2);
  _pf.LABEL(mklbl(lbl1 = lbl2));
}


void xpl::postfix_writer::do_stop_node(xpl::stop_node * const node, int lvl){
    _pf.JMP(mklbl(_stoplbls.top()));
    _stoplbls.pop();
}

void xpl::postfix_writer::do_next_node(xpl::next_node * const node, int lvl){
    _pf.JMP(mklbl(_nextlbls.top()));
    _nextlbls.pop();
}

void xpl::postfix_writer::do_return_node(xpl::return_node * const node, int lvl){
    _pf.JMP(mklbl(_retlbl));
}

void xpl::postfix_writer::do_variable_declaration_node(xpl::variable_declaration_node * const node, int lvl){
    ASSERT_SAFE_EXPRESSIONS;
    if(!_arg_def){
        if(node->qualuse()){
            _externs.push_back(node->name());
            std::string id = node->name();
            std::shared_ptr<xpl::symbol> symbol = _symtab.find(id);
            symbol->global(true);
        }
        else if(_glb){
            std::string id = node->name();
            std::shared_ptr<xpl::symbol> symbol = _symtab.find(id);
            symbol->global(true);
            if(node->initvalue()==nullptr){
                if(node->type()->name()==basic_type::TYPE_STRING){
                    _pf.DATA();
                }
                else{
                    _pf.BSS();
                }
                _pf.ALIGN();
                if(node->qualpublic()){
                    _pf.GLOBAL(node->name(), _pf.OBJ());
                }
                _pf.LABEL(node->name());
                if(node->type()->name()==basic_type::TYPE_DOUBLE){
                    _pf.BYTE(8);
                }
                else{
                    _pf.BYTE(4);
                }
            }
            else{
                if(node->type()->name()==basic_type::TYPE_STRING){
                    node->initvalue()->accept(this,lvl);
                }
                _pf.DATA();
                _pf.ALIGN();
                if(node->qualpublic()){
                    _pf.GLOBAL(node->name(),_pf.OBJ());
                }
                _pf.LABEL(node->name());
                if(node->type()->name()==basic_type::TYPE_STRING){
                    _pf.ID(mklbl(_declbl));
                }
                else{
                    if(node->type()->name()==basic_type::TYPE_DOUBLE && node->initvalue()->type()->name()==basic_type::TYPE_INT){
                        _dec_conv=true;
                        node->initvalue()->accept(this,lvl);
                        _dec_conv=false;
                    }
                    else{
                        node->initvalue()->accept(this,lvl);
                    }
                }
            }
        }
        else{
            _rel_sp-=node->type()->size();
            std::string id = node->name();
            std::shared_ptr<xpl::symbol> symbol = _symtab.find(id);
            symbol->offset(_rel_sp);
            if(node->initvalue()!=nullptr){
                node->initvalue()->accept(this,lvl);
                _pf.LOCAL(_rel_sp);
                if(node->type()->name()==basic_type::TYPE_DOUBLE)
                    _pf.DSTORE();
                else
                    _pf.STORE();
            }
        }
        
        
    }
    
    else{
        std::string id = node->name();
        std::shared_ptr<xpl::symbol> symbol = _symtab.find(id);
        symbol->offset(_arg_sp);
        _arg_sp+=node->type()->size();
        
    }
    
}

void xpl::postfix_writer::do_sweep_up_node(xpl::sweep_up_node * const node, int lvl){
    ASSERT_SAFE_EXPRESSIONS;
    int lbl1=++_lbl, lbl2,lbl3;
    _nextlbls.push(lbl2=++_lbl);
    _stoplbls.push(lbl3=++_lbl);
    cdk::assignment_node* assign = new cdk::assignment_node(node->lineno(),node->lvalue(),node->init());
    assign->accept(this,lvl);
    _pf.LABEL(mklbl(lbl1));
    cdk::rvalue_node* rval = new cdk::rvalue_node(node->lineno(),node->lvalue());
    cdk::le_node* le = new cdk::le_node(node->lineno(),rval,node->cond());
     le->accept(this,lvl);
    _pf.JZ(mklbl(lbl3));
    node->block()->accept(this, lvl + 2);
    _pf.LABEL(mklbl(lbl2));
    cdk::add_node* add = new cdk::add_node(node->lineno(),rval,node->step());
     add->accept(this,lvl);
     cdk::assignment_node* inc = new cdk::assignment_node(node->lineno(),node->lvalue(),add);
     inc->accept(this,lvl);
     if(node->lvalue()->type()->name()==basic_type::TYPE_DOUBLE || node->step()->type()->name()==basic_type::TYPE_DOUBLE){
      _pf.TRASH(8);   
     }
     else{
      _pf.TRASH(4);
     }
    _pf.JMP(mklbl(lbl1));
    _pf.LABEL(mklbl(lbl3));
    _stoplbls.pop();
    _nextlbls.pop();
        
}

void xpl::postfix_writer::do_sweep_down_node(xpl::sweep_down_node * const node, int lvl){
    ASSERT_SAFE_EXPRESSIONS;
    int lbl1=++_lbl, lbl2,lbl3;
    _nextlbls.push(lbl2=++_lbl);
    _stoplbls.push(lbl3=++_lbl);
    cdk::assignment_node* assign = new cdk::assignment_node(node->lineno(),node->lvalue(),node->init());
    assign->accept(this,lvl);
    _pf.LABEL(mklbl(lbl1));
    cdk::rvalue_node* rval = new cdk::rvalue_node(node->lineno(),node->lvalue());
    cdk::ge_node* ge = new cdk::ge_node(node->lineno(),rval,node->cond());
     ge->accept(this,lvl);
    _pf.JZ(mklbl(lbl3));
    node->block()->accept(this, lvl + 2);
    _pf.LABEL(mklbl(lbl2));
    cdk::sub_node* sub = new cdk::sub_node(node->lineno(),rval,node->step());
     sub->accept(this,lvl);
     cdk::assignment_node* inc = new cdk::assignment_node(node->lineno(),node->lvalue(),sub);
     inc->accept(this,lvl);
     if(node->lvalue()->type()->name()==basic_type::TYPE_DOUBLE || node->step()->type()->name()==basic_type::TYPE_DOUBLE){
      _pf.TRASH(8);   
     }
     else{
      _pf.TRASH(4);
     }
    _pf.JMP(mklbl(lbl1));
    _pf.LABEL(mklbl(lbl3));
    _stoplbls.pop();
    _nextlbls.pop();
}

void xpl::postfix_writer::do_pratic1_node(xpl::pratic1_node * const node, int lvl){
    //all types are checked because we accept everything
    xpl::variable_declaration_node* vardec = new xpl::variable_declaration_node(node->lineno(),false,false,new basic_type(4,basic_type::TYPE_INT),new std::string(".i"),nullptr);
    vardec->accept(this,lvl);
    cdk::identifier_node* i = new cdk::identifier_node(node->lineno(), new std::string(".i"));
    cdk::identifier_node* v = new cdk::identifier_node(node->lineno(), new std::string(node->vec()));
    cdk::rvalue_node* irval = new cdk::rvalue_node(node->lineno(),i);
    cdk::rvalue_node* vrval = new cdk::rvalue_node(node->lineno(),v);
    xpl::index_node* index = new xpl::index_node(node->lineno(), vrval, irval);
    cdk::rvalue_node* rval = new cdk::rvalue_node(node->lineno(),index);
    cdk::sequence_node* args = new cdk::sequence_node(node->lineno(), rval);
    xpl::function_call_node* call = new xpl::function_call_node(node->lineno(),new std::string(node->func()),args );
    cdk::sequence_node* block = new cdk::sequence_node(node->lineno(),call);
    xpl::sweep_up_node* sweep = new xpl::sweep_up_node(node->lineno(),i, node->low(), node->high(),new cdk::integer_node(node->lineno(),1), block );
    sweep->accept(this,lvl);
    
}


void xpl::postfix_writer::do_index_node(xpl::index_node * const node, int lvl){
    ASSERT_SAFE_EXPRESSIONS;
    node->ptr()->accept(this,lvl);
    node->offset()->accept(this,lvl);
    _pf.INT(node->type()->size());
    _pf.MUL();
    _pf.ADD();
}

void xpl::postfix_writer::do_block_node(xpl::block_node * const node, int lvl){
  _symtab.push();
  node->declarations()->accept(this,lvl);
  node->instructions()->accept(this,lvl);
  _symtab.pop();  
}

void xpl::postfix_writer::do_function_declaration_node(xpl::function_declaration_node * const node, int lvl){
    ASSERT_SAFE_EXPRESSIONS;
    //public or use declarations are always extern unless they have a definition, in which case we will remove them later
    if(node->qualuse() || node->qualpublic())
        _externs.push_back(node->name());
}

void xpl::postfix_writer::do_function_definition_node(xpl::function_definition_node * const node, int lvl){
  ASSERT_SAFE_EXPRESSIONS;
  int pos_size,neg_size;
  std::string fname;
  
  const std::string &id = node->name();
  std::shared_ptr<xpl::symbol> symbol = _symtab.find(id);
  if(symbol && symbol->use()){
    removeExtern(node->name());
  }
  
  pos_size= node->returntype()->size();
  neg_size= -pos_size;
  _rel_sp= neg_size;
  _arg_sp= 8; //gotta take return address into account, otherwhise every argument value is compromised!!!!
  _func_name=node->name();
  xpl::enter_size_visitor sizeVis(_compiler);
  //actual pf code
  _pf.TEXT();
  _pf.ALIGN();
  if(node->name()=="_main"){
      //names that start in . are ilegal anyways, so this is a fine name
      fname=".main";
  }
  else{
    fname= node->name()=="xpl" ? "_main" : node->name();
  }
  if(node->qualpublic()){
    _pf.GLOBAL(fname, _pf.FUNC());
  }
  _pf.LABEL(fname);
  node->accept(&sizeVis,lvl);
  _pf.ENTER(sizeVis.totalsize()+pos_size);
  _glb=false;
  //atribute default return
  if(node->defaultreturn()!=nullptr){
      node->defaultreturn()->accept(this,lvl);
      if(node->defaultreturn()->type()->name()==basic_type::TYPE_INT && node->returntype()->name()==basic_type::TYPE_DOUBLE){
        _pf.I2D();
      }
      _pf.LOCAL(_rel_sp);
      if(node->returntype()->name()==basic_type::TYPE_DOUBLE)
        _pf.DSTORE();
      else
        _pf.STORE();
  }
  //register parameters in symtab
  _symtab.push(); //this is important so that the arguments in the symtab are deleted after execution. This seems dumb but it's either this or a clownfiesta which includes if's and global variables
  _arg_def=true;
  if(node->parameters()->size()>0){
        for (int i = node->parameters()->size()-1; i >=0; i--) {
            node->parameters()->node(i)->accept(this,lvl);
        }
  }
  _arg_def=false;
  _retlbl=++_lbl; //defining it before so that we get the right one when we mention it in the body
  //accepting function body
  node->body()->accept(this, lvl);
  _pf.LABEL(mklbl(_retlbl)); //defining where we gotta go if we return
  // end the main function
  _func_name="";
  _glb=true;
  //actual pf code
  _pf.LOCAL(neg_size);
  if(node->returntype()->name()==basic_type::TYPE_DOUBLE){
    _pf.DLOAD();
    _pf.DPOP();
  }
  else if(!node->returntype()->name()!=basic_type::TYPE_VOID){
    _pf.LOAD();
    _pf.POP();
  }
  _pf.LEAVE();
  _pf.RET();
  _symtab.pop(); //popping the arg context
  //we only gotta do this once, and every file has a xpl function
   if(node->name()=="xpl"){
        _pf.EXTERN("readi");
        _pf.EXTERN("readd");
        _pf.EXTERN("printi");
        _pf.EXTERN("prints");
        _pf.EXTERN("printd");
        _pf.EXTERN("println");
   }

       
}

void xpl::postfix_writer::do_function_call_node(xpl::function_call_node * const node, int lvl){
    ASSERT_SAFE_EXPRESSIONS;
    xpl::enter_size_visitor sizeVis(_compiler); 
    const std::string &id = node->name();
    std::shared_ptr<xpl::symbol> symbol = _symtab.find(id);
    //if we dont find it, we gotta create it
    //we gotta see if the arguments types are the same, otherwhise its a different function
    
    if(!symbol || !symbol->func()){
        throw "could not find" + id;
    }
    //push all the arguments
    if(node->arguments()->size()>0){
        for (int i = node->arguments()->size()-1; i >=0; i--) {
            basic_type* p = symbol->parvec()[symbol->parvec().size()-1-i];
            cdk::expression_node* a = dynamic_cast<cdk::expression_node*> (node->arguments()->node(i));
            node->arguments()->node(i)->accept(this,lvl);
            if(p->name()==basic_type::TYPE_DOUBLE && a->type()->name()==basic_type::TYPE_INT){
                _pf.I2D();
            }
        }
    }
    _pf.CALL(node->name());
    node->arguments()->accept(&sizeVis,lvl);
    _pf.TRASH(sizeVis.totalsize());
    if(node->type()->name()==basic_type::TYPE_DOUBLE)
      _pf.DPUSH();
    else
      _pf.PUSH();
}

void xpl::postfix_writer::do_address_of_node(xpl::address_of_node * const node, int lvl){
    ASSERT_SAFE_EXPRESSIONS;
    node->argument()->accept(this,lvl);
    
}

void xpl::postfix_writer::do_memory_reservation_node(xpl::memory_reservation_node * const node, int lvl){
    ASSERT_SAFE_EXPRESSIONS;
    _pf.INT(node->type()->subtype()->size());
    node->argument()->accept(this,lvl);
    _pf.MUL();
    //allocates space on stack
    _pf.ALLOC();
    //leaves the address of the allocation in the stack
    _pf.SP();
}

void xpl::postfix_writer::do_read_node(xpl::read_node * const node, int lvl){
  // DISCLAIMER: I assumed that read could not be used in binary/unary expressions, otherwhise it would be extremly complex to deal with it
  ASSERT_SAFE_EXPRESSIONS;
  if (node->type()->name() == basic_type::TYPE_INT) {
    _pf.CALL("readi");
    _pf.PUSH(); // delete the printed value
  } else if (node->type()->name() == basic_type::TYPE_DOUBLE) {
    _pf.CALL("readd");
    _pf.DPUSH();
  }
    else {
    std::cerr << "ERROR: CANNOT HAPPEN!" << std::endl;
    exit(1);
  }
}

void xpl::postfix_writer::do_identity_node(xpl::identity_node * const node, int lvl){
  ASSERT_SAFE_EXPRESSIONS;
  node->argument()->accept(this, lvl);
}
