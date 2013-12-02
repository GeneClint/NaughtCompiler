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
#include "Block.h"

using namespace std;

extern int _WANT_DEBUG;

extern StrUtil *AST;


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

%token <string_val> TYPE
%token <string_val> STRING_LITERAL
%token <string_val> INT_LITERAL
%token <string_val> ID

/**********************************************************
 * Now we're defining the type associated with nodes
 * corresponding to non-terminals.
 **********************************************************/

%type <string_val> module
%type <string_val> funcdef
%type <block_val> block
%type <vardecl_val> vardecl
%type <string_val> funcdecl
%type <expr_val> expr
%type <term_val> term
%type <stmnt_val> stmt

%type <stmnt_list_val> stmt_list
%type <vardecl_list_val> vardecl_list
%type <string_val> funcdecl_list
%type <param_val> param;
%type <param_list_val> param_list;
%type <string_val> funcdef_list
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
          { AST = new StrUtil(*$1 + *$2 + *$3);
            $$ = AST;
            cout << *$$ << " -> module " << endl;
          }
        |              vardecl_list funcdef_list
          { AST = new StrUtil(*$1 + *$2);
            $$ = AST;
            cout << *$$ << " -> module " << endl;
          }
        | funcdecl_list             funcdef_list
          { AST = new StrUtil(*$1 + *$2);
            $$ = AST;
            cout << *$$ << " -> module " << endl;
          }
        |                            funcdef_list
          { AST = new StrUtil(*$1);
            $$ = AST;
            cout << *$$ << " -> module " << endl;
          }
        | funcdecl_list vardecl_list
          { AST = new StrUtil(*$1 + *$2);
            $$ = AST;
            cout << *$$ << " -> module " << endl;
          }
        |              vardecl_list
          { AST = new StrUtil((string)*$1);
            $$ = AST;
            cout << *$$ << " -> module " << endl;
          }
        | funcdecl_list             
          { AST = new StrUtil(*$1);
            $$ = AST;
            cout << *$$ << " -> module " << endl;
          }
        |
          { AST = new StrUtil(string());
            $$ = AST;
            cout << *$$ << " -> module " << endl;
          }
        ;

funcdecl_list :
          funcdecl_list funcdecl SEMI
          { $$ = new StrUtil(*$1 + *$2 + *$3);
            cout << *$$ << " -> funcdecl_list " << endl;
          }
        | funcdecl SEMI
          { $$ = new StrUtil(*$1 + *$2);
            cout << *$$ << " -> funcdecl_list " << endl;
          }
       ;
 
funcdecl :
          FUNCTION ID LPAREN param_list RPAREN
          { $$ = new StrUtil(*$1 + *$2 +*$3 + (string)*$4 +*$5);
            cout << *$$ << " -> funcdecl " << endl;
          }
        | FUNCTION ID LPAREN  RPAREN
          { $$ = new StrUtil(*$1 + *$2 +*$3 +*$4);
            cout << *$$ << " -> funcdecl " << endl;
          }
        | SFUNCTION ID LPAREN param_list RPAREN
          { $$ = new StrUtil(*$1 + *$2 +*$3 +(string)*$4 +*$5);
            cout << *$$ << " -> funcdecl " << endl;
          }
        | SFUNCTION ID LPAREN  RPAREN
          { $$ = new StrUtil(*$1 + *$2 +*$3 +*$4);
            cout << *$$ << " -> funcdecl " << endl;
          }
	;


vardecl_list : 
          vardecl_list vardecl SEMI
          { auto add = *$1 + *$2;
	    $$ = &add;
            cout << *$$ << " -> vardecl_list " << endl;
          }
        | vardecl SEMI
          { $$ = new VarDeclList(*$1);
            cout << *$$ << " -> vardecl_list " << endl;
          }
        ;

vardecl : 
         TYPE ID
          { $$ = new VarDecl(*$1, *$2);
            cout << *$$ << " -> vardecl " << endl;
          }
       | TYPE ID ASSIGN expr
          { $$ = new VarDecl(*$1, *$2, false, $4);
            cout << *$$ << " -> vardecl " << endl;
          }
       | EXTERN TYPE ID  /* extern variable */
          { $$ = new VarDecl(*$2, *$3, true);
            cout << *$$ << " -> vardecl " << endl;
          }
       ;

funcdef_list :
         funcdef
       | funcdef_list funcdef
        ;

