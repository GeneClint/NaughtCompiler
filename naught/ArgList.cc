// Gene Kim
// 1130267
// genelkim@uw.edu

#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include "Expression.h"
#include "ArgList.h"

using namespace std;

ArgList::ArgList(const Expression *e) {
  args.push_back(e);
}

ArgList* ArgList::operator+(const Expression *e) {
  args.push_back(e);
  return this;
}

vector<const Expression*> ArgList::getArgs() const {
  return args;
}

string ArgList::toString() const {
  stringstream ss;
  for(size_t i = 0; i < args.size(); ++i) {
    if(i != 0)
      ss << ",";
    ss << args[i]->toString();
  }
  return ss.str();
}
