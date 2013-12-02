#include <string>
#include "Id.h"
#include "VarDecl.h"

Id VarDecl::getId() const {
  return id;
}

std::string VarDecl::getType() const {
  return type;
}

bool VarDecl::isExtern() const {
  return ext;
}

Expression* VarDecl::getExpression() const {
  return const_cast<Expression*>(exp);
}

std::string VarDecl::toString() const {
  string external = ext ? "extern " : "";
  string expression = exp == NULL ? exp->toString() : "";
  return external + type + " " + id.toString() + expression;
}
