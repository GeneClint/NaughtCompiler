// Clint Malcolm
// 1134490
// clintm@cs.washington.edu
// Gene Kim
// 1130267
// genelkim@uw.edu

#include <string>

#ifndef __ASSIGN_EXPR_H
#define __ASSIGN_EXPR_H

#include "Term.h"
#include "Expression.h"

class AssignExpression : public Expression {
  public:
    AssignExpression(Term &t, Expression &e) : Expression(), term(&t), expr(&e) {};
    Term* getTerm() const;
    Expression* getValue1() const;
    virtual std::string toString() const;

    std::vector<std::string> getConnectors() const {return std::vector<std::string>({"="});};

  private:
    Term* term;
    Expression* expr;
};

#endif
