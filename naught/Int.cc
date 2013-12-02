#include <string>
#include <iostream>

#include "Int.h"

int Int::getValue() const {
  return val;
}

string Int::toString() const {
  std::cout << "in int tostring" << std::endl;
  return std::to_string(val);
}
