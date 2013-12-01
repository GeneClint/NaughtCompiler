#ifndef __EXPR_H
#define __EXPR_H

class Term;

class Expression {
 public:
  virtual ~Expression() {}
  
  //virtual Term* evaluate() =0;
};
#endif
