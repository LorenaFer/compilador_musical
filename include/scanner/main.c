#include <stdio.h>
#include <stdlib.h>
#include "token.h"

extern FILE* yyin;
extern int yylex();
extern char* yytext;

void usage(char* argv[])
{
    printf("Uso: %s archivo_entrada\n", argv[0]);
    exit(1);
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        usage(argv);
    }

    yyin = fopen(argv[1], "r");

    if (!yyin)
    {
        printf("No se pudo abrir %s\n", argv[1]);
        exit(1);
    }

    int token;
    printf("%-20s %-20s\n", "TOKEN", "TEXTO");
    printf("----------------------------------------\n");
    
    while ((token = yylex()) != 0) {
        char* token_name;
        switch (token) {
            case TOKEN_TONALIDAD: token_name = "TOKEN_TONALIDAD"; break;
            case TOKEN_TEMPO: token_name = "TOKEN_TEMPO"; break;
            case TOKEN_COMPAS: token_name = "TOKEN_COMPAS"; break;
            case TOKEN_BLANCA: token_name = "TOKEN_BLANCA"; break;
            case TOKEN_NEGRA: token_name = "TOKEN_NEGRA"; break;
            case TOKEN_CORCHEA: token_name = "TOKEN_CORCHEA"; break;
            case TOKEN_SEMICORCHEA: token_name = "TOKEN_SEMICORCHEA"; break;
            case TOKEN_NOTA_DO: token_name = "TOKEN_NOTA_DO"; break;
            case TOKEN_NOTA_RE: token_name = "TOKEN_NOTA_RE"; break;
            case TOKEN_NOTA_MI: token_name = "TOKEN_NOTA_MI"; break;
            case TOKEN_NOTA_FA: token_name = "TOKEN_NOTA_FA"; break;
            case TOKEN_NOTA_SOL: token_name = "TOKEN_NOTA_SOL"; break;
            case TOKEN_NOTA_LA: token_name = "TOKEN_NOTA_LA"; break;
            case TOKEN_NOTA_SI: token_name = "TOKEN_NOTA_SI"; break;
            case TOKEN_SOSTENIDO: token_name = "TOKEN_SOSTENIDO"; break;
            case TOKEN_BEMOL: token_name = "TOKEN_BEMOL"; break;
            case TOKEN_MAYOR: token_name = "TOKEN_MAYOR"; break;
            case TOKEN_MENOR: token_name = "TOKEN_MENOR"; break;
            case TOKEN_NUMERO: token_name = "TOKEN_NUMERO"; break;
            case TOKEN_BARRA: token_name = "TOKEN_BARRA"; break;
            case TOKEN_NOTA_COMPLETA: token_name = "TOKEN_NOTA_COMPLETA"; break;
            case TOKEN_IDENTIFIER: token_name = "TOKEN_IDENTIFIER"; break;
            case TOKEN_COMENTARIO: token_name = "TOKEN_COMENTARIO"; break;
            default: token_name = "DESCONOCIDO"; break;
        }
        printf("%-20s %-20s\n", token_name, yytext);
    }

    fclose(yyin);
    return 0;
} 