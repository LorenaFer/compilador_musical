#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "expression.hpp"

extern FILE* yyin;
extern int yyparse();
extern int parser_result;
extern MusicProgram* program_result;
extern int yydebug;

void print_help() {
    printf("Uso: parser [archivo]\n");
    printf("Evalúa un archivo de notación musical.\n");
    printf("Si no se proporciona un archivo, lee desde la entrada estándar.\n");
}

int main(int argc, char** argv) {
    // Activar depuración
    yydebug = 1;

    if (argc > 1 && (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0)) {
        print_help();
        return 0;
    }

    // Si hay argumento, es el nombre del archivo
    if (argc > 1) {
        FILE* file = fopen(argv[1], "r");
        if (!file) {
            printf("Error: No se pudo abrir el archivo %s\n", argv[1]);
            return 1;
        }
        yyin = file;
    } else {
        // Si no hay argumento, lee desde stdin
        yyin = stdin;
    }

    int result = yyparse();
    
    // Cerrar el archivo si se abrió uno
    if (argc > 1 && yyin != NULL) {
        fclose(yyin);
    }

    if (result != 0 || parser_result != 0) {
        printf("Error de parseo\n");
        return 1;
    }

    if (program_result) {
        printf("Programa musical analizado correctamente:\n");
        printf("%s\n", program_result->to_string().c_str());
        
        printf("Validación de configuración: %s\n", 
               program_result->validate() ? "Completa" : "Incompleta");
        
        program_result->destroy();
        delete program_result;
    }

    return 0;
} 