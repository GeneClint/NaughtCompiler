#include <string>

#include "Id.h"
#include "StrUtil.h"

#ifndef __PARAM_H
#define __PARAM_H

class Param {
 public:
  Param (const std::string &_type, const Id &_id) : type(_type), id(_id) {};
  Param (const StrUtil &_type, const Id &_id) : type(_type.toString()), id(_id) {};
  Id getId() const;
  std::string getType() const;
  std::string toString() const;
  
  friend std::ostream& operator<<(std::ostream &os, const Param &p) {
    os << p.toString();
    return os;
  }

  friend StrUtil operator+(const Param &p, const StrUtil &obj) {
    return StrUtil(p.toString() + " " + obj.toString());
  }

  friend StrUtil operator+(const StrUtil &obj, const Param &p) {
    return p + obj;
  }

 private:
  const std::string type;
  const Id id;
};

#endif
