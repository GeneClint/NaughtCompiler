#include <string>
#include "ArgList.h"
#include "Id.h"
#include "StrUtil.h"

#ifndef __FUNCTION_CALL_H
#define __FUNCTION_CALL_H

class FunctionCall : public Term {
 public:
  FunctionCall (const StrUtil &s, const ArgList* a = NULL) : id(Id(s.toString())), args(a) {};
  bool hasArgs() const;
  ArgList* getArgs() const;
  Id getId() const;
  std::string toString() const;
 private:
  const Id id;
  const ArgList *args;
};

#endif
