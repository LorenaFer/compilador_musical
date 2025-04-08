/*
    Compilador Musical: Análisis Semántico

    Este programa crea un AST para un programa musical simple y realiza análisis
    semántico sobre él. El programa musical hipotético tiene la siguiente forma:

    // Configuración musical
    Tempo 120;
    Compas 7/8;
    Tonalidad Si M;
    
    // Secuencia de notas musicales
    // Patrones rítmicos en 7/8 (agrupados 2+2+3)
    G4 Corchea
    G4 Corchea
    A4 Corchea
    A4 Corchea
    B4 Corchea
    B4 Corchea
    B4 Corchea
    
    // Otro patrón rítmico (3+2+2)
    C#5 Corchea
    C#5 Corchea
    C#5 Corchea
    
    // Mezcla de duraciones
    F#4 Negra
    B4 Negra
    C#5 Semicorchea
*/

#include <iostream>
#include <iomanip>

#include "datatype.hpp"
#include "declaration.hpp"
#include "expression.hpp"
#include "statement.hpp"
#include "symbol_table.hpp"

// Función auxiliar para imprimir el resultado de una validación
void print_validation_result(const std::string& node_name, bool success) {
    std::cout << std::setw(40) << std::left << node_name 
              << " | " << (success ? "✓ ÉXITO" : "✗ ERROR") << std::endl;
}

