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
#line 2 "crc.y" /* yacc.c:339  */

#include <stdio.h>
#include <string.h>
#include "nv40_shader.h"

void yyrestart ( FILE *input_file  );

#define uint32 unsigned int
#define uint32_t unsigned int

//#include "../../src/shaders/fragment.h"
void yyerror(const char *str);

uint32 endian_fp( uint32 v )
{
  return ( ( ( v >> 16 ) & 0xffff ) << 0 ) |
         ( ( ( v >> 0 ) & 0xffff ) << 16 );

}


#define NV40_FP_DEST_MASK(x,y,z,w)  ((w<<3)|(z<<2)|(y<<1)|x)
#define NV40_FP_SWIZZLE(x,y,z,w)  ((w<<6)|(z<<4)|(y<<2)|x)


uint32 fp_inst[4];
float  f[256];


uint32 inst_stack[256][4];
uint32 swizzles[4];
int swz_ptr = 0;

int inst_ptr = 0;
int n;
int v;
int h;
int type = 0;
int src_ptr = 0;
int mod = 0;
int neg = 0;
int cnst = 0;
int last_cmd = 0;
int max_reg = 0;
int creg = 0;
const char *outfile;

typedef union
{
	float f;
	int i;
}f2i;


void dump()
{
	if( fp_inst[0] == 0 )
	{
		cnst = 0;
		return;
	}
	inst_stack[inst_ptr][0] = fp_inst[0];
	inst_stack[inst_ptr][1] = fp_inst[1];
	inst_stack[inst_ptr][2] = fp_inst[2];
	inst_stack[inst_ptr][3] = fp_inst[3];
	
	++inst_ptr;
	last_cmd = 1;

	if( cnst )
	{
		f2i c;
		c.f = f[0];
		inst_stack[inst_ptr][0] = c.i;
		c.f = f[1];
		inst_stack[inst_ptr][1] = c.i;
		c.f = f[2];
		inst_stack[inst_ptr][2] = c.i;
		c.f = f[3];
		inst_stack[inst_ptr][3]	= c.i;
		++inst_ptr;
		last_cmd = 2;
		
	}
	cnst = 0;
	
	
}

void print()
{
	//printf( "asdasdasd" );
	//inst_stack[inst_ptr - 1][3] |= NV40_VP_INST_LAST;
	uint32 i;
	inst_stack[inst_ptr - last_cmd][0] |= NV40_FP_OP_PROGRAM_END;
	for( i = 0; i < inst_ptr; ++i )
	{
		printf( "%8x %8x %8x %8x \n", inst_stack[i][0], inst_stack[i][1], inst_stack[i][2], inst_stack[i][3]  );
		inst_stack[i][0] = endian_fp( inst_stack[i][0] );
		inst_stack[i][1] = endian_fp( inst_stack[i][1] );
		inst_stack[i][2] = endian_fp( inst_stack[i][2] );
		inst_stack[i][3] = endian_fp( inst_stack[i][3] );
		
	}

	
	//fragment_shader_desc_t desc;
    char name[512];
	
	char *pt=strstr(outfile,".h");

    if(!pt) {strcpy(name, outfile); strcat(name, ".h"); outfile = name; pt=strstr(outfile,".h");}

	#if 0
    if(!pt)
	{
	FILE *out = fopen( outfile, "wb" );
	if( out )
	{
	    desc.aux[0] = 0xcafebabe;
	    desc.dword_length = inst_ptr * 4;
	    desc.num_regs = max_reg;
	    fwrite( &desc, sizeof( desc ), 1, out );
	    fwrite( &inst_stack[0][0], 4 * desc.dword_length, 1, out );
	    fclose( out );
	    printf( "fp regs %x \n", max_reg );
	    	
	} 
	}
	else
    #endif
	{
	FILE *out = fopen( outfile, "w" );
	if( out )
	{
        unsigned *punt;
        int n;
        

        *pt=0;

        strcpy(name, outfile);
	    
	    fprintf(out,"/* Fragment Program - Output by Hermes / www.elotrolado.net\nOriginal work by Peter S. Popov */\n\n");

        fprintf(out,"#include <rsx/commands.h>\n\n");

        fprintf(out,"realityFragmentProgram nv30_fp_%s = {\n", name);

	    fprintf(out,".num_regs = %i,\n", max_reg);
	    fprintf(out,".size = (%i*4),\n", inst_ptr);
	    fprintf(out,".data = {\n");
	    
        punt=(unsigned *) &inst_stack[0][0];

	    for(n=0;n<inst_ptr * 4;n++)
	    {
		if(n==0) fprintf(out,"    0x%x", endian_fp(punt[n]));
		else
		if((n & 3)==0) fprintf(out,",\n    0x%x", endian_fp(punt[n]));
		else fprintf(out,", 0x%x", endian_fp(punt[n]));
	   
	    }
	    fprintf(out,"\n}\n};\n\n// End\n\n");
	    fclose( out );
	    printf( "fp regs %x \n", max_reg );
	    	
	} 
	
	}
	inst_ptr = 0;
}

void clean()
{
	
	fp_inst[0] = 0;
	fp_inst[1] = 0;
	fp_inst[2] = 0;
	fp_inst[3] = 0;
	src_ptr = 0;
	type = 0;
	mod = 0;
	neg = 0;
}

void opv( uint32 op )
{
	if( op == 0xff )
	{
	 	op = 0;
	}
	
	printf( "opv code 0x%2x ", op );
	fp_inst[0] &= ~NV40_FP_OP_OPCODE_MASK; 
  	fp_inst[0] |= ( op <<  NV40_FP_OP_OPCODE_SHIFT); 
	
}

void msk( uint32 ms )
{
	printf( "ms %x %x %x %x ", ( ms >> 0 ) & 1, ( ms >> 1 ) & 1, ( ms >> 2 ) & 1, ( ms >> 3 ) & 1  );
	fp_inst[0] &= ~NV40_FP_OP_OUTMASK_MASK; 
  	fp_inst[0] |= ( ms << NV40_FP_OP_OUTMASK_SHIFT ); 

}

