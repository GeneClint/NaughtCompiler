// Clint Malcolm
// 1134490
// clintm@cs.washington.edu
// Gene Kim
// 1130267
// genelkim@uw.edu

#include <string>
#include "AssignExpression.h"

Term* AssignExpression::getTerm() const {
  return term;
}

Expression* AssignExpression::getValue1() const {
  return expr;
}

std::string AssignExpression::toString() const {
  return term->toString() + " = " + expr->toString();
}
