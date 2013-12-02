#include "ArgList.h"
#include "Id.h"

#ifndef __FUNCTION_CALL_H
#define __FUNCTION_CALL_H

class FunctionCall : public Term {
 public:
  FunctionCall (Id i, ArgList* a = NULL) : id(i), args(a) {};
  bool hasArgs() const;
  ArgList* 
 private:
  ArgList *args;
  Id id;
  
}

#endif
