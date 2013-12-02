#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include "FuncDecl.h"
#include "FuncDeclList.h"

using namespace std;

FuncDeclList::FuncDeclList() {
  funcDecls = new vector<FuncDecl>;
}

FuncDeclList::FuncDeclList(FuncDeclList &&other) noexcept {
  funcDecls = other.funcDecls;
  other.funcDecls = NULL;
}

FuncDeclList::FuncDeclList(const FuncDeclList &other) {
  funcDecls = new vector<FuncDecl>(*other.funcDecls);
}

FuncDeclList& FuncDeclList::operator=(const FuncDeclList &other) {
  if (&other == this) return *this;
  if (funcDecls != NULL) delete funcDecls;
  funcDecls = new vector<FuncDecl>(*other.funcDecls);
  return *this;
}

FuncDeclList& FuncDeclList::operator=(FuncDeclList &&other) noexcept {
  if (&other == this) return *this;
  if (funcDecls != NULL) delete funcDecls;
  funcDecls = other.funcDecls;
  other.funcDecls = NULL;
  return *this;
}

FuncDeclList::FuncDeclList(const FuncDecl &fd) {
  funcDecls = new vector<FuncDecl>;
  funcDecls->push_back(fd);
}

FuncDeclList FuncDeclList::operator+(const FuncDecl &fd) {
  funcDecls->push_back(fd);
  return *this;
}

vector<FuncDecl> FuncDeclList::getFuncDecls() const {
  return *funcDecls;
}

std::string FuncDeclList::toString() const {
  stringstream ss;
  for(size_t i = 0; i < funcDecls->size(); ++i) {
    if(i != 0)
      ss << ",";
    ss << (*funcDecls)[i].toString();
  }
  ss << ";";
  return ss.str();
}
