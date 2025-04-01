#pragma once

#include "ast_node_interface.hpp"

// Clase base para todos los tipos de datos
class Datatype : public ASTNodeInterface
{
public:
    virtual std::string to_string() const override = 0;
};

// Clase para tipos de datos básicos
class BasicDatatype : public Datatype
{
public:
    void destroy() noexcept override;
};

// Tipo de dato para representar un valor nulo/vacío
class VoidDatatype : public BasicDatatype
{
public:
    std::string to_string() const override;
};

// Tipo de dato para representar valores booleanos
class BooleanDatatype : public BasicDatatype
{
public:
    std::string to_string() const override;
};

// Tipo de dato para representar caracteres
class CharacterDatatype : public BasicDatatype
{
public:
    std::string to_string() const override;
};

// Tipo de dato para representar enteros (duraciones, octavas, etc.)
class IntegerDatatype : public BasicDatatype
{
public:
    std::string to_string() const override;
};

// Tipo de dato para representar cadenas (nombres, etiquetas, etc.)
class StringDatatype : public BasicDatatype
{
public:
    std::string to_string() const override;
};

// Tipo de dato específico para notas musicales
class NoteDatatype : public BasicDatatype
{
public:
    std::string to_string() const override;
};

// Tipo de dato para indicaciones de tempo
class TempoDatatype : public BasicDatatype
{
public:
    std::string to_string() const override;
};

// Tipo de dato para tonalidades musicales
class KeyDatatype : public BasicDatatype
{
public:
    std::string to_string() const override;
};

// Tipo de dato para compases
class TimeSignatureDatatype : public BasicDatatype
{
public:
    std::string to_string() const override;
};

// Tipo de dato para arreglos (secuencias de notas, acordes, etc.)
class ArrayDatatype : public BasicDatatype
{
public:
    ArrayDatatype(Datatype* _inner_datatype) noexcept;
    
    void destroy() noexcept override;
    std::string to_string() const override;

private:
    Datatype* inner_datatype;
};

// Tipo de dato para funciones (secciones musicales, comportamientos, etc.)
class FunctionDatatype : public Datatype
{
public:
    FunctionDatatype(Datatype* ret_type, const ParamList& params) noexcept;
    
    void destroy() noexcept override;
    std::string to_string() const override;

private:
    Datatype* return_type;
    ParamList parameters;
}; 