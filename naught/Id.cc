#include <string>
#include "Id.h"

Id::Id(const string &n) {
  name = n;
}

Id::string getName() const {
  return const_cast<string>(name);
}
