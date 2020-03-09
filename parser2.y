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
%token <string> TIDENTIFIER TINTEGER TDOUBLE TVOID TINT TSTATIC
%token <token> TCEQ TCNE TCLT TCLE TCGT TCGE TEQUAL
%token <token> TLPAREN TRPAREN TLBRACE TRBRACE TCOMMA TDOT TSEMI TCOLON TLBRACK TRBRACK
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

program : declarationList { root = $1; };
		
declarationList : declaration { $$ = new NBlock(); $$->statements.push_back($<declaration>1); }
	  | declarationList declaration { $1->statements.push_back($<declaration>2); };

declaration : varDeclaration | funDeclaration

varDeclaration : typeSpecifier varDeclList

scopedVarDeclaration : scopedTypeSpecifier varDeclList

varDeclList : varDeclInitialize { $$ = NBlock(); $$->statements.push_back($<varDeclInitialize>1); } | varDeclList TCOMMA varDeclInitialize { $1->statements.push_back($<varDeclInitialize>2); };

varDeclInitialize : varDeclId | varDeclId TCOLON simpleExpression

varDeclId: TIDENTIFIER { $$ = new NIdentifier(*$1); delete $1; }; 
	| TIDENTIFIER { $$ = new NIdentifier(*$1); delete $1; } TLBRACK TINTEGER { $$ = new NInteger(atol($1->c_str())); delete $1; } TRBRACK
	
scopedTypeSpecifier : TSTATIC typeSpecifier | typeSpecifier

typeSpecifier : TINT { $$ = new NType(*$1); delete $1; }

funDeclaration : typeSpecifier TIDENTIFIER TLPAREN params TRPAREN statement | TIDENTIFIER TLPAREN params TRPAREN statement

params : paramList | /*blank*/  { $$ = new VariableList(); }

paramList: paramList TSEMI paramTypeList | paramTypeList 

paramTypeList : typeSpecifier paramIdList

paramIdList : paramIdList TCOMMA paramId | paramId

paramId : TIDENTIFIER { $$ = new NIdentifier(*$1); delete $1; } | TIDENTIFIER { $$ = new NIdentifier(*$1); delete $1; } TLBRACK TRBRACK

statement : expressionStmt | compountStmt | selectionStmt | iterationStmt | returnStmt | breakStmt

expressionStmt : expression TSEMI | TSEMI

compoundStmt : TLBRACE localDeclarations statementList TRBRACE

localDeclarations : localDeclarations scopedVarDeclaration | /*blank*/

statementList : statementList statement | /*blank*/

elsifList : elsifList TELSE TIF TLPAREN simpleExpresssion TRPAREN compoundStmt | /*blank*/

selectionStmt : TIF TLPAREN simpleExpression TRPAREN compoundStmt elsiflList 
	| TIF TLPAREN simpleExpression TRPAREN compoundStmt elsifList TELSE compoundStmt

iterationStmt : TWHILE TLPAREN simpleExpression TRPAREN compoundStmt 
	| TFOR TLPAREN expression TSEMI simpleExpression TSEMI simpleExpression TRPAREN compoundStmt
	
returnStmt : TRETURN TSEMI | TRETURN expression TSEMI

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

mutable : TIDENTIFIER { $$ = new NIdentifier(*$1); delete $1; } | mutable TLBRACK expression TRBRACK

immutable : TLPAREN expression TRPAREN | call | constant

call : TIDENTIFIER TLPAREN args TRPAREN

args : arglist | /*blank*/

argList : argList TCOMMA expression | expression

constant : TINTEGER { $$ = new NInteger(atol($1->c_str())); delete $1; }
	| TDOUBLE { $$ = new NDouble(atof($1->c_str())); delete $1; };

%%
