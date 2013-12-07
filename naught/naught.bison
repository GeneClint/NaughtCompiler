%{
#define YY_NO_UNPUT

#include <iostream>
#include <string>
#include <memory>
#include <cstring>

#include "yy.h"
#include "StrUtil.h"
#include "terms.h"

#include "Expression.h"
#include "ExprTerm.h"
#include "Param.h"
#include "ParamList.h"
#include "Statement.h"
#include "StatementList.h"
#include "VarDecl.h"
#include "VarDeclList.h"
#include "ArgList.h"
#include "UnaryTerm.h"
#include "FunctionCall.h"
#include "FuncDef.h"
#include "FuncDefList.h"

using namespace std;

extern int _WANT_DEBUG;

extern Module *AST;


%}

/***************************************
 * These are the union of the data types
 * that are associated with AST nodes.
 * They should all be pointers.
 * The C++ type is the first entry.
 * The second entry is a symbolic
 * name used later in this file.
 ***************************************/
%union {
  string*     type_val;
  Int*        int_val;
  String*     nstring_val;
  StrUtil*    string_val;
  Term*	      term_val;
  Param*      param_val;
  Expression* expr_val;
  ParamList*  param_list_val;
  Statement*  stmnt_val;
  StatementList* stmnt_list_val;
  VarDecl*    vardecl_val;
  VarDeclList* vardecl_list_val;
  ArgList*    arglist_val;
  Block*      block_val;
  FunctionCall* func_call_val;
  FuncDecl*   funcdecl_val;
  FuncDeclList* funcdecl_list_val;
  FuncDef*    funcdef_val;
  FuncDefList*   funcdef_list_val;
  Module*     module_val;
  Id*         id_val;
}

/***********************************************************************
 * The order of these next few lines sets operator precedence, which is
 * important to correct operation of the parser.  Don't change them.
 ***********************************************************************/
%right <string_val> ASSIGN
%right <string_val> COLON QUESTION
%left <string_val> ADD SUB
%left <string_val> STAR DIV
%right <type_val> UNARY_OP
/*********************************************************
 * Okay, that's it -- after this order doesn't matter
 *********************************************************/

/**********************************************************
 * Here (and in the precedence/associativity declarations 
 * above, we're defining symbols that can be returned by
 * the lexer. 
 **********************************************************/

%token <string_val> LCBRACE RCBRACE RPAREN LPAREN SEMI COMMA EXTERN FUNCTION SFUNCTION RETURN

%token <type_val> TYPE
%token <nstring_val> STRING_LITERAL
%token <int_val> INT_LITERAL
%token <id_val> ID

/**********************************************************
 * Now we're defining the type associated with nodes
 * corresponding to non-terminals.
 **********************************************************/

%type <module_val> module
%type <funcdef_val> funcdef
%type <block_val> block
%type <vardecl_val> vardecl
%type <funcdecl_val> funcdecl
%type <expr_val> expr
%type <term_val> term
%type <stmnt_val> stmt

%type <stmnt_list_val> stmt_list
%type <vardecl_list_val> vardecl_list
%type <funcdecl_list_val> funcdecl_list
%type <param_val> param;
%type <param_list_val> param_list;
%type <funcdef_list_val> funcdef_list
%type <arglist_val> arglist;

/*********************************************
 * This is the terminal symbol.  The entire
 * naught program should be reducable to this
 * symbol.
 *********************************************/
%start module

%%

/********************************************************
 * It will take a bit of study, but these rules are
 * the easiest to understand explanation of the grammar.
 ********************************************************/

module :
         funcdecl_list vardecl_list funcdef_list
          { AST = new Module($1, $2, $3);
            $$ = AST;
          }
        |              vardecl_list funcdef_list
          { AST = new Module(NULL, $1, $2);
            $$ = AST;
          }
        | funcdecl_list             funcdef_list
          { AST = new Module($1, NULL, $2);
            $$ = AST;
          }
        |                            funcdef_list
          { AST = new Module(NULL, NULL, $1);
            $$ = AST;
          }
        | funcdecl_list vardecl_list
          {             AST = new Module($1, $2, NULL);
            $$ = AST;
          }
        |              vardecl_list
          { AST = new Module(NULL, $1, NULL);
            $$ = AST;
          }
        | funcdecl_list             
          { AST = new Module($1, NULL, NULL);
            $$ = AST;
          }
        |
          { AST = new Module(NULL, NULL, NULL);
            $$ = AST;
          }
        ;

funcdecl_list :
          funcdecl_list funcdecl SEMI
          { auto add = *$1 + *$2;
            $$ = add;
	    delete $2;
          }
        | funcdecl SEMI
          { $$ = new FuncDeclList(*$1);
            delete $1;
          }
       ;
 
