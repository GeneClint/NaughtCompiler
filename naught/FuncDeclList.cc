#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include "FuncDecl.h"
#include "FuncDeclList.h"

using namespace std;

FuncDeclList::FuncDeclList(const FuncDecl &fd) {
  funcDecls.push_back(fd);
}

FuncDeclList FuncDeclList::operator+(const FuncDecl &fd) {
  funcDecls.push_back(fd);
  return *this;
}

vector<FuncDecl> FuncDeclList::getFuncDecls() const {
  return funcDecls;
}

std::string FuncDeclList::toString() const {
  stringstream ss;
  for(size_t i = 0; i < funcDecls.size(); ++i) {
    if(i != 0)
      ss << ",";
    ss << funcDecls[i].toString();
  }
  ss << ";";
  return ss.str();
}
