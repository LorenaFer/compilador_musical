#pragma once

#include "ast_node_interface.hpp"

class Expression : public ASTNodeInterface
{
};

// Expresiones de valores literales básicos
class BoolExpression : public Expression
{
public:
    explicit BoolExpression(bool _value) noexcept;

    void destroy() noexcept override;

    ASTNodeInterface* copy() const noexcept override;

    bool equal(ASTNodeInterface* other) const noexcept override;

    std::pair<bool, Datatype*> type_check() const noexcept override;

    bool resolve_name(SymbolTable& symbol_table) noexcept override;

    bool get_value() const noexcept;

private:
    bool value;
};

class IntExpression : public Expression
{
public:
    explicit IntExpression(int _value) noexcept;

    void destroy() noexcept override;

    ASTNodeInterface* copy() const noexcept override;

    bool equal(ASTNodeInterface* other) const noexcept override;

    std::pair<bool, Datatype*> type_check() const noexcept override;

    bool resolve_name(SymbolTable& symbol_table) noexcept override;

    int get_value() const noexcept;

private:
    int value;
};

class StrExpression : public Expression
{
public:
    explicit StrExpression(const std::string& _value) noexcept;

    void destroy() noexcept override;

    ASTNodeInterface* copy() const noexcept override;

    bool equal(ASTNodeInterface* other) const noexcept override;

    std::pair<bool, Datatype*> type_check() const noexcept override;

    bool resolve_name(SymbolTable& symbol_table) noexcept override;

    const std::string& get_value() const noexcept;

private:
    std::string value;
};

// Expresiones específicas musicales
class NoteExpression : public Expression
{
public:
    NoteExpression(const std::string& _pitch, int _octave, int _duration) noexcept;

    void destroy() noexcept override;

    ASTNodeInterface* copy() const noexcept override;

    bool equal(ASTNodeInterface* other) const noexcept override;

    std::pair<bool, Datatype*> type_check() const noexcept override;

    bool resolve_name(SymbolTable& symbol_table) noexcept override;

    const std::string& get_pitch() const noexcept;
    int get_octave() const noexcept;
    int get_duration() const noexcept;

private:
    std::string pitch;  // C, D, E, F, G, A, B (posiblemente con # o b)
    int octave;         // número de octava
    int duration;       // duración (negra, corchea, etc.)
};

class KeyExpression : public Expression
{
public:
    explicit KeyExpression(const std::string& _key) noexcept;

    void destroy() noexcept override;

    ASTNodeInterface* copy() const noexcept override;

    bool equal(ASTNodeInterface* other) const noexcept override;

    std::pair<bool, Datatype*> type_check() const noexcept override;

    bool resolve_name(SymbolTable& symbol_table) noexcept override;

    const std::string& get_key() const noexcept;

private:
    std::string key; // Tonalidad (C, Dm, etc.)
};

class TempoExpression : public Expression
{
public:
    explicit TempoExpression(int _bpm) noexcept;

    void destroy() noexcept override;

    ASTNodeInterface* copy() const noexcept override;

    bool equal(ASTNodeInterface* other) const noexcept override;

    std::pair<bool, Datatype*> type_check() const noexcept override;

    bool resolve_name(SymbolTable& symbol_table) noexcept override;

    int get_bpm() const noexcept;

private:
    int bpm; // Beats per minute
};

class TimeSignatureExpression : public Expression
{
public:
    TimeSignatureExpression(int _numerator, int _denominator) noexcept;

    void destroy() noexcept override;

    ASTNodeInterface* copy() const noexcept override;

    bool equal(ASTNodeInterface* other) const noexcept override;

    std::pair<bool, Datatype*> type_check() const noexcept override;

    bool resolve_name(SymbolTable& symbol_table) noexcept override;

    int get_numerator() const noexcept;
    int get_denominator() const noexcept;

private:
    int numerator;   // número de pulsos por compás
    int denominator; // duración de la nota que define el pulso
};

// Expresión para nombres/identificadores
class NameExpression : public Expression
{
public:
    explicit NameExpression(const std::string& _name) noexcept;

    void destroy() noexcept override;

    ASTNodeInterface* copy() const noexcept override;

    bool equal(ASTNodeInterface* other) const noexcept override;

    std::pair<bool, Datatype*> type_check() const noexcept override;

    bool resolve_name(SymbolTable& symbol_table) noexcept override;

    const std::string& get_name() const noexcept;

private:
    std::string name;
};

// Expresión para acceso a arrays
class ArrayAccessExpression : public Expression
{
public:
    ArrayAccessExpression(Expression* _array, Expression* _index) noexcept;

    void destroy() noexcept override;

    ASTNodeInterface* copy() const noexcept override;

    bool equal(ASTNodeInterface* other) const noexcept override;

    std::pair<bool, Datatype*> type_check() const noexcept override;

    bool resolve_name(SymbolTable& symbol_table) noexcept override;

    Expression* get_array() const noexcept;
    Expression* get_index() const noexcept;

private:
    Expression* array;
    Expression* index;
};

// Expresión para asignación
class AssignmentExpression : public Expression
{
public:
    AssignmentExpression(Expression* _target, Expression* _value) noexcept;

    void destroy() noexcept override;

    ASTNodeInterface* copy() const noexcept override;

    bool equal(ASTNodeInterface* other) const noexcept override;

    std::pair<bool, Datatype*> type_check() const noexcept override;

    bool resolve_name(SymbolTable& symbol_table) noexcept override;

    Expression* get_target() const noexcept;
    Expression* get_value() const noexcept;

private:
    Expression* target;
    Expression* value;
};

// Expresión para llamada a función
class CallExpression : public Expression
{
public:
    CallExpression(Expression* _function, Expression* _arguments) noexcept;

    void destroy() noexcept override;

    ASTNodeInterface* copy() const noexcept override;

    bool equal(ASTNodeInterface* other) const noexcept override;

    std::pair<bool, Datatype*> type_check() const noexcept override;

    bool resolve_name(SymbolTable& symbol_table) noexcept override;

    Expression* get_function() const noexcept;
    Expression* get_arguments() const noexcept;

private:
    Expression* function;
    Expression* arguments;
};

// Expresión para argumentos en llamadas a función
class ArgExpression : public Expression
{
public:
    ArgExpression(Expression* _value, Expression* _next) noexcept;

    void destroy() noexcept override;

    ASTNodeInterface* copy() const noexcept override;

    bool equal(ASTNodeInterface* other) const noexcept override;

    std::pair<bool, Datatype*> type_check() const noexcept override;

    bool resolve_name(SymbolTable& symbol_table) noexcept override;

    Expression* get_value() const noexcept;
    Expression* get_next() const noexcept;

private:
    Expression* value;
    Expression* next; // Siguiente argumento en la lista
};

// Expresiones unarias
class UnaryExpression : public Expression
{
public:
    explicit UnaryExpression(Expression* _operand) noexcept;

    void destroy() noexcept override;

protected:
    Expression* operand;
};

// Alteración de sostenido para notas
class SharpExpression : public UnaryExpression
{
public:
    using UnaryExpression::UnaryExpression;

    ASTNodeInterface* copy() const noexcept override;

    bool equal(ASTNodeInterface* other) const noexcept override;

    std::pair<bool, Datatype*> type_check() const noexcept override;

    bool resolve_name(SymbolTable& symbol_table) noexcept override;
}; 