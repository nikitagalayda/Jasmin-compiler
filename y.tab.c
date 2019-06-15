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
#line 2 "compiler_hw3.y" /* yacc.c:339  */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "jlib.h"

extern void yyerror(char*);

// typedef struct func_node {
//     char name[64];
//     struct func_node* next;
// } func_node_t;

typedef struct node {
    char name[64];
    char entry_type[16];
    char data_type[16];
    int scope_level;
    char formal_param[256];
    struct node* next;
    bool f_decl;
    int reg_id;
} node_t;

bool udecl_func = false;
bool check_undeclared = false;
node_t* symbol_table[10];
int curr_scope = 0;
char curr_dtype[16];
char curr_etype[16];
char* params;
bool parsing_func = false;
bool semantic_error = false;
bool function_error = false;
char error_msg[128];
char error_cause_name[32];
node_t* curr_node;
char func_def_param_types[32] = {0};
FILE *jasmine_file;


#define TRAVERSE_LIST(i) for(node_t* it = symbol_table[i]; it; it=it->next)
#define TRAVERSE_LIST_AFTER_HEAD(i) for(node_t* it = symbol_table[i]->next; it; it=it->next)
#define TRAVERSE_SCOPE_AFTER_HEAD(i) for(node_t* it = symbol_table[i]->next; it; it=it->next)
//#define TRAVERSE_FUNC_LIST for(func_node_t* it = decl_func_head; it; it=it->next)

extern int yylineno;
extern int yylex();
extern char* yytext;   // Get current token from lex
extern char buf[1024];  // Get current code line from lex

/* Symbol table function - you can add new function if needed. */
void yyerror(char*);
int lookup_symbol(char*, int);
void create_symbol();
void insert_symbol(char*, char*, char*, int);
void dump_symbol(bool);
void set_err_msg(bool, bool, char*);
void erase_table_scope(int);
int find_highest_reg(int);
int find_var_reg(char*, int);
//void add_func_name(char*);

#line 131 "y.tab.c" /* yacc.c:339  */

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
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    ADD = 258,
    SUB = 259,
    MUL = 260,
    DIV = 261,
    MOD = 262,
    INC = 263,
    DEC = 264,
    MT = 265,
    LT = 266,
    MTE = 267,
    LTE = 268,
    EQ = 269,
    NE = 270,
    ASGN = 271,
    ADDASGN = 272,
    SUBASGN = 273,
    MULASGN = 274,
    DIVASGN = 275,
    MODASGN = 276,
    AND = 277,
    OR = 278,
    NOT = 279,
    LB = 280,
    RB = 281,
    LCB = 282,
    RCB = 283,
    LSB = 284,
    RSB = 285,
    COMMA = 286,
    PRINT = 287,
    IF = 288,
    ELSE = 289,
    FOR = 290,
    WHILE = 291,
    ID = 292,
    SEMICOLON = 293,
    RET = 294,
    QUOTA = 295,
    INT = 296,
    FLOAT = 297,
    STRING = 298,
    VOID = 299,
    BOOL = 300,
    I_CONST = 301,
    F_CONST = 302,
    STR_CONST = 303,
    TRUE = 304,
    FALSE = 305
  };
#endif
/* Tokens.  */
#define ADD 258
#define SUB 259
#define MUL 260
#define DIV 261
#define MOD 262
#define INC 263
#define DEC 264
#define MT 265
#define LT 266
#define MTE 267
#define LTE 268
#define EQ 269
#define NE 270
#define ASGN 271
#define ADDASGN 272
#define SUBASGN 273
#define MULASGN 274
#define DIVASGN 275
#define MODASGN 276
#define AND 277
#define OR 278
#define NOT 279
#define LB 280
#define RB 281
#define LCB 282
#define RCB 283
#define LSB 284
#define RSB 285
#define COMMA 286
#define PRINT 287
#define IF 288
#define ELSE 289
#define FOR 290
#define WHILE 291
#define ID 292
#define SEMICOLON 293
#define RET 294
#define QUOTA 295
#define INT 296
#define FLOAT 297
#define STRING 298
#define VOID 299
#define BOOL 300
#define I_CONST 301
#define F_CONST 302
#define STR_CONST 303
#define TRUE 304
#define FALSE 305

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 70 "compiler_hw3.y" /* yacc.c:355  */

    int i_val;
    double f_val;
    char string[32];
    _Bool bool_val;