void cnd_msk( uint32 cn )
{
	fp_inst[1] &= ~NV40_FP_OP_COND_MASK;
	fp_inst[1] |= ( cn << NV40_FP_OP_COND_SHIFT );
	printf( "cnd %d ", cn );
	
}

void sat( uint32 s )
{
	printf( "sat %x ", s );
	fp_inst[0] &= ~NV40_FP_OP_OUT_SAT;
	if( s )
	{	
		fp_inst[0] |= NV40_FP_OP_OUT_SAT;	
	}

}

void cnd( uint32 s )
{
	printf( "cnd %x \n", s );
	fp_inst[0] &= ~NV40_FP_OP_COND_WRITE_ENABLE;
	if( s )
	{	
		fp_inst[0] |= NV40_FP_OP_COND_WRITE_ENABLE;	
	}

}
	

void com( uint32 s )
{
	swizzles[swz_ptr++] = s;
}

void set_input( uint32 in )
{
	type = 1;
	fp_inst[0] &= ~NV40_FP_OP_INPUT_SRC_MASK;
	fp_inst[0] |= ( in << NV40_FP_OP_INPUT_SRC_SHIFT );
	printf( "inp %d ", in  );
	
}

uint32 get_swizzle()
{
	int st;
	uint32 r;
	if( swz_ptr == 0 )
	{
		swizzles[0] = 0;
		swizzles[1] = 1;
		swizzles[2] = 2;
		swizzles[3] = 3;
		               	
	}
	else
	{
		for( st = swz_ptr; st < 4; ++st )
		{
			swizzles[st] = swizzles[swz_ptr - 1];
		} 
	}
	swz_ptr = 0;
	
	r = NV40_FP_SWIZZLE( swizzles[0], swizzles[1], swizzles[2], swizzles[3] );
	printf( "swz = %x %x %x %x ", swizzles[0], swizzles[1], swizzles[2], swizzles[3] );
	return r;
	
}

void prc( uint32 s )
{
	printf( "prc %x ", s );
	fp_inst[0] &= ~NV40_FP_OP_PRECISION_MASK;
	if( s )
	{	
		fp_inst[0] |= ( s << NV40_FP_OP_PRECISION_SHIFT );	
	}
}

void set_cns()
{
	type = 2;
}

void set_tex( uint32 r )
{
	fp_inst[0] &= ~( NV40_FP_OP_TEX_UNIT_MASK );
	fp_inst[0] |= ( r << NV40_FP_OP_TEX_UNIT_SHIFT );
	
	printf( "tex %d \n", r );
}

void src_reg( uint32 reg )
{

	fp_inst[src_ptr + 1] &= ~NV40_FP_REG_TYPE_MASK;
	fp_inst[src_ptr + 1] |= ( type << NV40_FP_REG_TYPE_SHIFT );

	fp_inst[src_ptr + 1] &= ~NV40_FP_REG_UNK_0;
	if( h )
	{
		fp_inst[src_ptr + 1] |= NV40_FP_REG_UNK_0;
	
	}
	
	fp_inst[src_ptr + 1] &= ~NV40_FP_REG_NEGATE;
	if( neg )
	{
		fp_inst[src_ptr + 1] |= NV40_FP_REG_NEGATE;
	}
	fp_inst[src_ptr + 1] &= ~NV40_FP_REG_SRC_MASK;
	fp_inst[src_ptr + 1] |= ( reg << NV40_FP_REG_SRC_SHIFT );
	
	fp_inst[src_ptr + 1] &= ~NV40_FP_REG_SWZ_ALL_MASK;
	fp_inst[src_ptr + 1] |= ( get_swizzle() << NV40_FP_REG_SWZ_ALL_SHIFT );
	
	printf( "... src %s %2d type %d neg %d \n", h ? "h" : "r", reg, type, neg  );
	src_ptr++;
	type = 0;
	neg = 0;
		
}

        
void out_reg( uint32 reg )
{
	uint32 reg_num =  h ? reg / 2 + 2: reg + 2;
	if( creg == 0 && reg_num > max_reg )
	{
		max_reg = reg_num;
	}
	fp_inst[0] &= ~NV40_FP_OP_UNK0_7;
	if( h )
	{
		fp_inst[0] |= NV40_FP_OP_UNK0_7;
	
	}
	
	
	fp_inst[0] &= ~NV40_FP_OP_OUT_REG_MASK;
	fp_inst[0] |= ( reg << NV40_FP_OP_OUT_REG_SHIFT );
	printf( "out %s %2d ", h ? "h" : "r", reg  );	
	creg = 0;
}

void cnd_swz()
{
	fp_inst[1] &= ~NV40_FP_OP_COND_SWZ_ALL_MASK;
	fp_inst[1] |= ( get_swizzle() << NV40_FP_OP_COND_SWZ_ALL_SHIFT );
	
}


#line 430 "y.tab.c" /* yacc.c:339  */

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
    _0 = 258,
    _1 = 259,
    _2 = 260,
    _3 = 261,
    _4 = 262,
    _5 = 263,
    _6 = 264,
    _7 = 265,
    _8 = 266,
    _9 = 267,
    _1D = 268,
    _2D = 269,
    _3D = 270,
    DOT = 271,
    CONST = 272,
    C = 273,
    WHITE = 274,
    DEC = 275,
    WORD = 276,
    SAT = 277,
    H = 278,
    END = 279,
    POW = 280,
    BEG = 281,
    CUBE = 282,
    RECT = 283,
    COLR = 284,
    COLH = 285,
    DEPR = 286,
    WPOS = 287,
    COL0 = 288,
    COL1 = 289,
    FOGC = 290,
    F = 291,
    R = 292,
    X = 293,
    Y = 294,
    Z = 295,
    W = 296,
    EQ = 297,
    GE = 298,
    GT = 299,
    LE = 300,
    LT = 301,
    NE = 302,
    TR = 303,
    FL = 304,
    DDX = 305,
    DDY = 306,
    FLR = 307,
    FRC = 308,
    LIT = 309,
    MOV = 310,
    PK2H = 311,
    PK2US = 312,
    PK4B = 313,
    PK4UB = 314,
    COS = 315,
    EXP = 316,
    LG2 = 317,
    RCP = 318,
    RSQ = 319,
    SIN = 320,
    UP2H = 321,
    UP2US = 322,
    UP4B = 323,
    UP4UB = 324,
    ADD = 325,
    DP3 = 326,
    DP4 = 327,
    DST = 328,
    MAX = 329,
    MIN = 330,
    MUL = 331,
    RFL = 332,
    SEQ = 333,
    SFL = 334,
    SGE = 335,
    SGT = 336,
    SLE = 337,
    SLT = 338,
    SNE = 339,
    STR = 340,
    SUB = 341,
    MAD = 342,
    LRP = 343,
    X2D = 344,
    KIL = 345,
    TEX = 346,
    TXP = 347,
    TXD = 348
  };
