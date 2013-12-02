#include <string>

#include "Id.h"
#include "StrUtil.h"

#ifndef __PARAM_H
#define __PARAM_H

class Param {
 public:
  Param (const std::string &_type, const Id &_id) : type(_type), id(_id) {};
  Param (const StrUtil &_type, const Id &_id) : type(_type.toString()), id(_id) {};
  Param (const StrUtil &_type, const StrUtil &_id) : 
    type(_type.toString()), id(Id(_id.toString())) {};
  Id getId() const;
  std::string getType() const;
  std::string toString() const;

  friend std::ostream& operator<<(std::ostream &os, const Param &p) {
    os << p.toString();
    return os;
  }

 private:
  const std::string type;
  const Id id;
};

#endif