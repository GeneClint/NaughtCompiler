// Clint Malcolm
// 1134490
// clintm@cs.washington.edu
// Gene Kim
// 1130267
// genelkim@uw.edu

#include <string>
#include <sstream>
#include <utility>

#ifndef __TEMP_GEN_H
#define __TEMP_GEN_H

using std::pair;
using std::make_pair;
using std::string;

class TempGen {
  public:
    TempGen() : i(0) {};
    pair<string, string> next(string type);

  private:
    uint32_t i;
};

#endif
