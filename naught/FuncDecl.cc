#include <vector>

#include "FuncDecl.h"
#include "Param.h"

vector<Param> FuncDecl::getParams() const {
  return params.getParams();
}

std::string FuncDecl::toString() const {
  return id.toString() + "(" + params.toString() + ")";
}
