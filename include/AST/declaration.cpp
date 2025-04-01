#include "declaration.hpp"

#include "expression.hpp"
#include "statement.hpp"

// Implementación de Declaration

Declaration::Declaration(std::string_view decl_name, Datatype* datatype) noexcept
    : name{decl_name}, type{datatype} {}

std::string Declaration::to_string() const
{
    return name + " : " + type->to_string();
}

// VariableDeclaration

VariableDeclaration::VariableDeclaration(std::string_view var_name, Datatype* datatype, Expression* expr) noexcept
    : Declaration{var_name, datatype}, expression{expr} {}

void VariableDeclaration::destroy() noexcept
{
    if (type)
    {
        type->destroy();
        delete type;
    }
    
    if (expression)
    {
        expression->destroy();
        delete expression;
    }
}

std::string VariableDeclaration::to_string() const
{
    std::string result = "var " + Declaration::to_string();
    if (expression)
    {
        result += " = " + expression->to_string();
    }
    return result;
}

// NoteDeclaration

NoteDeclaration::NoteDeclaration(std::string_view note_name, char pitch, int octave, std::string_view duration) noexcept
    : Declaration{note_name, new NoteDatatype{}}, pitch{pitch}, octave{octave}, duration{duration} {}

void NoteDeclaration::destroy() noexcept
{
    if (type)
    {
        type->destroy();
        delete type;
    }
}

std::string NoteDeclaration::to_string() const
{
    return std::string(1, pitch) + std::to_string(octave) + " " + duration;
}

// KeyDeclaration

KeyDeclaration::KeyDeclaration(std::string_view key_name, std::string_view root, std::string_view mode) noexcept
    : Declaration{key_name, new KeyDatatype{}}, root{root}, mode{mode} {}

void KeyDeclaration::destroy() noexcept
{
    if (type)
    {
        type->destroy();
        delete type;
    }
}

std::string KeyDeclaration::to_string() const
{
    return "Tonalidad " + root + mode;
}

// TimeSignatureDeclaration

TimeSignatureDeclaration::TimeSignatureDeclaration(std::string_view time_sig_name, int beats, int beat_value) noexcept
    : Declaration{time_sig_name, new TimeSignatureDatatype{}}, beats{beats}, beat_value{beat_value} {}

void TimeSignatureDeclaration::destroy() noexcept
{
    if (type)
    {
        type->destroy();
        delete type;
    }
}

std::string TimeSignatureDeclaration::to_string() const
{
    return "Compas " + std::to_string(beats) + "/" + std::to_string(beat_value);
}

// TempoDeclaration

TempoDeclaration::TempoDeclaration(std::string_view tempo_name, int bpm) noexcept
    : Declaration{tempo_name, new TempoDatatype{}}, bpm{bpm} {}

void TempoDeclaration::destroy() noexcept
{
    if (type)
    {
        type->destroy();
        delete type;
    }
}

std::string TempoDeclaration::to_string() const
{
    return "Tempo " + std::to_string(bpm);
}

// FunctionDeclaration

FunctionDeclaration::FunctionDeclaration(std::string_view fct_name, Datatype* datatype, const Body& fct_body) noexcept
    : Declaration{fct_name, datatype}, body{fct_body} {}

void FunctionDeclaration::destroy() noexcept
{
    if (type)
    {
        type->destroy();
        delete type;
    }
    
    for (auto statement : body)
    {
        statement->destroy();
        delete statement;
    }
}

std::string FunctionDeclaration::to_string() const
{
    std::string result;
    
    // Imprimir cada declaración del cuerpo (sin la cabecera de la función)
    for (auto statement : body)
    {
        result += statement->to_string() + "\n";
    }
    
    return result;
} 