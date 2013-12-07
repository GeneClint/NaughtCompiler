// Clint Malcolm
// 1134490
// clintm@cs.washington.edu
// Gene Kim
// 1130267
// genelkim@uw.edu

#include <string>
#include "Term.h"
#include "StrUtil.h"

#ifndef __INT_H
#define __INT_H

class Int: public Term {
 public:
  virtual ~Int() {};
  Int (int &v) : Term (), val(v) {};
  int getValue() const;
  virtual std::string toString() const;
 private:
  int val;
};

#endif
