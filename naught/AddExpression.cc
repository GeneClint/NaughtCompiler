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
