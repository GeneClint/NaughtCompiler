#include "NaughtParser.h"
#include "TempGen.h"

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

tempName NaughtParser::writeVarDecl(VarDecl* v) {
  tempName tempvar; 
  string id = v->getId().toString();
  string type = v->getType();
  Expression* exp = v->getExpression();
  
  if (exp)
    tempvar = writeExpression(exp);
  if (v->isExtern())
    out << "extern ";
  out << type << " " << id;
  if (exp) {
    out << " = " << tempvar.second;
  }
  out << ";";
  
  symbols.insert({id, v});
 
  tempName retVal = make_pair(type, id);

  return retVal;
}

tempName NaughtParser::writeExpression(const Expression *e) {
  Term* t = e->getTerm();

  Expression* sub_e;
  vector<string> connections = e->getConnectors();
  vector<tempName> temps;

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

  tempName tempname = this->temps.next("int");
  out << tempname.first << tempname.second << " = ";
  int connectOffset = 0;
  if (t != nullptr) {
    writeTerm(t);
    if (connections.size() > 0)
      out << connections[connectOffset++];
  }

  if (temps.size() > 0) {
    out << " " << temps[0].second;
    for(int i = 1; i < temps.size(); i++) {
      out << connections[connectOffset + i - 1] << " " << temps[i].second << " ";
    }
  }
  out << ";" << endl;
  return tempname;
}

tempName NaughtParser::writeTerm(Term *t) {
  UnaryTerm *ut = dynamic_cast<UnaryTerm*>(t);
  ExprTerm *et = dynamic_cast<ExprTerm*>(t);
  if (et) {
    tempName temp = writeExpression(et->evaluate());
    temp.second = " ( " + temp.second + " ) ";

    return temp;
  } else if (ut) {
    tempName otherTemp = writeTerm(ut->evaluate());
    tempName temp = temps.next("int");
    string oper = ut->getOperator();
    string result = "";
    

    if(oper.compare("print") == 0) {
      out << "printf(\"%d\", " << temp.second << ");" << endl; 
      result = temp.second;
    } else {
      result = oper + temp.second;
    }
    
    out << result;
    return temp;
  } else {
    tempName temp = temps.next("int");
    out << t->toString();
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
  vector<tempName> scope;
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
    symbols.erase (id.second);
  }
  out << " } " << endl;
}

void NaughtParser::writeStatement(Statement s) {
  auto exp = s.getExpression();
  tempName tempvar;
  if (exp) {
    tempvar = writeExpression(exp);
  }
  if (s.isReturn()) {
    out << "return " << tempvar.second << ";";
  }
  out << endl;
}

void NaughtParser::writeHeader() {
  out << "#include <stdio.h>" << endl;
  out << "#include <stdlib.h>" << endl << endl;
}

