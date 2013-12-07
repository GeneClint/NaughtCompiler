// Clint Malcolm
// 1134490
// clintm@cs.washington.edu
// Gene Kim
// 1130267
// genelkim@uw.edu

#include <string>

#include "Expression.h"

#ifndef __STATEMENT_H
#define __STATEMENT_H

class Statement {
 public:
  Statement (Expression *e, const bool &r = false) : isRet(r), exp(e) {};
  
  bool isReturn() const;
  const Expression* getExpression() const;
  std::string toString() const;

  void deleteExp() { delete exp; }

  friend std::ostream& operator<<(std::ostream &os, const Statement &p) {
    os << p.toString();
    return os;
  }

 private:
  bool isRet;
  Expression *exp; 
};

#endif
