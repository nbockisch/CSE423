/*code modified from this source https://gnuu.org/2009/09/18/writing-your-own-toy-compiler/*/

%{
#include <string>
#include "node.h"
#include "parser.hpp"

#define SAVE_TOKEN  yylval.string = new std::string(yytext, yyleng)
#define TOKEN(t)    (yylval.token = t)

int p_tokens;
int yycolumn = 1;

#define YY_USER_ACTION \
        yylloc.first_line = yylloc.last_line = yylineno; \
        yylloc.first_column = yycolumn; \
        yylloc.last_column = yycolumn+yyleng-1; \
        yycolumn += yyleng;
        
#define PRINT_TOK(t) \
        if(p_tokens) { \
                printf("<%s, %s>\n", yytext, t); \
        }


%}

%option noyywrap
%option yylineno
%array

%%

[ \t]                                           ;
[\n]					        yycolumn = 1;
"return"				        PRINT_TOK("TRETURN"); return TOKEN(TRETURN);
"if"						PRINT_TOK("TIF"); return TOKEN(TIF);
"else"						PRINT_TOK("TELSE"); return TOKEN(TELSE);
"while"						PRINT_TOK("TWHILE"); return TOKEN(TWHILE);
"void"						PRINT_TOK("TVOID"); SAVE_TOKEN; return TVOID;
"int"						PRINT_TOK("TINT"); SAVE_TOKEN; return TINT;
[a-zA-Z_][a-zA-Z0-9_]*  			PRINT_TOK("TIDENTIFIER"); SAVE_TOKEN; return TIDENTIFIER;
[0-9]+\.[0-9]* 			    		PRINT_TOK("TDOUBLE"); SAVE_TOKEN; return TDOUBLE;
[0-9]+					        PRINT_TOK("TINTEGER"); SAVE_TOKEN; return TINTEGER;

"="						PRINT_TOK("TEQUAL"); return TOKEN(TEQUAL);
"=="				          	PRINT_TOK("TCEQ"); return TOKEN(TCEQ);
"!="			          		PRINT_TOK("TCNE"); return TOKEN(TCNE);
"<"				          	PRINT_TOK("TCLT"); return TOKEN(TCLT);
"<="	          				PRINT_TOK("TCLE"); return TOKEN(TCLE);
">"				          	PRINT_TOK("TCGT"); return TOKEN(TCGT);
">="					        PRINT_TOK("TCGE"); return TOKEN(TCGE);

"("	          				PRINT_TOK("TLPAREN"); return TOKEN(TLPAREN);
")"					        PRINT_TOK("TRPAREN"); return TOKEN(TRPAREN);
"{"         					PRINT_TOK("TLBRACE"); return TOKEN(TLBRACE);
"}"					        PRINT_TOK("TRBRACE"); return TOKEN(TRBRACE);
"."         					PRINT_TOK("TDOT"); return TOKEN(TDOT);
","				          	PRINT_TOK("TCOMMA"); return TOKEN(TCOMMA);
"+"				          	PRINT_TOK("TPLUS"); return TOKEN(TPLUS);
"-"		          			PRINT_TOK("TMINUS"); return TOKEN(TMINUS);
"*"		          			PRINT_TOK("TMUL"); return TOKEN(TMUL);
"/"				          	PRINT_TOK("TDIV"); return TOKEN(TDIV);
";"                                             PRINT_TOK("TSEMI"); return TOKEN(TSEMI);


.                       printf("Unknown token!\n"); yyterminate();

%%
