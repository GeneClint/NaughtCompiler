#include <string>

#ifndef __ASSIGN_EXPR_H
#define __ASSIGN_EXPR_H

#include "Term.h"
#include "Expression.h"

class AssignExpression : public Expression {
  public:
    AssignExpression(Term &t, Expression &e) : Expression(), term(&t), expr(&e) {};
    Term* getTerm() const;
    Expression* getExpr() const;
    virtual std::string toString() const;

  private:
    Term* term;
    Expression* expr;
};

#endif
