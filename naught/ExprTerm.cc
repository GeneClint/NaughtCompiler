// Gene Kim
// 1130267
// genelkim@uw.edu

#include <string>
#include "ExprTerm.h"

using namespace std;

string ExprTerm::toString() const {
  return internal->toString();
}
