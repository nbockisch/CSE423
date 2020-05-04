/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 8 "parser.y" /* yacc.c:339  */

    #include "node.h"
    #include "nodevisitor.h"
    #include "irvisitor.h"
    #include "printvisitor.h"
    #include "ir.h"
    #include "X86.h"
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
    #define YYERROR_VERBOSE 1
	void yyerror(const char *s) {
                std::printf("Error (line %d:%d): %s at '%s'\n", yylineno, yycolumn, s, yytext);
                //std::exit(1);
        }
     
   #define YYPARSE_PARAM scanner
   #define YYLEX_PARAM scanner

        Symtable *symtab = new Symtable();
        int skip_newscope = 0;
        record_t *tmp_entry = NULL;


#line 107 "parser.cpp" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.hpp".  */
#ifndef YY_YY_PARSER_HPP_INCLUDED
# define YY_YY_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TIDENTIFIER = 258,
    TINTEGER = 259,
    TDOUBLE = 260,
    TVOID = 261,
    TINT = 262,
    TCEQ = 263,
    TCNE = 264,
    TCLT = 265,
    TCLE = 266,
    TCGT = 267,
    TCGE = 268,
    TEQUAL = 269,
    TLPAREN = 270,
    TRPAREN = 271,
    TLBRACE = 272,
    TRBRACE = 273,
    TCOMMA = 274,
    TDOT = 275,
    TSEMI = 276,
    TCOLON = 277,
    TPLUS = 278,
    TMINUS = 279,
    TMUL = 280,
    TDIV = 281,
    TINC = 282,
    TDEC = 283,
    TADR = 284,
    TNOT = 285,
    TRETURN = 286,
    TIF = 287,
    TELSE = 288,
    TWHILE = 289,
    TFOR = 290,
    TBREAK = 291,
    TGOTO = 292,
    TSIZEOF = 293
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 52 "parser.y" /* yacc.c:355  */

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

#line 200 "parser.cpp" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_PARSER_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 231 "parser.cpp" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  44
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   355

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  39
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  68
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  128

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   293

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    96,    96,    98,    99,   101,   101,   101,   101,   101,
     101,   101,   101,   102,   103,   103,   103,   106,   105,   121,
     123,   123,   126,   127,   129,   131,   150,   171,   175,   174,
     240,   241,   242,   244,   246,   246,   248,   249,   251,   253,
     255,   257,   269,   282,   294,   295,   296,   297,   298,   299,
     300,   301,   302,   303,   305,   305,   305,   305,   307,   307,
     309,   310,   311,   313,   313,   313,   313,   313,   313
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TIDENTIFIER", "TINTEGER", "TDOUBLE",
  "TVOID", "TINT", "TCEQ", "TCNE", "TCLT", "TCLE", "TCGT", "TCGE",
  "TEQUAL", "TLPAREN", "TRPAREN", "TLBRACE", "TRBRACE", "TCOMMA", "TDOT",
  "TSEMI", "TCOLON", "TPLUS", "TMINUS", "TMUL", "TDIV", "TINC", "TDEC",
  "TADR", "TNOT", "TRETURN", "TIF", "TELSE", "TWHILE", "TFOR", "TBREAK",
  "TGOTO", "TSIZEOF", "$accept", "program", "declist", "declaration",
  "block", "$@1", "if_decl", "elseif_decl", "else_decl", "var_decl",
  "func_var_decl", "func_decl", "$@2", "func_decl_args", "ident", "type",
  "number", "expr1", "expr2", "expr3", "expr", "prefix", "postfix",
  "call_args", "compare", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293
};
# endif

