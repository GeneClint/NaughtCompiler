#include "CondExpression.h"

CondExpression::CondExpression(Expression e1, Expression e2, Expression e3) {
  *expr1 = e1;
  *expr2 = e2;
  *expr3 = e3;
}

CondExpression::Expression* getValue1() const {
  return expr1;
}

CondExpression::Expression* getValue2() const {
  return expr2;
}

CondExpression::Expression* getValue3() const {
  return expr3;
}
