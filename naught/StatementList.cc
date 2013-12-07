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
#include "Statement.h"
#include "StatementList.h"

using namespace std;

StatementList::StatementList() {
  statements = new vector<Statement>;
}

StatementList::~StatementList() {
  delete statements;
}

StatementList::StatementList(StatementList &&other) noexcept {
  statements = other.statements;
  other.statements = NULL;
}

StatementList::StatementList(const StatementList &other) {
  statements = new vector<Statement>(*other.statements);
}

StatementList& StatementList::operator=(const StatementList &other) {
  if (&other == this) return *this;
  if (statements != NULL) delete statements;
  statements = new vector<Statement>(*other.statements);
  return *this;
}

StatementList::StatementList(const Statement &s) {
  statements = new vector<Statement>;
  statements->push_back(s);
}

StatementList& StatementList::operator=(StatementList &&other) noexcept {
  if (&other == this) return *this;
  if (statements != NULL) delete statements;
  statements = other.statements;
  other.statements = NULL;
  return *this;
}

StatementList* StatementList::operator+(const Statement &s) {
  statements->push_back(s);
  return this;
}

vector<Statement> StatementList::getStatements() const {
  return *statements;
}

string StatementList::toString() const {
  stringstream ss;
  for(size_t i = 0; i < statements->size(); ++i) {
    if(i != 0)
      ss << ",";
    ss << ((*statements)[i]).toString();
  }
  return ss.str();
}