#line 278 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 295 "y.tab.c" /* yacc.c:358  */

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
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   376

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  51
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  33
/* YYNRULES -- Number of rules.  */
#define YYNRULES  93
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  152

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   305

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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   126,   126,   127,   131,   132,   133,   134,   135,   136,
     137,   142,   143,   147,   155,   163,   167,   174,   178,   185,
     190,   194,   194,   195,   195,   199,   200,   204,   208,   209,
     213,   214,   218,   219,   222,   228,   234,   239,   244,   249,
     257,   258,   259,   263,   266,   270,   273,   279,   280,   281,
     295,   296,   303,   304,   305,   309,   310,   311,   312,   328,
     329,   330,   331,   332,   333,   337,   340,   341,   342,   346,
     347,   351,   354,   361,   367,   368,   372,   373,   395,   398,
     401,   404,   407,   410,   416,   417,   421,   422,   427,   428,
     429,   430,   431,   435
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ADD", "SUB", "MUL", "DIV", "MOD", "INC",
  "DEC", "MT", "LT", "MTE", "LTE", "EQ", "NE", "ASGN", "ADDASGN",
  "SUBASGN", "MULASGN", "DIVASGN", "MODASGN", "AND", "OR", "NOT", "LB",
  "RB", "LCB", "RCB", "LSB", "RSB", "COMMA", "PRINT", "IF", "ELSE", "FOR",
  "WHILE", "ID", "SEMICOLON", "RET", "QUOTA", "INT", "FLOAT", "STRING",
  "VOID", "BOOL", "I_CONST", "F_CONST", "STR_CONST", "TRUE", "FALSE",
  "$accept", "program", "stat", "return_expression", "declaration",
  "func_item_list", "func_item", "compound_stat", "$@1", "$@2",
  "block_item_list", "block_item", "expression_stat", "print_func",
  "primary_expression", "constant", "unary_operator", "expression",
  "assignment_expression", "logical_expression", "relational_expression",
  "additive_expression", "multiplicative_expression",
  "relational_operator", "unary_expression", "cast_expression",
  "postfix_expression", "argument_expression_list", "assignment_operator",
  "selection_statement", "iteration_statement", "type", "id_expression", YY_NULLPTR
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305
};
# endif

#define YYPACT_NINF -119

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-119)))

