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
