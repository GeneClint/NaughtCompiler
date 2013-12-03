#include <string>

#ifndef __TEMP_GEN_H
#define __TEMP_GEN_H

class TempGen {
  public:
    TempGen() : i(0) {};
    std::string next() {
      i++;
      return "temp" + i;
    }

  private:
    uint32_t i;
};

#endif
