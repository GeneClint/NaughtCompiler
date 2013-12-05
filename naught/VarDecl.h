#include <string>

#include "Id.h"
#include "StrUtil.h"
#include "Expression.h"
#include "Decl.h"

#ifndef __VARDECL_H
#define __VARDECL_H

class VarDecl : public Decl {
 public:
  VarDecl (const std::string &t, const Id &i,
	   const bool &ex = false, const Expression *e = NULL) :
           type(t), id(i.getName()), ext(ex), exp(e) {};
  
  Id getId() const;
  std::string getType() const;
  bool isExtern() const;
  Expression* getExpression() const;
  bool isFunction() const {return false;};

  std::string toString() const;

  friend std::ostream& operator<<(std::ostream &os, const VarDecl &v) {
    os << v.toString();
    return os;
  }

 private:
  const std::string type;
  const Id id;
  const bool ext;
  const Expression *exp;
};

#endif
