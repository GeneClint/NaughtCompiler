#include <string>
#include "Term.h"

#ifndef __NAUGHT_STR_H
#define __NAUGHT_STR_H

using std::string;

class String : public Term {
  public:
    String(string s);
    string getString() const;
    int getLength() const;
    virtual string toString() const;

  private:
    string str;
    int length;
};

#endif
