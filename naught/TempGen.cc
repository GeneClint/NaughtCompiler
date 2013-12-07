// Clint Malcolm
// 1134490
// clintm@cs.washington.edu
// Gene Kim
// 1130267
// genelkim@uw.edu

#include <string>
#include <sstream>
#include <utility>

#include "TempGen.h"

using std::pair;
using std::make_pair;
using std::string;

pair<string, string> TempGen::next(string type) {
  std::stringstream sstm; 
  sstm << "temp" << i;
  i++;
  string tempname = sstm.str();
  return make_pair(type, tempname);
}
