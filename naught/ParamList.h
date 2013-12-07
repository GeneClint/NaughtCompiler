// Gene Kim
// 1130267
// genelkim@uw.edu

#include <iostream>
#include <vector>
#include <string>
#include "Param.h"
#include "StrUtil.h"

#ifndef __PARAM_LIST_H
#define __PARAM_LIST_H

class ParamList {
 public:
  ParamList ();
  ParamList (const Param &p);

  ParamList(const ParamList &other);
  ParamList& operator=(const ParamList &other);
  ParamList (ParamList &&other) noexcept;
  ParamList& operator=(ParamList &&other) noexcept;

  ParamList* operator+ (const Param &p);
  virtual ~ParamList ();
  vector<Param> getParams() const; 

  explicit operator string() const { return toString(); }
  std::string toString() const;

  friend std::ostream& operator<<(std::ostream &os, const ParamList &p) {
    os << p.toString();
    return os;
  }

  friend StrUtil operator+(const ParamList &p, const StrUtil &obj) {
    return StrUtil(p.toString() + " " + obj.toString());
  }

  friend StrUtil operator+(const StrUtil &obj, const ParamList &p) {
    return p + obj;
  }

 private:
  vector<Param> *params; 
};

#endif
