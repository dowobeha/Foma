/* A Bison parser, made by GNU Bison 3.7.5.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_REGEX_H_INCLUDED
# define YY_YY_REGEX_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    NET = 258,                     /* NET  */
    END = 259,                     /* END  */
    LBRACKET = 260,                /* LBRACKET  */
    RBRACKET = 261,                /* RBRACKET  */
    LPAREN = 262,                  /* LPAREN  */
    RPAREN = 263,                  /* RPAREN  */
    ENDM = 264,                    /* ENDM  */
    ENDD = 265,                    /* ENDD  */
    CRESTRICT = 266,               /* CRESTRICT  */
    CONTAINS = 267,                /* CONTAINS  */
    CONTAINS_OPT_ONE = 268,        /* CONTAINS_OPT_ONE  */
    CONTAINS_ONE = 269,            /* CONTAINS_ONE  */
    XUPPER = 270,                  /* XUPPER  */
    XLOWER = 271,                  /* XLOWER  */
    FLAG_ELIMINATE = 272,          /* FLAG_ELIMINATE  */
    IGNORE_ALL = 273,              /* IGNORE_ALL  */
    IGNORE_INTERNAL = 274,         /* IGNORE_INTERNAL  */
    CONTEXT = 275,                 /* CONTEXT  */
    NCONCAT = 276,                 /* NCONCAT  */
    MNCONCAT = 277,                /* MNCONCAT  */
    MORENCONCAT = 278,             /* MORENCONCAT  */
    LESSNCONCAT = 279,             /* LESSNCONCAT  */
    DOUBLE_COMMA = 280,            /* DOUBLE_COMMA  */
    COMMA = 281,                   /* COMMA  */
    SHUFFLE = 282,                 /* SHUFFLE  */
    PRECEDES = 283,                /* PRECEDES  */
    FOLLOWS = 284,                 /* FOLLOWS  */
    RIGHT_QUOTIENT = 285,          /* RIGHT_QUOTIENT  */
    LEFT_QUOTIENT = 286,           /* LEFT_QUOTIENT  */
    INTERLEAVE_QUOTIENT = 287,     /* INTERLEAVE_QUOTIENT  */
    UQUANT = 288,                  /* UQUANT  */
    EQUANT = 289,                  /* EQUANT  */
    VAR = 290,                     /* VAR  */
    IN = 291,                      /* IN  */
    IMPLIES = 292,                 /* IMPLIES  */
    BICOND = 293,                  /* BICOND  */
    EQUALS = 294,                  /* EQUALS  */
    NEQ = 295,                     /* NEQ  */
    SUBSTITUTE = 296,              /* SUBSTITUTE  */
    SUCCESSOR_OF = 297,            /* SUCCESSOR_OF  */
    PRIORITY_UNION_U = 298,        /* PRIORITY_UNION_U  */
    PRIORITY_UNION_L = 299,        /* PRIORITY_UNION_L  */
    LENIENT_COMPOSE = 300,         /* LENIENT_COMPOSE  */
    TRIPLE_DOT = 301,              /* TRIPLE_DOT  */
    LDOT = 302,                    /* LDOT  */
    RDOT = 303,                    /* RDOT  */
    FUNCTION = 304,                /* FUNCTION  */
    SUBVAL = 305,                  /* SUBVAL  */
    ISUNAMBIGUOUS = 306,           /* ISUNAMBIGUOUS  */
    ISIDENTITY = 307,              /* ISIDENTITY  */
    ISFUNCTIONAL = 308,            /* ISFUNCTIONAL  */
    NOTID = 309,                   /* NOTID  */
    LOWERUNIQ = 310,               /* LOWERUNIQ  */
    LOWERUNIQEPS = 311,            /* LOWERUNIQEPS  */
    ALLFINAL = 312,                /* ALLFINAL  */
    UNAMBIGUOUSPART = 313,         /* UNAMBIGUOUSPART  */
    AMBIGUOUSPART = 314,           /* AMBIGUOUSPART  */
    AMBIGUOUSDOMAIN = 315,         /* AMBIGUOUSDOMAIN  */
    EQSUBSTRINGS = 316,            /* EQSUBSTRINGS  */
    LETTERMACHINE = 317,           /* LETTERMACHINE  */
    MARKFSMTAIL = 318,             /* MARKFSMTAIL  */
    MARKFSMTAILLOOP = 319,         /* MARKFSMTAILLOOP  */
    MARKFSMMIDLOOP = 320,          /* MARKFSMMIDLOOP  */
    MARKFSMLOOP = 321,             /* MARKFSMLOOP  */
    ADDSINK = 322,                 /* ADDSINK  */
    LEFTREWR = 323,                /* LEFTREWR  */
    FLATTEN = 324,                 /* FLATTEN  */
    SUBLABEL = 325,                /* SUBLABEL  */
    CLOSESIGMA = 326,              /* CLOSESIGMA  */
    CLOSESIGMAUNK = 327,           /* CLOSESIGMAUNK  */
    ARROW = 328,                   /* ARROW  */
    DIRECTION = 329,               /* DIRECTION  */
    COMPOSE = 330,                 /* COMPOSE  */
    CROSS_PRODUCT = 331,           /* CROSS_PRODUCT  */
    HIGH_CROSS_PRODUCT = 332,      /* HIGH_CROSS_PRODUCT  */
    UNION = 333,                   /* UNION  */
    INTERSECT = 334,               /* INTERSECT  */
    MINUS = 335,                   /* MINUS  */
    COMPLEMENT = 336,              /* COMPLEMENT  */
    KLEENE_STAR = 337,             /* KLEENE_STAR  */
    KLEENE_PLUS = 338,             /* KLEENE_PLUS  */
    REVERSE = 339,                 /* REVERSE  */
    INVERSE = 340,                 /* INVERSE  */
    TERM_NEGATION = 341            /* TERM_NEGATION  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 198 "regex.y"

     char *string;
     struct fsm *net;
     int  type;

#line 156 "regex.h"

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



int yyparse (void *scanner, struct defined_networks *defined_nets, struct defined_functions *defined_funcs);

#endif /* !YY_YY_REGEX_H_INCLUDED  */
