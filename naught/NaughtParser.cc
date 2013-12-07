// Gene Kim
// 1130267
// genelkim@uw.edu

#include "NaughtParser.h"
#include "TempGen.h"
#include "FunctionCall.h"
#include "AddExpression.h"

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
    vector<FuncDef> defs = m->getFuncDefs()->getFuncDefs();
    for(FuncDef def : defs) {
      writeFunctionDef(&def);
      out << endl;
    }
  }
  for(auto kv : symbols) {
    delete kv.second;
  }
  symbols.clear();
}

void NaughtParser::writeFunctionDecl(FuncDecl *f) {
  string id = f->getId().toString();
  Id *insertId = new Id(id);
  symbols.insert(make_pair(id, new FuncDecl(*insertId, f->isStringReturning())));
  string type = f->isStringReturning() ? "char * " : "int32_t ";
  out << type << id << " ( ";
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
 
  Id *insId = new Id(id); 
  symbols.insert({id, new VarDecl(v->getType(), *insId)});
 
  tempName retVal = make_pair(type, id);

  return retVal;
}

tempName NaughtParser::writeExpression(const Expression *e) {
  Term* t = e->getTerm();

  Expression* sub_e;
  vector<string> connections = e->getConnectors();
  vector<tempName> temps;

  CondExpression* ce = dynamic_cast<CondExpression*>(const_cast<Expression*>(e));

  sub_e = e->getValue1();
  if (sub_e) {
    temps.push_back(writeExpression(sub_e));
  }

  if (ce) {
    tempName result = (this->temps).next(temps[0].first);
    out << result.first << " " << result.second << ";" << endl; 
    
    out << "if (" << temps[0].second << ") {"<<endl;
    sub_e = e->getValue2();
    tempName val2 = writeExpression(sub_e);
    out << "  " << result.second << " = " << val2.second << ";" << endl;
    out << "} else {" << endl;
    sub_e = e->getValue3();
    tempName val3 = writeExpression(sub_e);
    out << "  " << result.second << " = " << val3.second << ";" << endl;
    out << "}" << endl << endl;

    return result;
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

  // a VarDecl
  if(thisTerm) {
    // variable
    Id *id = dynamic_cast<Id *>(thisTerm);
    if(id) {
      string name = id->getName();
      if(symbols.find(name) != symbols.end()) {
        // exists
        Decl *res = symbols.find(id->getName())->second;
        VarDecl *vd   = dynamic_cast<VarDecl *>(res);
        
        if(vd) {
          // variable exists, so just return the variable with type
          return writeTerm(thisTerm);
        } 
      } else {
        // TODO: error, unknown id
      }
    }
    tempName temp = writeTerm(thisTerm);
    out << temp.first << " " << temp.second << " = " << thisTerm->toString() << ";" << endl;
    Term *test = dynamic_cast<Term *>(const_cast<Expression *>(e));
    if (test != thisTerm)
      delete thisTerm;
    return temp;
  }

  int connectOffset = 0;
  
  tempName temp;
  auto isAdd = dynamic_cast<AddExpression*>(const_cast<Expression*>(e));
  if (temps[0].first == "char *" && isAdd) {
    tempName newLength = (this->temps).next("int32_t");
    tempName snew = (this->temps).next("nstring_st*");
    out << newLength.first << " " << newLength.second << " = ";
    out << "*((int32_t*)" << temps[0].second << " - 1) + *((int32_t*)" << temps[1].second << " - 1);" << endl;
    out << snew.first << " " << snew.second << " = " << " malloc(sizeof(int32_t) + (" << newLength.second << " + 1) * sizeof(char));" << endl;
    out << snew.second << "->len = " << newLength.second << " ;" << endl;
    tempName fakestring = (this->temps).next("char *");
    out << fakestring.first << " " << fakestring.second << " = " << snew.second << "->str;" << endl;
    out << "strcpy (" << fakestring.second << ", " << temps[0].second << ");" << endl;
    out << "strcat (" << fakestring.second << ", " << temps[1].second << ");" << endl;
    return fakestring;
  } else {
    // if the expression is an assignment expression
    if (t != nullptr && !thisTerm) { 
      tempName termTemp = writeTerm(t);
      temp = (this->temps).next(termTemp.first);
      out << t->toString() << " "; 
      if (connections.size() > 0)
	      out << connections[connectOffset++];
    } else {
      temp = (this->temps).next(temps[0].first);
      out << temp.first << " " << temp.second << " = ";
    }

    if (temps.size() > 0) {
      out << " " << temps[0].second;
      for(size_t i = 1; i < temps.size(); i++) {
	      out << " " << connections[connectOffset + i - 1] << " " << temps[i].second << " ";
      }
    }
  } 
  out << ";" << endl;

  if(t != nullptr && !thisTerm) {
    out << temp.first << " " << temp.second << " = " << t->toString() << ";" << endl;
  }

  return temp;
}

tempName NaughtParser::writeTerm(Term *&t) {
  String *s        = dynamic_cast<String*>(t);
  Int *in          = dynamic_cast<Int*>(t);
  Id *id           = dynamic_cast<Id*>(t);
  UnaryTerm *ut    = dynamic_cast<UnaryTerm*>(t);
  ExprTerm *et     = dynamic_cast<ExprTerm*>(t);
  FunctionCall *fc = dynamic_cast<FunctionCall*>(t);

  if (et) {
    tempName temp = writeExpression(et->evaluate());
    //delete t;
    t = new Id(temp.second);
    return temps.next(temp.first);
  } else if (ut) {
    Term* other = ut->evaluate();
    tempName otherTemp = writeTerm(other);
    string oper = ut->getOperator();
    string result = "";
    

    if(oper.compare("print") == 0) {
      Id *otherI = dynamic_cast<Id*>(other);
      if (!otherI)
	out << otherTemp.first << " " << otherTemp.second << " = " << other->toString() << ";" << endl;
      string code;
      string alter = "";
      if (otherTemp.first == "int32_t") {
	      code = "%d";
      } else if (otherTemp.first == "char *") {
	      code = "%s";
      } else {
	      code = "%p";
	      alter = "(void *) ";
      }
      out << "printf(\"" << code << "\\n\", " << alter << otherTemp.second << ");" << endl; 
      result = otherTemp.second;
      //delete t;
      t = new Id(otherTemp.second);
      return temps.next(otherTemp.first);
    } else if(oper.compare("&") == 0) {

      return temps.next(otherTemp.first + " *"); 
    
    } else {
      string curType = otherTemp.first;
      size_t starIndex = curType.rfind("*");
      if(starIndex != string::npos) {
        //found star
        curType.erase(starIndex - 1, 2);
        return temps.next(curType);
      }
      
      // Not found, ERROR
      return temps.next(curType);

    }   
  } else if(s) {
    string val = s->getString();
    tempName len = temps.next("int32_t");
    out << len.first << " " << len.second << " = strlen(" << val << ");" << endl;
    tempName snew = temps.next("nstring_st*");
    out << snew.first << " " << snew.second << " = malloc(sizeof(int32_t) + sizeof(char) * (" << len.second << " + 1));" << endl;
    out << snew.second << "->len = " << len.second << ";" << endl;
    out << "strcpy(" << snew.second << "->str, " << val << ");" << endl;
    //delete t;
    t = new Id(snew.second + "->str");
    return temps.next("char *");
  } else if(in) {
    tempName temp = temps.next("int32_t");
    return temp;
  } else if(id) {  
      string name = id->getName();
      if(symbols.find(name) != symbols.end()) {
        // exists
        Decl *res = symbols.find(name)->second;
        VarDecl *vd   = dynamic_cast<VarDecl *>(res);
       
        if(vd) {
          // variable exists, so just return the variable with type
          return make_pair(vd->getType(), name);
        }
      }
    // ERROR message
    tempName temp = make_pair("id", id->getName());
    return temp;
  } else if (fc) {
    // function call
    string id = fc->getId().toString();
    if (symbols.find(id) != symbols.end()) {
      Decl *res = symbols.find(id)->second;
      FuncDecl *fd = dynamic_cast<FuncDecl *>(res);
      if (fd) {
	string type = fd->isStringReturning() ? "char *" : "int32_t";
	
  // calulate args and insert new temp arg names into the functionCall
  if (fc->hasArgs()) {
	  auto args = fc->getArgs()->getArgs();
	  vector<tempName> *tempArgs = new vector<tempName>;
	  for(auto arg : args) {
	    tempArgs->push_back(writeExpression(arg)); 
	  }
       
	  fc->setTempArgs(tempArgs);  
	}
        tempName temp = temps.next(type);
	      return temp;
      }
    }
    //default a function returns an int
    tempName temp = temps.next("int32_t");
    return temp;
  } else {
    // defualt...
    tempName temp = temps.next("int32_t");
    return temp;
  }
}

void NaughtParser::writeFunctionDef(FuncDef *f) {
  Id id = f->getId();
  string type = f->isStringReturning() ? "char * " : "int32_t ";
  out << type << id.toString() << " ( ";
  Id *insertId = new Id(id.getName());

  ParamList *ps;
  vector<Param> params; 
  FuncDecl *toInsert;
  if (f->hasParams()) {
    ps = f->getParams();
    toInsert = new FuncDecl(*insertId, *ps, f->isStringReturning());
    params = ps->getParams();
    if (params.size() > 0) {
      out << params[0].toString();
      for(size_t i = 1; i < params.size(); i++) {
	      out << " , " << params[i].toString();
      }
    }
  } else {
    toInsert = new FuncDecl(*insertId, f->isStringReturning());
  }
  out << " ) " << endl;

  symbols.insert(make_pair(id.toString(), toInsert));
  Block* bloc = f->getBlock();
  if (bloc) {
    vector<tempName> blocParams;
    for(Param p : params) {
      blocParams.push_back(make_pair(p.getType(), p.getId().getName()));
    }

    writeBlock(bloc, blocParams);
  }
}

void NaughtParser::writeBlock(Block *b, vector<tempName> params) {
  out << " { " << endl;
  auto decls = b->getVarDecls();
  vector<tempName> scope(params);
  
  // add parameters to symbol table
  for(tempName param : params) {
    Id *insId = new Id(param.second);
    symbols.insert({param.second, new VarDecl(param.first, *insId)});
  }

  for(auto decl : decls) {
    scope.push_back(writeVarDecl(&decl));
    out << endl;
  }
  auto stmts = b->getStatements();
  for(auto stmt : stmts) {
    writeStatement(&stmt);
    out << endl;
  }
  for (auto id : scope) {
    Decl* removed = symbols[id.second];
    symbols.erase (id.second);
    delete removed;
  }
  out << " } " << endl;
}

void NaughtParser::writeStatement(Statement *s) {
  auto exp = s->getExpression();
  tempName tempvar = writeExpression(exp);
  if (s->isReturn()) {
    out << "return " << tempvar.second << ";" << endl;
  }
}

void NaughtParser::writeHeader() {
  out << "#include <stdio.h>" << endl;
  out << "#include <stdlib.h>" << endl;
  out << "#include <string.h>" << endl;
  out << "#include <inttypes.h>" << endl << endl;

  out << "typedef struct nstring_st {" << endl <<
         "  int32_t   len;" << endl <<
         "  char      str[];" << endl <<
         "} nstring_st;" << endl << endl;
}

