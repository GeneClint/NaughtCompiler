// Clint Malcolm
// 1134490
// clintm@cs.washington.edu
// Gene Kim
// 1130267
// genelkim@uw.edu


#include <string>
#include "Id.h"
#include "ParamList.h"
#include "StrUtil.h"
#include "Block.h"

#ifndef __FUNC_DEF_H
#define __FUNC_DEF_H

class FuncDef {
 public:
  FuncDef(Id &i, const Block *b, bool s = false) :
    id(&i), bloc(b), params(nullptr), isString(s) {};
  FuncDef(Id &i, const Block *b, const ParamList *p, bool s = false) :
    id(&i), bloc(b), params(p), isString(s) {};

//  ~FuncDef() {delete id;}

  bool hasParams() const;
  Block* getBlock() const;
  ParamList* getParams() const;
  Id getId() const;
  std::string toString() const;
  bool isStringReturning() const {return isString;};
  void deleteBloc() { delete bloc; }


  friend ostream& operator<<(ostream &os, const FuncDef &obj) {
    os << obj.toString();
    return os;
  }

 private:
  Id *id;
  const Block *bloc;
  const ParamList *params;
  bool isString;
};

#endif
