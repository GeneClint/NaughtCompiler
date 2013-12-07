// Gene Kim
// 1130267
// genelkim@uw.edu

#include <string>
#include "Id.h"
#include "Param.h"

Id Param::getId() const {
  return *id;
}

std::string Param::getType() const {
  return type;
}

std::string Param::toString() const {
  return type + " " + id->toString();
}
