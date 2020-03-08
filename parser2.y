/*code modified from this source https://gnuu.org/2009/09/18/writing-your-own-toy-compiler/*/

%{
	#include "node.h"
        #include <cstdio>
        #include <cstdlib>
	NBlock *root; /* the top level root node of our final AST */
	#ifdef YYDEBUG
  		yydebug = 1;
	#endif
	extern int yylex();
	void yyerror(const char *s) { std::printf("Error: %s\n", s);std::exit(1); }
%}

/* Represents the many different ways we can access our data */
%union {
	Node *node;
	NBlock *block;
	NExpression *expr;
	NStatement *declaration;
	NIdentifier *ident;
	NType *type;
	NVariableDeclaration *var_decl;
	std::vector<NVariableDeclaration*> *varvec;
	std::vector<NExpression*> *exprvec;
	std::string *string;
	int token;
}

/* Define our terminal symbols (tokens). This should
   match our tokens.l lex file. We also define the node type
   they represent.
 */
%token <string> TIDENTIFIER TINTEGER TDOUBLE TVOID TINT
%token <token> TCEQ TCNE TCLT TCLE TCGT TCGE TEQUAL
%token <token> TLPAREN TRPAREN TLBRACE TRBRACE TCOMMA TDOT TSEMI
%token <token> TPLUS TMINUS TMUL TDIV
%token <token> TRETURN TIF TELSE TWHILE TFOR

/* Define the type of node our nonterminal symbols represent.
   The types refer to the %union declaration above.
 */
%type <ident> ident 
%type <type> type
%type <expr> number expr 
%type <varvec> func_decl_args
%type <exprvec> call_args
%type <block> program declist block
%type <declaration> declaration var_decl func_decl if_decl else_decl for_decl local_var_decl local_func_decl local_declist local_declaration
%type <token> compare 

/* Operator precedence for mathematical operators */
%left TPLUS TMINUS
%left TMUL TDIV

%start program

%%

program : declist { root = $1; };
		
declist : declaration { $$ = new NBlock(); $$->statements.push_back($<declaration>1); }
	  | declist declaration { $1->statements.push_back($<declaration>2); };
	  
local_declist : local_declaration { $$ = NBlock(); $$->statements.push_back($<local_declaration>1); } | local_declist local_declaration { $1->statements.push_back($<local_declaration>2); };

declaration : var_decl | func_decl

local_declaration: local_var_decl | local_func_decl | expr TSEMI { $$ = new NExpressionStatement(*$1); } | TRETURN expr TSEMI { $$ = new NReturnStatement(*$2); }
		| if_decl | TWHILE TLPAREN expr TRPAREN block {$$ = new NWhileStatement(*$2, *$3); };

block : TLBRACE local_declist TRBRACE { $$ = $2; }
	  | TLBRACE TRBRACE { $$ = new NBlock(); };

if_decl : TIF TLPAREN expr TRPAREN block else_decl {$$ = new NIfStatement(*$2, *$3); } | TIF expr block {$$ = new NIfStatement(*$2, *$3); };

for_decl: TFOR TLPAREN expr TSEMI expr TSEMI expr TRPAREN block {$$ = new NForStatement(*$2, *$3, *$4, *$5); };

else_decl : TELSE block {$$ = new NElseStatement(*$2); };

var_decl : type ident { $$ = new NVariableDeclaration(*$1, *$2); }
		 | type ident TEQUAL expr TSEMI { $$ = new NVariableDeclaration(*$1, *$2, $4); };

local_var_decl : type ident { $$ = new NVariableDeclaration(*$1, *$2); }
		 | type ident TEQUAL expr TSEMI { $$ = new NVariableDeclaration(*$1, *$2, $4); };

func_decl : type ident TLPAREN func_decl_args TRPAREN block 
			{ $$ = new NFunctionDeclaration(*$1, *$2, *$4, *$6); delete $4; };
			
local_func_decl : type ident TLPAREN func_decl_args TRPAREN block 
			{ $$ = new NFunctionDeclaration(*$1, *$2, *$4, *$6); delete $4; };

func_decl_args : /*blank*/  { $$ = new VariableList(); }
		  | loca_var_decl { $$ = new VariableList(); $$->push_back($<local_var_decl>1); }
		  | func_decl_args TCOMMA local_var_decl { $1->push_back($<local_var_decl>3); };

ident : TIDENTIFIER { $$ = new NIdentifier(*$1); delete $1; };

type : TINT { $$ = new NType(*$1); delete $1; } | TVOID { $$ = new NType(*$1); delete $1; };

number : TINTEGER { $$ = new NInteger(atol($1->c_str())); delete $1; }
		| TDOUBLE { $$ = new NDouble(atof($1->c_str())); delete $1; };

expr : ident TEQUAL expr { $$ = new NAssignment(*$<ident>1, *$3); }
	 | ident TLPAREN call_args TRPAREN { $$ = new NMethodCall(*$1, *$3); delete $3; }
	 | ident { $<ident>$ = $1; }
	 | number
         | expr TMUL expr { $$ = new NBinaryOperator(*$1, $2, *$3); }
         | expr TDIV expr { $$ = new NBinaryOperator(*$1, $2, *$3); }
         | expr TPLUS expr { $$ = new NBinaryOperator(*$1, $2, *$3); }
         | expr TMINUS expr { $$ = new NBinaryOperator(*$1, $2, *$3); }
 	 | expr compare expr { $$ = new NBinaryOperator(*$1, $2, *$3); }
     | TLPAREN expr TRPAREN { $$ = $2; };

call_args : /*blank*/  { $$ = new ExpressionList(); }
		  | expr { $$ = new ExpressionList(); $$->push_back($1); }
		  | call_args TCOMMA expr  { $1->push_back($3); } ;

compare : TCEQ | TCNE | TCLT | TCLE | TCGT | TCGE;



%%
