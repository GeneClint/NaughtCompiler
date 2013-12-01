#include <string>
#include "StrUtil.h"
#include "Term.h"

#ifndef __ID_H
#define __ID_H

class Id : public Term {
public:
  Id (const string &) : Term() {};
  Id (StrUtil * ignore) : Term() {name = "";};
  string getName() const;
private:
  string name;
};

#endif
