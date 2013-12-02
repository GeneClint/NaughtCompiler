#include <string>
#include "UnaryTerm.h"

using namespace std;

string UnaryTerm::toString() const {
  return internal->toString();
}
