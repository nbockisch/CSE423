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
%token <token> TLPAREN TRPAREN TLBRACE TRBRACE TCOMMA TDOT TSEMI TLBRACK TRBRACK
%token <token> TPLUS TMINUS TMUL TDIV TOR TAND TNOT TMOD 
%token <token> TRETURN TIF TELSE TWHILE TFOR TBREAK

/* Define the type of node our nonterminal symbols represent.
   The types refer to the %union declaration above.
 */
%type <ident> ident 
%type <type> type
%type <expr> number expr 
%type <varvec> func_decl_args
%type <exprvec> call_args
%type <block> program declist block
%type <declaration> declaration varDeclInitialize
%type <token> compare 

/* Operator precedence for mathematical operators */
%left TPLUS TMINUS
%left TMUL TDIV

%start program

%%

program : declarationList { root = $1; }
		
declarationList : declaration { $$ = new NBlock(); $$->statements.push_back($<declaration>1); } 
	| declarationList declaration { $1->statements.push_back($<declaration>2); }

declaration : varDeclaration | funDeclaration

varDeclaration : typeSpecifier varDeclList { $$ = new NVariableDeclaration(*$1, *$2); }

varDeclList : varDeclInitialize | varDeclList TCOMMA varDeclInitialize

varDeclInitialize : varDeclId 

varDeclId: TIDENTIFIER { $$ = new NIdentifier(*$1); delete $1; } 
	| TIDENTIFIER TLBRACK TINTEGER TRBRACK { $$ = new NIdentifier(*$1); delete $1; }

typeSpecifier : TINT { $$ = new NType(*$1); delete $1; } | TVOID { $$ = new NType(*$1); delete $1; }

funDeclaration : typeSpecifier TIDENTIFIER TLPAREN params TRPAREN statement { $$ = new NFunctionDeclaration(*$1, *$2, *$4, *$6); delete $4; }

params : paramList | %empty { $$ = new VariableList(); }

paramList: paramList TSEMI paramTypeList | paramTypeList 

paramTypeList : typeSpecifier paramIdList

paramIdList : paramIdList TCOMMA paramId { $1->push_back($<var_decl>3); } 
	| paramId { $$ = new VariableList(); $$->push_back($<var_decl>1); }

paramId : TIDENTIFIER { $$ = new NIdentifier(*$1); delete $1; } 
	| TIDENTIFIER TLBRACK TRBRACK { $$ = new NIdentifier(*$1); delete $1; }

statement : expressionStmt { $$ = new NExpressionStatement(*$1); } 
	| compountStmt
	| selectionStmt
	| iterationStmt
	| returnStmt
	| breakStmt

expressionStmt : expression TSEMI { $$ = $1; } | TSEMI

compoundStmt : TLBRACE localDeclarations statementList TRBRACE 

localDeclarations : localDeclarations VarDeclaration { $$ = new NBlock(); $$->statements.push_back($<declaration>2); } | %empty { $$ = new NBlock(); }

statementList : statementList statement { $$ = new NBlock(); $$->statements.push_back($<declaration>2); } | %empty { $$ = new NBlock(); }

elsifList : elsifList TELSE TIF TLPAREN simpleExpresssion TRPAREN compoundStmt {$$ = new NIfStatement(*$5, *$7); } 
	| %empty { $$ = new NBlock(); }

selectionStmt : TIF TLPAREN simpleExpression TRPAREN compoundStmt elsiflList {$$ = new NIfStatement(*$3, *$5); }
	| TIF TLPAREN simpleExpression TRPAREN compoundStmt elsifList elseHolder {$$ = new NIfStatement(*$3, *$5); }

elseHolder: TELSE compoundStmt {$$ = new NElseStatement(*$2); }

iterationStmt : TWHILE TLPAREN simpleExpression TRPAREN compoundStmt {$$ = new NWhileStatement(*$3, *$5); }
	| TFOR TLPAREN expression TSEMI simpleExpression TSEMI simpleExpression TRPAREN compoundStmt {$$ = new NForStatement(*$3, *$5, *$7, *$9); }
	
returnStmt : TRETURN TSEMI { $$ = new NReturnStatement(); } 
	| TRETURN expression TSEMI { $$ = new NReturnStatement(*$2); }

breakStmt : TBREAK TSEMI

expression : mutable TEQUAL expression { $$ = new NAssignment(*$1, *$3); } | simpleExpression

simpleExpression : simpleExpression TOR andExpression { $$ = new NBinaryOperator(*$1, $2, *$3); } | andExpression 

andExpression : andExpression TAND unaryRelExpression { $$ = new NBinaryOperator(*$1, $2, *$3); } | unaryRelExpression

unaryRelExpression : TNOT unaryRelExpression { $$ = new NBinaryOperator(*$1, $2); } | relExpression

relExpression : sumExpression relop sumExpression { $$ = new NBinaryOperator(*$1, $2, *$3); } | sumExpression

relop : TCLE | TCLT | TCGT | TCGE | TCEQ | TCNE

sumExpression : sumExpression sumop mulExpression { $$ = new NBinaryOperator(*$1, $2, *$3); } | mulExpression

sumop : TPLUS | TMINUS

mulExpression : mulExpression mulop factor { $$ = new NBinaryOperator(*$1, $2, *$3); } | factor

mulop : TMUL | TDIV | TMOD

factor : immutable | mutable

mutable : TIDENTIFIER { $$ = new NIdentifier(*$1); delete $1; } | mutable TLBRACK expression TRBRACK

immutable : TLPAREN expression TRPAREN | call | constant

call : TIDENTIFIER TLPAREN args TRPAREN

args : arglist | %empty

argList : argList TCOMMA expression | expression

constant : TINTEGER { $$ = new NInteger(atol($1->c_str())); delete $1; } 
	| TDOUBLE { $$ = new NDouble(atof($1->c_str())); delete $1; }

%%
