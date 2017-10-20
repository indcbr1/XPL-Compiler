#ifndef __XPL_SEMANTICS_SYMBOL_H__
#define __XPL_SEMANTICS_SYMBOL_H__

#include <string>
#include <cdk/basic_type.h>

#include <vector>



namespace xpl {

    class symbol {
      basic_type *_type;
      std::string _name;
      int _offset; 
      bool _global;
      bool _func;
      bool _use;
      std::vector<basic_type*> _parvec;
      
      public:
      inline symbol(basic_type *type, const std::string &name, int offset,bool global,bool func, bool use) :
          _type(type), _name(name), _offset(offset), _global(global), _func(func),_use(use) {
      }

      virtual ~symbol() {
        delete _type;
      }

      inline basic_type *type() const {
        return _type;
      }
      inline const std::string &name() const {
        return _name;
      }
      inline int offset() const {
        return _offset;
      }
      inline int offset(int i) {
        return _offset = i;
      }
      inline bool global() const{
        return _global;
      }
      inline void global(bool global){
        _global = global;
      }
      inline bool func() const{
        return _func;
      }
      inline void func(bool func){
        _func = func;
      }
      inline bool use() const{
        return _use;
      }
      inline void use(bool use){
        _use = use;
      }
      inline std::vector<basic_type*> parvec() const{
        return _parvec;
      }
      inline void parvec(std::vector<basic_type*> parvec){
        _parvec = parvec;
      }
      
      
    };

} // xpl

#endif
