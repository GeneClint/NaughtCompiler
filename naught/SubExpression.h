// Clint Malcolm
// 1134490
// clintm@cs.washington.edu
// Gene Kim
// 1130267
// genelkim@uw.edu

#include <string>

#ifndef __SUB_EXPR_H
#define __SUB_EXPR_H

#include "Term.h"
#include "Expression.h"

class SubExpression : public Expression {
  public:
    SubExpression(Expression &e1, Expression &e2) : Expression(), expr1(&e1), expr2(&e2) {};
    Expression* getValue1() const;
    Expression* getValue2() const;
    virtual std::string toString() const;

    std::vector<std::string> getConnectors() const {return std::vector<std::string>({"-"});};

  private:
    Expression* expr1;
    Expression* expr2;
};

#endif
