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
  out << "int32_t " << id << " ( ";
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

  Term* thisTerm = dynamic_cast<Term *>(const_cast<Expression *>(e));

  // if the expression itself is a term
  if(thisTerm) {
    // variable
  /* 
    Id *id = dynamic_cast<Id *>(thisTerm);
    if(id) {
      string name = id->getName();
      if(symbols.find(name) != symbols.end()) {
        // exists
        Decl *res = symbols.find(id->getName())->second;
        VarDecl *vd   = dynamic_cast<VarDecl *>(res);
        
        if(vd) {
          // variable exists, so just return the variable with type
          return make_pair(vd->getType(), name);
        } 
      } else {
        // TODO: error, unknown id
      }
    }
*/
    tempName temp = writeTerm(thisTerm);
    out << temp.first << " " << temp.second << " = " << thisTerm->toString() << ";" << endl;
    return temp;
  }

  int connectOffset = 0;
  
  tempName temp;

  // if the expression is an assignment expression
  if (t != nullptr && !thisTerm) { 
    temp = writeTerm(t);
    out << t->toString() << " "; 
    if (connections.size() > 0)
      out << connections[connectOffset++];
  } else {
    temp = (this->temps).next("int32_t");
    out << temp.first << " " << temp.second << " = ";
  }

  if (temps.size() > 0) {
    out << " " << temps[0].second;
    for(size_t i = 1; i < temps.size(); i++) {
      out << " " << connections[connectOffset + i - 1] << " " << temps[i].second << " ";
    }
  }
  out << ";" << endl;
  return temp;
}

tempName NaughtParser::writeTerm(Term *&t) {
  String *s     = dynamic_cast<String*>(t);
  Int *in       = dynamic_cast<Int*>(t);
  Id *id        = dynamic_cast<Id*>(t);
  UnaryTerm *ut = dynamic_cast<UnaryTerm*>(t);
  ExprTerm *et  = dynamic_cast<ExprTerm*>(t);

  if (et) {
    tempName temp = writeExpression(et->evaluate());
    t = new Id(temp.second);
    return temps.next(temp.first);
  } else if (ut) {
    // TODO: change type based on operator
    Term* other = ut->evaluate();
    tempName otherTemp = writeTerm(other);
    tempName temp = temps.next("int32_t");
    string oper = ut->getOperator();
    string result = "";
    

    if(oper.compare("print") == 0) {
      out << "printf(\"%d\", " << temp.second << ");" << endl; 
      result = temp.second;
    } else {
      result = oper + temp.second;
    }
    
    return temp;
  } else if(s) {
    tempName temp = temps.next("char *");
    return temp;
  } else if(in) {
    tempName temp = temps.next("int32_t");
    return temp;
  } else if(id) {  
      string name = id->getName();
      if(symbols.find(name) != symbols.end()) {
        // exists
        Decl *res = symbols.find(id->getName())->second;
        VarDecl *vd   = dynamic_cast<VarDecl *>(res);
        
        if(vd) {
          // variable exists, so just return the variable with type
          return make_pair(vd->getType(), name);
        } 
        // TODO: ERROR
       }
    tempName temp = make_pair("id", id->getName());
    return temp;
  } else {
    // defualt...
    tempName temp = temps.next("int32_t");
    return temp;
  }
}

void NaughtParser::writeFunctionDef(FuncDef f) {
  out << "int32_t " << f.getId().toString() << " ( ";
  
  vector<Param> params; 
  if (f.hasParams()) {
    params = f.getParams()->getParams();
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
    vector<tempName> blocParams;
    for(Param p : params) {
      blocParams.push_back(make_pair(p.getType(), p.getId().getName()));
    }

    writeBlock(*bloc, blocParams);
  }
}

void NaughtParser::writeBlock(Block b, vector<tempName> params) {
  out << " { " << endl;
  auto decls = b.getVarDecls();
  vector<tempName> scope(params);
  
  // add parameters to symbol table
  for(tempName param : params) {
    symbols.insert({param.second, new VarDecl(param.first, new Id(param.second))});
  }

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
  
  out << "typedef struct nstring_st {" << endl <<
         "  int32_t   len;" << endl <<
         "  char      str[];" << endl <<
         "} nstring_st;" << endl << endl;
}

