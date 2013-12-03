#include <string>
#include <unordered_map>
#include <iostream>
#include <fstream>

#include "Module.h"
#include "TempGen.h"

#ifndef __NAUGHT_PARSER_H
#define __NAUGHT_PARSER_H
using std::string;

class NaughtParser {
 public:
  static void write(Module ast, string o);
 private:
  NaughtParser(std::ofstream o) : out(o), exprCount(0), temps(new TempGen()) {};

  void writeModule(Module m);
  void writeVarDecl(VarDecl v);
  std::string writeExpression(Expression e);
  void writeFunctionDecl(FuncDecl f);
  void writeFunctionDef(FuncDef f);
  void writeBlock(Block b);

  std::ofstream out;
  size_t exprCount;
  std::unordered_map<string, VarDecl> symbols;
  TempGen temps;
};

#endif
