// Clint Malcolm
// 1134490
// clintm@cs.washington.edu
// Gene Kim
// 1130267
// genelkim@uw.edu

#include <iostream>
#include <vector>
#include <string>
#include "FuncDecl.h"

#ifndef __FUNC_DECL_LIST_H
#define __FUNC_DECL_LIST_H

class FuncDeclList {
 public:
  FuncDeclList ();
  FuncDeclList (const FuncDecl &fd);
  FuncDeclList* operator+ (const FuncDecl &fd);
  virtual ~FuncDeclList () {};
  vector<FuncDecl> getFuncDecls() const; 

  FuncDeclList(const FuncDeclList &other);
  FuncDeclList& operator=(const FuncDeclList &other);
  FuncDeclList (FuncDeclList &&other) noexcept;
  FuncDeclList& operator=(FuncDeclList &&other) noexcept;

  explicit operator string() const { return toString(); }
  std::string toString() const;

  friend std::ostream& operator<<(std::ostream &os, const FuncDeclList &fdl) {
    os << fdl.toString();
    return os;
  }

  friend StrUtil operator+(const FuncDeclList &fdl, const StrUtil &obj) {
    return StrUtil(fdl.toString() + " " + obj.toString());
  }

  friend StrUtil operator+(const StrUtil &obj, const FuncDeclList &fdl) {
    return fdl + obj;
  }

 private:
  vector<FuncDecl> *funcDecls; 
};

#endif
