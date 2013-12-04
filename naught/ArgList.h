#include <iostream>
#include <vector>
#include <string>
#include "Expression.h"
#include "StrUtil.h"

#ifndef __ARG_LIST_H
#define __ARG_LIST_H

class ArgList {
 public:
  ArgList (const Expression* e);
  ArgList* operator+ (const Expression* e);
  virtual ~ArgList () {};
  vector<const Expression*> getArgs() const; 

  explicit operator string() const { return toString(); }
  std::string toString() const;

  friend std::ostream& operator<<(std::ostream &os, const ArgList &a) {
    os << a.toString();
    return os;
  }

  friend StrUtil operator+(const ArgList &a, const StrUtil &obj) {
    return StrUtil(a.toString() + " " + obj.toString());
  }

  friend StrUtil operator+(const StrUtil &obj, const ArgList &a) {
    return a + obj;
  }

 private:
  vector<const Expression*> args; 
};

#endif
