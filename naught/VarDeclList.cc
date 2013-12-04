#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include "VarDecl.h"
#include "VarDeclList.h"

using namespace std;

VarDeclList::VarDeclList() {
  varDecls = new vector<VarDecl>;
}

VarDeclList::VarDeclList(VarDeclList &&other) noexcept {
  varDecls = other.varDecls;
  other.varDecls = NULL;
}

VarDeclList::VarDeclList(const VarDeclList &other) {
  varDecls = new vector<VarDecl>(*other.varDecls);
}

VarDeclList& VarDeclList::operator=(const VarDeclList &other) {
  if (&other == this) return *this;
  if (varDecls != NULL) delete varDecls;
  varDecls = new vector<VarDecl>(*other.varDecls);
  return *this;
}

VarDeclList::VarDeclList(const VarDecl &s) {
  varDecls = new vector<VarDecl>;
  varDecls->push_back(s);
}

VarDeclList& VarDeclList::operator=(VarDeclList &&other) noexcept {
  if (&other == this) return *this;
  if (varDecls != NULL) delete varDecls;
  varDecls = other.varDecls;
  other.varDecls = NULL;
  return *this;
}

VarDeclList* VarDeclList::operator+(const VarDecl &p) {
  varDecls->push_back(p);
  return this;
}

vector<VarDecl> VarDeclList::getVarDecls() const {
  return *varDecls;
}

string VarDeclList::toString() const {
  stringstream ss;
  
  for(size_t i = 0; i < varDecls->size(); ++i) {
    if(i != 0)
      ss << ",";
    ss << (*varDecls)[i].toString();
  }
  ss << ";";
  return ss.str();
}
