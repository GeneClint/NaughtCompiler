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
    FuncDecl(const Id &i, bool s = false) : id(&i), isString(s) {};
    FuncDecl(const Id &i, const ParamList &pl, bool s = false) : id(&i), params(pl), isString(s) {};
    virtual ~FuncDecl() {};
    
    const Id getId() const;
    vector<Param> getParams() const;

    std::string toString() const;
    bool isFunction() const { return true;};
    bool isStringReturning() const {return isString;};

    friend std::ostream& operator<<(std::ostream &os, const FuncDecl &fd) {
      os << fd.toString();
      return os;
    }

  private:
    const Id* id;
    const ParamList params;
    const bool isString;
};
#endif
