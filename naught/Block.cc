// Gene Kim
// 1130267
// genelkim@uw.edu

#include "Block.h"
#include <string>
#include <vector>

Block::Block(Block &&other) noexcept {
  vlist = other.vlist;
  slist = other.slist;
}

Block::Block(const Block &other) {
  vlist = other.vlist;
  slist = other.slist;
}

Block& Block::operator=(const Block &other) {
  if (&other == this) return *this;
  vlist = other.vlist;
  slist = other.slist;
  return *this;
}

Block& Block::operator=(Block &&other) noexcept {
  if (&other == this) return *this;
  vlist = other.vlist;
  slist = other.slist;
  return *this;
}

vector<VarDecl> Block::getVarDecls() const {
  return vlist.getVarDecls();
}

vector<Statement> Block::getStatements() const {
  return slist.getStatements();
}

std::string Block::toString() const {
  return "{" + vlist.toString() + ", " + slist.toString() + "}";
}
