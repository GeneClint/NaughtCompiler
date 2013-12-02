#include <iostream>
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
  
  std::cout << "statement toString" << std::endl;

  std::cout << exp << std::endl;

  return (isRet ? "return " : "") + exp->toString();
}
