#include <stdio.h>
#include <stdlib.h>

extern FILE* yyin;
extern int yyparse();
extern int parser_result;

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

    int result = yyparse();

    if (result == 0)
    {
        printf("Análisis completo: Código musical correcto\n");
        printf("Resultado: %d\n", parser_result);
    }
    else
    {
        printf("¡El análisis falló! Hay errores en el código musical.\n");
    }

    fclose(yyin);
    return 0;
} 