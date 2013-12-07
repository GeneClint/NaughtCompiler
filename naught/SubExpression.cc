// Clint Malcolm
// 1134490
// clintm@cs.washington.edu
// Gene Kim
// 1130267
// genelkim@uw.edu

#include <string>
#include "SubExpression.h"

Expression* SubExpression::getValue1() const {
  return expr1;
}

Expression* SubExpression::getValue2() const {
  return expr2;
}

std::string SubExpression::toString() const {
  return "(" + expr1->toString() + " - " + expr2->toString() + ")";
}
