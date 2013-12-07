// Gene Kim
// 1130267
// genelkim@uw.edu

#include <string>
#include <vector>
#include <iostream>

#include "Statement.h"
#include "VarDecl.h"
#include "VarDeclList.h"
#include "StatementList.h"

#ifndef __BLOCK_VAL_H
#define __BLOCK_VAL_H

class Block {
 public:
  Block() {};
  Block(const VarDeclList &vl) : vlist(vl) {};
  Block(const StatementList &sl) : slist(sl) {};
  Block(const VarDeclList &vl, const StatementList &sl) :
          vlist(vl), slist(sl) {};
  virtual ~Block() {};

  Block(const Block &other);
  Block& operator=(const Block &other);
  Block (Block &&other) noexcept;
  Block& operator=(Block &&other) noexcept;

  vector<VarDecl> getVarDecls() const;
  vector<Statement> getStatements() const;
  std::string toString() const;

  friend std::ostream& operator<<(std::ostream &os, const Block &b) {
    os << b.toString();
    return os;
  }

 private:
  VarDeclList vlist;
  StatementList slist;
};
#endif
