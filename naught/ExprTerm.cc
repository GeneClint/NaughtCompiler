// Clint Malcolm
// 1134490
// clintm@cs.washington.edu
// Gene Kim
// 1130267
// genelkim@uw.edu

#include <string>
#include "ExprTerm.h"

using namespace std;

string ExprTerm::toString() const {
  return internal->toString();
}