#define YYTABLE_NINF -22

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -119,   101,  -119,  -119,  -119,   307,   307,  -119,   245,   -19,
      -2,    23,    26,    39,  -119,  -119,    16,   -27,  -119,  -119,
    -119,  -119,  -119,  -119,  -119,  -119,  -119,  -119,  -119,  -119,
    -119,  -119,  -119,  -119,  -119,   326,   -26,  -119,    47,   150,
      69,    52,   151,  -119,     8,  -119,  -119,     0,   326,  -119,
    -119,    -4,    62,    61,   197,    46,   326,    75,   326,  -119,
      53,    50,  -119,  -119,   326,  -119,   326,   326,  -119,  -119,
    -119,  -119,  -119,  -119,   326,   326,   326,   326,   326,   326,
    -119,  -119,  -119,  -119,  -119,  -119,   326,  -119,  -119,   272,
    -119,   -12,  -119,   326,  -119,  -119,   149,  -119,    49,     6,
       3,   299,     4,  -119,  -119,  -119,   150,   150,    69,    52,
      52,  -119,  -119,  -119,    47,  -119,  -119,    12,   326,    75,
    -119,  -119,  -119,  -119,    58,    64,    72,   326,    72,  -119,
     326,   -20,    13,  -119,     0,    74,  -119,    73,    29,  -119,
    -119,  -119,    65,    75,  -119,    68,    72,  -119,  -119,  -119,
    -119,  -119
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     1,    40,    41,     0,     0,    42,     0,    23,
       0,     0,     0,     0,    32,    28,     0,     0,    88,    89,
      91,    92,    90,    36,    35,    38,    39,     2,    10,     4,
       5,     6,     7,    71,    33,     0,     0,    43,    46,    49,
      51,    52,    69,    55,    65,     8,     9,     0,     0,    66,
      67,     0,     0,     0,     0,     0,     0,     0,     0,    11,
       0,     0,    69,    68,     0,    29,     0,     0,    59,    60,
      61,    62,    63,    64,     0,     0,     0,     0,     0,     0,
      78,    79,    80,    81,    82,    83,     0,    74,    75,     0,
      93,     0,    34,     0,    22,    27,     0,    25,     0,     0,
       0,     0,     0,    12,    37,    44,    48,    47,    50,    53,
      54,    56,    57,    58,    45,    72,    76,     0,     0,    20,
      14,    70,    24,    26,     0,     0,     0,     0,     0,    73,
       0,     0,     0,    18,     0,    37,    31,    85,     0,    86,
      77,    13,    15,    20,    19,     0,     0,    87,    16,    17,
      30,    84
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -119,  -119,   107,  -119,    56,  -119,   -29,  -118,  -119,  -119,
    -119,    27,    21,  -119,  -119,  -119,  -119,    -6,   -15,    38,
      15,    55,     9,  -119,     1,   -32,    76,  -119,  -119,  -119,
    -119,    -8,    -7
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    95,    28,    29,   132,   133,    30,    53,    54,
      96,    97,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    74,    42,    43,    44,   117,    86,    45,
      46,    47,    91
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      52,    60,    51,    63,   118,    64,    49,    50,   137,   -21,
     139,    64,    65,   119,    87,    88,    87,    88,   141,     3,
       4,    61,    92,    55,     5,     6,   120,    64,   151,   126,
     128,    89,   125,    89,    64,    64,    62,    90,   129,   142,
       7,     8,    51,   130,   143,   111,   112,   113,    56,   105,
     100,    57,   102,    14,    59,   147,    17,    77,    78,    79,
      64,   121,    23,    24,    58,    25,    26,    62,    62,    66,
      67,    48,    75,    76,   116,    62,    62,    62,    62,    62,
      62,   106,   107,    14,   109,   110,    98,    62,    93,    94,
     104,   103,    23,    24,    62,    25,    26,   124,   135,     9,
     145,     2,   136,   148,     3,     4,   150,   146,    27,     5,
       6,   134,   131,   101,   149,   140,    18,    19,    20,    21,
      22,   138,   127,   123,   114,     7,     8,   144,     9,   108,
       0,    99,     0,    10,    11,   134,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,     0,
      25,    26,     3,     4,     0,     0,     0,     5,     6,     0,
      68,    69,    70,    71,    72,    73,     0,    80,    81,    82,
      83,    84,    85,     7,     8,     0,     9,   122,     0,     0,
       0,    10,    11,     0,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,     0,    25,    26,
       3,     4,     0,     0,     0,     5,     6,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     7,     8,     0,     9,     0,     0,     0,     0,    10,
      11,     0,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,     0,    25,    26,     3,     4,
       0,     0,     0,     5,     6,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     7,
       8,     0,     0,     0,     0,     3,     4,     0,     0,     0,
       5,     6,    14,     0,     0,    17,    18,    19,    20,    21,
      22,    23,    24,     0,    25,    26,     7,     8,   115,     0,
       0,     0,     3,     4,     0,     0,     0,     5,     6,    14,
       3,     4,    17,     0,     0,     5,     6,     0,    23,    24,
       0,    25,    26,     7,     8,     0,     0,     0,     0,     3,
       4,     7,    48,     0,     5,     6,    14,    15,     0,    17,
       0,     0,     0,     0,    14,    23,    24,    17,    25,    26,
       7,     8,     0,    23,    24,     0,    25,    26,     0,     0,
       0,     0,     0,    14,     0,     0,    17,     0,     0,     0,
       0,     0,    23,    24,     0,    25,    26
};

