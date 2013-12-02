#include <string>
#include <iostream>
#include "UnaryTerm.h"

using namespace std;

string UnaryTerm::toString() const {
  std::cout << "in unary tostring" << std::endl;
  return internal->toString();
}
