// Gene Kim
// 1130267
// genelkim@uw.edu

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
  FunctionCall (Id &i, const ArgList* a = nullptr) : id(&i), args(a), tempArgs(nullptr) {};
  ~FunctionCall() { 
    /*delete id; 
    if(tempArgs != nullptr)
      delete tempArgs*/;
  }
  
  bool hasArgs() const;
  ArgList* getArgs() const;
  Id getId() const;
  string toString() const;
  void setTempArgs(vector<pair<string, string>> *temps);
  vector<pair<string, string>> *getTempArgs();

 private:
  Id *id;
  const ArgList *args;
  vector<pair<string, string>> *tempArgs;
};

#endif