funcdecl :
          FUNCTION ID LPAREN param_list RPAREN
          { 
            $$ = new FuncDecl(*$2, *$4);
	          delete $4;
          }
        | FUNCTION ID LPAREN  RPAREN
          {
            $$ = new FuncDecl(*$2);
          }
        | SFUNCTION ID LPAREN param_list RPAREN
          { 
            $$ = new FuncDecl(*$2, *$4, true);
	          delete $4;
         }
        | SFUNCTION ID LPAREN  RPAREN
          { 
            $$ = new FuncDecl(*$2, true);
          }
	;


vardecl_list : 
          vardecl_list vardecl SEMI
          { auto add = *$1 + *$2;
	          $$ = add;
            delete $2;
          }
        | vardecl SEMI
          { 
            $$ = new VarDeclList(*$1); 
            delete $1;
          }
        ;

vardecl : 
         TYPE ID
          { 
            $$ = new VarDecl(*$1, *$2);
            delete $1;
          }
       | TYPE ID ASSIGN expr
          { 
            $$ = new VarDecl(*$1, *$2, false, $4);
            delete $1;
          }
       | EXTERN TYPE ID  /* extern variable */
          { 
            $$ = new VarDecl(*$2, *$3, true);
            delete $2;
          }
       ;

funcdef_list :
         funcdef
        { 
            $$ = new FuncDefList(*$1);
            delete $1;
	        }	 
       | funcdef_list funcdef
         { 
            auto add = *$1 + *$2;
	          $$ = add;
            delete $2;
         }	
	;

funcdef :
	      FUNCTION ID LPAREN param_list RPAREN block
          { 
            $$ = new FuncDef(*$2, $6, $4);
          }
        | FUNCTION ID LPAREN RPAREN block
          { 
            $$ = new FuncDef(*$2, $5);
          }
	      | SFUNCTION ID LPAREN param_list RPAREN block
          { 
            $$ = new FuncDef(*$2, $6, $4, true);
          }
        | SFUNCTION ID LPAREN RPAREN block
          { 
            $$ = new FuncDef(*$2, $5, true);
          }
        ;

param_list : 
          param_list COMMA param
          { auto add = *$1 + *$3;
	    $$ = add;
	    delete $3;
          }
        | param
          { $$ = new ParamList(*$1);
	    delete $1;
          }
        ;

param :
         TYPE ID
          { 
            $$ = new Param(*$1, *$2);
            delete $1;
          }
        ;

block : 
	      LCBRACE vardecl_list stmt_list RCBRACE
        { $$ = new Block(*$2, *$3);
          delete $2;
          delete $3;
        }
	    | LCBRACE              stmt_list RCBRACE
        { $$ = new Block(*(new VarDeclList()), *$2); 
          delete $2;
        }
	    | LCBRACE vardecl_list           RCBRACE
        { 
          $$ = new Block(*$2); 
          delete $2;
        }
      | LCBRACE RCBRACE
        { $$ = new Block(); }
        ;

stmt_list :
        stmt_list stmt
        { 
          auto add = *$1 + *$2;
	        $$ = add;
          delete $2;
        }
      | stmt
        { $$ = new StatementList(*$1); 
          delete $1;
        }
       ;

stmt : 
        expr SEMI
        { $$ = new Statement($1); }
      | RETURN expr SEMI
        { $$ = new Statement($2, true); }
     ;

expr : 
        expr ADD expr
        { $$ = new AddExpression(*$1, *$3); }
      | expr SUB expr
        { $$ = new SubExpression(*$1, *$3); }
      | expr STAR expr
        { $$ = new StarExpression(*$1, *$3); }
      | expr DIV expr
        { $$ = new DivExpression(*$1, *$3); }
      | term ASSIGN expr
        { $$ = new AssignExpression(*$1, *$3); }
      | expr QUESTION expr COLON expr
        { $$ = new CondExpression(*$1, *$3, *$5); }
      | term
        { $$ = $1; }
      ;

term :
        STRING_LITERAL
        { $$ = $1; }
      | INT_LITERAL
        { $$ = $1; }
      | ID
        { $$ = $1; }
      | LPAREN expr RPAREN
       { $$ = new ExprTerm($2); }
      | UNARY_OP term
       { $$ = new UnaryTerm(*$1, $2);
         delete $1; }
      | ID LPAREN arglist RPAREN  /* function call */
       { 
        $$ = new FunctionCall(*$1, $3); 
       }
      | ID LPAREN RPAREN  /* function call */
       { 
        $$ = new FunctionCall(*$1);
       }
      ;

arglist :
        expr
        { $$ = new ArgList($1); }
      | arglist COMMA expr
        { auto add = *$1 + $3;
	        $$ = add;
        }
      ;

%%
