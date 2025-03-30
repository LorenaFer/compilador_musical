%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.tab.h"

extern int yyerror(const char* msg);
%}

%option noyywrap
%option yylineno

ESPACIO     [ \t\n]
OCTAVA      [0-9]
LETRA       [A-Za-z]
NUMERO      {OCTAVA}+
COMENTARIO  "//".*
NOTA_LAT    "Do"|"Re"|"Mi"|"Fa"|"Sol"|"La"|"Si"
NOTA_ING    "C"|"D"|"E"|"F"|"G"|"A"|"B"
ALTER       "b"|"#"|"♭"

%%
{ESPACIO}       { /* Ignorar espacios */ }
{COMENTARIO}    { return TOKEN_COMENTARIO; }

"Tonalidad"     { return TOKEN_TONALIDAD; }
"Tempo"         { return TOKEN_TEMPO; }
"Compas"        { return TOKEN_COMPAS; }

"Mayor"|"M"     { return TOKEN_MAYOR; }
"menor"|"m"     { return TOKEN_MENOR; }

"Do"[0-9]       |
"Re"[0-9]       |
"Mi"[0-9]       |
"Fa"[0-9]       |
"Sol"[0-9]      |
"La"[0-9]       |
"Si"[0-9]       { return TOKEN_NOTA_COMPLETA; }

"Do"            { return TOKEN_NOTA_DO; }
"Re"            { return TOKEN_NOTA_RE; }
"Mi"            { return TOKEN_NOTA_MI; }
"Fa"            { return TOKEN_NOTA_FA; }
"Sol"           { return TOKEN_NOTA_SOL; }
"La"            { return TOKEN_NOTA_LA; }
"Si"            { return TOKEN_NOTA_SI; }

"#"             { return TOKEN_SOSTENIDO; }
"b"             { return TOKEN_BEMOL; }

"silencio"      { return TOKEN_NOTA_COMPLETA; }

[Bb][Ll][Aa][Nn][Cc][Aa] { return TOKEN_BLANCA; }
[Nn][Ee][Gg][Rr][Aa]     { return TOKEN_NEGRA; }
[Cc][Oo][Rr][Cc][Hh][Ee][Aa]         { return TOKEN_CORCHEA; }
[Ss][Ee][Mm][Ii][Cc][Oo][Rr][Cc][Hh][Ee][Aa] { return TOKEN_SEMICORCHEA; }

"/"             { return TOKEN_BARRA; }

[0-9]+          { return TOKEN_NUMERO; }

[a-zA-Z_][a-zA-Z0-9_]* { return TOKEN_IDENTIFIER; }

.               { yyerror("Token no reconocido"); }

%% 