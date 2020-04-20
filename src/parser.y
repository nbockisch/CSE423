/**
 * @file parser.y
 * @brief Grammar file and main program launcher for the compiler
 **/

/*code modified from this source https://gnuu.org/2009/09/18/writing-your-own-toy-compiler/*/

%{
    #include "node.h"
    #include "nodevisitor.h"
    #include "irvisitor.h"
    #include "printvisitor.h"
    #include "ir.h"
    #include "symtable.h"
    #include "symvisitor.h"
        #include <cstdio>
        #include <cstdlib>
    #include <iostream>
    #include <fstream>
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
    extern int yylineno;
    extern int yycolumn;
	void yyerror(const char *s) {
                std::printf("Error (line %d:%d): %s at '%s'\n", yylineno, yycolumn, s, yytext);
                std::exit(1);
        }
        
   #define YYPARSE_PARAM scanner
   #define YYLEX_PARAM scanner
%}

%locations

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
%token <token> TRETURN TIF TELSE TWHILE TFOR TBREAK TGOTO TSIZEOF

/* Define the type of node our nonterminal symbols represent.
   The types refer to the %union declaration above.
 */
%type <ident> ident
%type <type> type
%type <expr> number expr expr1 expr2 expr3
%type <varvec> func_decl_args
%type <exprvec> call_args
%type <block> program declist block 
%type <declaration> declaration var_decl func_var_decl func_decl if_decl else_decl elseif_decl
%type <token> compare prefix postfix

/* Operator precedence for mathematical operators */
%left TPLUS TMINUS
%left TMUL TDIV

%start program

%%

program : declist { root = $1; };
		
declist : declaration { $$ = new NBlock(); $$->statements.push_back($<declaration>1); }
	  | declist declaration { $1->statements.push_back($<declaration>2); };

declaration : var_decl | func_decl | expr { $$ = new NExpressionStatement(*$1); } | TRETURN expr TSEMI { $$ = new 				NReturnStatement(*$2); } | if_decl | else_decl | elseif_decl | 
			TWHILE TLPAREN expr TRPAREN block {$$ = new NWhileStatement(*$3, *$5); } 
		| TFOR TLPAREN expr1 expr2 expr3 TRPAREN block {$$ = new NForStatement(*$3, *$4, *$5, *$7); } 
		| TBREAK TSEMI {$$ = new NBreak();} | TGOTO ident TSEMI {$$ = new NGOTO(*$2);} | ident TCOLON {$$ = new NGOTOBlock(*$1);};

block : TLBRACE declist TRBRACE { $$ = $2; }
	  | TLBRACE TRBRACE { $$ = new NBlock(); };

if_decl : TIF TLPAREN expr TRPAREN block block {$$ = new NIfStatement(*$3, *$5); } | TIF TLPAREN expr TRPAREN block 
	{$$ = new NIfStatement(*$3, *$5); };

elseif_decl : TELSE TIF TLPAREN expr TRPAREN block block {$$ = new NElseIfStatement(*$4, *$6); } 
	| TELSE TIF TLPAREN expr TRPAREN block {$$ = new NElseIfStatement(*$4, *$6); };

else_decl : TELSE block {$$ = new NElseStatement(*$2); };

var_decl : type ident TSEMI { $$ = new NVariableDeclaration(*$1, *$2); } | 
		type ident TEQUAL expr TSEMI { $$ = new NVariableDeclaration(*$1, *$2, $4); };

func_var_decl : type ident { $$ = new NVariableDeclaration(*$1, *$2); };
		

func_decl : type ident TLPAREN func_decl_args TRPAREN block { $$ = new NFunctionDeclaration(*$1, *$2, *$4, *$6); delete $4; }
		| type ident TLPAREN func_decl_args TRPAREN block block { $$ = new NFunctionDeclaration(*$1, *$2, *$4, *$6); delete $4; };

func_decl_args : /*blank*/ %empty { $$ = new VariableList(); }
		  | func_var_decl { $$ = new VariableList(); $$->push_back($<var_decl>1); }
		  | func_decl_args TCOMMA func_var_decl { $1->push_back($<var_decl>3); };

ident : TIDENTIFIER { $$ = new NIdentifier(*$1); delete $1; };

type : TINT { $$ = new NType(*$1); delete $1; } | TVOID { $$ = new NType(*$1); delete $1; };

number : TINTEGER { $$ = new NInteger(atol($1->c_str())); delete $1; }
		| TDOUBLE { $$ = new NDouble(atof($1->c_str())); delete $1; };

expr1: ident TEQUAL expr TSEMI { $$ = new NAssignment(*$<ident>1, *$3); };

expr2: expr compare expr TSEMI { $$ = new NBinaryOperator(*$1, $2, *$3); };

expr3: expr postfix { $$ = new NUnaryOperator($2, *$1); };

