#include "SubExpression.h"

SubExpression::SubExpression(Expression e1, Expression e2) {
  *expr1 = e1;
  *expr2 = e2;
}

SubExpression::Expression* getValue1() const {
  return expr1;
}

SubExpression::Expression* getValue2() const {
  return expr2;
}
