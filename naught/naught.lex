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
";"          { yylval.string_val = new StrUtil(yytext); return SEMI; }
","          { yylval.string_val = new StrUtil(yytext); return COMMA; }
"="          { yylval.string_val = new StrUtil(yytext); return ASSIGN; }
"+"          { yylval.string_val = new StrUtil(yytext); return ADD; }
"*"          { yylval.string_val = new StrUtil(yytext); return STAR; }
"-"          { yylval.string_val = new StrUtil(yytext); return SUB; }
"/"          { yylval.string_val = new StrUtil(yytext); return DIV; }
"?"          { yylval.string_val = new StrUtil(yytext); return QUESTION; }
":"          { yylval.string_val = new StrUtil(yytext); return COLON; }
"("          { yylval.string_val = new StrUtil(yytext); return LPAREN; }
")"          { yylval.string_val = new StrUtil(yytext); return RPAREN; }
"{"          { yylval.string_val = new StrUtil(yytext); return LCBRACE; }
"}"          { yylval.string_val = new StrUtil(yytext); return RCBRACE; }
"extern"     { yylval.string_val = new StrUtil(yytext); return EXTERN; }
"sfunction"  { yylval.string_val = new StrUtil(yytext); return SFUNCTION; }
"function"   { yylval.string_val = new StrUtil(yytext); return FUNCTION; }
"return"     { yylval.string_val = new StrUtil(yytext); return RETURN; }
"print"      { yylval.string_val = new StrUtil(yytext); return UNARY_OP; }
"&"          { yylval.string_val = new StrUtil(yytext); return UNARY_OP; }
"@"          { yylval.string_val = new StrUtil(yytext); return UNARY_OP; }
"int"        { yylval.string_val = new StrUtil(yytext); return TYPE; }
"string"     { yylval.string_val = new StrUtil(yytext); return TYPE; }
"pointer"    { yylval.string_val = new StrUtil(yytext); return TYPE; }
\"[^\"]*\"   { yylval.string_val = new StrUtil(yytext); return STRING_LITERAL; }
{number}     { int temp = stoi((string)yytext, nullptr); yylval.int_val = &temp; return INT_LITERAL; }
{ident}      { yylval.string_val = new StrUtil(yytext); return ID; }
[ \t\r\f]    { /* ignore white space. */ }
[\n]         { yylineno++; }
.            { runtime_error e(string("Lexer: Line ") + to_string(yylineno) + 
                       ": Illegal character: " + yytext);
               throw e;
             }
