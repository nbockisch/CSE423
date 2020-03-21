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
//TO DO: rewrite node.h to reflect the grammar
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
//TO DO: Define types for grammer and rules that classify into it
%type <ident> 
%type <type> 
%type <expr> 
%type <varvec> 
%type <exprvec> 
%type <block> 
%type <declaration> 
%type <token>  

/* Operator precedence for mathematical operators */
%left TPLUS TMINUS
%left TMUL TDIV

%start program

//TO DO: Add new grammer and rules for C- grammer
%%

program : declarationList { root = $1; }
		
declarationList : declaration 
	| declarationList declaration 

declaration : varDeclaration | funDeclaration

varDeclaration : typeSpecifier varDeclList 

varDeclList : varDeclInitialize | varDeclList TCOMMA varDeclInitialize

varDeclInitialize : varDeclId 

varDeclId: TIDENTIFIER 
	| TIDENTIFIER TLBRACK TINTEGER TRBRACK 

typeSpecifier : TINT | TVOID

funDeclaration : typeSpecifier TIDENTIFIER TLPAREN params TRPAREN statement

params : paramList | %empty

paramList: paramList TSEMI paramTypeList | paramTypeList 

paramTypeList : typeSpecifier paramIdList

paramIdList : paramIdList TCOMMA paramId
	| paramId

paramId : TIDENTIFIER
	| TIDENTIFIER TLBRACK TRBRACK

statement : expressionStmt
	| compountStmt
	| selectionStmt
	| iterationStmt
	| returnStmt
	| breakStmt

expressionStmt : expression TSEMI | TSEMI

compoundStmt : TLBRACE localDeclarations statementList TRBRACE 

localDeclarations : localDeclarations VarDeclaration | %empty

statementList : statementList statement | %empty 

elsifList : elsifList TELSE TIF TLPAREN simpleExpresssion TRPAREN compoundStmt  
	| %empty 

selectionStmt : TIF TLPAREN simpleExpression TRPAREN compoundStmt elsiflList 
	| TIF TLPAREN simpleExpression TRPAREN compoundStmt elsifList elseHolder 

elseHolder: TELSE compoundStmt 

iterationStmt : TWHILE TLPAREN simpleExpression TRPAREN compoundStmt 
	| TFOR TLPAREN expression TSEMI simpleExpression TSEMI simpleExpression TRPAREN compoundStmt 
	
returnStmt : TRETURN TSEMI
	| TRETURN expression TSEMI

breakStmt : TBREAK TSEMI

expression : mutable TEQUAL expression | simpleExpression

simpleExpression : simpleExpression TOR andExpression | andExpression 

andExpression : andExpression TAND unaryRelExpression | unaryRelExpression

unaryRelExpression : TNOT unaryRelExpression | relExpression

relExpression : sumExpression relop sumExpression | sumExpression

relop : TCLE | TCLT | TCGT | TCGE | TCEQ | TCNE

sumExpression : sumExpression sumop mulExpression | mulExpression

sumop : TPLUS | TMINUS

mulExpression : mulExpression mulop factor | factor

mulop : TMUL | TDIV | TMOD

factor : immutable | mutable

mutable : TIDENTIFIER | mutable TLBRACK expression TRBRACK

immutable : TLPAREN expression TRPAREN | call | constant

call : TIDENTIFIER TLPAREN args TRPAREN

args : arglist | %empty

argList : argList TCOMMA expression | expression

constant : TINTEGER 
	| TDOUBLE 

%%
