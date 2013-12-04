#include <string>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <utility>

#include "Module.h"
#include "TempGen.h"
#include "Decl.h"
#include "UnaryTerm.h"
#include "ExprTerm.h"
#include "String.h"
#include "Int.h"
#include "Id.h"

#ifndef __NAUGHT_PARSER_H
#define __NAUGHT_PARSER_H
using std::string;
using std::pair;

typedef pair<string, string> tempName;

class NaughtParser {
 public:
  static void write(Module *ast, string o);
  virtual ~NaughtParser () {out.close();}
 private:
  NaughtParser(std::string o) : out(o) {};

  void writeHeader();
  void writeModule(Module *m);
  tempName writeVarDecl(VarDecl *v);
  tempName writeExpression(const Expression *e);
  void writeFunctionDecl(FuncDecl *f);
  void writeFunctionDef(FuncDef f);
  void writeBlock(Block b);
  void writeStatement(Statement s);
  tempName writeTerm(Term *& t);

  std::ofstream out;
  std::unordered_map<string, Decl*> symbols;
  TempGen temps;
};

#endif
