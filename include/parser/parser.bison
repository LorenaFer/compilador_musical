%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "expression.hpp"

extern int yylex();
extern char* yytext;
int yyerror(const char* s);

#define YYSTYPE Expression*
#define YYDEBUG 1

// Resultado del parser
int parser_result = 0;  // 0 = éxito, otro valor = error
MusicProgram* program_result = nullptr;

// Variables temporales para parsing
Configuration* current_config = nullptr;
std::string temp_note;
std::string temp_alteration;
int temp_octave = 0;
std::string temp_duration;
int temp_num = 0;  // Variable temporal para almacenar el numerador

// Funciones de depuración
void debug_print(const char* msg) {
    printf("DEBUG: %s\n", msg);
}

// Función para extraer la nota y octava de TOKEN_NOTA_COMPLETA
void extract_note_octave(char* text) {
    int len = strlen(text);
    if (len < 2) return;
    
    // Último caracter es la octava
    char octave_char = text[len-1];
    temp_octave = octave_char - '0';
    
    // Extraer el nombre de la nota
    text[len-1] = '\0';  // Eliminar el número
    temp_note = text;
    temp_alteration = "";
}
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
        debug_print("Programa completo");
        if (!current_config || !current_config->isComplete()) {
            printf("Configuración: %s\n", current_config ? current_config->to_string().c_str() : "nullptr");
            yyerror("Configuración incompleta. Se requiere Tempo, Compas y Tonalidad.");
            YYERROR;
        } else {
            debug_print("Configuración completa");
            program_result = new MusicProgram(current_config);
            parser_result = 0;
            $$ = program_result;
        }
    }
    ;

configuracion
    : /* vacío */ { 
        debug_print("Creando configuración");
        current_config = new Configuration(); 
        $$ = current_config;
    }
    | configuracion config_item { 
        debug_print("Añadiendo configuración");
        $$ = current_config; 
    }
    ;

config_item
    : config_tempo { 
        debug_print("Configuración: tempo");
        $$ = current_config; 
    }
    | config_compas { 
        debug_print("Configuración: compás");
        $$ = current_config; 
    }
    | config_tonalidad { 
        debug_print("Configuración: tonalidad");
        $$ = current_config; 
    }
    | TOKEN_COMENTARIO { 
        debug_print("Configuración: comentario");
        $$ = current_config; 
    }
    ;

config_tempo
    : TOKEN_TEMPO TOKEN_NUMERO {
        debug_print("Procesando tempo");
        int tempo_val = atoi(yytext);
        printf("Tempo valor: %d\n", tempo_val);
        if (tempo_val <= 0) {
            yyerror("El tempo debe ser un valor positivo");
            YYERROR;
        }
        if (current_config->hasTempo()) {
            yyerror("El tempo ya ha sido definido");
            YYERROR;
        } else {
            current_config->setTempo(tempo_val);
            $$ = current_config;
        }
    }
    ;

config_compas
    : TOKEN_COMPAS TOKEN_NUMERO {
        debug_print("Procesando compás (numerador)");
        temp_num = atoi(yytext);
        printf("Compás numerador: %d\n", temp_num);
        if (temp_num <= 0) {
            yyerror("El numerador del compás debe ser positivo");
            YYERROR;
        }
    } TOKEN_BARRA TOKEN_NUMERO {
        debug_print("Procesando compás (denominador)");
        int den = atoi(yytext);
        printf("Compás denominador: %d\n", den);
        if (den <= 0) {
            yyerror("El denominador del compás debe ser positivo");
            YYERROR;
        }
        if (current_config->hasTimeSignature()) {
            yyerror("El compás ya ha sido definido");
            YYERROR;
        } else {
            current_config->setTimeSignature(temp_num, den);
            $$ = current_config;
        }
    }
    ;

config_tonalidad
    : TOKEN_TONALIDAD nota_tonalidad modo {
        debug_print("Procesando tonalidad completa");
        printf("Nota: %s, Modo: %s\n", temp_note.c_str(), temp_alteration.c_str());
        if (current_config->hasKey()) {
            yyerror("La tonalidad ya ha sido definida");
            YYERROR;
        } else {
            current_config->setKey(temp_note, temp_alteration);
            $$ = current_config;
        }
    }
    ;

