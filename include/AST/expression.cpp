#include "expression.hpp"

// Implementación de UnaryExpression
UnaryExpression::UnaryExpression(Expression* expr) noexcept
    : expression{expr} {}

void UnaryExpression::destroy() noexcept
{
    if (this->expression)
    {
        this->expression->destroy();
        delete this->expression;
    }
}

std::string UnaryExpression::to_string() const
{
    return this->expression->to_string();
}

// Implementación de expresiones unarias específicas
std::string SharpExpression::to_string() const
{
    return this->expression->to_string() + "#";
}

std::string FlatExpression::to_string() const
{
    return this->expression->to_string() + "b";
}

// Implementación de BinaryExpression
BinaryExpression::BinaryExpression(Expression* left_expr, Expression* right_expr) noexcept
    : left_expression{left_expr}, right_expression{right_expr} {}

void BinaryExpression::destroy() noexcept
{
    if (this->left_expression)
    {
        this->left_expression->destroy();
        delete this->left_expression;
    }

    if (this->right_expression)
    {
        this->right_expression->destroy();
        delete this->right_expression;
    }
}

std::string BinaryExpression::to_string() const
{
    return this->left_expression->to_string() + " " + this->right_expression->to_string();
}

// Implementación de expresión de asignación
std::string AssignmentExpression::to_string() const
{
    return this->left_expression->to_string() + " = " + this->right_expression->to_string();
}

// Implementación de LeafExpression
void LeafExpression::destroy() noexcept {}

// Implementación de expresiones hoja específicas
NameExpression::NameExpression(std::string_view _name) noexcept
    : name{_name} {}

std::string NameExpression::to_string() const
{
    return name;
}

IntExpression::IntExpression(int _value) noexcept
    : value{_value} {}

std::string IntExpression::to_string() const
{
    return std::to_string(value);
}

StrExpression::StrExpression(std::string_view _value) noexcept
    : value{_value} {}

std::string StrExpression::to_string() const
{
    return "\"" + value + "\"";
}

NoteExpression::NoteExpression(char _pitch, int _octave, std::string_view _duration) noexcept
    : pitch{_pitch}, octave{_octave}, duration{_duration} {}

std::string NoteExpression::to_string() const
{
    std::stringstream ss;
    ss << pitch << octave << " " << duration;
    return ss.str();
} 