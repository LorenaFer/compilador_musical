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
    // Desactivar completamente la depuración
    yydebug = 0;
    
    // Procesar argumentos
    char* filename = NULL;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
            print_help();
            return 0;
        } else if (filename == NULL) {
            // Primer argumento no reconocido se toma como nombre de archivo
            filename = argv[i];
        }
    }

    // Abrir archivo si se proporcionó
    if (filename != NULL) {
        FILE* file = fopen(filename, "r");
        if (!file) {
            printf("Error: No se pudo abrir el archivo %s\n", filename);
            return 1;
        }
        yyin = file;
    } else {
        // Si no hay argumento, lee desde stdin
        yyin = stdin;
    }

    // Parsear el archivo
    int result = yyparse();
    
    // Cerrar el archivo si se abrió uno
    if (filename != NULL && yyin != NULL) {
        fclose(yyin);
    }

    if (result != 0 || parser_result != 0) {
        // Mostrar error con formato simple
        const char* basename = filename ? strrchr(filename, '/') : NULL;
        basename = basename ? basename + 1 : filename;
        printf("❌ Error: El archivo %s contiene errores de sintaxis o configuración.\n", 
               basename ? basename : "entrada");
        return 1;
    }

    if (program_result) {
        // Salida simplificada para éxito
        const char* basename = filename ? strrchr(filename, '/') : NULL;
        basename = basename ? basename + 1 : filename;
        printf("✅ Archivo %s procesado correctamente.\n", basename ? basename : "entrada");
        
        // Solo mostrar si hubo éxito en la validación
        if (program_result->validate()) {
            printf("✓ Configuración completa.\n");
        }
        
        program_result->destroy();
        delete program_result;
    }

    return 0;
} 