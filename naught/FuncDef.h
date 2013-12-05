#include <string>
#include "Id.h"
#include "ParamList.h"
#include "StrUtil.h"
#include "Block.h"

#ifndef __FUNC_DEF_H
#define __FUNC_DEF_H

class FuncDef {
 public:
  FuncDef(Id i, const Block *b, bool s = false) :
    id(i.getName()), bloc(b), params(NULL), isString(s) {};
  FuncDef(Id i, const Block *b, const ParamList *p, bool s = false) :
    id(i.getName()), bloc(b), params(p), isString(s) {};
  bool hasParams() const;
  Block* getBlock() const;
  ParamList* getParams() const;
  Id getId() const;
  std::string toString() const;
  bool isStringReturning() const {return isString;};

  friend ostream& operator<<(ostream &os, const FuncDef &obj) {
    os << obj.toString();
    return os;
  }

 private:
  Id id;
  const Block *bloc;
  const ParamList *params;
  bool isString;
};

#endif
