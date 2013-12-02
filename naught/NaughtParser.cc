#include "NaughtParser.h"
using namespace std;

static void NaughtParser::write(Module ast, string o) {
  ofstream output;
  output.open ("o");
  NaughtParser parser(o);
  parser.writeModule(ast);
}

void NaughtParser::writeModule(Module m) {
  if (m.hasFunctionDecls()) {
    auto decls = *(m.getFunctionDecls());
    for(auto decl : decls) {
      writeFunctionDecl(decl);
      out << endl;
    }
  }
  if (m.hasVarDecls()) {
    auto decls = *(m.getVarDecls());
    for(auto decl : decls) {
      writeVarDecl(decl);
      out << endl;
    }
  }
  if (m.hasFuncDefs()) {
    auto defs = *(m.getFunDefs());
    for(auto def : defs) {
      writeFunctionDef(def);
      out << endl;
    }
  }
}
