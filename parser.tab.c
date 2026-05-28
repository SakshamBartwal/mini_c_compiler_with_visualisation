/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "compiler/2_parser/parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compiler/3_ast/ast.h"

extern char current_file[100];
extern int yylex();
extern int line_num;

void yyerror(const char *s);

#line 85 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IMPORT = 3,                     /* IMPORT  */
  YYSYMBOL_INT = 4,                        /* INT  */
  YYSYMBOL_FLOAT = 5,                      /* FLOAT  */
  YYSYMBOL_CHAR = 6,                       /* CHAR  */
  YYSYMBOL_VOID = 7,                       /* VOID  */
  YYSYMBOL_DOUBLE = 8,                     /* DOUBLE  */
  YYSYMBOL_LONG = 9,                       /* LONG  */
  YYSYMBOL_SHORT = 10,                     /* SHORT  */
  YYSYMBOL_SIGNED = 11,                    /* SIGNED  */
  YYSYMBOL_UNSIGNED = 12,                  /* UNSIGNED  */
  YYSYMBOL_IF = 13,                        /* IF  */
  YYSYMBOL_ELSE = 14,                      /* ELSE  */
  YYSYMBOL_WHILE = 15,                     /* WHILE  */
  YYSYMBOL_FOR = 16,                       /* FOR  */
  YYSYMBOL_DO = 17,                        /* DO  */
  YYSYMBOL_RETURN = 18,                    /* RETURN  */
  YYSYMBOL_SWITCH = 19,                    /* SWITCH  */
  YYSYMBOL_CASE = 20,                      /* CASE  */
  YYSYMBOL_DEFAULT = 21,                   /* DEFAULT  */
  YYSYMBOL_BREAK = 22,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 23,                  /* CONTINUE  */
  YYSYMBOL_EQ = 24,                        /* EQ  */
  YYSYMBOL_NEQ = 25,                       /* NEQ  */
  YYSYMBOL_LE = 26,                        /* LE  */
  YYSYMBOL_GE = 27,                        /* GE  */
  YYSYMBOL_AND = 28,                       /* AND  */
  YYSYMBOL_OR = 29,                        /* OR  */
  YYSYMBOL_INC = 30,                       /* INC  */
  YYSYMBOL_DEC = 31,                       /* DEC  */
  YYSYMBOL_SIZEOF = 32,                    /* SIZEOF  */
  YYSYMBOL_ADD_ASSIGN = 33,                /* ADD_ASSIGN  */
  YYSYMBOL_SUB_ASSIGN = 34,                /* SUB_ASSIGN  */
  YYSYMBOL_MUL_ASSIGN = 35,                /* MUL_ASSIGN  */
  YYSYMBOL_DIV_ASSIGN = 36,                /* DIV_ASSIGN  */
  YYSYMBOL_INT_LITERAL = 37,               /* INT_LITERAL  */
  YYSYMBOL_FLOAT_LITERAL = 38,             /* FLOAT_LITERAL  */
  YYSYMBOL_STRING_LITERAL = 39,            /* STRING_LITERAL  */
  YYSYMBOL_IDENTIFIER = 40,                /* IDENTIFIER  */
  YYSYMBOL_41_ = 41,                       /* '='  */
  YYSYMBOL_UMINUS = 42,                    /* UMINUS  */
  YYSYMBOL_LOWER_THAN_ELSE = 43,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_44_ = 44,                       /* ';'  */
  YYSYMBOL_45_ = 45,                       /* '('  */
  YYSYMBOL_46_ = 46,                       /* ')'  */
  YYSYMBOL_47_ = 47,                       /* ','  */
  YYSYMBOL_48_ = 48,                       /* '*'  */
  YYSYMBOL_49_ = 49,                       /* '['  */
  YYSYMBOL_50_ = 50,                       /* ']'  */
  YYSYMBOL_51_ = 51,                       /* '{'  */
  YYSYMBOL_52_ = 52,                       /* '}'  */
  YYSYMBOL_53_ = 53,                       /* ':'  */
  YYSYMBOL_54_ = 54,                       /* '?'  */
  YYSYMBOL_55_ = 55,                       /* '<'  */
  YYSYMBOL_56_ = 56,                       /* '>'  */
  YYSYMBOL_57_ = 57,                       /* '+'  */
  YYSYMBOL_58_ = 58,                       /* '-'  */
  YYSYMBOL_59_ = 59,                       /* '/'  */
  YYSYMBOL_60_ = 60,                       /* '%'  */
  YYSYMBOL_61_ = 61,                       /* '&'  */
  YYSYMBOL_62_ = 62,                       /* '!'  */
  YYSYMBOL_YYACCEPT = 63,                  /* $accept  */
  YYSYMBOL_program = 64,                   /* program  */
  YYSYMBOL_external_declaration = 65,      /* external_declaration  */
  YYSYMBOL_import_statement = 66,          /* import_statement  */
  YYSYMBOL_function_definition = 67,       /* function_definition  */
  YYSYMBOL_function_declaration = 68,      /* function_declaration  */
  YYSYMBOL_parameter_list = 69,            /* parameter_list  */
  YYSYMBOL_parameter = 70,                 /* parameter  */
  YYSYMBOL_declaration = 71,               /* declaration  */
  YYSYMBOL_variable_list = 72,             /* variable_list  */
  YYSYMBOL_initialized_declarator = 73,    /* initialized_declarator  */
  YYSYMBOL_declarator = 74,                /* declarator  */
  YYSYMBOL_compound_statement = 75,        /* compound_statement  */
  YYSYMBOL_statement_list = 76,            /* statement_list  */
  YYSYMBOL_statement = 77,                 /* statement  */
  YYSYMBOL_expression_statement = 78,      /* expression_statement  */
  YYSYMBOL_selection_statement = 79,       /* selection_statement  */
  YYSYMBOL_case_list = 80,                 /* case_list  */
  YYSYMBOL_case_statement = 81,            /* case_statement  */
  YYSYMBOL_constant_expression = 82,       /* constant_expression  */
  YYSYMBOL_iteration_statement = 83,       /* iteration_statement  */
  YYSYMBOL_for_init_statement = 84,        /* for_init_statement  */
  YYSYMBOL_optional_expression = 85,       /* optional_expression  */
  YYSYMBOL_jump_statement = 86,            /* jump_statement  */
  YYSYMBOL_expression = 87,                /* expression  */
  YYSYMBOL_assignment_expression = 88,     /* assignment_expression  */
  YYSYMBOL_conditional_expression = 89,    /* conditional_expression  */
  YYSYMBOL_logical_or_expression = 90,     /* logical_or_expression  */
  YYSYMBOL_logical_and_expression = 91,    /* logical_and_expression  */
  YYSYMBOL_equality_expression = 92,       /* equality_expression  */
  YYSYMBOL_relational_expression = 93,     /* relational_expression  */
  YYSYMBOL_additive_expression = 94,       /* additive_expression  */
  YYSYMBOL_multiplicative_expression = 95, /* multiplicative_expression  */
  YYSYMBOL_unary_expression = 96,          /* unary_expression  */
  YYSYMBOL_postfix_expression = 97,        /* postfix_expression  */
  YYSYMBOL_primary_expression = 98,        /* primary_expression  */
  YYSYMBOL_argument_list_opt = 99,         /* argument_list_opt  */
  YYSYMBOL_argument_list = 100,            /* argument_list  */
  YYSYMBOL_type_specifier = 101            /* type_specifier  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  64
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   545

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  63
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  39
/* YYNRULES -- Number of rules.  */
#define YYNRULES  118
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  211

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   297


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    62,     2,     2,     2,    60,    61,     2,
      45,    46,    48,    57,    47,    58,     2,    59,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    53,    44,
      55,    41,    56,    54,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    49,     2,    50,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    51,     2,    52,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    42,    43
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    58,    58,    63,    71,    72,    73,    74,    75,    79,
      83,    92,    96,    97,    98,   102,   107,   115,   119,   123,
     127,   134,   143,   147,   152,   160,   164,   173,   179,   195,
     196,   197,   198,   199,   200,   204,   205,   209,   210,   211,
     215,   216,   220,   221,   225,   226,   227,   231,   232,   233,
     237,   238,   242,   243,   247,   248,   249,   250,   255,   259,
     266,   272,   273,   274,   275,   276,   283,   284,   288,   289,
     293,   294,   298,   299,   300,   304,   305,   306,   307,   308,
     312,   318,   324,   331,   337,   343,   349,   356,   357,   362,
     367,   372,   377,   382,   387,   392,   400,   401,   402,   403,
     404,   408,   409,   410,   411,   412,   416,   417,   421,   422,
     426,   426,   426,   426,   426,   426,   426,   426,   426
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "IMPORT", "INT",
  "FLOAT", "CHAR", "VOID", "DOUBLE", "LONG", "SHORT", "SIGNED", "UNSIGNED",
  "IF", "ELSE", "WHILE", "FOR", "DO", "RETURN", "SWITCH", "CASE",
  "DEFAULT", "BREAK", "CONTINUE", "EQ", "NEQ", "LE", "GE", "AND", "OR",
  "INC", "DEC", "SIZEOF", "ADD_ASSIGN", "SUB_ASSIGN", "MUL_ASSIGN",
  "DIV_ASSIGN", "INT_LITERAL", "FLOAT_LITERAL", "STRING_LITERAL",
  "IDENTIFIER", "'='", "UMINUS", "LOWER_THAN_ELSE", "';'", "'('", "')'",
  "','", "'*'", "'['", "']'", "'{'", "'}'", "':'", "'?'", "'<'", "'>'",
  "'+'", "'-'", "'/'", "'%'", "'&'", "'!'", "$accept", "program",
  "external_declaration", "import_statement", "function_definition",
  "function_declaration", "parameter_list", "parameter", "declaration",
  "variable_list", "initialized_declarator", "declarator",
  "compound_statement", "statement_list", "statement",
  "expression_statement", "selection_statement", "case_list",
  "case_statement", "constant_expression", "iteration_statement",
  "for_init_statement", "optional_expression", "jump_statement",
  "expression", "assignment_expression", "conditional_expression",
  "logical_or_expression", "logical_and_expression", "equality_expression",
  "relational_expression", "additive_expression",
  "multiplicative_expression", "unary_expression", "postfix_expression",
  "primary_expression", "argument_list_opt", "argument_list",
  "type_specifier", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-85)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     152,   -33,   -85,   -85,   -85,   -85,   -85,   -85,   -85,   -85,
     -85,   183,    77,   -85,   -85,   -85,   -85,   -85,   -85,    22,
     -14,   -25,   -11,    -4,   301,   417,    11,    19,    32,   483,
     483,   483,   -85,   -85,   -85,   -85,   -85,   405,   483,   -85,
     483,   483,   483,   -85,   -85,   242,   -85,   -85,   -85,   -85,
     -85,    24,   -85,   -85,   -19,    62,   101,    -8,    80,   -37,
      18,    15,   -85,    22,   -85,   -85,   -85,    22,    31,   -85,
      16,   -85,   483,   483,   360,    82,   -85,    47,   483,   -85,
     -85,   -85,   -85,   -85,    93,    49,   -85,   -85,   -85,   -85,
     -85,   -85,   -85,   483,   483,   483,   483,   483,   483,   483,
     483,   483,   483,   483,   483,   483,   483,   483,   483,   483,
     483,   483,   483,   -85,   -85,   483,   483,    25,    85,   -85,
      22,   483,   110,   104,   102,   106,   -85,   -85,   450,    99,
     -85,   119,   -85,   483,   -85,    62,   -85,    20,   101,    -8,
      -8,    80,    80,    80,    80,   -37,   -37,   -85,   -85,   -85,
     -85,   -85,   -85,   -85,   -85,   100,   108,   103,    86,   -85,
      25,   -85,   123,   -85,    22,   127,   301,   301,   483,   483,
     122,   -85,   483,   -85,   483,   -85,   -15,   110,    85,   -85,
     170,   -85,   151,   100,   125,   155,   -85,   100,   -85,   -85,
     -85,   301,   301,   160,    73,   154,   -13,   -85,   -85,   -85,
     -85,   -85,   -85,   -85,   156,   301,   -85,   -85,   301,   301,
     301
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,   110,   111,   112,   113,   114,   115,   116,   117,
     118,     0,     0,     3,     7,     4,     5,     6,     8,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   103,   104,   102,   101,    36,     0,     0,    25,
       0,     0,     0,    29,    34,     0,    27,    30,    31,    32,
      33,     0,    59,    65,    66,    69,    71,    74,    79,    82,
      86,    87,    96,     0,     1,     2,    22,     0,     0,    20,
      19,     9,     0,     0,     0,     0,    55,     0,     0,    56,
      57,    88,    89,    94,     0,     0,    91,    92,    90,    93,
      26,    28,    35,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    99,   100,   107,     0,    19,    23,    16,
       0,     0,    14,     0,     0,     0,    50,    51,     0,     0,
      54,     0,   105,     0,    58,    68,    86,     0,    70,    72,
      73,    77,    78,    75,    76,    80,    81,    83,    84,    85,
      61,    62,    63,    64,    60,   109,     0,   106,     0,    18,
      17,    21,     0,    13,     0,     0,     0,     0,    53,     0,
       0,    95,     0,    98,     0,    97,     0,     0,    15,    24,
      37,    47,     0,    52,     0,     0,    67,   108,    11,    10,
      12,     0,     0,     0,     0,     0,     0,    41,    38,    49,
      48,    44,    45,    46,     0,     0,    39,    40,     0,    43,
      42
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -85,   -85,   196,   -85,   -85,   -85,   -85,    33,     5,   -85,
      91,   -51,     3,   -81,   -24,   -70,   -85,   -85,    21,   -85,
     -85,   -85,   -85,   -85,   -23,   -84,    40,   -85,   124,   120,
      83,    30,    79,     2,   -85,   -85,   -85,   -85,     1
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    12,    13,    14,    15,    16,   162,   163,    43,    68,
      69,    70,    44,    45,    46,    47,    48,   196,   197,   204,
      49,   128,   182,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,   156,   157,    63
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      75,    19,    77,    18,   127,    17,    20,   194,   195,   134,
      94,   105,   117,    19,    84,    18,   118,    17,    99,   100,
      72,    91,   106,   107,   150,   151,   152,   153,   154,   188,
      71,    81,    82,    83,    73,    95,    11,   161,    85,   206,
      86,    74,    87,    88,    89,   113,   114,   101,   102,   124,
     125,   108,   109,   110,   111,   131,    78,   121,   168,   112,
     115,   122,    66,    79,   116,   123,   121,    93,    92,   160,
      67,    93,   137,   172,   123,   119,    80,    64,   120,   126,
       1,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      96,   130,   155,   158,    93,   133,   136,   129,   136,   136,
     136,   136,   136,   136,   136,   136,   136,   147,   148,   149,
     201,   202,   203,   178,     2,     3,     4,     5,     6,     7,
       8,     9,    10,   164,   209,    97,    98,   210,    11,   141,
     142,   143,   144,    93,   123,   171,   175,   103,   104,   132,
      93,   165,   180,   181,   169,   183,   184,    93,   166,    93,
     174,   187,   167,    93,   173,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,   170,    93,   198,   199,   176,
     177,   193,    93,   185,   136,   194,   195,   179,   164,   189,
     139,   140,   145,   146,   191,    91,    91,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    21,   192,    22,    23,
      24,    25,    26,    11,   200,    27,    28,   205,    65,   208,
     190,   159,   186,    29,    30,    31,   138,   207,   135,     0,
      32,    33,    34,    35,     0,     0,     0,    36,    37,     0,
       0,    38,     0,     0,    11,    39,     0,     0,     0,     0,
       0,    40,     0,     0,    41,    42,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    21,     0,    22,    23,    24,
      25,    26,     0,     0,    27,    28,     0,     0,     0,     0,
       0,     0,    29,    30,    31,     0,     0,     0,     0,    32,
      33,    34,    35,     0,     0,     0,    36,    37,     0,     0,
      38,     0,     0,    11,    90,     0,     0,     0,     0,     0,
      40,     0,     0,    41,    42,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    21,     0,    22,    23,    24,    25,
      26,     0,     0,    27,    28,     0,     0,     0,     0,     0,
       0,    29,    30,    31,     0,     0,     0,     0,    32,    33,
      34,    35,     0,     0,     0,    36,    37,     0,     0,    38,
       0,     0,    11,     0,     0,     0,     0,     0,     0,    40,
       0,     0,    41,    42,     2,     3,     4,     5,     6,     7,
       8,     9,    10,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      29,    30,    31,     0,     0,     0,     0,    32,    33,    34,
      35,     0,     0,     0,    36,    37,     0,     0,    38,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    40,     0,
       0,    41,    42,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    29,    30,    31,     0,     0,
       0,     0,    32,    33,    34,    35,     0,    29,    30,    31,
      37,     0,     0,    38,    32,    33,    34,    35,     0,     0,
       0,    76,    37,    40,     0,    38,    41,    42,     0,     0,
       0,     0,     0,     0,     0,    40,     0,     0,    41,    42,
      29,    30,    31,     0,     0,     0,     0,    32,    33,    34,
      35,     0,     0,     0,    36,    37,     0,     0,    38,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    40,     0,
       0,    41,    42,    29,    30,    31,     0,     0,     0,     0,
      32,    33,    34,    35,     0,     0,     0,     0,    37,     0,
       0,    38,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    40,     0,     0,    41,    42
};

