#include <string>

#include "Id.h"
#include "StrUtil.h"

#ifndef __PARAM_H
#define __PARAM_H

class Param {
 public:
  Param (const std::string &_type, Id &_id) : type(_type), id(&_id) {};
  Param (const StrUtil &_type, Id &_id) : type(_type.toString()), id(&_id) {};
  //~Param() { delete id; }
  
  Id getId() const;
  std::string getType() const;
  std::string toString() const;

  friend std::ostream& operator<<(std::ostream &os, const Param &p) {
    os << p.toString();
    return os;
  }

 private:
  const std::string type;
  Id *id;
};

#endif
