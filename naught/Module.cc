#include <string>

#include "Module.h"

bool Module::hasFuncDecls() const {
  return funcDeclList != NULL;
}

bool Module::hasVarDecls() const {
  return varDeclList != NULL;
}

bool Module::hasFuncDefs() const {
  return funcDefList != NULL;
}

FuncDeclList* Module::getFuncDecls() const {
  return const_cast<FuncDeclList *>(funcDeclList);
}

VarDeclList* Module::getVarDecls() const {
  return const_cast<VarDeclList *>(varDeclList);
}

FuncDefList* Module::getFuncDefs() const {
  return const_cast<FuncDefList *>(funcDefList);
}

std::string Module::toString() const {
  return funcDeclList->toString() + "\n" 
          + varDeclList->toString() + "\n" 
          + funcDefList->toString();
}
