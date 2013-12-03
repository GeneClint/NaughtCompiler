#include <string>
#include <sstream>

#ifndef __TEMP_GEN_H
#define __TEMP_GEN_H

class TempGen {
  public:
    TempGen() : i(0) {};
    std::string next(std::string type) {
      std::stringstream sstm; 
      sstm << type << " temp" << i;
      i++;
      return sstm.str();
    }

  private:
    uint32_t i;
};

#endif
