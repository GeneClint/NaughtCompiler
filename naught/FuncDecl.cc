#include <vector>

#include "FuncDecl.h"
#include "Param.h"

const Id FuncDecl::getId() const {
  return id;
}

vector<Param> FuncDecl::getParams() const {
  return params.getParams();
}

std::string FuncDecl::toString() const {
  return id.toString() + "(" + params.toString() + ")";
}
