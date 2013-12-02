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
  std::cout << "starting block toString " << vlist << endl;
  vlist.toString();
  std::cout << "completed vlist toString" << endl;
  slist.toString();
  std::cout <<"completed slist tostring" <<endl;

  
  return "{" + vlist.toString() + ", " + slist.toString() + "}";
}
