#include <string>
#include <unordered_map>
#include <iostream>
#include <fstream>

#include "Module.h"

#ifndef __NAUGHT_PARSER_H
#define __NAUGHT_PARSER_H

class NaughtParser {
 public:
  static void write(Module ast, string o);
 private:
  NaughtParser(std::ofstream o) : out(o), exprCount(0) {};

  void writeModule(Module m);
  void writeVarDecl(VarDecl v);
  void writeExpression(Expression e);
  void writeFunctionDecl(FuncDecl f);
  void writeFunctionDef(FuncDef f);
  void writeBlock(Block b);

  std::ofstream out;
  size_t exprCount;
  std::unordered_map<string, VarDecl> symbols;
};

#endif
