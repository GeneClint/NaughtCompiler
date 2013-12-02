#include <string>
#include "Expression.h"
#include "Statement.h"

bool Statement::isReturn() const {
  return isRet;
}

Expression Statement::getExpression() const {
  return exp;
}

std::string Statement::toString() const {
  return (isRet ? "return " : "") + exp.toString();
}
