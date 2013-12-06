#include <string>
#include "FunctionCall.h"

using namespace std;

bool FunctionCall::hasArgs() const {
  return args;
}

ArgList* FunctionCall::getArgs() const {
  return const_cast<ArgList*>(args);
}

Id FunctionCall::getId() const {
  return *id;
}

string FunctionCall::toString() const {
  stringstream result;
  result << id->toString();
  if(tempArgs != nullptr) {
    result << " (";
    for(uint32_t i = 0; i < tempArgs->size(); ++i) {
      if(i != 0) {
        result << ", ";
      }
      result << (*tempArgs)[i].second;
    }
    result << ")";
  } else {
    result << " (" + (hasArgs() ? args->toString() : "") + ")";
  }
  return result.str();
}

void FunctionCall::setTempArgs(vector<pair<string, string>> *temps) {
  tempArgs = temps;
}

vector<pair<string, string>> * FunctionCall::getTempArgs() {
  return tempArgs;
}