static const yytype_int16 yycheck[] =
{
       8,    16,     8,    35,    16,    31,     5,     6,   126,    28,
     128,    31,    38,    25,     8,     9,     8,     9,    38,     3,
       4,    48,    26,    25,     8,     9,    38,    31,   146,    26,
      26,    25,    26,    25,    31,    31,    35,    37,    26,    26,
      24,    25,    48,    31,    31,    77,    78,    79,    25,    64,
      56,    25,    58,    37,    38,    26,    40,     5,     6,     7,
      31,    93,    46,    47,    25,    49,    50,    66,    67,    22,
      23,    25,     3,     4,    89,    74,    75,    76,    77,    78,
      79,    66,    67,    37,    75,    76,    40,    86,    26,    28,
      40,    38,    46,    47,    93,    49,    50,    48,    40,    27,
      26,     0,    38,    38,     3,     4,    38,    34,     1,     8,
       9,   119,   118,    57,   143,   130,    41,    42,    43,    44,
      45,   127,   101,    96,    86,    24,    25,   134,    27,    74,
      -1,    55,    -1,    32,    33,   143,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    -1,
      49,    50,     3,     4,    -1,    -1,    -1,     8,     9,    -1,
      10,    11,    12,    13,    14,    15,    -1,    16,    17,    18,
      19,    20,    21,    24,    25,    -1,    27,    28,    -1,    -1,
      -1,    32,    33,    -1,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    -1,    49,    50,
       3,     4,    -1,    -1,    -1,     8,     9,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    24,    25,    -1,    27,    -1,    -1,    -1,    -1,    32,
      33,    -1,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    -1,    49,    50,     3,     4,
      -1,    -1,    -1,     8,     9,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    24,
      25,    -1,    -1,    -1,    -1,     3,     4,    -1,    -1,    -1,
       8,     9,    37,    -1,    -1,    40,    41,    42,    43,    44,
      45,    46,    47,    -1,    49,    50,    24,    25,    26,    -1,
      -1,    -1,     3,     4,    -1,    -1,    -1,     8,     9,    37,
       3,     4,    40,    -1,    -1,     8,     9,    -1,    46,    47,
      -1,    49,    50,    24,    25,    -1,    -1,    -1,    -1,     3,
       4,    24,    25,    -1,     8,     9,    37,    38,    -1,    40,
      -1,    -1,    -1,    -1,    37,    46,    47,    40,    49,    50,
      24,    25,    -1,    46,    47,    -1,    49,    50,    -1,    -1,
      -1,    -1,    -1,    37,    -1,    -1,    40,    -1,    -1,    -1,
      -1,    -1,    46,    47,    -1,    49,    50
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    52,     0,     3,     4,     8,     9,    24,    25,    27,
      32,    33,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    49,    50,    53,    54,    55,
      58,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    75,    76,    77,    80,    81,    82,    25,    75,
      75,    68,    82,    59,    60,    25,    25,    25,    25,    38,
      69,    48,    75,    76,    31,    38,    22,    23,    10,    11,
      12,    13,    14,    15,    74,     3,     4,     5,     6,     7,
      16,    17,    18,    19,    20,    21,    79,     8,     9,    25,
      37,    83,    26,    26,    28,    53,    61,    62,    40,    77,
      68,    55,    68,    38,    40,    69,    71,    71,    72,    73,
      73,    76,    76,    76,    70,    26,    69,    78,    16,    25,
      38,    76,    28,    62,    48,    26,    26,    63,    26,    26,
      31,    68,    56,    57,    82,    40,    38,    58,    68,    58,
      69,    38,    26,    31,    83,    26,    34,    26,    38,    57,
      38,    58
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    51,    52,    52,    53,    53,    53,    53,    53,    53,
      53,    54,    54,    55,    55,    55,    55,    56,    56,    57,
      57,    59,    58,    60,    58,    61,    61,    62,    63,    63,
      64,    64,    65,    65,    65,    66,    66,    66,    66,    66,
      67,    67,    67,    68,    68,    69,    69,    70,    70,    70,
      71,    71,    72,    72,    72,    73,    73,    73,    73,    74,
      74,    74,    74,    74,    74,    75,    75,    75,    75,    76,
      76,    77,    77,    77,    77,    77,    78,    78,    79,    79,
      79,    79,    79,    79,    80,    80,    81,    81,    82,    82,
      82,    82,    82,    83
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     0,     1,     1,     1,     1,     1,     1,
       1,     2,     3,     5,     3,     5,     6,     3,     1,     2,
       0,     0,     3,     0,     4,     1,     2,     1,     1,     2,
       7,     5,     1,     1,     3,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     3,     3,     1,     3,     3,     1,
       3,     1,     1,     3,     3,     1,     3,     3,     3,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     2,     1,
       4,     1,     3,     4,     2,     2,     1,     3,     1,     1,
       1,     1,     1,     1,     7,     5,     5,     6,     1,     1,
       1,     1,     1,     1
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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
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
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
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

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

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
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 13:
#line 147 "compiler_hw3.y" /* yacc.c:1646  */
    { 
        insert_symbol((yyvsp[-4].string), (yyvsp[-3].string), "variable", curr_scope);
        int reg = 0;
        if(curr_scope != 0) {
            reg =  find_var_reg((yyvsp[-3].string), curr_scope);
        }
        process_variable((yyvsp[-3].string), (yyvsp[-1].string), (yyvsp[-4].string), curr_scope, reg);
    }
#line 1542 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 155 "compiler_hw3.y" /* yacc.c:1646  */
    { 
        insert_symbol((yyvsp[-2].string), (yyvsp[-1].string), "variable", curr_scope); 
        int reg = 0;
        if(curr_scope != 0) {
            reg =  find_var_reg((yyvsp[-1].string), curr_scope);
        }
        process_variable((yyvsp[-1].string), NULL, (yyvsp[-2].string), curr_scope, reg);
    }
#line 1555 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 163 "compiler_hw3.y" /* yacc.c:1646  */
    { 
        insert_symbol((yyvsp[-4].string), (yyvsp[-3].string), "function", curr_scope); 
        process_function_definition((yyvsp[-4].string), (yyvsp[-3].string), func_def_param_types);
    }
#line 1564 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 167 "compiler_hw3.y" /* yacc.c:1646  */
    {
        insert_symbol((yyvsp[-5].string), (yyvsp[-4].string), "function_decl", curr_scope);
        erase_table_scope(curr_scope+1); 
    }
#line 1573 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 174 "compiler_hw3.y" /* yacc.c:1646  */
    {
        type_map((yyvsp[0].string), func_def_param_types);
        printf("%s\n", func_def_param_types);
    }
#line 1582 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 178 "compiler_hw3.y" /* yacc.c:1646  */
    {
        type_map((yyvsp[0].string), func_def_param_types);
    }
#line 1590 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 185 "compiler_hw3.y" /* yacc.c:1646  */
    { 
        insert_symbol((yyvsp[-1].string), (yyvsp[0].string), "parameter", curr_scope+1); 
        strcpy((yyval.string), (yyvsp[-1].string));
        // another production that I deleted | assignment_expression   
    }
#line 1600 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 194 "compiler_hw3.y" /* yacc.c:1646  */
    {++curr_scope;}
#line 1606 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 194 "compiler_hw3.y" /* yacc.c:1646  */
    {--curr_scope;}
#line 1612 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 195 "compiler_hw3.y" /* yacc.c:1646  */
    {++curr_scope;}
#line 1618 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 195 "compiler_hw3.y" /* yacc.c:1646  */
    { /*dump_symbol(false);*/ --curr_scope; }
#line 1624 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 218 "compiler_hw3.y" /* yacc.c:1646  */
    { lookup_symbol(yytext, curr_scope); strcat(error_msg, error_cause_name); }
#line 1630 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 219 "compiler_hw3.y" /* yacc.c:1646  */
    {
        strcpy((yyval.string), (yyvsp[0].string));
    }
#line 1638 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 222 "compiler_hw3.y" /* yacc.c:1646  */
    {
        strcpy((yyval.string), (yyvsp[-1].string));
    }
#line 1646 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 228 "compiler_hw3.y" /* yacc.c:1646  */
    {
        // Convert the specific types into string (float/int/etc --> int)
        char conv_type[32] = {0};
        sprintf(conv_type, "%f", (yyvsp[0].f_val));
        strcpy((yyval.string), conv_type);
    }
#line 1657 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 234 "compiler_hw3.y" /* yacc.c:1646  */
    {
        char conv_type[32] = {0};
        sprintf(conv_type, "%d", (yyvsp[0].i_val));
        strcpy((yyval.string), conv_type);
    }
#line 1667 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 239 "compiler_hw3.y" /* yacc.c:1646  */
    {
        char conv_type[32] = {0};
        sprintf(conv_type, "%s", (yyvsp[-1].string));
        strcpy((yyval.string), conv_type);
    }
#line 1677 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 244 "compiler_hw3.y" /* yacc.c:1646  */
    {
        char conv_type[32] = {0};
        sprintf(conv_type, "%s", "true");
        strcpy((yyval.string), conv_type);
    }
#line 1687 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 249 "compiler_hw3.y" /* yacc.c:1646  */
    {
        char conv_type[32] = {0};
        sprintf(conv_type, "%s", "false");
        strcpy((yyval.string), conv_type);
    }
#line 1697 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 263 "compiler_hw3.y" /* yacc.c:1646  */
    {
        strcpy((yyval.string), (yyvsp[0].string));
    }
#line 1705 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 270 "compiler_hw3.y" /* yacc.c:1646  */
    {

    }
#line 1713 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 273 "compiler_hw3.y" /* yacc.c:1646  */
    {
        strcpy((yyval.string), (yyvsp[0].string));
    }
#line 1721 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 281 "compiler_hw3.y" /* yacc.c:1646  */
    {
        strcpy((yyval.string), (yyvsp[0].string));
    }
#line 1729 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 296 "compiler_hw3.y" /* yacc.c:1646  */
    {
        // strcpy($$, $1);
    }
#line 1737 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 337 "compiler_hw3.y" /* yacc.c:1646  */
    {
        strcpy((yyval.string), (yyvsp[0].string));
    }
#line 1745 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 351 "compiler_hw3.y" /* yacc.c:1646  */
    {
        strcpy((yyval.string), (yyvsp[0].string));
    }
#line 1753 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 354 "compiler_hw3.y" /* yacc.c:1646  */
    {
        //printf("FUNCTION\n");
        if(semantic_error) {
            strcpy(strstr(error_msg, "variable"), "function ");
            strcat(error_msg, error_cause_name);
        }
    }
#line 1765 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 361 "compiler_hw3.y" /* yacc.c:1646  */
    {
        if(semantic_error) {
            strcpy(strstr(error_msg, "variable"), "function ");
            strcat(error_msg, error_cause_name);
        }
    }
#line 1776 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 395 "compiler_hw3.y" /* yacc.c:1646  */
    {
        strcpy((yyval.string), "=");
    }
#line 1784 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 398 "compiler_hw3.y" /* yacc.c:1646  */
    {
        strcpy((yyval.string), "+=");
    }
#line 1792 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 401 "compiler_hw3.y" /* yacc.c:1646  */
    {
        strcpy((yyval.string), "-=");
    }
#line 1800 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 404 "compiler_hw3.y" /* yacc.c:1646  */
    {
        strcpy((yyval.string), "*=");
    }
#line 1808 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 407 "compiler_hw3.y" /* yacc.c:1646  */
    {
        strcpy((yyval.string), "/=");
    }
#line 1816 "y.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 410 "compiler_hw3.y" /* yacc.c:1646  */
    {
        strcpy((yyval.string), "%=");
    }
#line 1824 "y.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 427 "compiler_hw3.y" /* yacc.c:1646  */
    { strcpy((yyval.string), "int"); }
#line 1830 "y.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 428 "compiler_hw3.y" /* yacc.c:1646  */
    { strcpy((yyval.string), "float"); }
#line 1836 "y.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 429 "compiler_hw3.y" /* yacc.c:1646  */
    { strcpy((yyval.string), "bool"); }
#line 1842 "y.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 430 "compiler_hw3.y" /* yacc.c:1646  */
    { strcpy((yyval.string), "string"); }
#line 1848 "y.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 431 "compiler_hw3.y" /* yacc.c:1646  */
    { strcpy((yyval.string), "void"); }
#line 1854 "y.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 435 "compiler_hw3.y" /* yacc.c:1646  */
    { strcpy((yyval.string), yytext); }
#line 1860 "y.tab.c" /* yacc.c:1646  */
    break;


#line 1864 "y.tab.c" /* yacc.c:1646  */
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
                      yytoken, &yylval);
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


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
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
#line 438 "compiler_hw3.y" /* yacc.c:1906  */


