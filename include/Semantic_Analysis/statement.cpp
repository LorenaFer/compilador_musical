#include "statement.hpp"
#include "declaration.hpp"
#include "expression.hpp"
#include "datatype.hpp"
#include "symbol_table.hpp"

DeclarationStatement::DeclarationStatement(Declaration* _declaration) noexcept
    : declaration(_declaration)
{
}

void DeclarationStatement::destroy() noexcept
{
    if (declaration != nullptr){
        declaration->destroy();
        delete declaration;
        declaration = nullptr;
    }
}

ASTNodeInterface* DeclarationStatement::copy() const noexcept
{
    return new DeclarationStatement(
        dynamic_cast<Declaration*>(declaration->copy())
    );
}

bool DeclarationStatement::equal(ASTNodeInterface* other) const noexcept
{
    auto other_decl = dynamic_cast<DeclarationStatement*>(other);
    if (other_decl == nullptr){
        return false;
    }

    return declaration->equal(other_decl->declaration);
}

std::pair<bool, Datatype*> DeclarationStatement::type_check() const noexcept
{
    return declaration->type_check();
}

bool DeclarationStatement::resolve_name(SymbolTable& symbol_table) noexcept
{
    return declaration->resolve_name(symbol_table);
}

Declaration* DeclarationStatement::get_declaration() const noexcept
{
    return declaration;
}

ExpressionStatement::ExpressionStatement(Expression* _expression) noexcept
    : expression(_expression)
{
}

void ExpressionStatement::destroy() noexcept
{
    if (expression != nullptr){
        expression->destroy();
        delete expression;
        expression = nullptr;
    }
}

ASTNodeInterface* ExpressionStatement::copy() const noexcept
{
    return new ExpressionStatement(
        dynamic_cast<Expression*>(expression->copy())
    );
}

bool ExpressionStatement::equal(ASTNodeInterface* other) const noexcept
{
    auto other_expr = dynamic_cast<ExpressionStatement*>(other);
    if (other_expr == nullptr){
        return false;
    }

    return expression->equal(other_expr->expression);
}

std::pair<bool, Datatype*> ExpressionStatement::type_check() const noexcept
{
    auto expr_type = expression->type_check();
    if (!expr_type.first){
        if (expr_type.second != nullptr)
        {
            delete expr_type.second;
            expr_type.second = nullptr;
        }
        return std::make_pair(false, nullptr);
    }

    if (expr_type.second != nullptr){
        delete expr_type.second;
        expr_type.second = nullptr;
    }

    return std::make_pair(true, nullptr);
}

bool ExpressionStatement::resolve_name(SymbolTable& symbol_table) noexcept
{
    return expression->resolve_name(symbol_table);
}

Expression* ExpressionStatement::get_expression() const noexcept
{
    return expression;
}

PrintStatement::PrintStatement(Expression* _value) noexcept
    : value(_value)
{
}

void PrintStatement::destroy() noexcept
{
    if (value != nullptr){
        value->destroy();
        delete value;
        value = nullptr;
    }
}

ASTNodeInterface* PrintStatement::copy() const noexcept
{
    return new PrintStatement(
        dynamic_cast<Expression*>(value->copy())
    );
}

bool PrintStatement::equal(ASTNodeInterface* other) const noexcept
{
    auto other_print = dynamic_cast<PrintStatement*>(other);
    if (other_print == nullptr){
        return false;
    }

    return value->equal(other_print->value);
}

std::pair<bool, Datatype*> PrintStatement::type_check() const noexcept
{
    auto value_type = value->type_check();
    if (!value_type.first){
        if (value_type.second != nullptr)
        {
            delete value_type.second;
            value_type.second = nullptr;
        }
        return std::make_pair(false, nullptr);
    }

    if (value_type.second != nullptr){
        delete value_type.second;
        value_type.second = nullptr;
    }

    return std::make_pair(true, nullptr);
}

bool PrintStatement::resolve_name(SymbolTable& symbol_table) noexcept
{
    return value->resolve_name(symbol_table);
}

Expression* PrintStatement::get_value() const noexcept
{
    return value;
} 