#endif
/* Tokens.  */
#define _0 258
#define _1 259
#define _2 260
#define _3 261
#define _4 262
#define _5 263
#define _6 264
#define _7 265
#define _8 266
#define _9 267
#define _1D 268
#define _2D 269
#define _3D 270
#define DOT 271
#define CONST 272
#define C 273
#define WHITE 274
#define DEC 275
#define WORD 276
#define SAT 277
#define H 278
#define END 279
#define POW 280
#define BEG 281
#define CUBE 282
#define RECT 283
#define COLR 284
#define COLH 285
#define DEPR 286
#define WPOS 287
#define COL0 288
#define COL1 289
#define FOGC 290
#define F 291
#define R 292
#define X 293
#define Y 294
#define Z 295
#define W 296
#define EQ 297
#define GE 298
#define GT 299
#define LE 300
#define LT 301
#define NE 302
#define TR 303
#define FL 304
#define DDX 305
#define DDY 306
#define FLR 307
#define FRC 308
#define LIT 309
#define MOV 310
#define PK2H 311
#define PK2US 312
#define PK4B 313
#define PK4UB 314
#define COS 315
#define EXP 316
#define LG2 317
#define RCP 318
#define RSQ 319
#define SIN 320
#define UP2H 321
#define UP2US 322
#define UP4B 323
#define UP4UB 324
#define ADD 325
#define DP3 326
#define DP4 327
#define DST 328
#define MAX 329
#define MIN 330
#define MUL 331
#define RFL 332
#define SEQ 333
#define SFL 334
#define SGE 335
#define SGT 336
#define SLE 337
#define SLT 338
#define SNE 339
#define STR 340
#define SUB 341
#define MAD 342
#define LRP 343
#define X2D 344
#define KIL 345
#define TEX 346
#define TXP 347
#define TXD 348

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 667 "y.tab.c" /* yacc.c:358  */

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
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   265

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  106
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  61
/* YYNRULES -- Number of rules.  */
#define YYNRULES  172
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  268

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   348

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
      97,    98,     2,   103,    95,   104,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    94,
       2,   105,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   100,     2,   101,     2,     2,     2,     2,     2,     2,
       2,     2,    99,     2,     2,     2,     2,     2,     2,     2,
       2,   102,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    96,     2,     2,     2,     2,     2,
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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   377,   377,   377,   380,   381,   383,   385,   389,   392,
     395,   396,   397,   398,   399,   400,   401,   402,   403,   406,
     409,   412,   415,   419,   422,   425,   429,   433,   434,   435,
     436,   440,   441,   444,   445,   448,   452,   453,   454,   455,
     456,   457,   458,   459,   460,   461,   464,   465,   466,   467,
     468,   469,   470,   471,   472,   473,   476,   479,   480,   481,
     482,   483,   484,   485,   486,   487,   488,   489,   490,   491,
     492,   497,   498,   501,   505,   506,   509,   513,   514,   517,
     521,   522,   525,   526,   530,   534,   535,   539,   543,   544,
     548,   549,   552,   555,   556,   557,   558,   559,   560,   561,
     562,   566,   567,   568,   569,   570,   571,   572,   573,   574,
     575,   576,   577,   578,   579,   580,   581,   585,   586,   589,
     593,   594,   595,   596,   597,   600,   600,   604,   605,   606,
     607,   608,   609,   610,   611,   612,   613,   618,   619,   623,
     624,   627,   628,   631,   635,   636,   637,   642,   645,   646,
     647,   648,   648,   652,   653,   654,   655,   658,   661,   666,
     667,   668,   669,   670,   674,   675,   679,   680,   681,   685,
     689,   691,   693
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "_0", "_1", "_2", "_3", "_4", "_5", "_6",
  "_7", "_8", "_9", "_1D", "_2D", "_3D", "DOT", "CONST", "C", "WHITE",
  "DEC", "WORD", "SAT", "H", "END", "POW", "BEG", "CUBE", "RECT", "COLR",
  "COLH", "DEPR", "WPOS", "COL0", "COL1", "FOGC", "F", "R", "X", "Y", "Z",
  "W", "EQ", "GE", "GT", "LE", "LT", "NE", "TR", "FL", "DDX", "DDY", "FLR",
  "FRC", "LIT", "MOV", "PK2H", "PK2US", "PK4B", "PK4UB", "COS", "EXP",
  "LG2", "RCP", "RSQ", "SIN", "UP2H", "UP2US", "UP4B", "UP4UB", "ADD",
  "DP3", "DP4", "DST", "MAX", "MIN", "MUL", "RFL", "SEQ", "SFL", "SGE",
  "SGT", "SLE", "SLT", "SNE", "STR", "SUB", "MAD", "LRP", "X2D", "KIL",
  "TEX", "TXP", "TXD", "';'", "','", "'|'", "'('", "')'", "'f'", "'['",
  "']'", "'o'", "'+'", "'-'", "'='", "$accept", "program", "$@1",
  "instructionSequence", "space", "empty", "instructionStatement",
  "instruction", "VECTORop_instruction", "SCALARop_instruction",
  "BINSCop_instruction", "BINop_instruction", "TRIop_instruction",
  "KILop_instruction", "TEXop_instruction", "TXDop_instruction", "prec",
  "cond", "sat", "pref", "VECTORop", "SCALARop", "BINSCop", "BINop",
  "TRIop", "KILop", "TEXop", "TXDop", "scalarSrc", "absScalarSrc",
  "baseScalarSrc", "vectorSrc", "absVectorSrc", "baseVectorSrc",
  "maskedDstReg", "dstRegister", "optionalCCMask", "ccMask", "ccMaskRule",
  "optionalWriteMask", "srcRegister", "fragAttribReg", "fragAttribRegId",
  "fragTempReg", "NUMBER", "decCalc", "fragF32Reg", "fragF16Reg",
  "fragOutputReg", "fragOutputRegName", "scalarSuffix", "swizzleSuffix",
  "component", "texImageId", "texImageUnit", "texImageTarget",
  "vectorConstant", "negate", "localDeclaration", "namedLocalParameter",
  "optionalLocalValue", YY_NULLPTR
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
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,    59,    44,   124,    40,    41,   102,
      91,    93,   111,    43,    45,    61
};
# endif

