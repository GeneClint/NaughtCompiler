// Gene Kim
// 1130267
// genelkim@uw.edu

#include <string>

#include "Int.h"

int Int::getValue() const {
  return val;
}

string Int::toString() const {
  return std::to_string(val);
}
