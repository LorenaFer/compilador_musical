#pragma once

#include "ast_node_interface.hpp"
#include "datatype.hpp"

class Declaration : public ASTNodeInterface
{
public:
    virtual std::string get_name() const noexcept = 0;
    
    virtual Datatype* get_type() const noexcept = 0;
};

class VariableDeclaration : public Declaration
{
public:
    VariableDeclaration(
        const std::string& name,
        Datatype* type,
        Expression* initializer = nullptr
    ) noexcept;

    void destroy() noexcept override;

    ASTNodeInterface* copy() const noexcept override;

    bool equal(ASTNodeInterface* other) const noexcept override;

    std::pair<bool, Datatype*> type_check() const noexcept override;

    bool resolve_name(SymbolTable& symbol_table) noexcept override;
    
    std::string get_name() const noexcept override;
    
    Datatype* get_type() const noexcept override;
    
    Expression* get_initializer() const noexcept;

private:
    std::string name;
    Datatype* type;
    Expression* initializer;
};

// Declaraciones específicas para música
class TempoDeclaration : public Declaration
{
public:
    TempoDeclaration(
        const std::string& name,
        int bpm
    ) noexcept;

    void destroy() noexcept override;

    ASTNodeInterface* copy() const noexcept override;

    bool equal(ASTNodeInterface* other) const noexcept override;

    std::pair<bool, Datatype*> type_check() const noexcept override;

    bool resolve_name(SymbolTable& symbol_table) noexcept override;
    
    std::string get_name() const noexcept override;
    
    Datatype* get_type() const noexcept override;
    
    int get_bpm() const noexcept;

private:
    std::string name;
    int bpm;
};

class KeyDeclaration : public Declaration
{
public:
    KeyDeclaration(
        const std::string& name,
        const std::string& pitch,
        const std::string& mode
    ) noexcept;

    void destroy() noexcept override;

    ASTNodeInterface* copy() const noexcept override;

    bool equal(ASTNodeInterface* other) const noexcept override;

    std::pair<bool, Datatype*> type_check() const noexcept override;

    bool resolve_name(SymbolTable& symbol_table) noexcept override;
    
    std::string get_name() const noexcept override;
    
    Datatype* get_type() const noexcept override;
    
    const std::string& get_pitch() const noexcept;
    const std::string& get_mode() const noexcept;

private:
    std::string name;
    std::string pitch;  // Nota base (Do, Re, etc.)
    std::string mode;   // Modo (M, m)
};

class TimeSignatureDeclaration : public Declaration
{
public:
    TimeSignatureDeclaration(
        const std::string& name,
        int numerator,
        int denominator
    ) noexcept;

    void destroy() noexcept override;

    ASTNodeInterface* copy() const noexcept override;

    bool equal(ASTNodeInterface* other) const noexcept override;

    std::pair<bool, Datatype*> type_check() const noexcept override;

    bool resolve_name(SymbolTable& symbol_table) noexcept override;
    
    std::string get_name() const noexcept override;
    
    Datatype* get_type() const noexcept override;
    
    int get_numerator() const noexcept;
    int get_denominator() const noexcept;

private:
    std::string name;
    int numerator;
    int denominator;
};

class NoteDeclaration : public Declaration
{
public:
    NoteDeclaration(
        const std::string& name,
        char pitch,
        int octave,
        const std::string& duration
    ) noexcept;

    void destroy() noexcept override;

    ASTNodeInterface* copy() const noexcept override;

    bool equal(ASTNodeInterface* other) const noexcept override;

    std::pair<bool, Datatype*> type_check() const noexcept override;

    bool resolve_name(SymbolTable& symbol_table) noexcept override;
    
    std::string get_name() const noexcept override;
    
    Datatype* get_type() const noexcept override;
    
    char get_pitch() const noexcept;
    int get_octave() const noexcept;
    const std::string& get_duration() const noexcept;

private:
    std::string name;
    char pitch;          // C, D, E, F, G, A, B
    int octave;          // 0-8
    std::string duration; // Blanca, Negra, Corchea, Semicorchea
};

class FunctionDeclaration : public Declaration
{
public:
    FunctionDeclaration(
        const std::string& name,
        FunctionDatatype* type,
        const Body& body
    ) noexcept;

    void destroy() noexcept override;

    ASTNodeInterface* copy() const noexcept override;

    bool equal(ASTNodeInterface* other) const noexcept override;

    std::pair<bool, Datatype*> type_check() const noexcept override;

    bool resolve_name(SymbolTable& symbol_table) noexcept override;
    
    std::string get_name() const noexcept override;
    
    Datatype* get_type() const noexcept override;
    
    const Body& get_body() const noexcept;

private:
    std::string name;
    FunctionDatatype* type;
    Body body;
}; 