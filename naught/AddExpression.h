#ifndef __ADD_EXPR_H
#define __ADD_EXPR_H

#include "Term.h"
#include "Expression.h"

class AddExpression : public Expression {
  public:
    virtual ~AddExpression() {};
    AddExpression(StrUtil *ignore) : Expression(), expr1(nullptr), expr2(nullptr) {};
    AddExpression(Expression e1, Expression e2) : Expression(), expr1(&e1), expr2(&e2) {};
    Expression* getValue1() const;
    Expression* getValue2() const;

  private:
    Expression* expr1;
    Expression* expr2;
};

#endif
