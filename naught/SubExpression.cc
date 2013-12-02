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
