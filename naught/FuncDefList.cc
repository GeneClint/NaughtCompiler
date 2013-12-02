#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include "FuncDef.h"
#include "FuncDefList.h"

using namespace std;

FuncDefList::FuncDefList(const FuncDef *p) {
  funcDefs.push_back(p);
}

FuncDefList FuncDefList::operator+(const FuncDef *p) {
  funcDefs.push_back(p);
  return *this;
}

vector<const FuncDef*> FuncDefList::getFuncDefs() const {
  return funcDefs;
}

string FuncDefList::toString() const {
  stringstream ss;
  for(size_t i = 0; i < funcDefs.size(); ++i) {
    if(i != 0)
      ss << ",";
    ss << funcDefs[i]->toString();
  }
  return ss.str();
}