#define YYPACT_NINF -77

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-77)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     126,   -77,   -77,   -77,   -77,   -77,    51,    51,   -77,   -77,
     -77,   -77,    51,    -3,   -12,    -1,    13,    -2,     6,    31,
     126,   -77,   -77,   -77,   -77,   -77,   -77,    -7,     6,   -77,
     300,    51,    21,   156,   321,   165,    51,    15,    22,   -77,
      51,     6,   -77,    18,   -77,   -77,    51,    51,   -77,    -4,
     -77,   -77,   -77,   -77,   -77,   -77,    51,    51,    51,    51,
     -77,   -77,    25,    51,   186,   -77,   -77,   192,   -77,   126,
      51,   213,    29,    51,   -77,   222,   300,     2,    51,    42,
     -77,   321,   321,   327,   327,   -77,   300,   -77,    41,    91,
     243,    41,    51,    51,   300,   -77,    38,    51,   252,   -77,
       7,     6,    41,   -77,    41,   -77,   273,    44,   300,    51,
     -77,   300,   -77,   -77,    42,   -77,   -77,    41,   -77,    41,
      25,   294,    41,   -77,   -77,   -77,   -77,   -77
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    33,    36,    37,    35,    34,     0,     0,    54,    55,
      57,    56,     0,     0,     0,     0,     0,     0,     0,     0,
       2,     3,     9,    11,    10,     5,     6,    43,     0,    45,
       7,     0,    43,     0,    44,     0,     0,    17,     0,    24,
       0,     0,    14,     0,     1,     4,     0,    60,    16,     0,
      63,    64,    65,    66,    67,    68,     0,     0,     0,     0,
      58,    59,     0,     0,     0,    53,     8,     0,    19,     0,
       0,     0,     0,     0,    15,     0,    61,     0,     0,    30,
      25,    48,    49,    46,    47,    52,    50,    51,     0,     0,
       0,     0,     0,     0,     0,    41,     0,     0,     0,    31,
       0,     0,    21,    18,     0,    12,     0,     0,     0,     0,
      42,    62,    26,    28,     0,    27,    20,    23,    38,     0,
      40,     0,     0,    32,    22,    13,    39,    29
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -77,   -77,    -8,   -18,   -75,   -77,   -77,   -77,   -77,   -77,
     -52,   -77,   -77,   -77,     4,   -76,   -77,   -77,   -77,   -77,
      -6,   -77,   -45,   -77,   -29
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    19,    20,    21,    39,    69,    22,    23,    24,    25,
      99,    26,   122,   100,    32,    28,    29,    73,    93,   107,
      30,    31,    62,    77,    63
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      33,    34,    45,   101,    27,    37,    35,    46,    47,     1,
      78,    79,    36,   102,    40,    48,   105,    80,    96,    42,
      38,    97,    43,   113,    27,    64,   114,   116,    41,   117,
      67,    44,    49,    68,    71,    46,    47,    70,   101,    74,
      75,    76,   124,    92,   125,    72,    85,   127,     4,     5,
      81,    82,    83,    84,     1,     2,     3,    86,    37,   110,
     119,    89,   123,   120,    90,   109,     6,    94,     0,     0,
       0,    45,    98,    27,     0,     7,     0,     0,     8,     9,
      10,    11,     0,     0,     0,     0,   106,   108,     0,     0,
       0,   111,     0,    27,     1,     2,     3,     4,     5,     0,
       0,     0,     0,   121,     0,   115,     6,     0,     0,   103,
       0,     0,     0,     0,     0,     7,     0,     0,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,     1,
       2,     3,     4,     5,     0,     0,     0,     0,     0,     0,
       0,     6,     0,     0,     0,     0,     0,     0,     0,     0,
       7,     0,     0,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    50,    51,    52,    53,    54,    55,
       0,     0,    65,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,     0,    66,     0,    56,    57,
      58,    59,    60,    61,    50,    51,    52,    53,    54,    55,
      50,    51,    52,    53,    54,    55,     0,    87,    88,    56,
      57,    58,    59,    60,    61,    56,    57,    58,    59,    60,
      61,    50,    51,    52,    53,    54,    55,     0,     0,    91,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,     0,    95,     0,    56,    57,    58,    59,    60,
      61,    50,    51,    52,    53,    54,    55,     0,     0,   104,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,     0,   112,     0,    56,    57,    58,    59,    60,
      61,    50,    51,    52,    53,    54,    55,     0,     0,     0,
       0,     0,     0,     0,   118,     0,    56,    57,    58,    59,
      60,    61,    50,    51,    52,    53,    54,    55,    50,    51,
      52,    53,    54,    55,     0,   126,     0,    56,    57,    58,
      59,    60,    61,    56,    57,    58,    59,    60,    61,    50,
      51,    52,    53,    54,    55,    50,    51,    52,    53,    54,
      55,     0,     0,     0,     0,     0,    58,    59,    60,    61,
       0,     0,     0,     0,    60,    61
};

