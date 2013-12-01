#include "StarExpression.h"

StarExpression::StarExpression(Expression e1, Expression e2) {
  *expr1 = e1;
  *expr2 = e2;
}

StarExpression::Expression* getValue1() const {
  return expr1;
}

StarExpression::Expression* getValue2() const {
  return expr2;
}
