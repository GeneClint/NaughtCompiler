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

  private:
    Expression* expr1;
    Expression* expr2;
};

#endif