static const yytype_int8 yycheck[] =
{
       6,     7,    20,    79,     0,    17,    12,    14,    15,     3,
      14,    15,    15,    88,    15,    22,    91,    21,    16,    21,
      32,    19,    18,    16,    20,    31,    19,   102,    15,   104,
      36,     0,    28,    18,    40,    14,    15,    15,   114,    21,
      46,    47,   117,    14,   119,    41,    21,   122,     6,     7,
      56,    57,    58,    59,     3,     4,     5,    63,    17,    21,
      16,    69,   114,   108,    70,    94,    15,    73,    -1,    -1,
      -1,    89,    78,    69,    -1,    24,    -1,    -1,    27,    28,
      29,    30,    -1,    -1,    -1,    -1,    92,    93,    -1,    -1,
      -1,    97,    -1,    89,     3,     4,     5,     6,     7,    -1,
      -1,    -1,    -1,   109,    -1,   101,    15,    -1,    -1,    18,
      -1,    -1,    -1,    -1,    -1,    24,    -1,    -1,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,     3,
       4,     5,     6,     7,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      24,    -1,    -1,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,     8,     9,    10,    11,    12,    13,
      -1,    -1,    16,     8,     9,    10,    11,    12,    13,    23,
      24,    25,    26,    27,    28,    -1,    21,    -1,    23,    24,
      25,    26,    27,    28,     8,     9,    10,    11,    12,    13,
       8,     9,    10,    11,    12,    13,    -1,    21,    16,    23,
      24,    25,    26,    27,    28,    23,    24,    25,    26,    27,
      28,     8,     9,    10,    11,    12,    13,    -1,    -1,    16,
       8,     9,    10,    11,    12,    13,    23,    24,    25,    26,
      27,    28,    -1,    21,    -1,    23,    24,    25,    26,    27,
      28,     8,     9,    10,    11,    12,    13,    -1,    -1,    16,
       8,     9,    10,    11,    12,    13,    23,    24,    25,    26,
      27,    28,    -1,    21,    -1,    23,    24,    25,    26,    27,
      28,     8,     9,    10,    11,    12,    13,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    25,    26,
      27,    28,     8,     9,    10,    11,    12,    13,     8,     9,
      10,    11,    12,    13,    -1,    21,    -1,    23,    24,    25,
      26,    27,    28,    23,    24,    25,    26,    27,    28,     8,
       9,    10,    11,    12,    13,     8,     9,    10,    11,    12,
      13,    -1,    -1,    -1,    -1,    -1,    25,    26,    27,    28,
      -1,    -1,    -1,    -1,    27,    28
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,    15,    24,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    40,
      41,    42,    45,    46,    47,    48,    50,    53,    54,    55,
      59,    60,    53,    59,    59,    59,    15,    17,    32,    43,
      15,    15,    21,    53,     0,    42,    14,    15,    22,    53,
       8,     9,    10,    11,    12,    13,    23,    24,    25,    26,
      27,    28,    61,    63,    59,    16,    21,    59,    18,    44,
      15,    59,    53,    56,    21,    59,    59,    62,    14,    15,
      21,    59,    59,    59,    59,    21,    59,    21,    16,    41,
      59,    16,    14,    57,    59,    21,    16,    19,    59,    49,
      52,    54,    43,    18,    16,    43,    59,    58,    59,    63,
      21,    59,    21,    16,    19,    53,    43,    43,    21,    16,
      61,    59,    51,    49,    43,    43,    21,    43
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    39,    40,    41,    41,    42,    42,    42,    42,    42,
      42,    42,    42,    42,    42,    42,    42,    44,    43,    43,
      45,    45,    46,    46,    47,    48,    48,    49,    51,    50,
      52,    52,    52,    53,    54,    54,    55,    55,    56,    57,
      58,    59,    59,    59,    59,    59,    59,    59,    59,    59,
      59,    59,    59,    59,    60,    60,    60,    60,    61,    61,
      62,    62,    62,    63,    63,    63,    63,    63,    63
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     1,     3,     1,
       1,     1,     5,     7,     2,     3,     2,     0,     4,     2,
       6,     5,     7,     6,     2,     3,     5,     2,     0,     7,
       0,     1,     3,     1,     1,     1,     1,     1,     4,     4,
       2,     4,     5,     1,     2,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     1,     1,     1,     1,     1,     1,
       0,     1,     3,     1,     1,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);

        yyls = yyls1;
        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 96 "parser.y" /* yacc.c:1646  */
    { root = (yyvsp[0].block); }
