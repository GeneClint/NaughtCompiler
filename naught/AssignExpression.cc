#include "AssignExpression.h"

AssignExpression::AssignExpression(Int i, Expression e) {
  *term = i;
  *expr = e;
}

AssignExpression::AssignExpression(Id i, Expression e) {
  *term = i;
  *expr = e;
}
AssignExpression::Term* getTerm() const {
  return term;
}

AssignExpression::Expression* getExpr() const {
  return expr;
}
