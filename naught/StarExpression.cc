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
