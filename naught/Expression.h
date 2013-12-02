#ifndef __EXPR_H
#define __EXPR_H
#include <string>

class Term;

class Expression {
 public:
  virtual ~Expression() {}
  
  Expression* evaluate() {return this;}

  virtual std::string toString() const = 0;
      

  friend std::ostream& operator<<(std::ostream &os, const Expression &e) {
    os << e.toString();
    return os;
  }
};
#endif