#define YYPACT_NINF -178

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-178)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       9,    29,    50,  -178,   152,  -178,    35,  -178,  -178,  -178,
    -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,
    -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,
    -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,
    -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,   152,  -178,
     -38,  -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,   -10,
     -10,   -10,   -10,   -10,    59,   -10,   -10,  -178,  -178,    58,
      69,  -178,  -178,  -178,  -178,  -178,    77,    35,    35,    35,
      35,    35,  -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,
    -178,    81,    35,    35,  -178,     4,  -178,  -178,   100,   -17,
     -17,   -17,   -17,   -17,   111,  -178,   -17,   -17,    12,  -178,
    -178,  -178,    62,   109,    26,    39,   148,  -178,  -178,  -178,
    -178,    71,    72,    73,    74,  -178,  -178,  -178,  -178,   111,
      75,    76,  -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,
    -178,  -178,  -178,  -178,  -178,  -178,  -178,   136,  -178,   136,
      57,    29,   117,    68,    29,    29,    29,    29,   111,    29,
      29,  -178,  -178,  -178,  -178,    78,   -43,  -178,   120,    43,
     132,  -178,    59,  -178,   -43,  -178,    79,    80,    83,   111,
      85,    86,  -178,  -178,  -178,    29,    29,    -7,   122,   135,
    -178,   141,  -178,  -178,    88,    29,    29,     0,    29,    29,
      29,  -178,    29,    29,  -178,  -178,   -43,    87,    81,  -178,
    -178,    81,   142,  -178,  -178,  -178,  -178,  -178,  -178,   -43,
     172,   172,  -178,  -178,    94,    99,  -178,    96,    97,     1,
       7,  -178,  -178,  -178,   102,     1,   111,  -178,  -178,    29,
     136,    29,    29,  -178,  -178,  -178,  -178,  -178,    91,  -178,
    -178,  -178,  -178,   136,   101,   104,  -178,    29,    29,   110,
    -178,  -178,  -178,  -178,  -178,  -178,    29,  -178
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     6,     0,     7,     0,     1,     0,    56,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,     2,     5,
       0,    11,    12,    13,    14,    15,    16,    17,    18,    30,
      30,    30,    30,    30,     0,    30,    30,    10,     8,     0,
       0,     4,     9,    28,    27,    29,    32,     0,     0,     0,
       0,     0,    93,    94,    95,    96,    97,    98,    99,   100,
      24,   152,     0,     0,   170,   171,     3,    31,    34,     0,
       0,     0,     0,     0,     0,    92,     0,     0,     0,   169,
      33,    35,     0,     0,     0,     0,   116,    88,   125,   126,
      89,     0,     0,     0,     0,   153,   154,   155,   156,   151,
       0,     0,   164,   165,   172,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   142,   137,   141,   140,   139,
       0,     6,     0,    91,     6,     6,     6,     6,   150,     6,
       6,   138,   144,   145,   146,     0,   166,    19,   101,   102,
     104,   108,     0,    87,   166,    20,     0,     0,     0,   149,
       0,     0,   143,   167,   168,     6,     6,     0,   103,   105,
     109,   106,   110,   112,     0,     6,     6,     0,     6,     6,
       6,   148,     6,     6,    82,    83,   166,     0,   152,   117,
     118,   152,   107,   111,   113,   114,    90,    77,    78,   166,
       0,     0,    21,    22,     0,     0,    25,     0,     0,     0,
       0,    86,    85,   115,     0,     0,     0,    81,    80,     6,
       0,     6,     6,    84,   120,   121,   122,   123,     0,   124,
      79,   147,    23,   158,     0,     0,   119,     6,     6,     0,
      26,   159,   160,   161,   162,   163,     6,   157
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -178,  -178,  -178,  -178,    -1,   -34,   181,  -178,  -178,  -178,
    -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,    70,
    -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,  -136,  -178,
     -19,  -148,  -178,    25,   -25,  -178,  -178,    65,  -178,  -178,
    -171,  -178,  -178,  -172,  -142,  -111,  -178,  -178,  -178,  -178,
      27,  -177,  -126,   -12,    17,  -178,  -107,  -170,  -178,  -178,
    -178
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,    70,    48,   166,    69,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    76,    98,   111,    77,
      59,    60,    61,    62,    63,    64,    65,    66,   175,   195,
     196,   167,   185,   186,   115,   116,   173,    90,    91,   153,
     208,   209,   248,   117,   146,   147,   118,   119,   120,   165,
     237,   105,   129,   226,   241,   266,   211,   187,    67,    95,
     109
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint16 yytable[] =
{
       4,   134,   149,   158,   197,   161,   112,   161,   177,   178,
     132,   180,   181,    73,   133,   210,   112,   132,   132,   176,
     113,   133,   133,   112,   112,   210,   220,    74,    75,   132,
     113,   231,   179,   133,   232,     1,   229,   113,   113,   244,
     245,   246,   247,    99,   100,   101,   102,   103,     3,   235,
       5,   223,   224,   201,    68,   227,    72,   210,   106,   107,
     183,   184,   222,   210,   220,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   121,   122,   123,   124,    94,
     145,   130,   131,   191,   192,   114,   162,   163,   164,   206,
     221,   252,   207,    96,   255,    97,   219,   104,   240,   207,
     207,    82,    83,    84,    85,    86,    87,    88,    89,   108,
     251,   161,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   110,   261,   262,   263,   150,   148,   221,   253,
      78,    79,    80,    81,   151,    92,    93,   264,   265,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   125,
     126,   127,   128,   174,   174,   168,   169,   170,   171,   188,
     189,   190,   212,   213,   152,   172,   154,   155,   156,   157,
     159,   160,     6,   193,   198,   199,   214,     7,   200,   182,
     202,   203,   215,   233,   204,   205,   216,   230,   236,   239,
     240,   242,   256,   243,   217,   218,   257,   174,   250,   258,
     234,   225,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    71,
      35,   228,    36,    37,    38,    39,    40,   194,    41,    42,
     254,    43,    44,    45,    46,    47,   260,   249,   238,     0,
       0,     0,     0,     0,     0,     0,   259,   225,     0,     0,
       0,     0,     0,     0,     0,   267
};

