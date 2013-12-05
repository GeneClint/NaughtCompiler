%{
 #define YY_NO_UNPUT

 #include <iostream>
 #include <string>
 #include <stdexcept>
 using namespace std;


 int yyerror(char *s);

 #include "StrUtil.h"
 #include "VarDecl.h"
 #include "Param.h"
 #include "ParamList.h"
 #include "Statement.h"
 #include "StatementList.h"
 #include "VarDecl.h"
 #include "VarDeclList.h"
 #include "ArgList.h"
 #include "UnaryTerm.h"
 #include "ExprTerm.h"
 #include "Block.h"
 #include "FunctionCall.h"
 #include "FuncDecl.h"
 #include "FuncDeclList.h"
 #include "FuncDef.h"
 #include "FuncDefList.h"
 #include "Module.h"
 #include "String.h"
 #include "Int.h"
 #include "Id.h"
 #include "parser.hh"
%}

digit       [0-9]
char        [a-zA-Z_]
nmchar      [a-zA-Z0-9_]
hexdigit    [0-9a-fA-F]
ident       {char}{nmchar}*
number      {digit}+

%%

"#".*        { /* ignore single line comments. */ }
";"          { yylval.string_val = NULL; return SEMI; }
","          { yylval.string_val = NULL; return COMMA; }
"="          { yylval.string_val = NULL; return ASSIGN; }
"+"          { yylval.string_val = NULL; return ADD; }
"*"          { yylval.string_val = NULL; return STAR; }
"-"          { yylval.string_val = NULL; return SUB; }
"/"          { yylval.string_val = NULL; return DIV; }
"?"          { yylval.string_val = NULL; return QUESTION; }
":"          { yylval.string_val = NULL; return COLON; }
"("          { yylval.string_val = NULL; return LPAREN; }
")"          { yylval.string_val = NULL; return RPAREN; }
"{"          { yylval.string_val = NULL; return LCBRACE; }
"}"          { yylval.string_val = NULL; return RCBRACE; }
"extern"     { yylval.string_val = NULL; return EXTERN; }
"sfunction"  { yylval.string_val = NULL; return SFUNCTION; }
"function"   { yylval.string_val = NULL; return FUNCTION; }
"return"     { yylval.string_val = NULL; return RETURN; }
"print"      { yylval.type_val = new string("print"); return UNARY_OP; }
"&"          { yylval.type_val = new string("&"); return UNARY_OP; }
"@"          { yylval.type_val = new string("*"); return UNARY_OP; }
"int"        { yylval.type_val = new string("int32_t"); return TYPE; }
"string"     { yylval.type_val = new string("char *"); return TYPE; }
"pointer"    { yylval.type_val = new string("int32_t *"); return TYPE; }
\"[^\"]*\"   { yylval.nstring_val = new String(yytext); return STRING_LITERAL; }
{number}     { int temp = stoi((string)yytext, nullptr); yylval.int_val = new Int(temp); return INT_LITERAL; }
{ident}      { yylval.id_val = new Id(yytext); return ID; }
[ \t\r\f]    { /* ignore white space. */ }
[\n]         { yylineno++; }
.            { runtime_error e(string("Lexer: Line ") + to_string(yylineno) + 
                       ": Illegal character: " + yytext);
               throw e;
             }