/* C code section */
int main(int argc, char** argv)
{
    write_to_file(".class public compiler_hw3\n.super java/lang/Object\n");

    create_symbol();
    yylineno = 0;

    int syn_error = yyparse();
    if(!syn_error) {
        //dump_symbol(true);
        //printf("\n\nTotal lines: %d \n",yylineno);
    }
    //free_func_list();
    return 0;
}

void yyerror(char *s)
{
    // if semantic error is present, we want to display it before the syntax
    // error stops execution
    if(semantic_error) {
        printf("%d: %s\n", yylineno+1, buf); 
        printf("\n|-----------------------------------------------|\n");
        printf("| Error found in line %d: %s\n", yylineno+1, buf);
        printf("| %s", error_msg);
        printf("\n|-----------------------------------------------|\n\n");
    }
    printf("\n|-----------------------------------------------|\n");
    printf("| Error found in line %d: %s\n", yylineno+1, buf);
    printf("| %s", s);
    printf("\n|-----------------------------------------------|\n\n");
}

void create_symbol() {
    // Create the symbol table
    for(int i = 0; i < 10; i++) {
        symbol_table[i] = (node_t*)malloc(sizeof(node_t));
        symbol_table[i]->next = NULL;
    }
}

void insert_symbol(char* dtype, char* name, char* etype, int scope) { 
    node_t* new_node = (node_t* )malloc(sizeof(node_t));
    new_node->next = NULL;
    new_node->f_decl = false;
    new_node->scope_level = scope;
    strcpy(new_node->name, name);
    strcpy(new_node->entry_type, etype);
    strcpy(new_node->data_type, dtype);
    strcpy(new_node->formal_param, "");
    
    // Find the highest taken register r, so that we can put variable in r+1
    if(((strcmp(etype, "variable") == 0) || (strcmp(etype, "parameter") == 0)) && scope != 0) {
        new_node->reg_id = find_highest_reg(scope);
    }
    else {
        new_node->reg_id = -1;
    }

    printf("ASSIGN %s REG %d\n", name, new_node->reg_id);

    if(strcmp(etype, "parameter") == 0) {
        // is a parameter
        if(params) {
            strcat(params, ", ");
        }
        else {
            params = (char*)malloc(64);
            memset(params, 0, 64);
        }
        strcat(params, dtype);
    } 
    if(strcmp(etype, "function") == 0) {
        if(params) {
            strcpy(new_node->formal_param, params);
            free(params);
            params = NULL;
        }
    }
    if(strcmp(etype, "function_decl") == 0) {
        strcpy(new_node->entry_type, "function");
        if(params) {
            strcpy(new_node->formal_param, params);
            free(params);
            params = NULL;
        }
        new_node->f_decl = true;
    }

    TRAVERSE_LIST(scope) {
        if(it->next == NULL) {
            if(strcmp(it->name, name) == 0) {
                // redeclaration
                set_err_msg(false, true, name);
                strcpy(error_msg, "Redeclared ");
                strcat(error_msg, it->entry_type);
                strcat(error_msg, " ");
                strcat(error_msg, it->name);
                // if(it->f_decl == true) {
                //     continue;
                // }
                if(!it->f_decl) {
                    semantic_error = true;
                    return;
                }
            }
            it->next = new_node;
            break;
        }
    }
    curr_node = new_node;
    parsing_func = false;
}

