#include <iostream>
#include <vector>
#include <string>

#include "Id.h"
#include "ParamList.h"
#include "Decl.h"

#ifndef __FUNC_DECL_H
#define __FUNC_DECL_H

class FuncDecl : public Decl {
  public:
    FuncDecl(const Id &i) : id(i) {};
    FuncDecl(const Id &i, const ParamList &pl) : id(i), params(pl) {};
    virtual ~FuncDecl() {};
    
    const Id getId() const;
    vector<Param> getParams() const;

    std::string toString() const;
    bool isFunction() const { return true;};

    friend std::ostream& operator<<(std::ostream &os, const FuncDecl &fd) {
      os << fd.toString();
      return os;
    }

  private:
    const Id id;
    const ParamList params;
};
#endif