#line 1534 "parser.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 98 "parser.y" /* yacc.c:1646  */
    { (yyval.block) = new NBlock(); (yyval.block)->statements.push_back((yyvsp[0].declaration)); }
#line 1540 "parser.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 99 "parser.y" /* yacc.c:1646  */
    { (yyvsp[-1].block)->statements.push_back((yyvsp[0].declaration)); }
#line 1546 "parser.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 101 "parser.y" /* yacc.c:1646  */
    { (yyval.declaration) = new NExpressionStatement(*(yyvsp[0].expr)); }
#line 1552 "parser.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 101 "parser.y" /* yacc.c:1646  */
    { (yyval.declaration) = new NReturnStatement(*(yyvsp[-1].expr)); }
#line 1558 "parser.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 101 "parser.y" /* yacc.c:1646  */
    {(yyval.declaration) = new NWhileStatement(*(yyvsp[-2].expr), *(yyvsp[0].block)); }
#line 1564 "parser.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 102 "parser.y" /* yacc.c:1646  */
    {(yyval.declaration) = new NForStatement(*(yyvsp[-4].expr), *(yyvsp[-3].expr), *(yyvsp[-2].expr), *(yyvsp[0].block)); }
#line 1570 "parser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 103 "parser.y" /* yacc.c:1646  */
    {(yyval.declaration) = new NBreak();}
#line 1576 "parser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 103 "parser.y" /* yacc.c:1646  */
    {(yyval.declaration) = new NGOTO(*(yyvsp[-1].ident));}
#line 1582 "parser.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 103 "parser.y" /* yacc.c:1646  */
    {(yyval.declaration) = new NGOTOBlock(*(yyvsp[-1].ident));}
#line 1588 "parser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 106 "parser.y" /* yacc.c:1646  */
    {
                /* Check if this flag set.. skips making new scope when making functions.. see func_decl */
                if(!skip_newscope) {
                        //printf("Creating new scope..\n");
                        symtab->initializeScope();
                }
        }
#line 1600 "parser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 114 "parser.y" /* yacc.c:1646  */
    {
                (yyval.block) = (yyvsp[-1].block);
                if(!skip_newscope) {
                        //printf("Finalizing scope..\n");
                        symtab->finalizeScope();
                }
        }
#line 1612 "parser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 121 "parser.y" /* yacc.c:1646  */
    { /* Dont need new scope since empty block? */ (yyval.block) = new NBlock(); }
#line 1618 "parser.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 123 "parser.y" /* yacc.c:1646  */
    {(yyval.declaration) = new NIfStatement(*(yyvsp[-3].expr), *(yyvsp[-1].block)); }
#line 1624 "parser.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 124 "parser.y" /* yacc.c:1646  */
    {(yyval.declaration) = new NIfStatement(*(yyvsp[-2].expr), *(yyvsp[0].block)); }
#line 1630 "parser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 126 "parser.y" /* yacc.c:1646  */
    {(yyval.declaration) = new NElseIfStatement(*(yyvsp[-3].expr), *(yyvsp[-1].block)); }
#line 1636 "parser.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 127 "parser.y" /* yacc.c:1646  */
    {(yyval.declaration) = new NElseIfStatement(*(yyvsp[-2].expr), *(yyvsp[0].block)); }
