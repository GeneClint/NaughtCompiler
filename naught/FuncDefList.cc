// Clint Malcolm
// 1134490
// clintm@cs.washington.edu
// Gene Kim
// 1130267
// genelkim@uw.edu

#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include "FuncDef.h"
#include "FuncDefList.h"

using namespace std;

FuncDefList::FuncDefList() {
  funcDefs = new vector<FuncDef>;
}

FuncDefList::~FuncDefList() {
  for(FuncDef fd : *funcDefs) {
    fd.deleteBloc();
  }
  
  delete funcDefs;
}

FuncDefList::FuncDefList(FuncDefList &&other) noexcept {
  funcDefs = other.funcDefs;
  other.funcDefs = NULL;
}

FuncDefList::FuncDefList(const FuncDefList &other) {
  funcDefs = new vector<FuncDef>(*other.funcDefs);
}

FuncDefList& FuncDefList::operator=(const FuncDefList &other) {
  if (&other == this) return *this;
  if (funcDefs != NULL) delete funcDefs; 
  funcDefs = new vector<FuncDef>(*other.funcDefs);
  return *this;
}

FuncDefList& FuncDefList::operator=(FuncDefList &&other) noexcept {
  if (&other == this) return *this;
  if (funcDefs != NULL) delete funcDefs;
  funcDefs = other.funcDefs;
  other.funcDefs = NULL;
  return *this;
}

FuncDefList::FuncDefList(const FuncDef &p) {
  funcDefs = new vector<FuncDef>;
  funcDefs->push_back(p);
}

FuncDefList* FuncDefList::operator+(const FuncDef &p) {
  funcDefs->push_back(p);
  return this;
}

vector<FuncDef> FuncDefList::getFuncDefs() const {
  return *funcDefs;
}

string FuncDefList::toString() const {
  stringstream ss;
  for(size_t i = 0; i < funcDefs->size(); ++i) {
    if(i != 0)
      ss << ",";
    ss << (*funcDefs)[i].toString();
  }
  return ss.str();
}
