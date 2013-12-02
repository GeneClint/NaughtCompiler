#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include "Statement.h"
#include "StatementList.h"

using namespace std;

StatementList::StatementList(const Statement &s) {
  statements.push_back(s);
}

StatementList StatementList::operator+(const Statement &s) {
  statements.push_back(s);
  return *this;
}

vector<Statement> StatementList::getStatements() const {
  return statements;
}

string StatementList::toString() const {
  stringstream ss;
  for(size_t i = 0; i < statements.size(); ++i) {
    if(i != 0)
      ss << ",";
    ss << statements[i].toString();
  }
  return ss.str();
}
