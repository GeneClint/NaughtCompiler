#include <iostream>
#include <vector>
#include <string>
#include "VarDecl.h"
#include "StrUtil.h"

#ifndef __VARDECL_LIST_H
#define __VARDECL_LIST_H

class VarDeclList {
 public:
  VarDeclList ();
  VarDeclList (const VarDecl &v);

  VarDeclList(const VarDeclList &other);
  VarDeclList& operator=(const VarDeclList &other);
  VarDeclList (VarDeclList &&other) noexcept;
  VarDeclList& operator=(VarDeclList &&other) noexcept;

  VarDeclList operator+ (const VarDecl &v);
  virtual ~VarDeclList () {};
  vector<VarDecl> getVarDecls() const; 

  explicit operator string() const { return toString(); }
  std::string toString() const;

  friend std::ostream& operator<<(std::ostream &os, const VarDeclList &v) {
    os << v.toString();
    return os;
  }

  friend StrUtil operator+(const VarDeclList &v, const StrUtil &obj) {
    return StrUtil(v.toString() + " " + obj.toString());
  }

  friend StrUtil operator+(const StrUtil &obj, const VarDeclList &v) {
    return v + obj;
  }

 private:
  vector<VarDecl> *varDecls; 
};

#endif
