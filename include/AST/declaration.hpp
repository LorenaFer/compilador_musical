#pragma once

#include <string>
#include <string_view>

#include "ast_node_interface.hpp"
#include "datatype.hpp"

// Clase base para declaraciones
class Declaration : public ASTNodeInterface
{
public:
    Declaration(std::string_view decl_name, Datatype* datatype) noexcept;
    
    virtual std::string to_string() const override;

protected:
    std::string name;
    Datatype* type;
};

// Declaración de variables (instrumentos, valores, etc.)
class VariableDeclaration : public Declaration
{
public:
    VariableDeclaration(std::string_view var_name, Datatype* datatype, Expression* expr = nullptr) noexcept;
    
    void destroy() noexcept override;
    std::string to_string() const override;

private:
    Expression* expression;
};

// Declaración de notas musicales
class NoteDeclaration : public Declaration
{
public:
    NoteDeclaration(std::string_view note_name, char pitch, int octave, std::string_view duration) noexcept;
    
    void destroy() noexcept override;
    std::string to_string() const override;

private:
    char pitch;           // La nota (A, B, C, D, E, F, G)
    int octave;           // La octava
    std::string duration; // La duración (negra, blanca, etc.)
};

// Declaración de tonalidades
class KeyDeclaration : public Declaration
{
public:
    KeyDeclaration(std::string_view key_name, std::string_view root, std::string_view mode) noexcept;
    
    void destroy() noexcept override;
    std::string to_string() const override;

private:
    std::string root;    // Nota raíz (C, D, etc.)
    std::string mode;    // Modo: "M" para mayor, "m" para menor
};

// Declaración de compases
class TimeSignatureDeclaration : public Declaration
{
public:
    TimeSignatureDeclaration(std::string_view time_sig_name, int beats, int beat_value) noexcept;
    
    void destroy() noexcept override;
    std::string to_string() const override;

private:
    int beats;      // Número de tiempos por compás
    int beat_value; // Valor de la figura que recibe un tiempo
};

// Declaración de tempo
class TempoDeclaration : public Declaration
{
public:
    TempoDeclaration(std::string_view tempo_name, int bpm) noexcept;
    
    void destroy() noexcept override;
    std::string to_string() const override;

private:
    int bpm; // Pulsos por minuto
};

// Declaración de funciones (secciones musicales, comportamientos, etc.)
class FunctionDeclaration : public Declaration
{
public:
    FunctionDeclaration(std::string_view fct_name, Datatype* datatype, const Body& fct_body = Body{}) noexcept;
    
    void destroy() noexcept override;
    std::string to_string() const override;

private:
    Body body;
}; 