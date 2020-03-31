/*code modified from this source https://gnuu.org/2009/09/18/writing-your-own-toy-compiler/*/

%{
#include <string>
#include "node.h"
#include "parser2.hpp"

#define SAVE_TOKEN  yylval.string = new std::string(yytext, yyleng)
#define TOKEN(t)    (yylval.token = t)
%}

%option noyywrap

%%

[ \t\n]					        ;
"return"				        return TOKEN(TRETURN);
"break"         return TOKEN(TBREAK);
"if"						return TOKEN(TIF);
"else"						return TOKEN(TELSE);
"while"						return TOKEN(TWHILE);
"for"             return TOKEN(TFOR);
"void"						SAVE_TOKEN; return TVOID;
"int"						SAVE_TOKEN; return TINT;
[a-zA-Z_][a-zA-Z0-9_]*  			SAVE_TOKEN; return TIDENTIFIER;
[0-9]+\.[0-9]* 			    		SAVE_TOKEN; return TDOUBLE;
[0-9]+					        SAVE_TOKEN; return TINTEGER;

"="       						return TOKEN(TEQUAL);
"=="				          return TOKEN(TCEQ);
"!="			          	return TOKEN(TCNE);
"<"				          	return TOKEN(TCLT);
"<="	          			return TOKEN(TCLE);
">"				          	return TOKEN(TCGT);
">="					        return TOKEN(TCGE);

"("	          				return TOKEN(TLPAREN);
")"					          return TOKEN(TRPAREN);
"{"         					return TOKEN(TLBRACE);
"}"					          return TOKEN(TRBRACE);
"["					          return TOKEN(TLBRACK);
"]"					          return TOKEN(TRBRACK);
"."         					return TOKEN(TDOT);
","				          	return TOKEN(TCOMMA);
"+"				          	return TOKEN(TPLUS);
"-"		          			return TOKEN(TMINUS);
"*"		          			return TOKEN(TMUL);
"%"                   return TOKEN(TMOD);
"/"				          	return TOKEN(TDIV);
";"                   return TOKEN(TSEMI);
"&"                   return TOKEN(TAND);
"|"                   return TOKEN(TOR);
"!"                   return TOKEN(TNOT);

.                       printf("Unknown token!\n"); yyterminate();

%%