funcdef :
	  FUNCTION ID LPAREN param_list RPAREN block
          { $$ = new StrUtil(*$1 + *$2 + *$3 + (string)*$4 + *$5 /*+ *$6*/);
            cout << *$$ << " -> funcdef " << endl;
          }
        | FUNCTION ID LPAREN RPAREN block
          { $$ = new StrUtil(*$1 + *$2 + *$3 + *$4/* + *$5*/);
            cout << *$$ << " -> funcdef " << endl;
          }
	| SFUNCTION ID LPAREN param_list RPAREN block
          { $$ = new StrUtil(*$1 + *$2 + *$3 + (string)*$4 + *$5 /*+ *$6*/);
            cout << *$$ << " -> funcdef " << endl;
          }
        | SFUNCTION ID LPAREN RPAREN block
          { $$ = new StrUtil(*$1 + *$2 + *$3 + *$4 /*+ *$5*/);
            cout << *$$ << " -> funcdef " << endl;
          }
        ;

param_list : 
          param_list COMMA param
          { auto add = *$1 + *$3;
	    $$ = &add;
            cout << *$$ << " -> param_list " << endl;
          }
        | param
          { $$ = new ParamList(*$1);
            cout << *$$ << " -> param_list " << endl;
          }
        ;

param :
         TYPE ID
          { $$ = new Param(*$1, *$2);
            cout << *$$ << " -> param " << endl;
          }
        ;

block : 
	  LCBRACE vardecl_list stmt_list RCBRACE
          { $$ = new Block(*$2, *$3);
            cout << *$$ << " -> block " << endl;
          }
	| LCBRACE              stmt_list RCBRACE
          { $$ = new Block(*(new VarDeclList()), *$2);
            cout << *$$ << " -> block " << endl;
          }
	| LCBRACE vardecl_list           RCBRACE
          { $$ = new Block(*$2);
            cout << *$$ << " -> block " << endl;
          }
        | LCBRACE RCBRACE
          { $$ = new Block();
            cout << *$$ << " -> block " << endl;
          }
        ;

stmt_list :
          stmt_list stmt
          { auto add = *$1 + *$2;
	    $$ = &add;
            cout << *$$ << " -> stmt_list " << endl;
          }
        | stmt
          { $$ = new StatementList(*$1);
            cout << *$$ << " -> stmt_list " << endl;
          }
       ;

stmt : 
         expr SEMI
          { $$ = new Statement(*$1);
            cout << *$$ << " -> stmt " << endl;
          }
       | RETURN expr SEMI
          { $$ = new Statement(*$2, true);
            cout << *$$ << " -> stmt " << endl;
          }
     ;

expr : 
        expr ADD expr
        { $$ = new AddExpression(*$1, *$3);
          cout << *$$ << " -> expr" << endl;
        }
      | expr SUB expr
        { $$ = new SubExpression(*$1, *$3);
          cout << *$$ << " -> expr" << endl;
        }
      | expr STAR expr
        { $$ = new StarExpression(*$1, *$3);
          cout << *$$ << " -> expr" << endl;
        }
      | expr DIV expr
        { $$ = new DivExpression(*$1, *$3);
          cout << *$$ << " -> expr" << endl;
        }
      | term  ASSIGN expr
        { $$ = new AssignExpression(*$1, *$3); 
          cout << *$$ << " -> expr" << endl;
        }
      | expr QUESTION expr COLON expr
        { $$ = new CondExpression(*$1, *$3, *$5);
          cout << *$$ << " -> expr" << endl;
        }
      | term
        { $$ = $1;
          cout << *$$ << " -> expr" << endl;
        }
      ;

term :
        STRING_LITERAL
        { /* GULP $$ = new Term();
          cout << *$$ << " -> term" << endl; */
        }
      | INT_LITERAL
        { $$ = new Int($1);
          cout << *$$ << " -> term" << endl;
        }
      | ID
        { $$ = new Id($1);
          cout << *$$ << " -> term" << endl;
        }
      | LPAREN expr RPAREN
       { $$ = new ExprTerm($2);
         cout << *$$ << " -> term" << endl;
        }
      | UNARY_OP term
        { $$ = new UnaryTerm(*$1, $2);
          cout << *$$ << " -> term" << endl;
        }
      | ID LPAREN arglist RPAREN  /* function call */
       { /* GULP $$ = new Term();
         cout << *$$ << " -> term" << endl; */
       }
      | ID LPAREN RPAREN  /* function call */
       { /* GULP $$ = new Term();
         cout << *$$ << " -> term" << endl; */
       }
      ;

arglist :
        expr
        { $$ = new ArgList($1);
          cout << *$$ << " -> arglist" << endl;
        }
      | arglist COMMA expr
        { auto add = *$1 + $3;
	$$ = &add;
        cout << *$$ << " -> arglist" << endl;
        }
      ;

%%
