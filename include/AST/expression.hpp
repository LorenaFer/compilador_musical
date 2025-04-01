#pragma once

#include <string>
#include <string_view>
#include <sstream>

#include "ast_node_interface.hpp"

// Clase base para todas las expresiones
class Expression : public ASTNodeInterface
{
public:
    virtual std::string to_string() const override = 0;
};

// Expresiones unarias (modificadores de nota específicas, etc.)
class UnaryExpression : public Expression
{
public:
    UnaryExpression(Expression* expr) noexcept;
    
    void destroy() noexcept override;
    virtual std::string to_string() const override;

protected:
    Expression* expression;
};

// Expresión para sostenido en nota musical
class SharpExpression : public UnaryExpression
{
public:
    using UnaryExpression::UnaryExpression;
    std::string to_string() const override;
};

// Expresión para bemol en nota musical
class FlatExpression : public UnaryExpression
{
public:
    using UnaryExpression::UnaryExpression;
    std::string to_string() const override;
};

// Expresiones binarias (operaciones entre dos elementos)
class BinaryExpression : public Expression
{
public:
    BinaryExpression(Expression* left_expr, Expression* right_expr) noexcept;
    
    void destroy() noexcept override;
    virtual std::string to_string() const override;

protected:
    Expression* left_expression;
    Expression* right_expression;
};

// Expresión de asignación
class AssignmentExpression : public BinaryExpression
{
public:
    using BinaryExpression::BinaryExpression;
    std::string to_string() const override;
};

// Expresiones hoja (valores terminales)
class LeafExpression : public Expression
{
public:
    void destroy() noexcept override;
};

// Expresión para nombres (variables, etc.)
class NameExpression : public LeafExpression
{
public:
    NameExpression(std::string_view _name) noexcept;
    std::string to_string() const override;

private:
    std::string name;
};

// Expresión para valores enteros
class IntExpression : public LeafExpression
{
public:
    IntExpression(int _value) noexcept;
    std::string to_string() const override;

private:
    int value;
};

// Expresión para cadenas de texto
class StrExpression : public LeafExpression
{
public:
    StrExpression(std::string_view _value) noexcept;
    std::string to_string() const override;

private:
    std::string value;
};

// Expresión para notas musicales simples
class NoteExpression : public LeafExpression
{
public:
    NoteExpression(char _pitch, int _octave, std::string_view _duration) noexcept;
    std::string to_string() const override;

private:
    char pitch;           // La nota (A, B, C, D, E, F, G) o (Do, Re, Mi, Fa, Sol, La, Si)
    int octave;           // La octava
    std::string duration; // La duración (Blanca, Negra, Corchea, Semicorchea)
}; 