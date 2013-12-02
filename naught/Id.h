#include <string>
#include "StrUtil.h"
#include "Term.h"

#ifndef __ID_H
#define __ID_H

class Id : public Term {
public:
  Id (const std::string &n) : Term(), name(n) {};
  //Id (StrUtil * ignore) : Term(), name("") {};
  std::string getName() const;
  std::string toString() const;
private:
  const std::string name;
};

#endif
