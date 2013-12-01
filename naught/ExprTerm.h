#include "Expression.h"
#include "Term.h"

#ifndef __EXPR_TERM_H
#define __EXPR_TERM_H

class ExprTerm : public Expression {
 public:
  ExprTerm(Term& t) : internal(&t) {};
  ExprTerm(Term *t) : internal(t) {};
  Term* evaluate() const {return internal;};
 private:
  Term *internal;
};

#endif
