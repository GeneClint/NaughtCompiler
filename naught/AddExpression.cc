// Clint Malcolm
// 1134490
// clintm@cs.washington.edu
// Gene Kim
// 1130267
// genelkim@uw.edu

#include <string>
#include "AddExpression.h"

Expression* AddExpression::getValue1() const {
  return expr1;
}

Expression* AddExpression::getValue2() const {
  return expr2;
}

std::string AddExpression::toString() const {
  return "(" + expr1->toString() + " + " + expr2->toString() + ")";
}  