#line 1642 "parser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 129 "parser.y" /* yacc.c:1646  */
    {(yyval.declaration) = new NElseStatement(*(yyvsp[0].block)); }
#line 1648 "parser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 132 "parser.y" /* yacc.c:1646  */
    {
                   /* Check if defined in symtable first */
                   //printf("Checking symtable for name '%s'\n", $2->name.c_str());
                   if(symtab->lookup((yyvsp[-1].ident)->name) == NULL) {
                           record_t entry;
                           entry.name = (yyvsp[-1].ident)->name;
                           entry.rtype = record_type::variable;
                           entry.type = (yyvsp[-2].type)->name;
                                              
                           (yyval.declaration) = new NVariableDeclaration(*(yyvsp[-2].type), *(yyvsp[-1].ident));
                           entry.node = (yyval.declaration);

                           symtab->insert(entry.name, entry);
                   } else {
                           std::string str("redeclaration of variable '"+(yyvsp[-1].ident)->name+"'");
                           yyerror(str.c_str());
                           YYABORT;
                   }
           }
#line 1672 "parser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 151 "parser.y" /* yacc.c:1646  */
    {
                   /* Check if defined in symtable first */
                   //printf("Checking symtable for name '%s'\n", $2->name.c_str());
                   if(symtab->lookup((yyvsp[-3].ident)->name) == NULL) {
                           record_t entry;
                           entry.name = (yyvsp[-3].ident)->name;
                           entry.rtype = record_type::variable;
                           entry.type = (yyvsp[-4].type)->name;
                                              
                           (yyval.declaration) = new NVariableDeclaration(*(yyvsp[-4].type), *(yyvsp[-3].ident), (yyvsp[-1].expr));
                           entry.node = (yyval.declaration);

                           symtab->insert(entry.name, entry);
                   } else {
                           std::string str("redeclaration of variable '"+(yyvsp[-3].ident)->name+"'");
                           yyerror(str.c_str());
                           YYABORT;
                   }
           }
#line 1696 "parser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 171 "parser.y" /* yacc.c:1646  */
    { (yyval.declaration) = new NVariableDeclaration(*(yyvsp[-1].type), *(yyvsp[0].ident)); }
#line 1702 "parser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 175 "parser.y" /* yacc.c:1646  */
    {
                    /* Check if defined in symtable first */
                    //printf("Checking symtable for function name '%s'\n", $2->name.c_str());
                    if(symtab->lookup((yyvsp[-3].ident)->name) == NULL) {

                            tmp_entry = new record_t();
                            tmp_entry->name = (yyvsp[-3].ident)->name;
                            tmp_entry->rtype = record_type::function;
                            tmp_entry->type = (yyvsp[-4].type)->name;

                            symtab->insert(tmp_entry->name, *tmp_entry);

                            /* Create a scope for the function. We do this here since the
                               function block always creates a scope, but if the function has
                               arguments, then we want the block to be in the same scope as
                               the arguments. */
                            symtab->initializeScope();
                            if((yyvsp[-1].varvec)->size() != 0) {
                                    /* Add all function arguments to the function's scope */
                                    for (auto var : *(yyvsp[-1].varvec)) {
                                            record_t entry;
                                            entry.name = var->id.name;
                                            entry.rtype = record_type::funcarg;
                                            entry.type = var->type.name;
                                            entry.node = var;
                                
                                            symtab->insert(entry.name, entry);
                                    }
                            }
                            
                            /* If function name is unique, then we are going to set 
                               symbol table skip_newscope flag to true, so that 
                               processing the block does not create a new scope.
                               There is probably a better way to do this.. but it works for now. */
                            skip_newscope = 1;
                    } else {
                            std::string str("redeclaration of function '"+(yyvsp[-3].ident)->name+"'");
                            yyerror(str.c_str());
                            YYABORT;
                    }
            }
