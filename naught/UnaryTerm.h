// Gene Kim
// 1130267
// genelkim@uw.edu

#include <string>
#include "StrUtil.h"
#include "Expression.h"
#include "Term.h"

#ifndef __UNARY_TERM_H
#define __UNARY_TERM_H

class UnaryTerm : public Term {
 public:
  UnaryTerm (std::string _op, Term *t) : op(_op), internal(t) {};
  std::string getOperator() {return op;}
  Term* evaluate() {return internal;}
  std::string toString() const;
 private:
  std::string op;
  Term *internal;
};

#endif
