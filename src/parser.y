/**
 * @file parser.y
 * @brief Grammar file and main program launcher for the compiler
 **/

/*code modified from this source https://gnuu.org/2009/09/18/writing-your-own-toy-compiler/*/

%{
    #include "node.h"
    #include "nodevisitor.h"
    #include "printvisitor.h"
    #include "ir.h"
    #include "symtable.h"
    #include "symvisitor.h"
        #include <cstdio>
        #include <cstdlib>
    #include <iostream>
    #include <unistd.h>
    #include <stdio.h>
    #include <string>
	NBlock *root; /* the top level root node of our final AST */
	#ifdef YYDEBUG
  		yydebug = 1;
	#endif
    extern FILE *yyin;
	extern int yylex();
    extern char yytext[];
    extern int p_tokens;
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
%token <token> TLPAREN TRPAREN TLBRACE TRBRACE TCOMMA TDOT TSEMI TCOLON
%token <token> TPLUS TMINUS TMUL TDIV TINC TDEC TADR TNOT
%token <token> TRETURN TIF TELSE TWHILE TFOR TBREAK TGOTO 

/* Define the type of node our nonterminal symbols represent.
   The types refer to the %union declaration above.
 */
%type <ident> ident 
%type <type> type
%type <expr> number expr 
%type <varvec> func_decl_args
%type <exprvec> call_args
%type <block> program declist block
%type <declaration> declaration var_decl func_var_decl func_decl if_decl else_decl
%type <token> compare 

/* Operator precedence for mathematical operators */
%left TPLUS TMINUS
%left TMUL TDIV

%start program

%%

program : declist { root = $1; };
		
declist : declaration { $$ = new NBlock(); $$->statements.push_back($<declaration>1); }
	  | declist declaration { $1->statements.push_back($<declaration>2); };

declaration : var_decl | func_decl | expr { $$ = new NExpressionStatement(*$1); } | TRETURN expr TSEMI { $$ = new NReturnStatement(*$2); }
		| if_decl | else_decl | TWHILE expr block {$$ = new NWhileStatement(*$2, *$3); } 
		| TFOR TLPAREN expr TSEMI expr TSEMI expr TRPAREN block {$$ = new NForStatement(*$3, *$5, *$7, *$9);} 
		| TBREAK TSEMI | TGOTO ident | ident TCOLON; 

block : TLBRACE declist TRBRACE { $$ = $2; }
	  | TLBRACE TRBRACE { $$ = new NBlock(); };

if_decl : TIF expr block block {$$ = new NIfStatement(*$2, *$3); } | TIF expr block {$$ = new NIfStatement(*$2, *$3); };

else_decl : TELSE block {$$ = new NElseStatement(*$2); };

var_decl : type ident TSEMI { $$ = new NVariableDeclaration(*$1, *$2); } | 
		type ident TEQUAL expr TSEMI { $$ = new NVariableDeclaration(*$1, *$2, $4); };

func_var_decl : type ident { $$ = new NVariableDeclaration(*$1, *$2); };
		

func_decl : type ident TLPAREN func_decl_args TRPAREN block declist { $$ = new NFunctionDeclaration(*$1, *$2, *$4, *$6); delete $4; }
			| type ident TLPAREN func_decl_args TRPAREN block { $$ = new NFunctionDeclaration(*$1, *$2, *$4, *$6); delete $4; };

func_decl_args : /*blank*/  { $$ = new VariableList(); }
		  | func_var_decl { $$ = new VariableList(); $$->push_back($<var_decl>1); }
		  | func_decl_args TCOMMA func_var_decl { $1->push_back($<var_decl>3); };

ident : TIDENTIFIER { $$ = new NIdentifier(*$1); delete $1; };

type : TINT { $$ = new NType(*$1); delete $1; } | TVOID { $$ = new NType(*$1); delete $1; };

number : TINTEGER { $$ = new NInteger(atol($1->c_str())); delete $1; }
		| TDOUBLE { $$ = new NDouble(atof($1->c_str())); delete $1; };

expr : ident TEQUAL expr TSEMI { $$ = new NAssignment(*$<ident>1, *$3); }
	 | ident TLPAREN call_args TRPAREN TSEMI { $$ = new NMethodCall(*$1, *$3); delete $3; }
	 | ident { $<ident>$ = $1; }
	 | number
         | expr TMUL expr { $$ = new NBinaryOperator(*$1, $2, *$3); }
         | expr TDIV expr { $$ = new NBinaryOperator(*$1, $2, *$3); }
         | expr TPLUS expr { $$ = new NBinaryOperator(*$1, $2, *$3); }
         | expr TMINUS expr { $$ = new NBinaryOperator(*$1, $2, *$3); }
 	 | expr compare expr { $$ = new NBinaryOperator(*$1, $2, *$3); }
	 | unary expr { $$ = new NUnaryOperator($1, *$2, -1); }
	 | expr unary { $$ = new NUnaryOperator(-1, *$2, $3); }
	 | TSIZEOF TLPAREN expr TRPAREN { $$ = new NUnaryOperator($1, *$2, -1); }
     | TLPAREN expr TRPAREN { $$ = $2; };

unary: TINC | TDEC | TNOT | TADR

call_args : /*blank*/  { $$ = new ExpressionList(); }
		  | expr { $$ = new ExpressionList(); $$->push_back($1); }
		  | call_args TCOMMA expr  { $1->push_back($3); } ;

compare : TCEQ | TCNE | TCLT | TCLE | TCGT | TCGE;



%%
int main(int argc, char **argv)
{
    int opt;
    p_tokens = 0;
    int p_tree = 0;
    int p_ir = 0;
    int p_sym = 0;
    std::string fname;
    std::vector<std::string> ir_list;
    ir *ir_gen;

    while ((opt = getopt(argc, argv,  ":ptisf:ax"))  != -1) {
        switch(opt) {
            case 'f':
                // get filename and open file
                yyin = fopen(optarg, "r");
                if (!yyin) {
                    std::cout << "Failure\n" << std::endl;
                }

                break;
            case 't':
                // print out tokens 
                p_tokens = 1;
                break;
            case 'p':
                // print out the tree
                p_tree = 1;
                break;
            case 'i':
                // print out IR
                p_ir = 1;
                break;
            case 's':
                // print out the symbol table
                p_sym = 1;
                break;
        }
    }

    if (p_tokens) {
        std::cout << "Tokens:" << std::endl;
    }
    yyparse();
   
    // Generate the IR with the parse tree
    ir_gen = new ir(root);
    ir_list = ir_gen->getIR();

    // Print tree if flag used
    if (p_tree) {
        std::cout << "Tree:" << std::endl;
        PrintVisitor visitor;
        root->accept(visitor);
        std::string tree = visitor.getResult();
        printf("%s\n", tree.c_str());
    }

    if (p_ir) {
        std::cout << "IR:" << std::endl;
        for (std::string ir_line : ir_list) {
            std::cout << ir_line << std::endl;
        }
    }

    if (p_sym) {
       Symtable *symtab = new Symtable();
       SymVisitor symvis(symtab);
       root->accept(symvis);
       symtab->print();
    }
    
    fclose(yyin);
    
    return 0;

}
