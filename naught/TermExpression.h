#ifndef __TERM_EXPR_H
#define __TERM_EXPR_H

#include "Term.h"
#include "Expression.h"

class TermExpression : public Expression {
  public:
    TermExpression(Int i) : Expression(), val(&i) {};
    TermExpression(Id i) : Expression(), val(&i) {};
    Term* getValue() const;

  private:
    Term* val;
};

#endif
