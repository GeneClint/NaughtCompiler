#include <string>
#include <vector>

#include "VarDeclList.h"
#include "StatementList.h"

#ifndef __BLOCK_H
#define __BLOCK_H

class Block {
 public:
  Block(const VarDeclList &vl = NULL, 
        const StatementList &sl = NULL) :
          vlist(vl), slist(sl) {};
  virtual ~Block() {};

  vector<VarDecl> getVarDecls() const;
  vector<Statement> getStatements() const;
  std::string toString() const;

  friend std::ostream& operator<<(std::ostream &os, const Block &b) {
    os << b.toString();
    return os;
  }

 private:
  const VarDeclList vlist;
  const StatementList slist;
};
#endif
