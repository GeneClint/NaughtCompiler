#include "DivExpression.h"

DivExpression::DivExpression(Expression e1, Expression e2) {
  *expr1 = e1;
  *expr2 = e2;
}

DivExpression::Expression* getValue1() const {
  return expr1;
}

DivExpression::Expression* getValue2() const {
  return expr2;
}
