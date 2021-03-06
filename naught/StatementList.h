// Clint Malcolm
// 1134490
// clintm@cs.washington.edu
// Gene Kim
// 1130267
// genelkim@uw.edu

#include <iostream>
#include <vector>
#include <string>
#include "Statement.h"
#include "StrUtil.h"

#ifndef __STATEMENT_LIST_H
#define __STATEMENT_LIST_H

class StatementList {
 public:
  StatementList ();
  StatementList (const Statement &s);
  virtual ~StatementList ();

  StatementList(const StatementList &other);
  StatementList& operator=(const StatementList &other);
  StatementList (StatementList &&other) noexcept;
  StatementList& operator=(StatementList &&other) noexcept;

  StatementList* operator+ (const Statement &s);
  vector<Statement> getStatements() const; 

  explicit operator string() const { return toString(); }
  std::string toString() const;

  friend std::ostream& operator<<(std::ostream &os, const StatementList &s) {
    os << s.toString();
    return os;
  }

  friend StrUtil operator+(const StatementList &s, const StrUtil &obj) {
    return StrUtil(s.toString() + " " + obj.toString());
  }

  friend StrUtil operator+(const StrUtil &obj, const StatementList &s) {
    return s + obj;
  }

 private:
  vector<Statement> *statements; 
};

#endif
