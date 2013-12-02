#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include "VarDecl.h"
#include "VarDeclList.h"

using namespace std;

VarDeclList::VarDeclList(const VarDecl &p) {
  varDecls.push_back(p);
}

VarDeclList VarDeclList::operator+(const VarDecl &p) {
  varDecls.push_back(p);
  return *this;
}

vector<VarDecl> VarDeclList::getVarDecls() const {
  return varDecls;
}

string VarDeclList::toString() const {
  stringstream ss;
  
  for(size_t i = 0; i < varDecls.size(); ++i) {
    if(i != 0)
      ss << ",";
    ss << varDecls[i].toString();
  }
  ss << ";";
  return ss.str();
}
