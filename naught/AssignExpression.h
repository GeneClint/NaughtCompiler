#ifndef __ASSIGN_EXPR_H
#define __ASSIGN_EXPR_H

#include "Term.h"
#include "Expression.h"

class AssignExpression : public Expression {
  public:
    AssignExpression(Int t, Expression e) : Expression() {};
    AssignExpression(Id t, Expression e) : Expression() {};
    Term* getTerm() const;
    Expression* getExpr() const;

  private:
    Term* term;
    Expression* expr;
};

#endif
