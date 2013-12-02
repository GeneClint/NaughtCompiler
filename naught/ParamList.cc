#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include "Param.h"
#include "ParamList.h"

using namespace std;

ParamList::ParamList() {
  params = new vector<Param>;
}

ParamList::ParamList(ParamList &&other) noexcept {
  params = other.params;
  other.params = NULL;
}

ParamList::ParamList(const ParamList &other) {
  params = new vector<Param>(*other.params);
}

ParamList& ParamList::operator=(const ParamList &other) {
  if(&other == this) return *this;
  if(params != NULL) delete params;
  params = new vector<Param>(*other.params);
  return *this;
}

ParamList::ParamList(const Param &p) {
  params = new vector<Param>;
  params->push_back(p);
}

ParamList& ParamList::operator=(ParamList &&other) noexcept {
  if(&other == this) return *this;
  if(params != NULL) delete params;
  params = other.params;
  other.params = NULL;
  return *this;
}

ParamList ParamList::operator+(const Param &p) {
  params->push_back(p);
  return *this;
}

vector<Param> ParamList::getParams() const {
  return *params;
}

string ParamList::toString() const {
  stringstream ss;
  for(size_t i = 0; i < params->size(); ++i) {
    if(i != 0)
      ss << ",";
    ss << (*params)[i].toString();
  }
  return ss.str();
}
