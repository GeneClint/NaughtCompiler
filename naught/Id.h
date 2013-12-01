#include <string>
#include "Term.h"

#ifndef __ID_H
#define __ID_H

class Id : public Term {
public:
  Id (const string &) : Term();
  string getName() const;
private:
  const string name;
};

#endif
