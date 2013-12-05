#include <string>
#include <vector>
#include <utility>
#include <sstream>
#include "ArgList.h"
#include "Id.h"
#include "StrUtil.h"

#ifndef __FUNCTION_CALL_H
#define __FUNCTION_CALL_H

using std::string;
using std::vector;
using std::pair;
using std::make_pair;

class FunctionCall : public Term {
 public:
  FunctionCall (const StrUtil &s, const ArgList* a = NULL) : id(Id(s.toString())), args(a), tempArgs(NULL) {};
  bool hasArgs() const;
  ArgList* getArgs() const;
  Id getId() const;
  string toString() const;
  void setTempArgs(vector<pair<string, string>> *temps);
  vector<pair<string, string>> *getTempArgs();

 private:
  const Id id;
  const ArgList *args;
  vector<pair<string, string>> *tempArgs;
};

#endif
