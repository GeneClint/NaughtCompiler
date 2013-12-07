// Gene Kim
// 1130267
// genelkim@uw.edu

#include <string>
#include "CondExpression.h"

Expression* CondExpression::getValue1() const {
  return expr1;
}

Expression* CondExpression::getValue2() const {
  return expr2;
}

Expression* CondExpression::getValue3() const {
  return expr3;
}

std::string CondExpression::toString() const {
  return "(" + expr1->toString() + " ? " + expr2->toString() + " : " + expr3->toString() + ")";
}
