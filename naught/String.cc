#include <string>

#include "String.h"

using std::string;

string String::getString() const {
  return str;
}

int String::getLength() const {
  return length;
}

string String::toString() const {
  return getString();
}