expr : ident TEQUAL expr TSEMI { $$ = new NAssignment(*$<ident>1, *$3); }
	 | ident TLPAREN call_args TRPAREN TSEMI { $$ = new NMethodCall(*$1, *$3); delete $3; }
	 | ident { $<ident>$ = $1; } 
	 | TMINUS expr { $$ = new NUnaryOperator($1, *$2); }
	 | number
         | expr TMUL expr { $$ = new NBinaryOperator(*$1, $2, *$3); }
         | expr TDIV expr { $$ = new NBinaryOperator(*$1, $2, *$3); }
         | expr TPLUS expr { $$ = new NBinaryOperator(*$1, $2, *$3); }
         | expr TMINUS expr { $$ = new NBinaryOperator(*$1, $2, *$3); }
 	 | expr compare expr { $$ = new NBinaryOperator(*$1, $2, *$3); }
	 | prefix expr TSEMI { $$ = new NUnaryOperator($1, *$2); }
	 | expr postfix TSEMI { $$ = new NUnaryOperator($2, *$1); }
     | TLPAREN expr TRPAREN { $$ = $2; };

prefix: TINC | TDEC | TNOT | TADR;

postfix: TINC | TDEC;

call_args : /*blank*/ %empty { $$ = new ExpressionList(); }
		  | expr { $$ = new ExpressionList(); $$->push_back($1); }
		  | call_args TCOMMA expr  { $1->push_back($3); } ;

compare : TCEQ | TCNE | TCLT | TCLE | TCGT | TCGE;



%%
void usage(const char *name);

int main(int argc, char **argv)
{
    int opt;
    p_tokens = 0;
    int p_tree = 0;
    int p_ir = 0;
    int p_sym = 0;
    int ir_file = 0;
    std::string ir_out_file;
    std::string fname;
    std::vector<std::string> ir_list;
    ir *ir_gen = NULL;
    Symtable *symtab = NULL;
    FILE *ir_in;

    while ((opt = getopt(argc, argv,  ":ho:r:ptisf:ax"))  != -1) {
        switch(opt) {
            case 'h':
                usage(argv[0]);
                return 0;
            case 'f':
                // get filename and open file
                yyin = fopen(optarg, "r");
                if (!yyin) {
                    std::cout << "Failure: Couldn't open file '" << optarg << "'\n" << std::endl;
                    return -1;
                }
                break;
            case 'r':
                // get filename and open file
                ir_in = fopen(optarg, "r");
                if (!ir_in) {
                    std::cout << "Failure: Couldn't open file '" << optarg << "'\n" << std::endl;
                    return -1;
                }
                break;
            case 'o':
                // output ir to file
                ir_out_file = optarg;
                ir_file = 1;
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

    // Throw an error if no input file was specified
    if(!yyin) {
            printf("Error: an input file must be specified with -f!\n");
            return -1;
    }

    if (p_tokens) {
        std::cout << "Tokens:" << std::endl;
    }
    yyparse();
   
    // Create the symbol table using the tree visitor
    symtab = new Symtable();
    SymVisitor symvis(symtab);
    root->accept(symvis);
    
    // Generate the IR with the parse tree
    ir_gen = new ir(symtab);
    //ir_list = ir_gen->getIR();
    IrVisitor irvis(ir_gen);
    root->accept(irvis);

    for (item_t tmp : ir_gen->items) {
        if (!tmp.label.empty()) {
            std::cout << tmp.label << ", ";
        }
        if (!tmp.id.empty()) {
            std::cout << tmp.id << ", ";
        }
        for (auto test : tmp.params) {
            std::cout << test.id << ", ";
        }
        std::cout << std::endl;
    }

    // Print tree if flag used
    if (p_tree) {
        printf("-----------------------------\n");
        std::cout << "Tree:" << std::endl;
        printf("-----------------------------\n");
        PrintVisitor visitor;
        root->accept(visitor);
        std::string tree = visitor.getResult();
        printf("%s\n", tree.c_str());
        printf("-----------------------------\n");
    }

    /*if (p_ir) {
        if (ir_file == 1) {
            std::ofstream ir_out(ir_out_file);
            for (std::string ir_line : ir_list) {
                ir_out << ir_line << std::endl;
            }
            ir_out.close();
        }
        printf("-----------------------------\n");
        std::cout << "IR:" << std::endl;
        printf("-----------------------------\n");
        for (std::string ir_line : ir_list) {
            std::cout << ir_line << std::endl;
        }
        printf("-----------------------------\n");
    } */

    if (p_sym) {
        printf("-----------------------------\n");
        printf("Symbol Table: (%d total scopes)\n", symtab->getNumScopes());
        printf("-----------------------------\n");
        symtab->print();
        printf("-----------------------------\n");
    }
    
    fclose(yyin);

    // Free memory
    delete ir_gen;
    delete symtab;
    
    return 0;

}

void usage(const char *name) {
        printf("Usage: %s [-p] [-t] [-i] [-s] [-r file] [-o output] -f input\n", name);
        printf("Options:\n");
        printf("  -f file     Specify the input source file, required.\n");
        printf("  -p          Print the AST/parse tree representation.\n");
        printf("  -t          Print the token representation.\n");
        printf("  -i          Print the IR representation.\n");
        printf("  -s          Print the symbol table.\n");
        printf("  -r file     Read in an ir file.\n");
        printf("  -o file     Output ir to a file.\n");
        printf("  -h          Display this help message.\n");
}