static const yytype_int16 yycheck[] =
{
       1,   108,   113,   129,   174,   147,    23,   149,   156,   157,
      17,   159,   160,    23,    21,   187,    23,    17,    17,   155,
      37,    21,    21,    23,    23,   197,   197,    37,    38,    17,
      37,   208,   158,    21,   211,    26,   206,    37,    37,    32,
      33,    34,    35,    77,    78,    79,    80,    81,    19,   219,
       0,   199,   200,   179,    19,   203,    94,   229,    92,    93,
     103,   104,   198,   235,   235,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,   100,   101,   102,   103,    21,
      18,   106,   107,    40,    41,   102,    29,    30,    31,    96,
     197,   239,    99,    24,   242,    18,    96,    16,    91,    99,
      99,    42,    43,    44,    45,    46,    47,    48,    49,   105,
     236,   253,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    22,    13,    14,    15,   100,    18,   235,   240,
      60,    61,    62,    63,    95,    65,    66,    27,    28,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    38,
      39,    40,    41,   154,   155,    38,    39,    40,    41,    39,
      40,    41,    40,    41,    16,    97,    95,    95,    95,    95,
      95,    95,    20,    41,    95,    95,    41,    25,    95,   101,
      95,    95,    41,    41,   185,   186,    98,   100,    16,    95,
      91,    95,   101,    96,   195,   196,    95,   198,    96,    95,
     219,   202,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    48,
      78,   206,    80,    81,    82,    83,    84,   172,    86,    87,
     241,    89,    90,    91,    92,    93,   258,   230,   221,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   257,   258,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   266
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    26,   107,    19,   110,     0,    20,    25,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    78,    80,    81,    82,    83,
      84,    86,    87,    89,    90,    91,    92,    93,   109,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   126,
     127,   128,   129,   130,   131,   132,   133,   164,    19,   111,
     108,   112,    94,    23,    37,    38,   122,   125,   125,   125,
     125,   125,    42,    43,    44,    45,    46,    47,    48,    49,
     143,   144,   125,   125,    21,   165,    24,    18,   123,   111,
     111,   111,   111,   111,    16,   157,   111,   111,   105,   166,
      22,   124,    23,    37,   102,   140,   141,   149,   152,   153,
     154,   140,   140,   140,   140,    38,    39,    40,    41,   158,
     140,   140,    17,    21,   162,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    18,   150,   151,    18,   151,
     100,    95,    16,   145,    95,    95,    95,    95,   158,    95,
      95,   150,    29,    30,    31,   155,   110,   137,    38,    39,
      40,    41,    97,   142,   110,   134,   134,   137,   137,   158,
     137,   137,   101,   103,   104,   138,   139,   163,    39,    40,
      41,    40,    41,    41,   143,   135,   136,   163,    95,    95,
      95,   158,    95,    95,   110,   110,    96,    99,   146,   147,
     149,   162,    40,    41,    41,    41,    98,   110,   110,    96,
     146,   162,   134,   137,   137,   110,   159,   137,   139,   163,
     100,   157,   157,    41,   136,   163,    16,   156,   156,    95,
      91,   160,    95,    96,    32,    33,    34,    35,   148,   160,
      96,   158,   137,   151,   110,   137,   101,    95,    95,   110,
     159,    13,    14,    15,    27,    28,   161,   110
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   106,   108,   107,   109,   109,   110,   110,   111,   112,
     113,   113,   113,   113,   113,   113,   113,   113,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   122,   122,
     122,   123,   123,   124,   124,   125,   126,   126,   126,   126,
     126,   126,   126,   126,   126,   126,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   128,   129,   129,   129,
     129,   129,   129,   129,   129,   129,   129,   129,   129,   129,
     129,   130,   130,   131,   132,   132,   133,   134,   134,   135,
     136,   136,   137,   137,   138,   139,   139,   140,   141,   141,
     142,   142,   143,   144,   144,   144,   144,   144,   144,   144,
     144,   145,   145,   145,   145,   145,   145,   145,   145,   145,
     145,   145,   145,   145,   145,   145,   145,   146,   146,   147,
     148,   148,   148,   148,   148,   149,   149,   150,   150,   150,
     150,   150,   150,   150,   150,   150,   150,   151,   151,   152,
     152,   153,   153,   154,   155,   155,   155,   156,   157,   157,
     157,   157,   157,   158,   158,   158,   158,   159,   160,   161,
     161,   161,   161,   161,   162,   162,   163,   163,   163,   164,
     165,   166,   166
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     5,     2,     1,     0,     1,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     6,
       6,     8,     8,    10,     2,     8,    12,     1,     1,     1,
       0,     1,     0,     1,     0,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     3,     4,
       3,     3,     3,     3,     4,     3,     3,     3,     1,     1,
       3,     0,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     3,     2,     3,     3,     4,     2,     3,
       3,     4,     3,     4,     4,     5,     0,     1,     1,     4,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     2,
       2,     2,     2,     4,     1,     1,     1,     2,     5,     4,
       3,     2,     0,     1,     1,     1,     1,     7,     2,     1,
       1,     1,     1,     1,     1,     1,     0,     1,     1,     4,
       1,     0,     2
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
        case 2:
#line 377 "crc.y" /* yacc.c:1646  */
    { print(); }
#line 1967 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 392 "crc.y" /* yacc.c:1646  */
    { dump(); clean();}
#line 1973 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 433 "crc.y" /* yacc.c:1646  */
    { prc( 0 ); }
#line 1979 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 434 "crc.y" /* yacc.c:1646  */
    { prc( 1 ); }
#line 1985 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 435 "crc.y" /* yacc.c:1646  */
    { prc( 2 ); }
#line 1991 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 436 "crc.y" /* yacc.c:1646  */
    { prc( 0 );	}
#line 1997 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 440 "crc.y" /* yacc.c:1646  */
    { cnd( 1 ); }
#line 2003 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 441 "crc.y" /* yacc.c:1646  */
    { cnd( 0 ); }
#line 2009 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 444 "crc.y" /* yacc.c:1646  */
    { sat( 1 ); }
#line 2015 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 445 "crc.y" /* yacc.c:1646  */
    { sat( 0 ); }
#line 2021 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 448 "crc.y" /* yacc.c:1646  */
    { type = 0; }
#line 2027 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 452 "crc.y" /* yacc.c:1646  */
    { opv( NV40_FP_OP_OPCODE_DDX ); }
#line 2033 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 453 "crc.y" /* yacc.c:1646  */
    { opv( NV40_FP_OP_OPCODE_DDY ); }
#line 2039 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 454 "crc.y" /* yacc.c:1646  */
    { opv( NV40_FP_OP_OPCODE_FLR ); }
#line 2045 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 455 "crc.y" /* yacc.c:1646  */
    { opv( NV40_FP_OP_OPCODE_FRC ); }
#line 2051 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 456 "crc.y" /* yacc.c:1646  */
    { opv( 0xff ); }
#line 2057 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 457 "crc.y" /* yacc.c:1646  */
    { opv( NV40_FP_OP_OPCODE_MOV ); }
#line 2063 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 458 "crc.y" /* yacc.c:1646  */
    { opv( NV40_FP_OP_OPCODE_PK2H ); }
#line 2069 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 459 "crc.y" /* yacc.c:1646  */
    { opv( NV40_FP_OP_OPCODE_PK2US ); }
#line 2075 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 460 "crc.y" /* yacc.c:1646  */
    { opv( NV40_FP_OP_OPCODE_PK4B ); }
#line 2081 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 461 "crc.y" /* yacc.c:1646  */
    { opv( NV40_FP_OP_OPCODE_PK4UB ); }
#line 2087 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 464 "crc.y" /* yacc.c:1646  */
    { opv( NV40_FP_OP_OPCODE_COS ); }
#line 2093 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 465 "crc.y" /* yacc.c:1646  */
    { opv( NV40_FP_OP_OPCODE_EX2 ); }
#line 2099 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 466 "crc.y" /* yacc.c:1646  */
    { opv( NV40_FP_OP_OPCODE_LG2 ); }
#line 2105 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 467 "crc.y" /* yacc.c:1646  */
    { opv( NV40_FP_OP_OPCODE_RCP ); }
#line 2111 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 468 "crc.y" /* yacc.c:1646  */
    { opv( 0xff ); }
#line 2117 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 469 "crc.y" /* yacc.c:1646  */
    { opv( NV40_FP_OP_OPCODE_SIN ); }
#line 2123 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 470 "crc.y" /* yacc.c:1646  */
    { opv( NV40_FP_OP_OPCODE_UP2H ); }
#line 2129 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 471 "crc.y" /* yacc.c:1646  */
    { opv( NV40_FP_OP_OPCODE_UP2US ); }
#line 2135 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 472 "crc.y" /* yacc.c:1646  */
    { opv( NV40_FP_OP_OPCODE_UP4B ); }
#line 2141 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 473 "crc.y" /* yacc.c:1646  */
    { opv( NV40_FP_OP_OPCODE_UP4UB ); }
#line 2147 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 479 "crc.y" /* yacc.c:1646  */
    { opv( NV40_FP_OP_OPCODE_ADD ); }
#line 2153 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 480 "crc.y" /* yacc.c:1646  */
    { opv( NV40_FP_OP_OPCODE_DP3 ); }
#line 2159 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 481 "crc.y" /* yacc.c:1646  */
    { opv( NV40_FP_OP_OPCODE_DP4 ); }
#line 2165 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 482 "crc.y" /* yacc.c:1646  */
    { opv( NV40_FP_OP_OPCODE_DST ); }
#line 2171 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 483 "crc.y" /* yacc.c:1646  */
    { opv( NV40_FP_OP_OPCODE_MAX ); }
#line 2177 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 484 "crc.y" /* yacc.c:1646  */
    { opv( NV40_FP_OP_OPCODE_MIN ); }
#line 2183 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 485 "crc.y" /* yacc.c:1646  */
    { opv( NV40_FP_OP_OPCODE_MUL ); }
#line 2189 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 486 "crc.y" /* yacc.c:1646  */
    { opv( NV40_FP_OP_OPCODE_SEQ ); }
#line 2195 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 487 "crc.y" /* yacc.c:1646  */
    { opv( NV40_FP_OP_OPCODE_SGE ); }
#line 2201 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 488 "crc.y" /* yacc.c:1646  */
    { opv( NV40_FP_OP_OPCODE_SGT ); }
#line 2207 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 489 "crc.y" /* yacc.c:1646  */
    { opv( NV40_FP_OP_OPCODE_SLE ); }
#line 2213 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 490 "crc.y" /* yacc.c:1646  */
    { opv( NV40_FP_OP_OPCODE_SLT ); }
#line 2219 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 491 "crc.y" /* yacc.c:1646  */
    { opv( NV40_FP_OP_OPCODE_SNE ); }
#line 2225 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 492 "crc.y" /* yacc.c:1646  */
    { opv( NV40_FP_OP_OPCODE_ADD ); }
#line 2231 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 497 "crc.y" /* yacc.c:1646  */
    { opv( NV40_FP_OP_OPCODE_MAD ); }
#line 2237 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 498 "crc.y" /* yacc.c:1646  */
    { opv( 0xff ); }
#line 2243 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 501 "crc.y" /* yacc.c:1646  */
    { opv( NV40_FP_OP_OPCODE_KIL ); }
#line 2249 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 505 "crc.y" /* yacc.c:1646  */
    { opv( NV40_FP_OP_OPCODE_TEX ); }
#line 2255 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 506 "crc.y" /* yacc.c:1646  */
    { opv( NV40_FP_OP_OPCODE_TXP ); }
#line 2261 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 509 "crc.y" /* yacc.c:1646  */
    { opv( NV40_FP_OP_OPCODE_TXD ); }
#line 2267 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 513 "crc.y" /* yacc.c:1646  */
    {src_reg( v ); }
#line 2273 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 514 "crc.y" /* yacc.c:1646  */
    {src_reg( v ); }
#line 2279 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 525 "crc.y" /* yacc.c:1646  */
    {src_reg( v ); }
#line 2285 "y.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 526 "crc.y" /* yacc.c:1646  */
    {src_reg( v ); }
#line 2291 "y.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 530 "crc.y" /* yacc.c:1646  */
    { mod = 1; }
#line 2297 "y.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 539 "crc.y" /* yacc.c:1646  */
    { out_reg( v );  cnd_swz(); type = 0; h = 0; printf( "\n" ); }
#line 2303 "y.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 549 "crc.y" /* yacc.c:1646  */
    { cnd_msk( NV40_FP_OP_COND_TR ); }
#line 2309 "y.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 555 "crc.y" /* yacc.c:1646  */
    { cnd_msk( NV40_FP_OP_COND_EQ ); }
#line 2315 "y.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 556 "crc.y" /* yacc.c:1646  */
    { cnd_msk( NV40_FP_OP_COND_GE ); }
#line 2321 "y.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 557 "crc.y" /* yacc.c:1646  */
    { cnd_msk( NV40_FP_OP_COND_GT ); }
#line 2327 "y.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 558 "crc.y" /* yacc.c:1646  */
    { cnd_msk( NV40_FP_OP_COND_LE ); }
#line 2333 "y.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 559 "crc.y" /* yacc.c:1646  */
    { cnd_msk( NV40_FP_OP_COND_LT ); }
#line 2339 "y.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 560 "crc.y" /* yacc.c:1646  */
    { cnd_msk( NV40_FP_OP_COND_NE ); }
#line 2345 "y.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 561 "crc.y" /* yacc.c:1646  */
    { cnd_msk( NV40_FP_OP_COND_TR ); }
#line 2351 "y.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 562 "crc.y" /* yacc.c:1646  */
    { cnd_msk( NV40_FP_OP_COND_FL ); }
#line 2357 "y.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 566 "crc.y" /* yacc.c:1646  */
    { msk( NV40_FP_DEST_MASK( 1, 0, 0, 0 ) ); }
#line 2363 "y.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 567 "crc.y" /* yacc.c:1646  */
    { msk( NV40_FP_DEST_MASK( 0, 1, 0, 0 ) ); }
#line 2369 "y.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 568 "crc.y" /* yacc.c:1646  */
    { msk( NV40_FP_DEST_MASK( 1, 1, 0, 0 ) ); }
#line 2375 "y.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 569 "crc.y" /* yacc.c:1646  */
    { msk( NV40_FP_DEST_MASK( 0, 0, 1, 0 ) ); }
#line 2381 "y.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 570 "crc.y" /* yacc.c:1646  */
    { msk( NV40_FP_DEST_MASK( 1, 0, 1, 0 ) ); }
#line 2387 "y.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 571 "crc.y" /* yacc.c:1646  */
    { msk( NV40_FP_DEST_MASK( 0, 1, 1, 0 ) ); }
#line 2393 "y.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 572 "crc.y" /* yacc.c:1646  */
    { msk( NV40_FP_DEST_MASK( 1, 1, 1, 0 ) ); }
#line 2399 "y.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 573 "crc.y" /* yacc.c:1646  */
    { msk( NV40_FP_DEST_MASK( 0, 0, 0, 1 ) ); }
#line 2405 "y.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 574 "crc.y" /* yacc.c:1646  */
    { msk( NV40_FP_DEST_MASK( 1, 0, 0, 1 ) ); }
#line 2411 "y.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 575 "crc.y" /* yacc.c:1646  */
    { msk( NV40_FP_DEST_MASK( 0, 1, 0, 1 ) ); }
#line 2417 "y.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 576 "crc.y" /* yacc.c:1646  */
    { msk( NV40_FP_DEST_MASK( 1, 1, 0, 1 ) ); }
#line 2423 "y.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 577 "crc.y" /* yacc.c:1646  */
    { msk( NV40_FP_DEST_MASK( 0, 0, 1, 1 ) ); }
#line 2429 "y.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 578 "crc.y" /* yacc.c:1646  */
    { msk( NV40_FP_DEST_MASK( 1, 0, 1, 1 ) ); }
#line 2435 "y.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 579 "crc.y" /* yacc.c:1646  */
    { msk( NV40_FP_DEST_MASK( 0, 1, 1, 1 ) ); }
#line 2441 "y.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 580 "crc.y" /* yacc.c:1646  */
    { msk( NV40_FP_DEST_MASK( 1, 1, 1, 1 ) ); }
#line 2447 "y.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 581 "crc.y" /* yacc.c:1646  */
    { msk( NV40_FP_DEST_MASK( 1, 1, 1, 1 ) ); }
#line 2453 "y.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 593 "crc.y" /* yacc.c:1646  */
    { set_input( NV40_FP_OP_INPUT_SRC_POSITION ); }
#line 2459 "y.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 594 "crc.y" /* yacc.c:1646  */
    { set_input( NV40_FP_OP_INPUT_SRC_COL0 ); }
#line 2465 "y.tab.c" /* yacc.c:1646  */
    break;

  case 122:
#line 595 "crc.y" /* yacc.c:1646  */
    { set_input( NV40_FP_OP_INPUT_SRC_COL1 ); }
#line 2471 "y.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 596 "crc.y" /* yacc.c:1646  */
    { set_input( NV40_FP_OP_INPUT_SRC_FOGC ); }
#line 2477 "y.tab.c" /* yacc.c:1646  */
    break;

  case 124:
#line 597 "crc.y" /* yacc.c:1646  */
    { set_input( NV40_FP_OP_INPUT_SRC_TC0 + v ); }
#line 2483 "y.tab.c" /* yacc.c:1646  */
    break;

  case 127:
#line 604 "crc.y" /* yacc.c:1646  */
    { n = 0; }
#line 2489 "y.tab.c" /* yacc.c:1646  */
    break;

  case 128:
#line 605 "crc.y" /* yacc.c:1646  */
    { n = 1; }
#line 2495 "y.tab.c" /* yacc.c:1646  */
    break;

  case 129:
#line 606 "crc.y" /* yacc.c:1646  */
    { n = 2; }
#line 2501 "y.tab.c" /* yacc.c:1646  */
    break;

  case 130:
#line 607 "crc.y" /* yacc.c:1646  */
    { n = 3; }
#line 2507 "y.tab.c" /* yacc.c:1646  */
    break;

  case 131:
#line 608 "crc.y" /* yacc.c:1646  */
    { n = 4; }
#line 2513 "y.tab.c" /* yacc.c:1646  */
    break;

  case 132:
#line 609 "crc.y" /* yacc.c:1646  */
    { n = 5; }
#line 2519 "y.tab.c" /* yacc.c:1646  */
    break;

  case 133:
#line 610 "crc.y" /* yacc.c:1646  */
    { n = 6; }
#line 2525 "y.tab.c" /* yacc.c:1646  */
    break;

  case 134:
#line 611 "crc.y" /* yacc.c:1646  */
    { n = 7; }
#line 2531 "y.tab.c" /* yacc.c:1646  */
    break;

  case 135:
#line 612 "crc.y" /* yacc.c:1646  */
    { n = 8; }
#line 2537 "y.tab.c" /* yacc.c:1646  */
    break;

  case 136:
#line 613 "crc.y" /* yacc.c:1646  */
    { n = 9; }
#line 2543 "y.tab.c" /* yacc.c:1646  */
    break;

  case 137:
#line 618 "crc.y" /* yacc.c:1646  */
    { v = n; }
#line 2549 "y.tab.c" /* yacc.c:1646  */
    break;

  case 138:
#line 619 "crc.y" /* yacc.c:1646  */
    { v = v * 10 + n; }
#line 2555 "y.tab.c" /* yacc.c:1646  */
    break;

  case 139:
#line 623 "crc.y" /* yacc.c:1646  */
    { h = 0; }
#line 2561 "y.tab.c" /* yacc.c:1646  */
    break;

  case 140:
#line 624 "crc.y" /* yacc.c:1646  */
    { h = 0; v = 31; creg = 1; }
#line 2567 "y.tab.c" /* yacc.c:1646  */
    break;

  case 141:
#line 627 "crc.y" /* yacc.c:1646  */
    { h = 1; }
#line 2573 "y.tab.c" /* yacc.c:1646  */
    break;

  case 142:
#line 628 "crc.y" /* yacc.c:1646  */
    { h = 1; v = 63; creg = 1; }
#line 2579 "y.tab.c" /* yacc.c:1646  */
    break;

  case 144:
#line 635 "crc.y" /* yacc.c:1646  */
    { v = 0; h = 0; }
#line 2585 "y.tab.c" /* yacc.c:1646  */
    break;

  case 145:
#line 636 "crc.y" /* yacc.c:1646  */
    { v = 0; h = 1; }
#line 2591 "y.tab.c" /* yacc.c:1646  */
    break;

  case 153:
#line 652 "crc.y" /* yacc.c:1646  */
    { com( 0 ); }
#line 2597 "y.tab.c" /* yacc.c:1646  */
    break;

  case 154:
#line 653 "crc.y" /* yacc.c:1646  */
    { com( 1 ); }
#line 2603 "y.tab.c" /* yacc.c:1646  */
    break;

  case 155:
#line 654 "crc.y" /* yacc.c:1646  */
    { com( 2 ); }
#line 2609 "y.tab.c" /* yacc.c:1646  */
    break;

  case 156:
#line 655 "crc.y" /* yacc.c:1646  */
    { com( 3 ); }
#line 2615 "y.tab.c" /* yacc.c:1646  */
    break;

  case 157:
#line 658 "crc.y" /* yacc.c:1646  */
    { set_tex( v ); }
#line 2621 "y.tab.c" /* yacc.c:1646  */
    break;

  case 164:
#line 674 "crc.y" /* yacc.c:1646  */
    { set_cns(); cnst = 1;}
#line 2627 "y.tab.c" /* yacc.c:1646  */
    break;

  case 165:
#line 675 "crc.y" /* yacc.c:1646  */
    { set_cns(); cnst = 1;}
#line 2633 "y.tab.c" /* yacc.c:1646  */
    break;

  case 166:
#line 679 "crc.y" /* yacc.c:1646  */
    { neg = 0; }
#line 2639 "y.tab.c" /* yacc.c:1646  */
    break;

  case 167:
#line 680 "crc.y" /* yacc.c:1646  */
    { neg = 0; }
#line 2645 "y.tab.c" /* yacc.c:1646  */
    break;

  case 168:
#line 681 "crc.y" /* yacc.c:1646  */
    { neg = 1; }
#line 2651 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2655 "y.tab.c" /* yacc.c:1646  */
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
#line 697 "crc.y" /* yacc.c:1906  */


void yyerror(const char *str)
{
        fprintf(stderr,"error: %s\n",str);
}
 
  
int yywrap()
{
        return 1;
} 
  
int main( int argn, const char *argv[] )
{

    FILE * in;

	if( argn < 2 )
	{
	    printf( "Usage:\n\nfp asmprogram.fp [outname]\n\n" );
	    return 1;
	}

	in = fopen(argv[1], "r");
    if(!in) {printf( "cannot open input file\n" );return 1;}

    if(argn > 2)
	    outfile = argv[2];
    else outfile = "output.h";

    yyrestart(in);

    yyparse();

	return 0;
} 







