#include "statement.hpp"

#include "declaration.hpp"
#include "expression.hpp"

// Implementación de DeclarationStatement
DeclarationStatement::DeclarationStatement(Declaration* decl) noexcept
    : declaration{decl} {}

void DeclarationStatement::destroy() noexcept
{
    if (this->declaration)
    {
        this->declaration->destroy();
        delete this->declaration;
    }
}

std::string DeclarationStatement::to_string() const
{
    return this->declaration->to_string();
}

// Implementación de ExpressionStatement
ExpressionStatement::ExpressionStatement(Expression* expr) noexcept
    : expression{expr} {}

void ExpressionStatement::destroy() noexcept
{
    if (this->expression)
    {
        this->expression->destroy();
        delete this->expression;
    }
}

std::string ExpressionStatement::to_string() const
{
    return this->expression->to_string();
}

// Implementación de IfElseStatement
IfElseStatement::IfElseStatement(Expression* ctrl_expr, const Body& _body, const Body& _else_body) noexcept
    : ExpressionStatement{ctrl_expr}, body{_body}, else_body{_else_body} {}

void IfElseStatement::destroy() noexcept
{
    ExpressionStatement::destroy();
    destroy_body(this->body);
    destroy_body(this->else_body);
}

std::string IfElseStatement::to_string() const
{
    std::stringstream ss;
    ss << "if (" << this->expression->to_string() << ") {\n";
    
    for (const auto& statement : body)
    {
        ss << "  " << statement->to_string() << "\n";
    }
    
    if (!else_body.empty())
    {
        ss << "} else {\n";
        for (const auto& statement : else_body)
        {
            ss << "  " << statement->to_string() << "\n";
        }
    }
    
    ss << "}";
    return ss.str();
}

// Implementación de ForStatement
ForStatement::ForStatement(Expression* init_expr, Expression* ctrl_expr, Expression* next_expr, const Body& _body) noexcept
    : ExpressionStatement{ctrl_expr}, init_expression{init_expr}, next_expression{next_expr}, body{_body} {}

void ForStatement::destroy() noexcept
{
    ExpressionStatement::destroy();
    
    if (this->init_expression)
    {
        this->init_expression->destroy();
        delete this->init_expression;
    }
    
    if (this->next_expression)
    {
        this->next_expression->destroy();
        delete this->next_expression;
    }
    
    destroy_body(this->body);
}

std::string ForStatement::to_string() const
{
    std::stringstream ss;
    ss << "for (" << this->init_expression->to_string() << "; "
       << this->expression->to_string() << "; "
       << this->next_expression->to_string() << ") {\n";
    
    for (const auto& statement : body)
    {
        ss << "  " << statement->to_string() << "\n";
    }
    
    ss << "}";
    return ss.str();
}

// Implementación de RepeatStatement
RepeatStatement::RepeatStatement(Expression* count_expr, const Body& _body) noexcept
    : ExpressionStatement{count_expr}, body{_body} {}

void RepeatStatement::destroy() noexcept
{
    ExpressionStatement::destroy();
    destroy_body(this->body);
}

std::string RepeatStatement::to_string() const
{
    std::stringstream ss;
    ss << "repeat (" << this->expression->to_string() << ") {\n";
    
    for (const auto& statement : body)
    {
        ss << "  " << statement->to_string() << "\n";
    }
    
    ss << "}";
    return ss.str();
}

// Implementación de PrintStatement
std::string PrintStatement::to_string() const
{
    return "print(" + this->expression->to_string() + ")";
}

// Implementación de ReturnStatement
std::string ReturnStatement::to_string() const
{
    return "return " + this->expression->to_string();
}

// Implementación de PlayStatement
std::string PlayStatement::to_string() const
{
    return "play " + this->expression->to_string();
}

// Implementación de RestStatement
RestStatement::RestStatement(std::string_view duration) noexcept
    : duration{duration} {}

void RestStatement::destroy() noexcept
{
    // No hay nada que destruir
}

std::string RestStatement::to_string() const
{
    return "rest " + duration;
}

// Implementación de MeasureStatement (actualizada)
MeasureStatement::MeasureStatement(const Body& _notes_as_stmts) noexcept
    : notes_as_statements{_notes_as_stmts} {}

void MeasureStatement::destroy() noexcept
{
    destroy_body(this->notes_as_statements);
}

std::string MeasureStatement::to_string() const
{
    std::stringstream ss;
    ss << "measure {\n";
    
    for (const auto& statement : notes_as_statements)
    {
        ss << "  " << statement->to_string() << "\n";
    }
    
    ss << "}";
    return ss.str();
} 