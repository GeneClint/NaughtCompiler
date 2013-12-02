#include <string>
#include "AssignExpression.h"

Term* AssignExpression::getTerm() const {
  return term;
}

Expression* AssignExpression::getExpr() const {
  return expr;
}

std::string AssignExpression::toString() const {
  return "(" + term->toString() + " = " + expr->toString() + ")";
}
