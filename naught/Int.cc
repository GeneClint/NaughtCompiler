#include <string>

#include "Int.h"
using namespace std;


int Int::getValue() const {
  return val;
}

string Int::toString() const {
  return std::to_string(val);
}
