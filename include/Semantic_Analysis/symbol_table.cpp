#include "symbol_table.hpp"
#include "datatype.hpp"

std::shared_ptr<Symbol> Symbol::build(Datatype* type, std::string_view name) noexcept{
    auto symbol = std::make_shared<Symbol>();
    symbol->type = type;
    symbol->name = name;
    return symbol;
}

SymbolTable::SymbolTable() noexcept{
    // Iniciar con un ámbito global
    enter_scope();
}

SymbolTable::~SymbolTable() noexcept
{
    // limpiamos el vector directamente 
    scopes.clear();
}

void SymbolTable::enter_scope() noexcept{
    scopes.push_back(TableType());
}

bool SymbolTable::exit_scope() noexcept{
    if (scopes.size() <= 1){
        // no permitir eliminar el ambito global
        return false;
    }

    scopes.pop_back();
    return true;
}

SymbolTable::TableType::size_type SymbolTable::scope_level() const noexcept{
    return scopes.size();
}

bool SymbolTable::bind(const std::string& name, std::shared_ptr<Symbol> symbol) noexcept{
    // Verificar si el símbolo ya existe en el ámbito actual
    if (current_scope_lookup(name) != nullptr){
        return false; // si el simbolo ya existe en este ambito
    }

    // agregar el simbolo al ambito actual
    scopes.back()[name] = symbol;
    return true;
}

std::shared_ptr<Symbol> SymbolTable::lookup(const std::string& name) noexcept{
    // buscar el simbolo en todos los ambitos, comenzando por el mas reciente
    for (auto it = scopes.rbegin(); it != scopes.rend(); ++it){
        auto symbol = find_in_scope(name, *it);
        if (symbol != nullptr)
        {
            return symbol;
        }
    }

    return nullptr; // No se encontró el símbolo
}

std::shared_ptr<Symbol> SymbolTable::current_scope_lookup(const std::string& name) noexcept{
    // Buscar sólo en el ámbito actual
    return find_in_scope(name, scopes.back());
}

std::shared_ptr<Symbol> SymbolTable::find_in_scope(const std::string& name, const TableType& scope) noexcept{
    auto it = scope.find(name);
    if (it != scope.end()){
        return it->second;
    }  
    return nullptr;
} 