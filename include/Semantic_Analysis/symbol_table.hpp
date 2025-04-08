#pragma once

#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

class Datatype;

// Estructura para representar un símbolo en la tabla de símbolos
struct Symbol
{
    Datatype* type;
    std::string name;
    
    static std::shared_ptr<Symbol> build(Datatype* type, std::string_view name) noexcept;
};

// Tabla de símbolos para el análisis semántico del lenguaje musical
class SymbolTable
{
public:
    using TableType = std::unordered_map<std::string, std::shared_ptr<Symbol>>;
    using TableStack = std::vector<TableType>;

    SymbolTable() noexcept;

    ~SymbolTable() noexcept;

    // Crear un nuevo ámbito
    void enter_scope() noexcept;

    // Salir del ámbito actual
    bool exit_scope() noexcept;

    // Obtener el nivel de ámbito actual
    TableType::size_type scope_level() const noexcept;

    // Asociar un nombre a un símbolo en el ámbito actual
    bool bind(const std::string& name, std::shared_ptr<Symbol> symbol) noexcept;

    // Buscar un símbolo por nombre en todos los ámbitos, comenzando por el actual
    std::shared_ptr<Symbol> lookup(const std::string& name) noexcept;

    // Buscar un símbolo por nombre solo en el ámbito actual
    std::shared_ptr<Symbol> current_scope_lookup(const std::string& name) noexcept;

private:
    // Función auxiliar para buscar en un ámbito específico
    static std::shared_ptr<Symbol> find_in_scope(const std::string& name, const TableType& scope) noexcept;

    // Pila de ámbitos (el último es el actual)
    TableStack scopes;
}; 