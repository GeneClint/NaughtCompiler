#ifndef __DIV_EXPR_H
#define __DIV_EXPR_H

#include "Term.h"
#include "Expression.h"

class DivExpression : public Expression {
  public:
    DivExpression(Expression e1, Expression e2) : Expression() {};
    Expression* getValue1() const;
    Expression* getValue2() const;

  private:
    Expression* expr1;
    Expression* expr2;
};

#endif
