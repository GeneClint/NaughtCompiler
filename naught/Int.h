#include <string>
#include "Term.h"

#ifndef __INT_H
#define __INT_H

class Int: public Term {
 public:
  Int (int v) : Term ();
  Int (string v) : Term ();
  int getValue() const;
 private:
  int val;
};

#endif