#include <iostream>
#include <string>
#include "Term.h"

#ifndef _STRUTIL_H
#define _STRUTIL_H

using namespace std;

// A class that simplfies simply printing which
// grammar rules fire.
// This class is of no use in the naught compiler.

class StrUtil {
 public:
 StrUtil(const string &s) : str(s){};
 StrUtil(Term *t) : str(t->toString()){};
 StrUtil(Term &t) : str(t.toString()){};

  string toString() const {
    return str;
  }

  StrUtil operator+(const StrUtil &other) {
    return StrUtil(str + " " + other.str);
  }

  friend ostream& operator<<(ostream &os, const StrUtil &obj) {
    os << obj.str;
    return os;
  }

  friend StrUtil operator+(const Term &t, const StrUtil &obj) {
    return StrUtil(t.toString() + " " + obj.str);
  }

 private:
  string str;
};

#endif // _STRUTIL_H
