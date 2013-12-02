#include <iostream>
#include <vector>
#include <string>

#include "Id.h"
#include "ParamList.h"

#ifndef __FUNC_DECL_H
#define __FUNC_DECL_H

class FuncDecl {
  public:
    FuncDecl(const Id &i) : id(i) {};
    FuncDecl(const Id &i, const ParamList &pl) : id(i), params(pl) {};
    virtual ~FuncDecl() {};
    vector<Param> getParams() const;

    std::string toString() const;

    friend std::ostream& operator<<(std::ostream &os, const FuncDecl &fd) {
      os << fd.toString();
      return os;
    }

  private:
    const Id id;
    const ParamList params;
};
#endif
