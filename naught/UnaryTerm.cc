#include <string>
#include "UnaryTerm.h"

using namespace std;

string UnaryTerm::toString() const {
  string oper = op.compare("print") == 0 ? "print " : op;
  return oper + internal->toString();
}
