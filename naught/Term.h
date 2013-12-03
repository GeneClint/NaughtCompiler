// Looking at class this is an "each of type" as explained in 341,
// there are a lot of shitty ways to represent this in c++, and having
// a class that basically does nothing and then asking typeof seems to
// be the best solution
// reference: http://astitcher.github.io/ACCU2012/slides/algebraic.html
#include <string>
#include "Expression.h"

#ifndef __TERM_H
#define __TERM_H

class Term : public Expression {
public:
  virtual ~Term() {};
  Term* evaluate() {return this;}
  Term* getTerm() {return this;}
  Term* getInnerTerm() {return NULL;}
  Expression* getInnerExpression() {return NULL;}
  
  std::vector<std::string> getConnectors() const {return std::vector<std::string>();}
  virtual std::string toString() const =0;

  friend std::ostream& operator<<(std::ostream &os, const Term &t) {
    os << t.toString();
    return os;
  }

};

#endif // __TERM_H
