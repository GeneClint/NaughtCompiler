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
  int*        int_val;
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
}

/***********************************************************************
 * The order of these next few lines sets operator precedence, which is
 * important to correct operation of the parser.  Don't change them.
 ***********************************************************************/
%right <string_val> ASSIGN
%right <string_val> COLON QUESTION
%left <string_val> ADD SUB
%left <string_val> STAR DIV
%right <string_val> UNARY_OP
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
%token <string_val> STRING_LITERAL
%token <int_val> INT_LITERAL
%token <type_val> ID

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
            cout << (*$$).toString() << " -> module " << endl;
          }
        |              vardecl_list funcdef_list
          { AST = new Module(NULL, $1, $2);
            $$ = AST;
            cout << (*$$).toString() << " -> module " << endl;
          }
        | funcdecl_list             funcdef_list
          { AST = new Module($1, NULL, $2);
            $$ = AST;
            cout << (*$$).toString() << " -> module " << endl;
          }
        |                            funcdef_list
          { AST = new Module(NULL, NULL, $1);
            $$ = AST;
            cout << (*$$).toString() << " -> module " << endl;
          }
        | funcdecl_list vardecl_list
          {             AST = new Module($1, $2, NULL);
            $$ = AST;
            cout << (*$$).toString() << " -> module " << endl;
          }
        |              vardecl_list
          { AST = new Module(NULL, $1, NULL);
            $$ = AST;
            cout << (*$$).toString() << " -> module " << endl;
          }
        | funcdecl_list             
          { AST = new Module($1, NULL, NULL);
            $$ = AST;
            cout << (*$$).toString() << " -> module " << endl;
          }
        |
          { AST = new Module(NULL, NULL, NULL);
            $$ = AST;
            cout << (*$$).toString() << " -> module " << endl;
          }
        ;

funcdecl_list :
          funcdecl_list funcdecl SEMI
          { auto add = *$1 + *$2;
            $$ = &add;
            cout << (*$$).toString() << " -> funcdecl_list " << endl;
          }
        | funcdecl SEMI
          { $$ = new FuncDeclList(*$1);
            cout << (*$$).toString() << " -> funcdecl_list " << endl;
          }
       ;
 
funcdecl :
          FUNCTION ID LPAREN param_list RPAREN
          { Id *id = new Id(*$2);
            $$ = new FuncDecl(*id, *$4);
            cout << (*$$).toString() << " -> funcdecl " << endl;
          }
        | FUNCTION ID LPAREN  RPAREN
          { Id *id = new Id(*$2);
            $$ = new FuncDecl(*id);
            cout << (*$$).toString() << " -> funcdecl " << endl;
          }
        | SFUNCTION ID LPAREN param_list RPAREN
          {             /*(*$$).toString() = new StrUtil(*$1 + *$2 +*$3 +(string)*$4 +*$5);
            cout << (*$$).toString() << " -> funcdecl " << endl;
          */}
        | SFUNCTION ID LPAREN  RPAREN
          {             /*(*$$).toString() = new StrUtil(*$1 + *$2 +*$3 +*$4);
            cout << (*$$).toString() << " -> funcdecl " << endl;
          */}
	;


vardecl_list : 
          vardecl_list vardecl SEMI
          { auto add = *$1 + *$2;
	          $$ = &add;
            cout << (*$$).toString() << " -> vardecl_list " << endl;
          }
        | vardecl SEMI
          {    $$ = new VarDeclList(*$1);
            cout << (*$$).toString() << " -> vardecl_list " << endl;
          }
        ;

vardecl : 
         TYPE ID
          { Id *id = new Id(*$2);
            $$ = new VarDecl(*$1, *id);
            cout << (*$$).toString() << " -> vardecl " << endl;
          }
       | TYPE ID ASSIGN expr
          { $$ = new VarDecl(*$1, *$2, false, $4);
            cout << (*$$).toString() << " -> vardecl " << endl;
          }
       | EXTERN TYPE ID  /* extern variable */
          {    $$ = new VarDecl(*$2, *$3, true);
            cout << (*$$).toString() << " -> vardecl " << endl;
          }
       ;

funcdef_list :
         funcdef
	        { $$ = new FuncDefList($1);
	          cout << (*$$).toString() << " -> funcdef_list " << endl;
	        }	 
       | funcdef_list funcdef
         { auto add = *$1 + $2;
	         $$ = &add;
	   cout << (*$$).toString() << " -> funcdef_list " << endl;
	 }	
	;

