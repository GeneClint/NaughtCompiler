// Clint Malcolm
// 1134490
// clintm@cs.washington.edu
// Gene Kim
// 1130267
// genelkim@uw.edu

#include <string>
#include "Expression.h"
#include "Statement.h"

bool Statement::isReturn() const {
  return isRet;
}

const Expression* Statement::getExpression() const {
  return exp;
}

std::string Statement::toString() const {
  return (isRet ? "return " : "") + exp->toString();
}