static const yytype_int16 yycheck[] =
{
      24,     0,    25,     0,    74,     0,    39,    20,    21,    93,
      29,    48,    63,    12,    37,    12,    67,    12,    26,    27,
      45,    45,    59,    60,   108,   109,   110,   111,   112,    44,
      44,    29,    30,    31,    45,    54,    51,   121,    37,    52,
      38,    45,    40,    41,    42,    30,    31,    55,    56,    72,
      73,    33,    34,    35,    36,    78,    45,    41,   128,    41,
      45,    45,    40,    44,    49,    49,    41,    47,    44,   120,
      48,    47,    95,    53,    49,    44,    44,     0,    47,    74,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      28,    44,   115,   116,    47,    46,    94,    15,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
      37,    38,    39,   164,     4,     5,     6,     7,     8,     9,
      10,    11,    12,   122,   205,    24,    25,   208,    51,    99,
     100,   101,   102,    47,    49,   133,    50,    57,    58,    46,
      47,    37,   166,   167,    45,   168,   169,    47,    46,    47,
      47,   174,    46,    47,    46,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    46,    47,   191,   192,    46,
      47,    46,    47,    51,   172,    20,    21,    50,   177,   176,
      97,    98,   103,   104,    14,   209,   210,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    46,    15,    16,
      17,    18,    19,    51,    44,    22,    23,    53,    12,    53,
     177,   120,   172,    30,    31,    32,    96,   196,    94,    -1,
      37,    38,    39,    40,    -1,    -1,    -1,    44,    45,    -1,
      -1,    48,    -1,    -1,    51,    52,    -1,    -1,    -1,    -1,
      -1,    58,    -1,    -1,    61,    62,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    -1,    15,    16,    17,
      18,    19,    -1,    -1,    22,    23,    -1,    -1,    -1,    -1,
      -1,    -1,    30,    31,    32,    -1,    -1,    -1,    -1,    37,
      38,    39,    40,    -1,    -1,    -1,    44,    45,    -1,    -1,
      48,    -1,    -1,    51,    52,    -1,    -1,    -1,    -1,    -1,
      58,    -1,    -1,    61,    62,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    -1,    15,    16,    17,    18,
      19,    -1,    -1,    22,    23,    -1,    -1,    -1,    -1,    -1,
      -1,    30,    31,    32,    -1,    -1,    -1,    -1,    37,    38,
      39,    40,    -1,    -1,    -1,    44,    45,    -1,    -1,    48,
      -1,    -1,    51,    -1,    -1,    -1,    -1,    -1,    -1,    58,
      -1,    -1,    61,    62,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      30,    31,    32,    -1,    -1,    -1,    -1,    37,    38,    39,
      40,    -1,    -1,    -1,    44,    45,    -1,    -1,    48,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    58,    -1,
      -1,    61,    62,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    30,    31,    32,    -1,    -1,
      -1,    -1,    37,    38,    39,    40,    -1,    30,    31,    32,
      45,    -1,    -1,    48,    37,    38,    39,    40,    -1,    -1,
      -1,    44,    45,    58,    -1,    48,    61,    62,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    58,    -1,    -1,    61,    62,
      30,    31,    32,    -1,    -1,    -1,    -1,    37,    38,    39,
      40,    -1,    -1,    -1,    44,    45,    -1,    -1,    48,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    58,    -1,
      -1,    61,    62,    30,    31,    32,    -1,    -1,    -1,    -1,
      37,    38,    39,    40,    -1,    -1,    -1,    -1,    45,    -1,
      -1,    48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    58,    -1,    -1,    61,    62
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    51,    64,    65,    66,    67,    68,    71,    75,   101,
      39,    13,    15,    16,    17,    18,    19,    22,    23,    30,
      31,    32,    37,    38,    39,    40,    44,    45,    48,    52,
      58,    61,    62,    71,    75,    76,    77,    78,    79,    83,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,   101,     0,    65,    40,    48,    72,    73,
      74,    44,    45,    45,    45,    77,    44,    87,    45,    44,
      44,    96,    96,    96,    87,   101,    96,    96,    96,    96,
      52,    77,    44,    47,    29,    54,    28,    24,    25,    26,
      27,    55,    56,    57,    58,    48,    59,    60,    33,    34,
      35,    36,    41,    30,    31,    45,    49,    74,    74,    44,
      47,    41,    45,    49,    87,    87,    71,    78,    84,    15,
      44,    87,    46,    46,    88,    91,    96,    87,    92,    93,
      93,    94,    94,    94,    94,    95,    95,    96,    96,    96,
      88,    88,    88,    88,    88,    87,    99,   100,    87,    73,
      74,    88,    69,    70,   101,    37,    46,    46,    78,    45,
      46,    96,    53,    46,    47,    50,    46,    47,    74,    50,
      77,    77,    85,    87,    87,    51,    89,    87,    44,    75,
      70,    14,    46,    46,    20,    21,    80,    81,    77,    77,
      44,    37,    38,    39,    82,    53,    52,    81,    53,    76,
      76
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    63,    64,    64,    65,    65,    65,    65,    65,    66,
      67,    68,    69,    69,    69,    70,    71,    72,    72,    72,
      72,    73,    74,    74,    74,    75,    75,    76,    76,    77,
      77,    77,    77,    77,    77,    78,    78,    79,    79,    79,
      80,    80,    81,    81,    82,    82,    82,    83,    83,    83,
      84,    84,    85,    85,    86,    86,    86,    86,    87,    87,
      88,    88,    88,    88,    88,    88,    89,    89,    90,    90,
      91,    91,    92,    92,    92,    93,    93,    93,    93,    93,
      94,    94,    94,    95,    95,    95,    95,    96,    96,    96,
      96,    96,    96,    96,    96,    96,    97,    97,    97,    97,
      97,    98,    98,    98,    98,    98,    99,    99,   100,   100,
     101,   101,   101,   101,   101,   101,   101,   101,   101
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     3,
       6,     6,     3,     1,     0,     2,     3,     3,     3,     1,
       1,     3,     1,     2,     4,     2,     3,     1,     2,     1,
       1,     1,     1,     1,     1,     2,     1,     5,     7,     7,
       2,     1,     4,     3,     1,     1,     1,     5,     7,     7,
       1,     1,     1,     0,     3,     2,     2,     2,     3,     1,
       3,     3,     3,     3,     3,     1,     1,     5,     3,     1,
       3,     1,     3,     3,     1,     3,     3,     3,     3,     1,
       3,     3,     1,     3,     3,     3,     1,     1,     2,     2,
       2,     2,     2,     2,     2,     4,     1,     4,     4,     2,
       2,     1,     1,     1,     1,     3,     1,     0,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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
  case 2: /* program: program external_declaration  */
#line 59 "compiler/2_parser/parser.y"
      {
          (yyval.node) = append_node((yyvsp[-1].node), (yyvsp[0].node));
          root = (yyval.node);
      }
#line 1396 "parser.tab.c"
    break;

  case 3: /* program: external_declaration  */
#line 64 "compiler/2_parser/parser.y"
      {
          (yyval.node) = (yyvsp[0].node);
          if((yyvsp[0].node) != NULL) root = (yyvsp[0].node);
      }
#line 1405 "parser.tab.c"
    break;

  case 4: /* external_declaration: function_definition  */
#line 71 "compiler/2_parser/parser.y"
                            { (yyval.node) = (yyvsp[0].node); }
#line 1411 "parser.tab.c"
    break;

  case 5: /* external_declaration: function_declaration  */
#line 72 "compiler/2_parser/parser.y"
                            { (yyval.node) = NULL; }
#line 1417 "parser.tab.c"
    break;

  case 6: /* external_declaration: declaration  */
#line 73 "compiler/2_parser/parser.y"
                            { (yyval.node) = (yyvsp[0].node); }
#line 1423 "parser.tab.c"
    break;

  case 7: /* external_declaration: import_statement  */
#line 74 "compiler/2_parser/parser.y"
                            { (yyval.node) = NULL; }
#line 1429 "parser.tab.c"
    break;

  case 8: /* external_declaration: compound_statement  */
#line 75 "compiler/2_parser/parser.y"
                            { (yyval.node) = (yyvsp[0].node); }
#line 1435 "parser.tab.c"
    break;

  case 10: /* function_definition: type_specifier declarator '(' parameter_list ')' compound_statement  */
#line 84 "compiler/2_parser/parser.y"
      {
          (yyval.node) = create_node(NODE_FUNCTION_DEF, (yyvsp[-4].node)->value); 
          
          (yyval.node)->left = (yyvsp[0].node); 
      }
#line 1445 "parser.tab.c"
    break;

  case 16: /* declaration: type_specifier variable_list ';'  */
#line 108 "compiler/2_parser/parser.y"
      {
          (yyval.node) = create_node(NODE_DECLARATION, "declaration");
          (yyval.node)->left = (yyvsp[-1].node); // Points directly to the first variable node in the flat chain
      }
#line 1454 "parser.tab.c"
    break;

  case 17: /* variable_list: variable_list ',' declarator  */
#line 116 "compiler/2_parser/parser.y"
      {
          (yyval.node) = append_node((yyvsp[-2].node), (yyvsp[0].node));
      }
#line 1462 "parser.tab.c"
    break;

  case 18: /* variable_list: variable_list ',' initialized_declarator  */
#line 120 "compiler/2_parser/parser.y"
      {
          (yyval.node) = append_node((yyvsp[-2].node), (yyvsp[0].node));
      }
#line 1470 "parser.tab.c"
    break;

  case 19: /* variable_list: declarator  */
#line 124 "compiler/2_parser/parser.y"
      {
          (yyval.node) = (yyvsp[0].node); // Passes raw leaf straight up (No intermediate list wrappers)
      }
#line 1478 "parser.tab.c"
    break;

  case 20: /* variable_list: initialized_declarator  */
#line 128 "compiler/2_parser/parser.y"
      {
          (yyval.node) = (yyvsp[0].node); // Passes assignment sub-tree root straight up
      }
#line 1486 "parser.tab.c"
    break;

  case 21: /* initialized_declarator: declarator '=' assignment_expression  */
#line 135 "compiler/2_parser/parser.y"
      {
          (yyval.node) = create_node(NODE_ASSIGNMENT, "=");
          (yyval.node)->left = (yyvsp[-2].node);
          (yyval.node)->right = (yyvsp[0].node);
      }
#line 1496 "parser.tab.c"
    break;

  case 22: /* declarator: IDENTIFIER  */
#line 144 "compiler/2_parser/parser.y"
      {
          (yyval.node) = create_node(NODE_IDENTIFIER, (yyvsp[0].sval));
      }
#line 1504 "parser.tab.c"
    break;

  case 23: /* declarator: '*' declarator  */
#line 148 "compiler/2_parser/parser.y"
      {
          (yyval.node) = create_node(NODE_UNARY_OP, "*");
          (yyval.node)->left = (yyvsp[0].node);
      }
#line 1513 "parser.tab.c"
    break;

  case 24: /* declarator: declarator '[' INT_LITERAL ']'  */
#line 153 "compiler/2_parser/parser.y"
      {
          (yyval.node) = (yyvsp[-3].node);
      }
#line 1521 "parser.tab.c"
    break;

  case 25: /* compound_statement: '{' '}'  */
#line 161 "compiler/2_parser/parser.y"
      {
          (yyval.node) = create_node(NODE_COMPOUND_STATEMENT, "compound_statement");
      }
#line 1529 "parser.tab.c"
    break;

  case 26: /* compound_statement: '{' statement_list '}'  */
#line 165 "compiler/2_parser/parser.y"
      {
          (yyval.node) = create_node(NODE_COMPOUND_STATEMENT, "compound_statement");
          /* FIXED: $1 is '{', $2 is the actual statement_list node chain, $3 is '}' */
          (yyval.node)->left = (yyvsp[-1].node); 
      }
#line 1539 "parser.tab.c"
    break;

  case 27: /* statement_list: statement  */
#line 174 "compiler/2_parser/parser.y"
      {
          /* If the statement is an empty semicolon, pass NULL.
             Otherwise, this statement becomes the head of the chain. */
          (yyval.node) = (yyvsp[0].node); 
      }
#line 1549 "parser.tab.c"
    break;

  case 28: /* statement_list: statement_list statement  */
#line 180 "compiler/2_parser/parser.y"
      {
          if ((yyvsp[-1].node) == NULL) {
              /* If everything before was empty, this new statement 
                 becomes the new head of the list */
              (yyval.node) = (yyvsp[0].node);
          } else {
              if ((yyvsp[0].node) != NULL) {
                  append_node((yyvsp[-1].node), (yyvsp[0].node));
              }
              (yyval.node) = (yyvsp[-1].node);
          }
      }
#line 1566 "parser.tab.c"
    break;

  case 29: /* statement: declaration  */
#line 195 "compiler/2_parser/parser.y"
                            { (yyval.node) = (yyvsp[0].node); }
#line 1572 "parser.tab.c"
    break;

  case 30: /* statement: expression_statement  */
#line 196 "compiler/2_parser/parser.y"
                            { (yyval.node) = (yyvsp[0].node); }
#line 1578 "parser.tab.c"
    break;

  case 31: /* statement: selection_statement  */
#line 197 "compiler/2_parser/parser.y"
                            { (yyval.node) = NULL; }
#line 1584 "parser.tab.c"
    break;

  case 32: /* statement: iteration_statement  */
#line 198 "compiler/2_parser/parser.y"
                            { (yyval.node) = NULL; }
#line 1590 "parser.tab.c"
    break;

  case 33: /* statement: jump_statement  */
#line 199 "compiler/2_parser/parser.y"
                            { (yyval.node) = NULL; }
#line 1596 "parser.tab.c"
    break;

  case 34: /* statement: compound_statement  */
#line 200 "compiler/2_parser/parser.y"
                            { (yyval.node) = (yyvsp[0].node); }
#line 1602 "parser.tab.c"
    break;

  case 35: /* expression_statement: expression ';'  */
#line 204 "compiler/2_parser/parser.y"
                            { (yyval.node) = (yyvsp[-1].node); }
#line 1608 "parser.tab.c"
    break;

  case 36: /* expression_statement: ';'  */
#line 205 "compiler/2_parser/parser.y"
                            { (yyval.node) = NULL; }
#line 1614 "parser.tab.c"
    break;

  case 58: /* expression: expression ',' assignment_expression  */
#line 256 "compiler/2_parser/parser.y"
      {
          (yyval.node) = (yyvsp[0].node);
      }
#line 1622 "parser.tab.c"
    break;

  case 59: /* expression: assignment_expression  */
#line 260 "compiler/2_parser/parser.y"
      {
          (yyval.node) = (yyvsp[0].node);
      }
#line 1630 "parser.tab.c"
    break;

  case 60: /* assignment_expression: unary_expression '=' assignment_expression  */
#line 267 "compiler/2_parser/parser.y"
      {
          (yyval.node) = create_node(NODE_ASSIGNMENT, "=");
          (yyval.node)->left = (yyvsp[-2].node);
          (yyval.node)->right = (yyvsp[0].node);
      }
#line 1640 "parser.tab.c"
    break;

  case 61: /* assignment_expression: unary_expression ADD_ASSIGN assignment_expression  */
#line 272 "compiler/2_parser/parser.y"
                                                        { (yyval.node) = NULL; }
#line 1646 "parser.tab.c"
    break;

  case 62: /* assignment_expression: unary_expression SUB_ASSIGN assignment_expression  */
#line 273 "compiler/2_parser/parser.y"
                                                        { (yyval.node) = NULL; }
#line 1652 "parser.tab.c"
    break;

  case 63: /* assignment_expression: unary_expression MUL_ASSIGN assignment_expression  */
#line 274 "compiler/2_parser/parser.y"
                                                        { (yyval.node) = NULL; }
#line 1658 "parser.tab.c"
    break;

  case 64: /* assignment_expression: unary_expression DIV_ASSIGN assignment_expression  */
#line 275 "compiler/2_parser/parser.y"
                                                        { (yyval.node) = NULL; }
#line 1664 "parser.tab.c"
    break;

  case 65: /* assignment_expression: conditional_expression  */
#line 277 "compiler/2_parser/parser.y"
      {
          (yyval.node) = (yyvsp[0].node);
      }
#line 1672 "parser.tab.c"
    break;

  case 66: /* conditional_expression: logical_or_expression  */
#line 283 "compiler/2_parser/parser.y"
                              { (yyval.node) = (yyvsp[0].node); }
#line 1678 "parser.tab.c"
    break;

  case 67: /* conditional_expression: logical_or_expression '?' expression ':' conditional_expression  */
#line 284 "compiler/2_parser/parser.y"
                                                                      { (yyval.node) = NULL; }
#line 1684 "parser.tab.c"
    break;

  case 68: /* logical_or_expression: logical_or_expression OR logical_and_expression  */
#line 288 "compiler/2_parser/parser.y"
                                                      { (yyval.node) = NULL; }
#line 1690 "parser.tab.c"
    break;

  case 69: /* logical_or_expression: logical_and_expression  */
#line 289 "compiler/2_parser/parser.y"
                             { (yyval.node) = (yyvsp[0].node); }
#line 1696 "parser.tab.c"
    break;

  case 70: /* logical_and_expression: logical_and_expression AND equality_expression  */
#line 293 "compiler/2_parser/parser.y"
                                                     { (yyval.node) = NULL; }
#line 1702 "parser.tab.c"
    break;

  case 71: /* logical_and_expression: equality_expression  */
#line 294 "compiler/2_parser/parser.y"
                          { (yyval.node) = (yyvsp[0].node); }
#line 1708 "parser.tab.c"
    break;

  case 72: /* equality_expression: equality_expression EQ relational_expression  */
#line 298 "compiler/2_parser/parser.y"
                                                   { (yyval.node) = NULL; }
#line 1714 "parser.tab.c"
    break;

  case 73: /* equality_expression: equality_expression NEQ relational_expression  */
#line 299 "compiler/2_parser/parser.y"
                                                    { (yyval.node) = NULL; }
#line 1720 "parser.tab.c"
    break;

  case 74: /* equality_expression: relational_expression  */
#line 300 "compiler/2_parser/parser.y"
                            { (yyval.node) = (yyvsp[0].node); }
#line 1726 "parser.tab.c"
    break;

  case 75: /* relational_expression: relational_expression '<' additive_expression  */
#line 304 "compiler/2_parser/parser.y"
                                                    { (yyval.node) = NULL; }
#line 1732 "parser.tab.c"
    break;

  case 76: /* relational_expression: relational_expression '>' additive_expression  */
#line 305 "compiler/2_parser/parser.y"
                                                    { (yyval.node) = NULL; }
#line 1738 "parser.tab.c"
    break;

  case 77: /* relational_expression: relational_expression LE additive_expression  */
#line 306 "compiler/2_parser/parser.y"
                                                    { (yyval.node) = NULL; }
#line 1744 "parser.tab.c"
    break;

  case 78: /* relational_expression: relational_expression GE additive_expression  */
#line 307 "compiler/2_parser/parser.y"
                                                    { (yyval.node) = NULL; }
#line 1750 "parser.tab.c"
    break;

  case 79: /* relational_expression: additive_expression  */
#line 308 "compiler/2_parser/parser.y"
                          { (yyval.node) = (yyvsp[0].node); }
#line 1756 "parser.tab.c"
    break;

  case 80: /* additive_expression: additive_expression '+' multiplicative_expression  */
#line 313 "compiler/2_parser/parser.y"
      {
          (yyval.node) = create_node(NODE_BINARY_OP, "+");
          (yyval.node)->left = (yyvsp[-2].node);
          (yyval.node)->right = (yyvsp[0].node);
      }
#line 1766 "parser.tab.c"
    break;

  case 81: /* additive_expression: additive_expression '-' multiplicative_expression  */
#line 319 "compiler/2_parser/parser.y"
      {
          (yyval.node) = create_node(NODE_BINARY_OP, "-");
          (yyval.node)->left = (yyvsp[-2].node);
          (yyval.node)->right = (yyvsp[0].node);
      }
#line 1776 "parser.tab.c"
    break;

  case 82: /* additive_expression: multiplicative_expression  */
#line 325 "compiler/2_parser/parser.y"
      {
          (yyval.node) = (yyvsp[0].node);
      }
#line 1784 "parser.tab.c"
    break;

  case 83: /* multiplicative_expression: multiplicative_expression '*' unary_expression  */
#line 332 "compiler/2_parser/parser.y"
      {
          (yyval.node) = create_node(NODE_BINARY_OP, "*");
          (yyval.node)->left = (yyvsp[-2].node);
          (yyval.node)->right = (yyvsp[0].node);
      }
#line 1794 "parser.tab.c"
    break;

  case 84: /* multiplicative_expression: multiplicative_expression '/' unary_expression  */
#line 338 "compiler/2_parser/parser.y"
      {
          (yyval.node) = create_node(NODE_BINARY_OP, "/");
          (yyval.node)->left = (yyvsp[-2].node);
          (yyval.node)->right = (yyvsp[0].node);
      }
#line 1804 "parser.tab.c"
    break;

  case 85: /* multiplicative_expression: multiplicative_expression '%' unary_expression  */
#line 344 "compiler/2_parser/parser.y"
      {
          (yyval.node) = create_node(NODE_BINARY_OP, "%");
          (yyval.node)->left = (yyvsp[-2].node);
          (yyval.node)->right = (yyvsp[0].node);
      }
#line 1814 "parser.tab.c"
    break;

  case 86: /* multiplicative_expression: unary_expression  */
#line 350 "compiler/2_parser/parser.y"
      {
          (yyval.node) = (yyvsp[0].node);
      }
#line 1822 "parser.tab.c"
    break;

  case 87: /* unary_expression: postfix_expression  */
#line 356 "compiler/2_parser/parser.y"
                         { (yyval.node) = (yyvsp[0].node); }
#line 1828 "parser.tab.c"
    break;

  case 88: /* unary_expression: INC unary_expression  */
#line 358 "compiler/2_parser/parser.y"
      {
          (yyval.node) = create_node(NODE_UNARY_OP, "++");
          (yyval.node)->left = (yyvsp[0].node);
      }
#line 1837 "parser.tab.c"
    break;

  case 89: /* unary_expression: DEC unary_expression  */
#line 363 "compiler/2_parser/parser.y"
      {
          (yyval.node) = create_node(NODE_UNARY_OP, "--");
          (yyval.node)->left = (yyvsp[0].node);
      }
#line 1846 "parser.tab.c"
    break;

  case 90: /* unary_expression: '&' unary_expression  */
#line 368 "compiler/2_parser/parser.y"
      {
          (yyval.node) = create_node(NODE_UNARY_OP, "&");
          (yyval.node)->left = (yyvsp[0].node);
      }
#line 1855 "parser.tab.c"
    break;

  case 91: /* unary_expression: '*' unary_expression  */
#line 373 "compiler/2_parser/parser.y"
      {
          (yyval.node) = create_node(NODE_UNARY_OP, "*");
          (yyval.node)->left = (yyvsp[0].node);
      }
#line 1864 "parser.tab.c"
    break;

  case 92: /* unary_expression: '-' unary_expression  */
#line 378 "compiler/2_parser/parser.y"
      {
          (yyval.node) = create_node(NODE_UNARY_OP, "-");
          (yyval.node)->left = (yyvsp[0].node);
      }
#line 1873 "parser.tab.c"
    break;

  case 93: /* unary_expression: '!' unary_expression  */
#line 383 "compiler/2_parser/parser.y"
      {
          (yyval.node) = create_node(NODE_UNARY_OP, "!");
          (yyval.node)->left = (yyvsp[0].node);
      }
#line 1882 "parser.tab.c"
    break;

  case 94: /* unary_expression: SIZEOF unary_expression  */
#line 388 "compiler/2_parser/parser.y"
      {
          (yyval.node) = create_node(NODE_UNARY_OP, "sizeof");
          (yyval.node)->left = (yyvsp[0].node);
      }
#line 1891 "parser.tab.c"
    break;

  case 95: /* unary_expression: '(' type_specifier ')' unary_expression  */
#line 393 "compiler/2_parser/parser.y"
      {
          (yyval.node) = create_node(NODE_UNARY_OP, "cast");
          (yyval.node)->left = (yyvsp[0].node);
      }
#line 1900 "parser.tab.c"
    break;

  case 96: /* postfix_expression: primary_expression  */
#line 400 "compiler/2_parser/parser.y"
                         { (yyval.node) = (yyvsp[0].node); }
#line 1906 "parser.tab.c"
    break;

  case 97: /* postfix_expression: postfix_expression '[' expression ']'  */
#line 401 "compiler/2_parser/parser.y"
                                            { (yyval.node) = NULL; }
#line 1912 "parser.tab.c"
    break;

  case 98: /* postfix_expression: postfix_expression '(' argument_list_opt ')'  */
#line 402 "compiler/2_parser/parser.y"
                                                   { (yyval.node) = NULL; }
#line 1918 "parser.tab.c"
    break;

  case 99: /* postfix_expression: postfix_expression INC  */
#line 403 "compiler/2_parser/parser.y"
                             { (yyval.node) = NULL; }
#line 1924 "parser.tab.c"
    break;

  case 100: /* postfix_expression: postfix_expression DEC  */
#line 404 "compiler/2_parser/parser.y"
                             { (yyval.node) = NULL; }
#line 1930 "parser.tab.c"
    break;

  case 101: /* primary_expression: IDENTIFIER  */
#line 408 "compiler/2_parser/parser.y"
                         { (yyval.node) = create_node(NODE_IDENTIFIER, (yyvsp[0].sval)); }
#line 1936 "parser.tab.c"
    break;

  case 102: /* primary_expression: STRING_LITERAL  */
#line 409 "compiler/2_parser/parser.y"
                         { (yyval.node) = create_node(NODE_STRING_LITERAL, (yyvsp[0].sval)); }
#line 1942 "parser.tab.c"
    break;

  case 103: /* primary_expression: INT_LITERAL  */
#line 410 "compiler/2_parser/parser.y"
                         { (yyval.node) = create_node(NODE_INT_LITERAL, (yyvsp[0].sval)); }
#line 1948 "parser.tab.c"
    break;

  case 104: /* primary_expression: FLOAT_LITERAL  */
#line 411 "compiler/2_parser/parser.y"
                         { (yyval.node) = create_node(NODE_FLOAT_LITERAL, (yyvsp[0].sval)); }
#line 1954 "parser.tab.c"
    break;

  case 105: /* primary_expression: '(' expression ')'  */
#line 412 "compiler/2_parser/parser.y"
                         { (yyval.node) = (yyvsp[-1].node); }
#line 1960 "parser.tab.c"
    break;


#line 1964 "parser.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 429 "compiler/2_parser/parser.y"


void yyerror(const char *s) {
    fprintf(stderr, "Parser Error: %s at line %d\n", s, line_num);
}
