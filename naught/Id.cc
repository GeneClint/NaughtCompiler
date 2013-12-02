#include <string>
#include <iostream>
#include "Id.h"

using namespace std;

string Id::getName() const {
  return name;
}

string Id::toString() const {
  std::cout << "in id tostring" << std::endl;
  return getName();
}
