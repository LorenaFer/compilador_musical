#pragma once

#include "ast_node_interface.hpp"

// Declaraciones necesarias
class Declaration;
class Expression;

// Clase base para todas las sentencias
class Statement : public ASTNodeInterface
{
public:
    virtual std::string to_string() const override = 0;
};

// Sentencia de declaración (variable, nota, etc.)
class DeclarationStatement : public Statement
{
public:
    DeclarationStatement(Declaration* decl) noexcept;
    
    void destroy() noexcept override;
    std::string to_string() const override;

private:
    Declaration* declaration;
};

// Sentencia de expresión
class ExpressionStatement : public Statement
{
public:
    ExpressionStatement(Expression* expr) noexcept;
    
    void destroy() noexcept override;
    std::string to_string() const override;

protected:
    Expression* expression;
};

// Sentencia condicional
class IfElseStatement : public ExpressionStatement
{
public:
    IfElseStatement(Expression* ctrl_expr, const Body& _body, const Body& _else_body = Body{}) noexcept;
    
    void destroy() noexcept override;
    std::string to_string() const override;

private:
    Body body;
    Body else_body;
};

// Sentencia de repetición
class ForStatement : public ExpressionStatement
{
public:
    ForStatement(Expression* init_expr, Expression* ctrl_expr, Expression* next_expr, const Body& _body) noexcept;
    
    void destroy() noexcept override;
    std::string to_string() const override;

private:
    Expression* init_expression;
    Expression* next_expression;
    Body body;
};

// Sentencia de repetición musical
class RepeatStatement : public ExpressionStatement
{
public:
    RepeatStatement(Expression* count_expr, const Body& _body) noexcept;
    
    void destroy() noexcept override;
    std::string to_string() const override;

private:
    Body body;
};

// Sentencia de impresión
class PrintStatement : public ExpressionStatement
{
public:
    using ExpressionStatement::ExpressionStatement;
    std::string to_string() const override;
};

// Sentencia de retorno
class ReturnStatement : public ExpressionStatement
{
public:
    using ExpressionStatement::ExpressionStatement;
    std::string to_string() const override;
};

// Sentencia de reproducción de nota
class PlayStatement : public ExpressionStatement
{
public:
    using ExpressionStatement::ExpressionStatement;
    std::string to_string() const override;
};

// Sentencia de pausa/silencio
class RestStatement : public Statement
{
public:
    RestStatement(std::string_view duration) noexcept;
    
    void destroy() noexcept override;
    std::string to_string() const override;

private:
    std::string duration;
};

// Sentencia para agrupar notas en un compás (simplificada)
class MeasureStatement : public Statement
{
public:
    // Constructor que acepta un Body en lugar de NoteSequence
    MeasureStatement(const Body& _notes_as_stmts = Body{}) noexcept;
    
    void destroy() noexcept override;
    std::string to_string() const override;

private:
    // Usamos Body (lista de Statement*) en lugar de NoteSequence
    Body notes_as_statements;
}; 