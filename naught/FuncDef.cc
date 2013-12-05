#include "FuncDef.h"

using namespace std;

FuncDef::~FuncDef() {
  delete params;
}

bool FuncDef::hasParams() const {
  return params != NULL;
}

Block* FuncDef::getBlock() const {
  return const_cast<Block*>(bloc);
}

ParamList* FuncDef::getParams() const {
  return const_cast<ParamList*>(params);
}

Id FuncDef::getId() const {
  return id;
}

std::string FuncDef::toString() const {
  string pars = hasParams() ? params->toString() + " " : "";
  return id.toString() + " " + pars + bloc->toString();
}
