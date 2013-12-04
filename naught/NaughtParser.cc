#include "NaughtParser.h"
using namespace std;

void NaughtParser::write(Module *ast, string o) {
  NaughtParser parser(o);
  parser.writeModule(ast);
}

void NaughtParser::writeModule(Module *m) {
  
  writeHeader();

  if (m->hasFuncDecls()) {
    vector<FuncDecl> decls = m->getFuncDecls()->getFuncDecls();
    for(FuncDecl fdecl : decls) {
      writeFunctionDecl(&fdecl);
      out << endl;
    }
  }
  if (m->hasVarDecls()) {
    vector<VarDecl> vdecls = m->getVarDecls()->getVarDecls();
    for(VarDecl vdecl : vdecls) {
      writeVarDecl(&vdecl);
      out << endl;
    }
  }
  if (m->hasFuncDefs()) {
    vector<const FuncDef*> defs = m->getFuncDefs()->getFuncDefs();
    for(const FuncDef* def : defs) {
      writeFunctionDef(*def);
      out << endl;
    }
  }
}

void NaughtParser::writeFunctionDecl(FuncDecl *f) {
  string id = f->getId().toString();
  symbols.insert({id, f});
  out << "int " << id << " ( ";
  auto params = f->getParams();
  if (params.size() > 0) {
    out << params[0].toString();
    for(size_t i = 1; i < params.size(); i++) {
      out << " , " << params[i].toString();
    }
  }
  out << " );" << endl;
}

string NaughtParser::writeVarDecl(VarDecl* v) {
  string tempvar; 
  string id = v->getId().toString();
  Expression* exp = v->getExpression();
  if (exp)
    tempvar = writeExpression(exp);
  if (v->isExtern())
    out << "extern ";
  out << id;
  if (exp) {
    out << " = " << tempvar;
  }
  out << ";";
  symbols.insert({id, v});
  return id;
}

string NaughtParser::writeExpression(const Expression *e) {
  Term* t = e->getTerm();

  Expression* sub_e;
  vector<string> connections = e->getConnectors();
  vector<string> temps;

  sub_e = e->getValue1();
  if (sub_e) {
    temps.push_back(writeExpression(sub_e));
  }

  sub_e = e->getValue2();
  if (sub_e) {
    temps.push_back(writeExpression(sub_e));
  }

  sub_e = e->getValue3();
  if (sub_e) {
    temps.push_back(writeExpression(sub_e));
  }

  string tempname = this->temps.next("int");
  out << tempname << " = ";
  int connectIndex = 0;
  if (t != nullptr) {
    out << writeTerm(t);
    if (connections.size() > 0)
      out << connections[connectIndex++];
  }

  for(string temp : temps)
    out << " " << temp << " " << connections[connectIndex++];
  out << ";" << endl;
  return tempname;
}

string NaughtParser::writeTerm(Term *t) {
  UnaryTerm *ut = dynamic_cast<UnaryTerm*>(t);
  ExprTerm *et = dynamic_cast<ExprTerm*>(t);
  if (et) {
    string temp = writeExpression(et->evaluate());
    return " ( " + temp + ")";
  } else if (ut) {
    string otherTemp = writeTerm(ut->evaluate());
    string temp = temps.next("int");
    string oper = ut->getOperator();
    string result = "";
    

    if(oper.compare("print") == 0) {
      out << "printf(\"%d\", " << otherTemp << ");" << endl; 
      result = otherTemp;
    } else {
      result = oper + otherTemp;
    }
    
    out << temp << " = " << result << " ;";
    return temp;
  } else {
    string temp = temps.next("int");
    out << temp << " = " << t->toString();
    return temp;
  }
}

void NaughtParser::writeFunctionDef(FuncDef f) {
  out << "int " << f.getId().toString() << " ( ";
  if (f.hasParams()) {
    auto params = f.getParams()->getParams();
    if (params.size() > 0) {
      out << params[0].toString();
      for(size_t i = 1; i < params.size(); i++) {
	out << " , " << params[i].toString();
      }
    }
  }
  out << " ) " << endl;
  Block* bloc = f.getBlock();
  if (bloc) {
    writeBlock(*bloc);
  }
}

void NaughtParser::writeBlock(Block b) {
  out << " { " << endl;
  auto decls = b.getVarDecls();
  vector<string> scope;
  for(auto decl : decls) {
    scope.push_back(writeVarDecl(&decl));
    out << endl;
  }
  auto stmts = b.getStatements();
  for(auto stmt : stmts) {
    writeStatement(stmt);
    out << endl;
  }
  for (auto id : scope) {
    symbols.erase (id);
  }
  out << " } " << endl;
}

void NaughtParser::writeStatement(Statement s) {
  auto exp = s.getExpression();
  string tempvar;
  if (exp) {
    tempvar = writeExpression(exp);
  }
  if (s.isReturn()) {
    out << "return " << tempvar << ";";
  }
  out << endl;
}

void NaughtParser::writeHeader() {
  out << "#include <stdio.h>" << endl;
  out << "#include <stdlib.h>" << endl << endl;
}

