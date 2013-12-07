// Clint Malcolm
// 1134490
// clintm@cs.washington.edu
// Gene Kim
// 1130267
// genelkim@uw.edu

#include <string>
#include "Id.h"

using namespace std;

string Id::getName() const {
  return name;
}

string Id::toString() const {
  return getName();
}
