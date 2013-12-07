// Clint Malcolm
// 1134490
// clintm@cs.washington.edu
// Gene Kim
// 1130267
// genelkim@uw.edu

#include <string>
#include "StarExpression.h"

Expression* StarExpression::getValue1() const {
  return expr1;
}

Expression* StarExpression::getValue2() const {
  return expr2;
}

std::string StarExpression::toString() const {
  return "(" + expr1->toString() + " * " + expr2->toString() + ")";
}