int lookup_symbol(char* name, int scope) {
    for(int i = scope; i >= 0; i--) {
        TRAVERSE_LIST(i) {  
            if(strcmp(it->name, name) == 0) {
                check_undeclared = false;
                return 0;
            }
        }
    }
        semantic_error = true;
        set_err_msg(false, true, name);
}

int find_highest_reg(int scope) {
    int curr_highest = 0;
    for(int i = scope; i >= 1; i--) {
        // because head is not a true node of the table (just there for reference)
        // we don't want to traverse it. So we start from the node after it.
        TRAVERSE_LIST_AFTER_HEAD(i) {
            if(it->reg_id > curr_highest) {
                curr_highest = it->reg_id;
            }
            else {
                curr_highest++;
            }
        }
    }
    return curr_highest;
}

int find_var_reg(char* name, int scope) {
    TRAVERSE_SCOPE_AFTER_HEAD(scope) {
        if(strcmp(name, it->name) == 0) {
            return it->reg_id;
        }
    }
    return -1;
}

void dump_symbol(bool last_print) {

    if(symbol_table[curr_scope]->next == NULL) {
        return;
    }
    int table_index = 0;
    if(!last_print) {
        printf("\n");
    }
    printf("\n%-10s%-10s%-12s%-10s%-10s%-10s\n",
           "Index", "Name", "Kind", "Type", "Scope", "Attribute");


    TRAVERSE_LIST(curr_scope) {
        // since the first node will be empty, it is skipped
        if(it == symbol_table[curr_scope]) {
            continue;
        }
        if(it->f_decl) {
            continue;
        }
        printf("\n%-10d%-10s%-12s%-10s%-10d%s",
            table_index++, it->name, it->entry_type, it->data_type, it->scope_level, it->formal_param);
    }
    printf("\n");

    node_t* tmp = symbol_table[curr_scope]->next;
    node_t* tmp_prev = NULL;

    while(tmp) {
        tmp_prev = tmp;
        tmp = tmp->next;
        free(tmp_prev);
    }

    // reset the table
    symbol_table[curr_scope]->next = NULL;
}

void set_err_msg(bool is_redeclare, bool is_function_error, char* name) {
    memset(error_cause_name, '\0', sizeof(error_cause_name));
    memset(error_msg, 0, 128);
    strcpy(error_msg, "Undeclared ");
    strcat(error_msg, "variable ");
    strcpy(error_cause_name, name);
    
}

void erase_table_scope(int scope) {
    node_t* tmp = symbol_table[scope]->next;
    node_t* tmp_prev = NULL;

    while(tmp) {
        tmp_prev = tmp;
        tmp = tmp->next;
        free(tmp_prev);
    }
    symbol_table[scope]->next = NULL;
}
