#include <string>

#include "Id.h"
#include "StrUtil.h"
#include "Expression.h"
#include "Decl.h"

#ifndef __VARDECL_H
#define __VARDECL_H

class VarDecl : public Decl {
 public:
  VarDecl (const std::string &t, Id &i,
	         const bool &ex = false, const Expression *e = nullptr) :
            type(t), id(&i), ext(ex), exp(e) {}; 

  //~VarDecl() { delete id; }

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
  Id *id;
  const bool ext;
  const Expression *exp;
};

#endif
