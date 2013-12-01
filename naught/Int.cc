#include <string>

#include "Int.h"

Int::Int(string v) {
  val = std::stoi( v );
}

Int::Int (int v) {
  val = v;
}

Int::int getValue() const {
  return val;
}
