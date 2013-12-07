// Gene Kim
// 1130267
// genelkim@uw.edu

#include <string>
#include "UnaryTerm.h"

using namespace std;

string UnaryTerm::toString() const {
  string oper = op.compare("print") == 0 ? "" : op;
  return oper + internal->toString();
}
