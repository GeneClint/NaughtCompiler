#include "Block.h"
#include <string>
#include <vector>

vector<VarDecl> Block::getVarDecls() const {
  if(vlist == NULL) {
    return std::vector<VarDecl>
  } else {
    return vlist.getVarDecls();
  }
}

vector<Statement> Block::getStatements() const {
  if(slist == NULL) {
    return std::vector<Statement>
  } else {
    return slist.getStatements();
  }
}

std::string Block::toString() const {
  return "{" + vlist.toString() + ", " + slist.toString() + "}";
}
