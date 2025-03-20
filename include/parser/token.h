/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TOKEN_TONALIDAD = 258,
     TOKEN_TEMPO = 259,
     TOKEN_COMPAS = 260,
     TOKEN_BLANCA = 261,
     TOKEN_NEGRA = 262,
     TOKEN_CORCHEA = 263,
     TOKEN_SEMICORCHEA = 264,
     TOKEN_NOTA_DO = 265,
     TOKEN_NOTA_RE = 266,
     TOKEN_NOTA_MI = 267,
     TOKEN_NOTA_FA = 268,
     TOKEN_NOTA_SOL = 269,
     TOKEN_NOTA_LA = 270,
     TOKEN_NOTA_SI = 271,
     TOKEN_SOSTENIDO = 272,
     TOKEN_BEMOL = 273,
     TOKEN_MAYOR = 274,
     TOKEN_MENOR = 275,
     TOKEN_NUMERO = 276,
     TOKEN_BARRA = 277,
     TOKEN_NOTA_COMPLETA = 278,
     TOKEN_IDENTIFIER = 279,
     TOKEN_COMENTARIO = 280
   };
#endif
/* Tokens.  */
#define TOKEN_TONALIDAD 258
#define TOKEN_TEMPO 259
#define TOKEN_COMPAS 260
#define TOKEN_BLANCA 261
#define TOKEN_NEGRA 262
#define TOKEN_CORCHEA 263
#define TOKEN_SEMICORCHEA 264
#define TOKEN_NOTA_DO 265
#define TOKEN_NOTA_RE 266
#define TOKEN_NOTA_MI 267
#define TOKEN_NOTA_FA 268
#define TOKEN_NOTA_SOL 269
#define TOKEN_NOTA_LA 270
#define TOKEN_NOTA_SI 271
#define TOKEN_SOSTENIDO 272
#define TOKEN_BEMOL 273
#define TOKEN_MAYOR 274
#define TOKEN_MENOR 275
#define TOKEN_NUMERO 276
#define TOKEN_BARRA 277
#define TOKEN_NOTA_COMPLETA 278
#define TOKEN_IDENTIFIER 279
#define TOKEN_COMENTARIO 280




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