#line 1748 "parser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 217 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.declaration) = new NFunctionDeclaration(*(yyvsp[-6].type), *(yyvsp[-5].ident), *(yyvsp[-3].varvec), *(yyvsp[0].block));
                    
                    tmp_entry->node = (yyval.declaration);
                    
                    /* After the block has been processed, we need to finish the function's scope */
                    symtab->finalizeScope();

                    skip_newscope = 0;

                    delete tmp_entry;

                    delete (yyvsp[-3].varvec);

            }
#line 1768 "parser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 240 "parser.y" /* yacc.c:1646  */
    { (yyval.varvec) = new VariableList(); }
#line 1774 "parser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 241 "parser.y" /* yacc.c:1646  */
    { (yyval.varvec) = new VariableList(); (yyval.varvec)->push_back((yyvsp[0].var_decl)); }
#line 1780 "parser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 242 "parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].varvec)->push_back((yyvsp[0].var_decl)); }
#line 1786 "parser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 244 "parser.y" /* yacc.c:1646  */
    { (yyval.ident) = new NIdentifier(*(yyvsp[0].string)); delete (yyvsp[0].string); }
#line 1792 "parser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 246 "parser.y" /* yacc.c:1646  */
    { (yyval.type) = new NType(*(yyvsp[0].string)); delete (yyvsp[0].string); }
#line 1798 "parser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 246 "parser.y" /* yacc.c:1646  */
    { (yyval.type) = new NType(*(yyvsp[0].string)); delete (yyvsp[0].string); }
#line 1804 "parser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 248 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new NInteger(atol((yyvsp[0].string)->c_str())); delete (yyvsp[0].string); }
#line 1810 "parser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 249 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new NDouble(atof((yyvsp[0].string)->c_str())); delete (yyvsp[0].string); }
#line 1816 "parser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 251 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new NAssignment(*(yyvsp[-3].ident), *(yyvsp[-1].expr)); }
#line 1822 "parser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 253 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new NBinaryOperator(*(yyvsp[-3].expr), (yyvsp[-2].token), *(yyvsp[-1].expr)); }
#line 1828 "parser.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 255 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new NUnaryOperator((yyvsp[0].token), *(yyvsp[-1].expr)); }
#line 1834 "parser.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 258 "parser.y" /* yacc.c:1646  */
    {
               /* See if the identifier exists in the symbol table, if it doesnt, then throw error */
               //printf("expr: checking symtable for '%s'\n", $1->name.c_str());
               if(symtab->lookup((yyvsp[-3].ident)->name) == NULL) {
                       std::string str("undefined reference to name '"+(yyvsp[-3].ident)->name+"'");
                       yyerror(str.c_str());
                       YYABORT;
               } else {
                       (yyval.expr) = new NAssignment(*(yyvsp[-3].ident), *(yyvsp[-1].expr));
               }
       }
#line 1850 "parser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 270 "parser.y" /* yacc.c:1646  */
    {
               /* See if the function call exists in the symbol table, if it doesnt, then throw error */
               //printf("expr: checking symtable for function call '%s'\n", $1->name.c_str());
               if(symtab->lookup((yyvsp[-4].ident)->name) == NULL) {
                       std::string str("undefined reference to function '"+(yyvsp[-4].ident)->name+"'");
                       yyerror(str.c_str());
                       YYABORT;
               } else {
                       (yyval.expr) = new NMethodCall(*(yyvsp[-4].ident), *(yyvsp[-2].exprvec));
                       delete (yyvsp[-2].exprvec);
               }
         }
#line 1867 "parser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 283 "parser.y" /* yacc.c:1646  */
    {
                 /* See if the identifier exists in the symbol table, if it doesnt, then throw error */
                 //printf("expr ident: checking symtable for '%s'\n", $1->name.c_str());
                 if(symtab->lookup((yyvsp[0].ident)->name) == NULL) {
                         std::string str("undefined reference to name '"+(yyvsp[0].ident)->name+"'");
                         yyerror(str.c_str());
                         YYABORT;
                 } else {
                         (yyval.ident) = (yyvsp[0].ident);
                 }
         }
