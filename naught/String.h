// Clint Malcolm
// 1134490
// clintm@cs.washington.edu
// Gene Kim
// 1130267
// genelkim@uw.edu

#include <string>
#include "Term.h"

#ifndef __NAUGHT_STR_H
#define __NAUGHT_STR_H

using std::string;

class String : public Term {
  public:
    String(string s) : str(s), length(str.length() - 1) {};
    string getString() const;
    int getLength() const;
    virtual string toString() const;

  private:
    string str;
    int length;
};

#endif
