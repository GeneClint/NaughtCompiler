#include <string>
#include <unordered_map>
#include <iostream>
#include <fstream>

#include "Module.h"
#include "TempGen.h"
#include "Decl.h"
#include "UnaryTerm.h"
#include "ExprTerm.h"

#ifndef __NAUGHT_PARSER_H
#define __NAUGHT_PARSER_H
using std::string;

class NaughtParser {
 public:
  static void write(Module *ast, string o);
 private:
  NaughtParser(std::string o) : out(o) {};

  void writeHeader();
  void writeModule(Module m);
  std::string writeVarDecl(VarDecl *v);
  std::string writeExpression(const Expression *e);
  void writeFunctionDecl(FuncDecl *f);
  void writeFunctionDef(FuncDef f);
  void writeBlock(Block b);
  void writeStatement(Statement s);
  std::string writeTerm(Term *t);

  std::ofstream out;
  std::unordered_map<string, Decl*> symbols;
  TempGen temps;
};

#endif
