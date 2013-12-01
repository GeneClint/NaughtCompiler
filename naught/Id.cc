#include <string>
#include "Id.h"

using namespace std;

string Id::getName() const {
  return name;
}

string Id::toString() const {
  return getName();
}