#line 1883 "parser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 294 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new NUnaryOperator((yyvsp[-1].token), *(yyvsp[0].expr)); }
#line 1889 "parser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 296 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new NBinaryOperator(*(yyvsp[-2].expr), (yyvsp[-1].token), *(yyvsp[0].expr)); }
#line 1895 "parser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 297 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new NBinaryOperator(*(yyvsp[-2].expr), (yyvsp[-1].token), *(yyvsp[0].expr)); }
#line 1901 "parser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 298 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new NBinaryOperator(*(yyvsp[-2].expr), (yyvsp[-1].token), *(yyvsp[0].expr)); }
#line 1907 "parser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 299 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new NBinaryOperator(*(yyvsp[-2].expr), (yyvsp[-1].token), *(yyvsp[0].expr)); }
#line 1913 "parser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 300 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new NBinaryOperator(*(yyvsp[-2].expr), (yyvsp[-1].token), *(yyvsp[0].expr)); }
#line 1919 "parser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 301 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new NUnaryOperator((yyvsp[-2].token), *(yyvsp[-1].expr)); }
#line 1925 "parser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 302 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new NUnaryOperator((yyvsp[-1].token), *(yyvsp[-2].expr)); }
#line 1931 "parser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 303 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[-1].expr); }
#line 1937 "parser.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 309 "parser.y" /* yacc.c:1646  */
    { (yyval.exprvec) = new ExpressionList(); }
#line 1943 "parser.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 310 "parser.y" /* yacc.c:1646  */
    { (yyval.exprvec) = new ExpressionList(); (yyval.exprvec)->push_back((yyvsp[0].expr)); }
#line 1949 "parser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 311 "parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].exprvec)->push_back((yyvsp[0].expr)); }
#line 1955 "parser.cpp" /* yacc.c:1646  */
    break;


#line 1959 "parser.cpp" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[1] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 317 "parser.y" /* yacc.c:1906  */


#ifdef RUN_TESTS
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#endif

void usage(const char *name);