int main(){
    try {
        std::cout << "====== Compilador Musical: Demo de Análisis Semántico ======" << std::endl;
        
        // Declaración de variables globales (configuración musical)
        auto tempo_declaration = new TempoDeclaration{
            "tempo", 120
        };
        
        auto key_declaration = new KeyDeclaration{
            "tonalidad", "Si", "M"
        };
        
        auto time_declaration = new TimeSignatureDeclaration{
            "compas", 7, 8
        };
        
        // Comentario para la primera secuencia
        auto comment1 = new PrintStatement{
            new StrExpression{"// Patrones rítmicos en 7/8 (agrupados 2+2+3)"}
        };
        
        // Primera secuencia de notas: patrón 2+2+3 en corcheas
        auto nota1 = new NoteDeclaration{
            "nota1", 'G', 4, "Corchea"
        };
        
        auto nota2 = new NoteDeclaration{
            "nota2", 'G', 4, "Corchea"
        };
        
        auto nota3 = new NoteDeclaration{
            "nota3", 'A', 4, "Corchea"
        };
        
        auto nota4 = new NoteDeclaration{
            "nota4", 'A', 4, "Corchea"
        };
        
        auto nota5 = new NoteDeclaration{
            "nota5", 'B', 4, "Corchea"
        };
        
        auto nota6 = new NoteDeclaration{
            "nota6", 'B', 4, "Corchea"
        };
        
        auto nota7 = new NoteDeclaration{
            "nota7", 'B', 4, "Corchea"
        };
        
        // Comentario para la segunda secuencia
        auto comment2 = new PrintStatement{
            new StrExpression{"// Otro patrón rítmico (3+2+2)"}
        };
        
        // Segunda secuencia de notas: notas con alteraciones
        auto nota8 = new NoteDeclaration{
            "nota8", 'C', 5, "Corchea"
        };
        
        auto nota9 = new NoteDeclaration{
            "nota9", 'C', 5, "Corchea"
        };
        
        auto nota10 = new NoteDeclaration{
            "nota10", 'C', 5, "Corchea"
        };
        
        // Aplicar sostenidos
        auto sharp_nota8 = new SharpExpression{
            new NameExpression{"nota8"}
        };
        
        auto sharp_nota9 = new SharpExpression{
            new NameExpression{"nota9"}
        };
        
        auto sharp_nota10 = new SharpExpression{
            new NameExpression{"nota10"}
        };
        
        // Comentario para la tercera secuencia
        auto comment3 = new PrintStatement{
            new StrExpression{"// Mezcla de duraciones"}
        };
        
        // Tercera secuencia: mezcla de duraciones
        auto nota11 = new NoteDeclaration{
            "nota11", 'F', 4, "Negra"
        };
        
        auto nota12 = new NoteDeclaration{
            "nota12", 'B', 4, "Negra"
        };
        
        auto nota13 = new NoteDeclaration{
            "nota13", 'C', 5, "Semicorchea"
        };
        
        // Aplicar sostenido a F4 y C5
        auto sharp_nota11 = new SharpExpression{
            new NameExpression{"nota11"}
        };
        
        auto sharp_nota13 = new SharpExpression{
            new NameExpression{"nota13"}
        };
        
        // programa completo
        auto program = Body{
            // Configuración
            new DeclarationStatement{tempo_declaration},
            new DeclarationStatement{key_declaration},
            new DeclarationStatement{time_declaration},
            
            // Primera secuencia
            comment1,
            new DeclarationStatement{nota1},
            new DeclarationStatement{nota2},
            new DeclarationStatement{nota3},
            new DeclarationStatement{nota4},
            new DeclarationStatement{nota5},
            new DeclarationStatement{nota6},
            new DeclarationStatement{nota7},
            
            // Segunda secuencia
            comment2,
            new DeclarationStatement{nota8},
            new ExpressionStatement{sharp_nota8},
            new DeclarationStatement{nota9},
            new ExpressionStatement{sharp_nota9},
            new DeclarationStatement{nota10},
            new ExpressionStatement{sharp_nota10},
            
            // Tercera secuencia
            comment3,
            new DeclarationStatement{nota11},
            new ExpressionStatement{sharp_nota11},
            new DeclarationStatement{nota12},
            new DeclarationStatement{nota13},
            new ExpressionStatement{sharp_nota13}
        };
        
        // Realizar análisis semántico 
        std::cout << "\n=== Resolución de nombres ===\n" << std::endl;
        std::cout << std::setw(40) << std::left << "NODO" << " | RESULTADO" << std::endl;
        std::cout << std::string(60, '-') << std::endl;
        
        SymbolTable symbol_table;
        bool all_names_resolved = true;
        
        // Procesar cada nodo individualmente e imprimir resultados
        for (Statement* statement : program) {
            std::string node_description;
            
            // Determinar el tipo de nodo para mostrar información específica
            if (auto decl_stmt = dynamic_cast<DeclarationStatement*>(statement)) {
                if (auto var_decl = dynamic_cast<VariableDeclaration*>(decl_stmt->get_declaration())) {
                    node_description = "Variable: " + var_decl->get_name();
                } else if (auto tempo_decl = dynamic_cast<TempoDeclaration*>(decl_stmt->get_declaration())) {
                    node_description = "Tempo: " + tempo_decl->get_name() + " (" + std::to_string(tempo_decl->get_bpm()) + " BPM)";
                } else if (auto key_decl = dynamic_cast<KeyDeclaration*>(decl_stmt->get_declaration())) {
                    node_description = "Tonalidad: " + key_decl->get_name() + " (" + key_decl->get_pitch() + " " + key_decl->get_mode() + ")";
                } else if (auto time_decl = dynamic_cast<TimeSignatureDeclaration*>(decl_stmt->get_declaration())) {
                    node_description = "Compás: " + time_decl->get_name() + " (" + 
                                     std::to_string(time_decl->get_numerator()) + "/" + 
                                     std::to_string(time_decl->get_denominator()) + ")";
                } else if (auto note_decl = dynamic_cast<NoteDeclaration*>(decl_stmt->get_declaration())) {
                    node_description = "Nota: " + note_decl->get_name() + " (" + 
                                     std::string(1, note_decl->get_pitch()) + 
                                     std::to_string(note_decl->get_octave()) + " " + 
                                     note_decl->get_duration() + ")";
                } else {
                    node_description = "Declaración";
                }
            } else if (auto expr_stmt = dynamic_cast<ExpressionStatement*>(statement)) {
                if (dynamic_cast<SharpExpression*>(expr_stmt->get_expression())) {
                    node_description = "Sostenido";
                } else {
                    node_description = "Expresión";
                }
            } else if (dynamic_cast<PrintStatement*>(statement)) {
                node_description = "Comentario";
            } else {
                node_description = "Nodo desconocido";
            }
            
            bool success = statement->resolve_name(symbol_table);
            print_validation_result(node_description, success);
            
            if (!success) {
                all_names_resolved = false;
            }
        }
        
        std::cout << "\nResultado final de resolución de nombres: " 
                 << (all_names_resolved ? "✓ ÉXITO" : "✗ ERROR") << std::endl;
        
        if (all_names_resolved) {
            std::cout << "\n=== Comprobación de tipos ===\n" << std::endl;
            std::cout << std::setw(40) << std::left << "NODO" << " | RESULTADO" << std::endl;
            std::cout << std::string(60, '-') << std::endl;
            
            bool all_types_valid = true;
            
            // Procesar cada nodo individualmente para comprobación de tipos
            for (Statement* statement : program) {
                std::string node_description;
                
                // Determinar el tipo de nodo para mostrar información específica 
                if (auto decl_stmt = dynamic_cast<DeclarationStatement*>(statement)) {
                    if (auto var_decl = dynamic_cast<VariableDeclaration*>(decl_stmt->get_declaration())) {
                        node_description = "Variable: " + var_decl->get_name();
                    } else if (auto tempo_decl = dynamic_cast<TempoDeclaration*>(decl_stmt->get_declaration())) {
                        node_description = "Tempo: " + tempo_decl->get_name();
                    } else if (auto key_decl = dynamic_cast<KeyDeclaration*>(decl_stmt->get_declaration())) {
                        node_description = "Tonalidad: " + key_decl->get_name();
                    } else if (auto time_decl = dynamic_cast<TimeSignatureDeclaration*>(decl_stmt->get_declaration())) {
                        node_description = "Compás: " + time_decl->get_name();
                    } else if (auto note_decl = dynamic_cast<NoteDeclaration*>(decl_stmt->get_declaration())) {
                        node_description = "Nota: " + note_decl->get_name();
                    } else {
                        node_description = "Declaración";
                    }
                } else if (auto expr_stmt = dynamic_cast<ExpressionStatement*>(statement)) {
                    if (dynamic_cast<SharpExpression*>(expr_stmt->get_expression())) {
                        node_description = "Sostenido";
                    } else {
                        node_description = "Expresión";
                    }
                } else if (dynamic_cast<PrintStatement*>(statement)) {
                    node_description = "Comentario";
                } else {
                    node_description = "Nodo desconocido";
                }
                
                auto type_result = statement->type_check();
                bool success = type_result.first;
                
                // Limpiar el tipo devuelto si existe
                if (type_result.second != nullptr) {
                    type_result.second->destroy();
                    delete type_result.second;
                }
                
                print_validation_result(node_description, success);
                
                if (!success) {
                    all_types_valid = false;
                }
            }
            
            std::cout << "\nResultado final de comprobación de tipos: " 
                     << (all_types_valid ? "✓ ÉXITO" : "✗ ERROR") << std::endl;
        }
        
        // Liberar memoria
        std::cout << "\n=== Liberando recursos ===" << std::endl;
        destroy_body(program);
        std::cout << "Análisis semántico completado." << std::endl;
        
        return EXIT_SUCCESS;
    } 
    catch (const std::exception& e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch (...) {
        std::cerr << "ERROR DESCONOCIDO" << std::endl;
        return EXIT_FAILURE;
    }
}