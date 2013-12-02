#include <string>
#include "Id.h"
#include "ParamList.h"
#include "StrUtil.h"
#include "Block.h"

#ifndef __FUNC_DEF_H
#define __FUNC_DEF_H

class FuncDef {
 public:
  FuncDef(Id i, const Block *b, const ParamList *p = NULL) : id(i), bloc(b), params(p) {};
  FuncDef(StrUtil &i, const Block *b, const ParamList *p = NULL) : 
    id(Id(i.toString())), bloc(b), params(p) {};
  bool hasParams() const;
  Block* getBlock() const;
  ParamList* getParams() const;
  Id getId() const;
  std::string toString() const;

  friend ostream& operator<<(ostream &os, const FuncDef &obj) {
    os << obj.toString();
    return os;
  }

 private:
  Id id;
  const Block *bloc;
  const ParamList *params;
};

#endif
