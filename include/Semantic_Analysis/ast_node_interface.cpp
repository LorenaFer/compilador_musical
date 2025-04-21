#include "ast_node_interface.hpp"

#include "datatype.hpp"
#include "statement.hpp"
#include "symbol_table.hpp"
#include <algorithm>
#include <unordered_set> 

// Variable global para rastrear los nodos visitados 
static std::unordered_set<void*> visited_nodes;

void destroy_body(Body& body) noexcept{
    while (!body.empty()){
        Statement* statement = body.front();
        body.pop_front();
        statement->destroy();
        delete statement;
    }
}

Body copy_body(const Body& body) noexcept{
    Body result;

    for (auto statement : body){
        result.push_front(dynamic_cast<Statement*>(statement->copy()));
    }
    
    result.reverse(); // Para mantener el orden 
    return result;
}

bool equal_body(const Body& body1, const Body& body2) noexcept{
    auto it1 = body1.begin();
    auto it2 = body2.begin();
    
    while (it1 != body1.end() && it2 != body2.end()) {
        if (!(*it1)->equal(*it2)) 
        {
            return false;
        }
        ++it1;
        ++it2;
    }
    
    // Verificar que ambas listas tengan la misma longitud
    return it1 == body1.end() && it2 == body2.end();
}

std::pair<bool, Datatype*> body_type_check(const Body& body) noexcept{
    for (auto stmt : body){
        auto stmt_type = stmt->type_check();

        if (stmt_type.second != nullptr)
        {
            delete stmt_type.second;
            stmt_type.second = nullptr;
        }

        if (!stmt_type.first)
        {
            return std::make_pair(false, nullptr);
        }
    }

    return std::make_pair(true, nullptr);
}

bool resolve_name_body(Body& body, SymbolTable& symbol_table) noexcept{ //registro de variables en la tabla de simbolos
    static bool is_first_call = true;
    if (is_first_call) { //recorrido de todos los statements en un bloque de codigo
        visited_nodes.clear();
        is_first_call = false;
    }
    
    static int recursion_depth = 0;
    constexpr int max_recursion_depth = 100;
    
    recursion_depth++;
    if (recursion_depth > max_recursion_depth) {
        recursion_depth--;
        return false;
    }
    
    bool result = true;
    for (Statement* statement : body){
        if (visited_nodes.find(statement) != visited_nodes.end()) {
            continue;
        }
        
        visited_nodes.insert(statement);
        
        if (!statement->resolve_name(symbol_table))
        {
            result = false;
            break;
        }
    }
    
    recursion_depth--;
    if (recursion_depth == 0) {
        is_first_call = true;
    }
    return result;
}

void destroy_param_list(ParamList& param_list) noexcept
{
    while (!param_list.empty()){
        Param param = param_list.front();
        param_list.pop_front();
        param.second->destroy();
        delete param.second;
        param.second = nullptr;
    }
}

ParamList copy_param_list(const ParamList& param_list) noexcept{
    ParamList result;

    for (auto param : param_list){
        result.push_front(std::make_pair(param.first, dynamic_cast<Datatype*>(param.second->copy())));
    }
    
    result.reverse(); // Para mantener el orden 
    return result;
}

bool equal_param_list(const ParamList& param_list1, const ParamList& param_list2) noexcept{
    auto it1 = param_list1.begin();
    auto it2 = param_list2.begin();
    
    while (it1 != param_list1.end() && it2 != param_list2.end()) {
        if (it1->first != it2->first || !it1->second->equal(it2->second)) 
        {
            return false;
        }
        ++it1;
        ++it2;
    }
    
    // Verificar que ambas listas tengan la misma longitud
    return it1 == param_list1.end() && it2 == param_list2.end();
}

std::pair<bool, Datatype*> param_list_type_check(const ParamList& param_list) noexcept{
    for (const Param& param : param_list){
        auto param_type = param.second->type_check();
        if (param_type.second != nullptr)
        {
            delete param_type.second;
            param_type.second = nullptr;
        }

        if (!param_type.first)
        {
            return std::make_pair(false, nullptr);
        }
    }

    return std::make_pair(true, nullptr);
}

bool resolve_name_param_list(const ParamList& param_list, SymbolTable& symbol_table) noexcept{ //registro de parametros en la tabla de simbolos
    for (const Param& param : param_list){
        auto symbol = Symbol::build(param.second, param.first);

        if (!symbol_table.bind(param.first, symbol)){
            return false;
        }
    }

    return true;
}

ASTNodeInterface::~ASTNodeInterface() noexcept {} 