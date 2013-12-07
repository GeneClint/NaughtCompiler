// Gene Kim
// 1130267
// genelkim@uw.edu

#include "Expression.h"
#include "Term.h"

#ifndef __EXPR_TERM_H
#define __EXPR_TERM_H

class ExprTerm : public Term {
 public:
  ExprTerm(Expression *e) : internal(e) {};
  Expression* evaluate() const {return internal;};
  std::string toString() const;
 private:
  Expression *internal;
};

#endif
