#include "ast_node_interface.hpp"

#include "statement.hpp"

// Implementación de la función para destruir el cuerpo de una declaración
void destroy_body(Body& body) noexcept
{
    while (!body.empty())
    {
        Statement* statement = body.front();
        body.pop_front();
        statement->destroy();
        delete statement;
    }
}

// Implementación del destructor virtual de la interfaz
ASTNodeInterface::~ASTNodeInterface() noexcept {} 