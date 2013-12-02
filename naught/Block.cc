#include "Block.h"
#include <string>
#include <vector>

vector<VarDecl> Block::getVarDecls() const {
  return vlist.getVarDecls();
}

vector<Statement> Block::getStatements() const {
  return slist.getStatements();
}

std::string Block::toString() const {
  return "{" + vlist.toString() + ", " + slist.toString() + "}";
}
