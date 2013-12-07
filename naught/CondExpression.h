// Clint Malcolm
// 1134490
// clintm@cs.washington.edu
// Gene Kim
// 1130267
// genelkim@uw.edu

#include <string>

#ifndef __COND_EXPR_H
#define __COND_EXPR_H

#include "Term.h"
#include "Expression.h"

class CondExpression : public Expression {
  public:
    CondExpression(Expression &e1, Expression &e2, Expression &e3) : Expression(), expr1(&e1), expr2(&e2), expr3(&e3) {};
    Expression* getValue1() const;
    Expression* getValue2() const;
    Expression* getValue3() const;

    std::vector<std::string> getConnectors() const {return std::vector<std::string>({"?",":"});};
    virtual std::string toString() const; 

  private:
    Expression* expr1;
    Expression* expr2;
    Expression* expr3;
};

#endif
