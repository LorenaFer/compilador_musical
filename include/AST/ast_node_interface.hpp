#pragma once

#include <forward_list>
#include <string>
#include <string_view>
#include <sstream>

class Declaration;
class Expression;
class Statement;
class Datatype;
class Note;
class TimeSignature;
class Key;
class Tempo;

// Lista para representar el cuerpo de una composición musical
using Body = std::forward_list<Statement*>;

// Declaración de parámetros para funciones
using Param = std::pair<std::string, Datatype*>;
using ParamList = std::forward_list<Param>;

// Función para destruir el cuerpo de una declaración
void destroy_body(Body& body) noexcept;

// Interfaz base para todos los nodos del AST musical
class ASTNodeInterface
{
public:
    virtual ~ASTNodeInterface() noexcept;

    // Método para destruir recursivamente el nodo y sus dependencias
    virtual void destroy() noexcept = 0;
    
    // Método para generar una representación en texto del nodo
    virtual std::string to_string() const = 0;
}; 