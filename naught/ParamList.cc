#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include "Param.h"
#include "ParamList.h"

using namespace std;

ParamList::ParamList(const Param &p) {
  params.push_back(p);
}

ParamList ParamList::operator+(const Param &p) {
  params.push_back(p);
  return *this;
}

vector<Param> ParamList::getParams() const {
  return params;
}

string ParamList::toString() const {
  stringstream ss;
  for(size_t i = 0; i < params.size(); ++i) {
    if(i != 0)
      ss << ",";
    ss << params[i].toString();
  }
  return ss.str();
}
