#ifndef __EXPR_H
#define __EXPR_H

class Term;

class Expression {
 public:
  virtual ~Expression() {}
  
  Term* evaluate() {return NULL;}
};
#endif