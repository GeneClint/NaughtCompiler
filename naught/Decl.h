#include "Id.h"

#ifndef __DECL_H
#define __DECL_H
class Decl {
 public:
  virtual ~Decl() {};
  virtual bool isFunction() const = 0;
};
#endif
