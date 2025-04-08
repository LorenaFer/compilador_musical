#pragma once

#include "ast_node_interface.hpp"

class Expression;
class Declaration;

class Statement : public ASTNodeInterface
{
};

class DeclarationStatement : public Statement
{
public:
    explicit DeclarationStatement(Declaration* _declaration) noexcept;

    void destroy() noexcept override;

    ASTNodeInterface* copy() const noexcept override;

    bool equal(ASTNodeInterface* other) const noexcept override;

    std::pair<bool, Datatype*> type_check() const noexcept override;

    bool resolve_name(SymbolTable& symbol_table) noexcept override;

    Declaration* get_declaration() const noexcept;

private:
    Declaration* declaration;
};

class ExpressionStatement : public Statement
{
public:
    explicit ExpressionStatement(Expression* _expression) noexcept;

    void destroy() noexcept override;

    ASTNodeInterface* copy() const noexcept override;

    bool equal(ASTNodeInterface* other) const noexcept override;

    std::pair<bool, Datatype*> type_check() const noexcept override;

    bool resolve_name(SymbolTable& symbol_table) noexcept override;

    Expression* get_expression() const noexcept;

private:
    Expression* expression;
};

// Sentencia de impresión para debugging
class PrintStatement : public Statement
{
public:
    explicit PrintStatement(Expression* _value) noexcept;

    void destroy() noexcept override;

    ASTNodeInterface* copy() const noexcept override;

    bool equal(ASTNodeInterface* other) const noexcept override;

    std::pair<bool, Datatype*> type_check() const noexcept override;

    bool resolve_name(SymbolTable& symbol_table) noexcept override;

    Expression* get_value() const noexcept;

private:
    Expression* value;
}; 