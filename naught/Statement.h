#include <string>

#include "Expression.h"

#ifndef __STATEMENT_H
#define __STATEMENT_H

class Statement {
 public:
  Statement (Expression &e, const bool &r = false) : isRet(r), exp(&e) {};
  bool isReturn() const;
  const Expression* getExpression() const;
  std::string toString() const;

  friend std::ostream& operator<<(std::ostream &os, const Statement &p) {
    os << p.toString();
    return os;
  }

 private:
  const bool isRet;
  const Expression* exp; 
};

#endif
