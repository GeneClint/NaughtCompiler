#include <iostream>
#include <vector>
#include <string>
#include "FuncDef.h"
#include "StrUtil.h"

#ifndef __FUNCDEF_LIST_H
#define __FUNCDEF_LIST_H

class FuncDefList {
 public:
  FuncDefList ();
  FuncDefList (const FuncDef *f);
  FuncDefList operator+ (const FuncDef *p);
  virtual ~FuncDefList () {};
  vector<const FuncDef*> getFuncDefs() const;

  FuncDefList(const FuncDefList &other);
  FuncDefList& operator=(const FuncDefList &other);
  FuncDefList (FuncDefList &&other) noexcept;
  FuncDefList& operator=(FuncDefList &&other) noexcept;

  explicit operator string() const { return toString(); }
  std::string toString() const;

  friend std::ostream& operator<<(std::ostream &os, const FuncDefList &f) {
    os << f.toString();
    return os;
  }

  friend StrUtil operator+(const FuncDefList &f, const StrUtil &obj) {
    return StrUtil(f.toString() + " " + obj.toString());
  }

  friend StrUtil operator+(const StrUtil &obj, const FuncDefList &f) {
    return f + obj;
  }

 private:
  vector<const FuncDef*> *funcDefs; 
};

#endif
