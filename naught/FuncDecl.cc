// Clint Malcolm
// 1134490
// clintm@cs.washington.edu
// Gene Kim
// 1130267
// genelkim@uw.edu

#include <vector>

#include "FuncDecl.h"
#include "Param.h"

const Id FuncDecl::getId() const {
  return *id;
}

vector<Param> FuncDecl::getParams() const {
  return params.getParams();
}

std::string FuncDecl::toString() const {
  return id->toString() + "(" + params.toString() + ")";
}
