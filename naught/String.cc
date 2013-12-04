#include <string>

#include "String.h"

using std::string;

String::String(string s) {
  str = s;
  length = s.length() - 2;
}

string String::getString() const {
  return str;
}

int String::getLength() const {
  return length;
}

string String::toString() const {
  return getString();
}