nota_tonalidad
    : TOKEN_NOTA_DO { 
        debug_print("Nota de tonalidad: Do");
        temp_note = "Do"; 
    }
    | TOKEN_NOTA_RE { 
        debug_print("Nota de tonalidad: Re");
        temp_note = "Re"; 
    }
    | TOKEN_NOTA_MI { 
        debug_print("Nota de tonalidad: Mi");
        temp_note = "Mi"; 
    }
    | TOKEN_NOTA_FA { 
        debug_print("Nota de tonalidad: Fa");
        temp_note = "Fa"; 
    }
    | TOKEN_NOTA_SOL { 
        debug_print("Nota de tonalidad: Sol");
        temp_note = "Sol"; 
    }
    | TOKEN_NOTA_LA { 
        debug_print("Nota de tonalidad: La");
        temp_note = "La"; 
    }
    | TOKEN_NOTA_SI { 
        debug_print("Nota de tonalidad: Si");
        temp_note = "Si"; 
    }
    ;

modo
    : TOKEN_MAYOR { 
        debug_print("Modo: Mayor");
        temp_alteration = "M"; 
    }
    | TOKEN_MENOR { 
        debug_print("Modo: Menor");
        temp_alteration = "m"; 
    }
    ;

secuencia_notas
    : /* vacío */ { 
        debug_print("Secuencia de notas vacía");
        $$ = nullptr; 
    }
    | secuencia_notas nota_item { 
        debug_print("Secuencia de notas");
        $$ = $2; 
    }
    ;

nota_item
    : nota { 
        debug_print("Nota");
        $$ = $1; 
    }
    | TOKEN_COMENTARIO { 
        debug_print("Comentario");
        $$ = nullptr; 
    }
    ;

nota
    : TOKEN_NOTA_COMPLETA duracion {
        debug_print("Nota completa");
        extract_note_octave(yytext);
        printf("Nota extraída: %s, octava: %d, duración: %s\n", 
               temp_note.c_str(), temp_octave, temp_duration.c_str());
        $$ = new Note(temp_note, temp_alteration, temp_octave, temp_duration);
    }
    | nota_individual duracion {
        debug_print("Nota individual");
        $$ = new Note(temp_note, temp_alteration, temp_octave, temp_duration);
    }
    ;

nota_individual
    : nota_basica octava {
        debug_print("Nota individual sin alteración");
        temp_alteration = "";
    }
    | nota_basica alteracion octava {
        debug_print("Nota individual con alteración");
        /* temp_alteration ya fue establecido en la regla alteracion */
    }
    ;

nota_basica
    : TOKEN_NOTA_DO { 
        debug_print("Nota: Do");
        temp_note = "Do"; 
    }
    | TOKEN_NOTA_RE { 
        debug_print("Nota: Re");
        temp_note = "Re"; 
    }
    | TOKEN_NOTA_MI { 
        debug_print("Nota: Mi");
        temp_note = "Mi"; 
    }
    | TOKEN_NOTA_FA { 
        debug_print("Nota: Fa");
        temp_note = "Fa"; 
    }
    | TOKEN_NOTA_SOL { 
        debug_print("Nota: Sol");
        temp_note = "Sol"; 
    }
    | TOKEN_NOTA_LA { 
        debug_print("Nota: La");
        temp_note = "La"; 
    }
    | TOKEN_NOTA_SI { 
        debug_print("Nota: Si");
        temp_note = "Si"; 
    }
    ;

alteracion
    : TOKEN_SOSTENIDO { 
        debug_print("Alteración: #");
        temp_alteration = "#"; 
    }
    | TOKEN_BEMOL { 
        debug_print("Alteración: b");
        temp_alteration = "b"; 
    }
    ;

octava
    : TOKEN_NUMERO { 
        debug_print("Octava");
        temp_octave = atoi(yytext); 
    }
    ;

duracion
    : TOKEN_BLANCA { 
        debug_print("Duración: blanca");
        temp_duration = "blanca"; 
    }
    | TOKEN_NEGRA { 
        debug_print("Duración: negra");
        temp_duration = "negra"; 
    }
    | TOKEN_CORCHEA { 
        debug_print("Duración: corchea");
        temp_duration = "corchea"; 
    }
    | TOKEN_SEMICORCHEA { 
        debug_print("Duración: semicorchea");
        temp_duration = "semicorchea"; 
    }
    ;

%%

int yyerror(const char* s) {
    printf("Error de parseo: %s\n", s);
    return 1;
} 