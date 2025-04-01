#include <iostream>
#include <cstdlib>
#include "datatype.hpp"
#include "declaration.hpp"
#include "expression.hpp"
#include "statement.hpp"

int main()
{
    // Creación del AST para una composición musical basada en los ejemplos válidos proporcionados
    Body composicion_body{
        new DeclarationStatement{            // --> Declaración de tempo
            new TempoDeclaration{
                "tempo",
                60                           // --> 60 
            }
        },
        new DeclarationStatement{            // --> Declaración de compás
            new TimeSignatureDeclaration{
                "compas",
                7,                           // --> 7 tiempos por compás
                8                            // --> La corchea recibe un tiempo
            }
        },
        new DeclarationStatement{            // --> Declaración de tonalidad: Si Mayor (Si M)
            new KeyDeclaration{
                "tonalidad",
                "Si",                        // --> Si
                "M"                          // --> M para Mayor
            }
        },
        
        // Comentario de la partitura
        new PrintStatement{
            new StrExpression{"// Patrones rítmicos en 7/8 (agrupados 2+2+3)"}
        },
        
        // Primera secuencia de notas: patrón 2+2+3 en corcheas
        new DeclarationStatement{                  
            new NoteDeclaration{
                "nota1",
                'G', 4, "Corchea"                  // --> Sol4 Corchea
            }
        },
        new DeclarationStatement{                  
            new NoteDeclaration{
                "nota2",
                'G', 4, "Corchea"                  // --> Sol4 Corchea
            }
        },
        new DeclarationStatement{                  
            new NoteDeclaration{
                "nota3",
                'A', 4, "Corchea"                  // --> La4 Corchea
            }
        },
        new DeclarationStatement{                  
            new NoteDeclaration{
                "nota4",
                'A', 4, "Corchea"                  // --> La4 Corchea
            }
        },
        new DeclarationStatement{                  
            new NoteDeclaration{
                "nota5",
                'B', 4, "Corchea"                  // --> Si4 Corchea
            }
        },
        new DeclarationStatement{                  
            new NoteDeclaration{
                "nota6",
                'B', 4, "Corchea"                  // --> Si4 Corchea
            }
        },
        new DeclarationStatement{                  
            new NoteDeclaration{
                "nota7",
                'B', 4, "Corchea"                  // --> Si4 Corchea
            }
        },
        
        // Comentario para la segunda secuencia
        new PrintStatement{
            new StrExpression{"// Otro patrón rítmico (3+2+2)"}
        },
        
        // Segunda secuencia de notas: notas con alteraciones
        new DeclarationStatement{                  
            new NoteDeclaration{
                "nota8",
                'C', 5, "Corchea"                  // --> Do#5 Corchea
            }
        },
        new ExpressionStatement{                   // Aplicamos el sostenido a la nota
            new SharpExpression{
                new NameExpression{"nota8"}
            }
        },
        new DeclarationStatement{                  
            new NoteDeclaration{
                "nota9",
                'C', 5, "Corchea"                  // --> Do#5 Corchea
            }
        },
        new ExpressionStatement{                   // Aplicamos el sostenido a la nota
            new SharpExpression{
                new NameExpression{"nota9"}
            }
        },
        new DeclarationStatement{                  
            new NoteDeclaration{
                "nota10",
                'C', 5, "Corchea"                  // --> Do#5 Corchea
            }
        },
        new ExpressionStatement{                   // Aplicamos el sostenido a la nota
            new SharpExpression{
                new NameExpression{"nota10"}
            }
        },
        
        // Comentario para la tercera secuencia
        new PrintStatement{
            new StrExpression{"// Mezcla de duraciones"}
        },
        
        // Tercera secuencia: mezcla de duraciones
        new DeclarationStatement{                  
            new NoteDeclaration{
                "nota11",
                'F', 4, "Negra"                   // --> Fa#4 Negra
            }
        },
        new ExpressionStatement{                   // Aplicamos el sostenido a la nota
            new SharpExpression{
                new NameExpression{"nota11"}
            }
        },
        new DeclarationStatement{                  
            new NoteDeclaration{
                "nota12",
                'B', 4, "Negra"                   // --> Si4 Negra
            }
        },
        new DeclarationStatement{                  
            new NoteDeclaration{
                "nota13",
                'C', 5, "Semicorchea"             // --> Do#5 Semicorchea
            }
        },
        new ExpressionStatement{                   // Aplicamos el sostenido a la nota
            new SharpExpression{
                new NameExpression{"nota13"}
            }
        }
    };
    
    // Usamos el constructor de FunctionDeclaration con el tipo de función y el cuerpo, con un nombre vacío
    auto composicion = new FunctionDeclaration{
        "",  // Nombre vacío para reflejar la gramática original
        new FunctionDatatype{new VoidDatatype{}, ParamList{}},
        composicion_body
    };

    // Imprimir la representación del AST
    std::cout << "Representación del AST para una composición musical:" << std::endl;
    std::cout << "=================================================" << std::endl;
    std::cout << composicion->to_string() << std::endl;
    std::cout << "=================================================" << std::endl;

    // Liberar memoria
    composicion->destroy();
    delete composicion;

    return EXIT_SUCCESS;
}

/*
 * Esta función crea un AST para una composición musical sencilla con la
 * siguiente estructura:
 * - Tempo: 120 BPM
 * - Compás: 4/4
 * - Tonalidad: D Mayor
 * - Secuencia de notas con sus duraciones
 */
FunctionDeclaration* create_c_function()
{
    // Creamos los tipos de datos necesarios
    auto function_type = new FunctionDatatype{new VoidDatatype{}, ParamList{}};
    
    // Cuerpo de la composición musical (secuencia de declaraciones)
    // Nota: el orden de declaración será el mismo que el orden de ejecución
    Body body{
        // Configuración inicial de la composición musical
        new DeclarationStatement{
            new TempoDeclaration{"tempo_principal", 120}
        },
        new DeclarationStatement{
            new TimeSignatureDeclaration{"compas_principal", 4, 4}
        },
        new DeclarationStatement{
            new KeyDeclaration{"tonalidad_principal", "D", "M"}
        },
        
        // Secuencia de notas musicales
        new DeclarationStatement{
            new NoteDeclaration{"nota1", 'D', 4, "negra"}
        },
        new DeclarationStatement{
            new NoteDeclaration{"nota2", 'F', 4, "negra"}
        },
        new DeclarationStatement{
            new NoteDeclaration{"nota3", 'A', 4, "blanca"}
        },
        new DeclarationStatement{
            new NoteDeclaration{"nota4", 'D', 5, "negra"}
        },
        new DeclarationStatement{
            new NoteDeclaration{"nota5", 'C', 5, "negra"}
        },
        new DeclarationStatement{
            new NoteDeclaration{"nota6", 'B', 4, "blanca"}
        }
    };
    
    return new FunctionDeclaration{"", function_type, body};
}