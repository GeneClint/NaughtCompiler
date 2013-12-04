#include <string>

#include "Module.h"

Module::Module(const Module &other) {
  if (other.funcDeclList)
    funcDeclList = new FuncDeclList(*other.funcDeclList);
  if (other.varDeclList)
    varDeclList = new VarDeclList(*other.varDeclList);
  if (other.funcDefList)
    funcDefList = new FuncDefList(*other.funcDefList);
}

Module& Module::operator=(const Module &other) {
  if (&other == this) return *this;
  if (other.funcDeclList)
    funcDeclList = new FuncDeclList(*other.funcDeclList);
  if (other.varDeclList)
    varDeclList = new VarDeclList(*other.varDeclList);
  if (other.funcDefList)
    funcDefList = new FuncDefList(*other.funcDefList);
  return *this;
}

Module::Module (Module &&other) noexcept {
  funcDeclList = other.funcDeclList;
  varDeclList = other.varDeclList;
  funcDefList = other.funcDefList;
  other.funcDeclList = NULL;
  other.varDeclList = NULL;
  other.funcDefList = NULL;
}

Module& Module::operator=(Module &&other) noexcept {
if (&other == this) return *this;
  if (funcDeclList != NULL) delete funcDeclList;
  if (varDeclList != NULL) delete varDeclList;
  if (funcDefList != NULL) delete funcDefList;
  funcDeclList = other.funcDeclList;
  varDeclList = other.varDeclList;
  funcDefList = other.funcDefList;
  other.funcDeclList = NULL;
  other.varDeclList = NULL;
  other.funcDefList = NULL;
  return *this;
}

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
  string funcdecl = (funcDeclList != NULL) ? (funcDeclList->toString() + "\n") : "";
  string vardecl = (varDeclList != NULL) ? (varDeclList->toString() + "\n") : "";
  string funcdef = (funcDefList != NULL) ? (funcDefList->toString() + "\n") : "";
  return funcdecl + vardecl + funcdef;
}