int p_opt = 0;
int main(int argc, char **argv)
{
    int opt;
    p_tokens = 0;
    int p_tree = 0;
    int p_ir = 0;
    int r_ir = 0;
    int p_sym = 0;
    int p_ass = 0;
    int ir_file = 0;
    std::string ir_out_file;
    std::string fname;
    std::vector<std::string> ir_list;
    std::vector<item_t> generated_ir;
    ir *ir_gen = NULL;
    //Symtable *symtab = NULL;
    std::string ir_in;

    #ifdef RUN_TESTS
    printf("Setting up catch\n");
    Catch::Session session;
    session.run();
    return 0;
    #endif

    while ((opt = getopt(argc, argv,  ":ho:r:ptisaf:ax"))  != -1) {
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
                ir_in = optarg;
                r_ir = 1;
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
	    case 'a':
                // create the assembly file
                p_ass = 1;
		
	    case 'z':
	    	//runs optimization code
		p_opt = 1;
        }
    }

    // Throw an error if no input file was specified
    if(!yyin && (r_ir == 0)) {
            printf("Error: an input file must be specified with -f or -r!\n");
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

    if (r_ir) {
        generated_ir = ir_gen->readIR(ir_in);
    } else {
        generated_ir = ir_gen->buildIr();
    }

    if (ir_file) {
        ir_gen->writeIR(ir_out_file, generated_ir);
    }

        

   /* for (item_t tmp : ir_gen->items) {
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
    }*/

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

    if (p_ir) {
            /**
        if (ir_file == 1) {
            std::ofstream ir_out(ir_out_file);
            for (std::string ir_line : ir_list) {
                ir_out << ir_line << std::endl;
            }
            ir_out.close();
            }**/
        printf("-----------------------------\n");
        std::cout << "IR:" << std::endl;
        printf("-----------------------------\n");
        std::string ir_out = ir_gen->printIR(generated_ir);
        printf("%s\n", ir_out.c_str());
        printf("-----------------------------\n");
    } 

    if (p_sym) {
        printf("-----------------------------\n");
        printf("Symbol Table: (%d total scopes)\n", symtab->getNumScopes());
        printf("-----------------------------\n");
        symtab->print();
        printf("-----------------------------\n");
    }

    if (p_ass) {
    	//generate assembly file
	X86 *assembly = new X86();
	assembly->initVariables(symtab, generated_ir);
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

#ifdef RUN_TESTS
/*
 * Helper function to open the given string as a file pointer for read only.
 */
FILE *strToFile(char *str) {
        return fmemopen(str, strlen(str), "r");
}

TEST_CASE("Testing language features", "[lang]") {
        symtab = new Symtable();
        
        SECTION( "testing function declarations" ) {
                char *text = "int main() { }";
                yyin = strToFile(text);
                REQUIRE(yyparse() == 0);
                fclose(yyin);
        }

        SECTION( "testing variable declarations" ) {
                char *text = "int main() { int x = 0; }";
                yyin = strToFile(text);
                REQUIRE(yyparse() == 0);
                fclose(yyin);
        }

        SECTION( "testing variable usage inside function") {
                char *text = "int main(int x) { return x; }";
                yyin = strToFile(text);
                REQUIRE(yyparse() == 0);
                fclose(yyin);
        }
        SECTION( "testing multiple function declarations") {
                char *text = "int test(int x) { return x; } int main(int argc) { test(5); }";
                yyin = strToFile(text);
                REQUIRE(yyparse() == 0);
                fclose(yyin);
        }
        SECTION( "testing function call from nested scopes") {
                char *text = "int test(int x) { return x; } int main(int argc) { int x = 1; if (x == 1) { x = test(5); } }";
                yyin = strToFile(text);
                REQUIRE(yyparse() == 0);
                fclose(yyin);
        }
}
TEST_CASE("Testing language semantics") {
        symtab = new Symtable();
        
        SECTION("seeing if assigning non-integer (character) to integer throws an error") {
                char *text = "int main() { int x = 't'; }";
                yyin = strToFile(text);
                REQUIRE(yyparse() == 1);
                fclose(yyin);
        }
        SECTION("seeing if assigning non-integer (double) to integer throws an error") {
                char *text = "int main() { int x = 5.999; }";
                yyin = strToFile(text);
                REQUIRE(yyparse() == 1);
                fclose(yyin);
        }
        SECTION("seeing if assigning non-integer (undefined ref) to integer throws an error") {
                char *text = "int main() { int x = garbage; }";
                yyin = strToFile(text);
                REQUIRE(yyparse() == 1);
                fclose(yyin);
        }
        SECTION("seeing if unsupported type throws an error") {
                char *text = "int main() { newtype y; }";
                yyin = strToFile(text);
                REQUIRE(yyparse() == 1);
                fclose(yyin);
        }
        SECTION("seeing if random undefined reference in code throws an error") {
                char *text = "int main() { int x = 0; nonsense }";
                yyin = strToFile(text);
                REQUIRE(yyparse() == 1);
                fclose(yyin);
        }
        SECTION("seeing if calling undefined function throws an error") {
                char *text = "int main() { func(); }";
                yyin = strToFile(text);
                REQUIRE(yyparse() == 1);
                fclose(yyin);
        }
        SECTION("seeing if calling function with mismatched args throws an error") {
                char *text = "int func(int x, int y) { return x + y; } int main() { int x = func(2); }";
                yyin = strToFile(text);
                REQUIRE(yyparse() == 1);
                fclose(yyin);
        }
        SECTION("seeing if redeclaring existing variable throws an error") {
                char *text = "int main() { int x = 1; int x = 2; }";
                yyin = strToFile(text);
                REQUIRE(yyparse() == 1);
                fclose(yyin);
        }
        SECTION("seeing if redeclaring existing function throws an error") {
                char *text = "int func(int x, int y) { return 0; } int func(int x, int y) { return x + y; }";
                yyin = strToFile(text);
                REQUIRE(yyparse() == 1);
                fclose(yyin);
        }
        SECTION("seeing if referencing undeclared variables throw an error") {
                char *text = "int main() { int x = 5; x = y + 2; }";
                yyin = strToFile(text);
                REQUIRE(yyparse() == 1); // Make sure parser returns ERROR!
                fclose(yyin);
        }
}
#endif
