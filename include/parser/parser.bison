%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylex();
extern char* yytext;
int yyerror(const char* s);
int parser_result = 0;  // 0 = éxito, otro valor = error

// Variables para almacenar información de configuración
int tempo = 0;
char tonalidad[20] = "";
char modo[5] = "";
int compas_num = 0;
int compas_den = 0;

// Variables temporales para parsing
char temp_numero[20];
%}

%token TOKEN_TONALIDAD TOKEN_TEMPO TOKEN_COMPAS
%token TOKEN_BLANCA TOKEN_NEGRA TOKEN_CORCHEA TOKEN_SEMICORCHEA
%token TOKEN_NOTA_DO TOKEN_NOTA_RE TOKEN_NOTA_MI TOKEN_NOTA_FA
%token TOKEN_NOTA_SOL TOKEN_NOTA_LA TOKEN_NOTA_SI
%token TOKEN_SOSTENIDO TOKEN_BEMOL
%token TOKEN_MAYOR TOKEN_MENOR
%token TOKEN_NUMERO TOKEN_BARRA
%token TOKEN_NOTA_COMPLETA
%token TOKEN_IDENTIFIER
%token TOKEN_COMENTARIO

// Definir precedencia para resolver conflictos
%left TOKEN_SOSTENIDO TOKEN_BEMOL

%%
programa
    : configuracion secuencia_notas  { 
        if (tempo == 0 || compas_num == 0 || compas_den == 0 || strlen(tonalidad) == 0) {
            yyerror("Configuración incompleta. Se requiere Tempo, Compas y Tonalidad.");
            YYERROR;
        } else {
            parser_result = 0;
        }
    }
    ;

configuracion
    : /* vacío */
    | configuracion config_item
    ;

config_item
    : config_tempo
    | config_compas
    | config_tonalidad
    | TOKEN_COMENTARIO
    ;

config_tempo
    : TOKEN_TEMPO TOKEN_NUMERO {
        tempo = atoi(yytext);
        if (tempo <= 0) {
            yyerror("El tempo debe ser un valor positivo");
            YYERROR;
        }
    }
    ;

config_compas
    : TOKEN_COMPAS TOKEN_NUMERO {
        compas_num = atoi(yytext);
        if (compas_num <= 0) {
            yyerror("El numerador del compás debe ser positivo");
            YYERROR;
        }
    } TOKEN_BARRA TOKEN_NUMERO {
        compas_den = atoi(yytext);
        if (compas_den <= 0) {
            yyerror("El denominador del compás debe ser positivo");
            YYERROR;
        }
    }
    ;

config_tonalidad
    : TOKEN_TONALIDAD nota_tonalidad modo {
        /* La tonalidad y modo ya se establecen en las reglas nota_tonalidad y modo */
    }
    ;

nota_tonalidad
    : TOKEN_NOTA_DO { strcpy(tonalidad, "Do"); }
    | TOKEN_NOTA_RE { strcpy(tonalidad, "Re"); }
    | TOKEN_NOTA_MI { strcpy(tonalidad, "Mi"); }
    | TOKEN_NOTA_FA { strcpy(tonalidad, "Fa"); }
    | TOKEN_NOTA_SOL { strcpy(tonalidad, "Sol"); }
    | TOKEN_NOTA_LA { strcpy(tonalidad, "La"); }
    | TOKEN_NOTA_SI { strcpy(tonalidad, "Si"); }
    ;

modo
    : TOKEN_MAYOR { strcpy(modo, "M"); }
    | TOKEN_MENOR { strcpy(modo, "m"); }
    ;

secuencia_notas
    : /* vacío */
    | secuencia_notas nota_item
    ;

nota_item
    : nota
    | TOKEN_COMENTARIO
    ;

nota
    : TOKEN_NOTA_COMPLETA duracion
    | nota_individual duracion
    ;

nota_individual
    : nota_basica octava
    | nota_basica alteracion octava
    ;

nota_basica
    : TOKEN_NOTA_DO
    | TOKEN_NOTA_RE
    | TOKEN_NOTA_MI
    | TOKEN_NOTA_FA
    | TOKEN_NOTA_SOL
    | TOKEN_NOTA_LA
    | TOKEN_NOTA_SI
    ;

alteracion
    : TOKEN_SOSTENIDO
    | TOKEN_BEMOL
    ;

octava
    : TOKEN_NUMERO
    ;

duracion
    : TOKEN_BLANCA
    | TOKEN_NEGRA
    | TOKEN_CORCHEA
    | TOKEN_SEMICORCHEA
    ;

%%

int yyerror(const char* s) {
    printf("Error de parseo: %s\n", s);
    return 1;
} 