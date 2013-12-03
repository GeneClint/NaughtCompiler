#ifndef __EXPR_H
#define __EXPR_H
#include <string>
#include <vector>

class Term;

class Expression {
 public:
  virtual ~Expression() {}
  
  const Expression* evaluate() {return this;}

  virtual std::string toString() const = 0;
  virtual Expression* getValue1() const {return NULL;};
  virtual Expression* getValue2() const {return NULL;};
  virtual Expression* getValue3() const {return NULL;};
  virtual Term* getTerm() const {return NULL;};
  virtual std::vector<std::string> getConnectors() const = 0;

  friend std::ostream& operator<<(std::ostream &os, const Expression &e) {
    os << e.toString();
    return os;
  }
};
#endif
