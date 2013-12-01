#ifndef __COND_EXPR_H
#define __COND_EXPR_H

#include "Term.h"
#include "Expression.h"

class CondExpression : public Expression {
  public:
    CondExpression(Expression e1, Expression e2, Expression e3) : Expression() {};
    Expression* getValue1() const;
    Expression* getValue2() const;
    Expression* getValue3() const;

  private:
    Expression* expr1;
    Expression* expr2;
    Expression* expr3;
};

#endif