funcdef :
	  FUNCTION ID LPAREN param_list RPAREN block
          {       $$ = new FuncDef(*$2, $6, $4);
            cout << (*$$).toString() << " -> funcdef " << endl;
          }
        | FUNCTION ID LPAREN RPAREN block
          { $$ = new FuncDef(*$2, $5);
            cout << (*$$).toString() << " -> funcdef " << endl;
          }
	| SFUNCTION ID LPAREN param_list RPAREN block
          { /* GULP $$ = new StrUtil(*$1 + *$2 + *$3 + (string)*$4 + *$5 + *$6);
            cout << (*$$).toString() << " -> funcdef " << endl; */
          }
        | SFUNCTION ID LPAREN RPAREN block
          { /* GULP $$ = new StrUtil(*$1 + *$2 + *$3 + *$4 + *$5);
            cout << (*$$).toString() << " -> funcdef " << endl; */
          }
        ;

param_list : 
          param_list COMMA param
          { auto add = *$1 + *$3;
	          $$ = $1;
            cout << (*$$).toString() << " -> param_list " << endl;
          }
        | param
          { $$ = new ParamList(*$1);
            cout << (*$$).toString() << " -> param_list " << endl;
          }
        ;

param :
         TYPE ID
          { $$ = new Param(*$1, *$2);
            cout << (*$$).toString() << " -> param " << endl;
          }
        ;

block : 
	  LCBRACE vardecl_list stmt_list RCBRACE
          { $$ = new Block(*$2, *$3);
            cout << (*$$).toString() << " -> block " << endl;
          }
	| LCBRACE              stmt_list RCBRACE
          { $$ = new Block(*(new VarDeclList()), *$2);
            cout << (*$$).toString() << " -> block " << endl;
          }
	| LCBRACE vardecl_list           RCBRACE
          { $$ = new Block(*$2);
            cout << (*$$).toString() << " -> block " << endl;
          }
        | LCBRACE RCBRACE
          { $$ = new Block();
            cout << (*$$).toString() << " -> block " << endl;
          }
        ;

stmt_list :
          stmt_list stmt
          { auto add = *$1 + *$2;
	          $$ = &add;
            cout << (*$$).toString() << " -> stmt_list " << endl;
          }
        | stmt
          { $$ = new StatementList(*$1);
            cout << (*$$).toString() << " -> stmt_list " << endl;
          }
       ;

stmt : 
         expr SEMI
          { $$ = new Statement($1);
            cout << (*$$).toString() << " -> stmt " << endl;
          }
       | RETURN expr SEMI
          { $$ = new Statement($2, true);
            cout << (*$$).toString() << " -> stmt " << endl;
          }
     ;

expr : 
        expr ADD expr
        { $$ = new AddExpression(*$1, *$3);
          cout << (*$$).toString() << " -> expr" << endl;
        }
      | expr SUB expr
        { $$ = new SubExpression(*$1, *$3);
          cout << (*$$).toString() << " -> expr" << endl;
        }
      | expr STAR expr
        { $$ = new StarExpression(*$1, *$3);
          cout << (*$$).toString() << " -> expr" << endl;
        }
      | expr DIV expr
        { $$ = new DivExpression(*$1, *$3);
          cout << (*$$).toString() << " -> expr" << endl;
        }
      | term  ASSIGN expr
        { $$ = new AssignExpression(*$1, *$3);
      	  cout << (*$$).toString() << " -> expr" << endl;
        }
      | expr QUESTION expr COLON expr
        { $$ = new CondExpression(*$1, *$3, *$5);
          cout << (*$$).toString() << " -> expr" << endl;
        }
      | term
        { $$ = $1;
          cout << (*$$).toString() << " -> expr" << endl;
        }
      ;

term :
        STRING_LITERAL
        { /* GULP $$ = new Term();
          cout << (*$$).toString() << " -> term" << endl; */
        }
      | INT_LITERAL
        { $$ = new Int(*$1);
          cout << (*$$).toString() << " -> term" << endl;
        }
      | ID
        { $$ = new Id(*$1);
          cout << (*$$).toString() << " -> term" << endl;
        }
      | LPAREN expr RPAREN
       {  $$ = new ExprTerm($2);
         cout << (*$$).toString() << " -> term" << endl;
        }
      | UNARY_OP term
        {  $$ = new UnaryTerm(*$1, $2);
          cout << (*$$).toString() << " -> term" << endl;
        }
      | ID LPAREN arglist RPAREN  /* function call */
       {  $$ = new FunctionCall(*$1, $3);
         cout << (*$$).toString() << " -> term" << endl;
       }
      | ID LPAREN RPAREN  /* function call */
       {  $$ = new FunctionCall(*$1);
         cout << (*$$).toString() << " -> term" << endl;
       }
      ;

arglist :
        expr
        { $$ = new ArgList($1);
          cout << (*$$).toString() << " -> arglist" << endl;
        }
      | arglist COMMA expr
        { auto add = *$1 + $3;
	        $$ = &add;
          cout << (*$$).toString() << " -> arglist" << endl;
        }
      ;

%%
