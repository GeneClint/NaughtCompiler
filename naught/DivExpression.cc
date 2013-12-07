// Gene Kim
// 1130267
// genelkim@uw.edu

#include <string>
#include "DivExpression.h"

Expression* DivExpression::getValue1() const {
  return expr1;
}

Expression* DivExpression::getValue2() const {
  return expr2;
}

std::string DivExpression::toString() const {
  return "(" + expr1->toString() + " / " + expr2->toString() + ")";
}
