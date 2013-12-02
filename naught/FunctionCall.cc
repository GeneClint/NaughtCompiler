#include <string>
#include "FunctionCall.h"

using namespace std;

bool FunctionCall::hasArgs() const {
  return args == NULL;
}

ArgList* FunctionCall::getArgs() const {
  return const_cast<ArgList*>(args);
}

Id FunctionCall::getId() const {
  return id;
}

string FunctionCall::toString() const {
  return id.toString() + " " + (hasArgs() ? args->toString() : "");
}
