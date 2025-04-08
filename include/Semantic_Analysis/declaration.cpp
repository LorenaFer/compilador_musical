#include "declaration.hpp"
#include "datatype.hpp"
#include "expression.hpp"
#include "symbol_table.hpp"
#include "statement.hpp"

// Implementación de VariableDeclaration
VariableDeclaration::VariableDeclaration(
    const std::string& _name,
    Datatype* _type,
    Expression* _initializer
) noexcept
    : name(_name), type(_type), initializer(_initializer)
{
}

void VariableDeclaration::destroy() noexcept{
    if (type != nullptr)
    {
        type->destroy();
        delete type;
        type = nullptr;
    }

    if (initializer != nullptr)
    {
        initializer->destroy();
        delete initializer;
        initializer = nullptr;
    }
}

ASTNodeInterface* VariableDeclaration::copy() const noexcept{
    return new VariableDeclaration(
        name,
        dynamic_cast<Datatype*>(type->copy()),
        initializer ? dynamic_cast<Expression*>(initializer->copy()) : nullptr
    );
}

bool VariableDeclaration::equal(ASTNodeInterface* other) const noexcept{
    auto other_var = dynamic_cast<VariableDeclaration*>(other);
    if (other_var == nullptr){
        return false;
    }

    if (name != other_var->name || !type->equal(other_var->type)){
        return false;
    }

    if (initializer == nullptr && other_var->initializer == nullptr){
        return true;
    }

    if (initializer == nullptr || other_var->initializer == nullptr){
        return false;
    }

    return initializer->equal(other_var->initializer);
}

std::pair<bool, Datatype*> VariableDeclaration::type_check() const noexcept{
    if (initializer != nullptr){
        auto init_type = initializer->type_check();
        if (!init_type.first){
            if (init_type.second != nullptr){
                delete init_type.second;
                init_type.second = nullptr;
            }
            return std::make_pair(false, nullptr);
        }

        // Verificando que el tipo del inicializador sea compatible con el tipo declarado
        if (init_type.second != nullptr){
            bool type_match = init_type.second->equal(type);
            delete init_type.second;
            init_type.second = nullptr;

            if (!type_match){
                return std::make_pair(false, nullptr);
            }
        }
    }

    return std::make_pair(true, dynamic_cast<Datatype*>(type->copy()));
}

bool VariableDeclaration::resolve_name(SymbolTable& symbol_table) noexcept{
    if (!type->resolve_name(symbol_table)){
        return false;
    }

    if (initializer != nullptr && !initializer->resolve_name(symbol_table)){
        return false;
    }

    auto symbol = Symbol::build(type, name);
    return symbol_table.bind(name, symbol);
}

std::string VariableDeclaration::get_name() const noexcept
{
    return name;
}

Datatype* VariableDeclaration::get_type() const noexcept
{
    return type;
}

Expression* VariableDeclaration::get_initializer() const noexcept
{
    return initializer;
}

FunctionDeclaration::FunctionDeclaration(
    const std::string& _name,
    FunctionDatatype* _type,
    const Body& _body
) noexcept
    : name(_name), type(_type), body(_body)
{
}

void FunctionDeclaration::destroy() noexcept{
    if (type != nullptr)
    {
        type->destroy();
        delete type;
        type = nullptr;
    }

    destroy_body(body);
}

ASTNodeInterface* FunctionDeclaration::copy() const noexcept{
    return new FunctionDeclaration(
        name,
        dynamic_cast<FunctionDatatype*>(type->copy()),
        copy_body(body)
    );
}

bool FunctionDeclaration::equal(ASTNodeInterface* other) const noexcept{
    auto other_func = dynamic_cast<FunctionDeclaration*>(other);
    if (other_func == nullptr){
        return false;
    }

    return name == other_func->name &&
           type->equal(other_func->type) &&
           equal_body(body, other_func->body);
}

std::pair<bool, Datatype*> FunctionDeclaration::type_check() const noexcept{
    // Verificamos que el cuerpo de la función sea correcto
    auto body_result = body_type_check(body);
    if (!body_result.first){
        return std::make_pair(false, nullptr);
    }

    // Para funciones que retornan algo distinto de void, verificamos que tengan return
    auto return_type = type->get_return_type();
    if (!return_type->is<VoidDatatype>()){
        // Esta verificación es simplificada para este ejemplo
        // En una implementación completa, verificaríamos que todos los caminos de ejecución tengan return
        bool has_return = true;

        if (!has_return)
        {
            return std::make_pair(false, nullptr);
        }
    }

    return std::make_pair(true, dynamic_cast<Datatype*>(type->copy()));
}

bool FunctionDeclaration::resolve_name(SymbolTable& symbol_table) noexcept{
    static bool already_resolving = false;
    if (already_resolving) {
        return true;
    }
    
    already_resolving = true;

    if (!type->resolve_name(symbol_table)){
        already_resolving = false;
        return false;
    }

    auto symbol = Symbol::build(type, name);
    if (!symbol_table.bind(name, symbol)){
        already_resolving = false;
        return false;
    }

    symbol_table.enter_scope();

    if (!resolve_name_param_list(type->get_parameters(), symbol_table)){
        symbol_table.exit_scope();
        already_resolving = false;
        return false;
    }

    bool result = resolve_name_body(body, symbol_table);
    
    symbol_table.exit_scope();
    
    already_resolving = false;
    return result;
}

std::string FunctionDeclaration::get_name() const noexcept{
    return name;
}

Datatype* FunctionDeclaration::get_type() const noexcept{
    return type;
}

const Body& FunctionDeclaration::get_body() const noexcept{
    return body;
}

TempoDeclaration::TempoDeclaration(
    const std::string& _name,
    int _bpm
) noexcept
    : name(_name), bpm(_bpm)
{
}

void TempoDeclaration::destroy() noexcept
{

}

ASTNodeInterface* TempoDeclaration::copy() const noexcept
{
    return new TempoDeclaration(name, bpm);
}

bool TempoDeclaration::equal(ASTNodeInterface* other) const noexcept{
    auto other_tempo = dynamic_cast<TempoDeclaration*>(other);
    if (other_tempo == nullptr){
        return false;
    }

    return name == other_tempo->name && bpm == other_tempo->bpm;
}

std::pair<bool, Datatype*> TempoDeclaration::type_check() const noexcept{
    // Validar que el tempo sea positivo
    if (bpm <= 0){
        return std::make_pair(false, nullptr);
    }

    return std::make_pair(true, new TempoDatatype());
}

bool TempoDeclaration::resolve_name(SymbolTable& symbol_table) noexcept{
    auto symbol = Symbol::build(new TempoDatatype(), name);
    return symbol_table.bind(name, symbol);
}

std::string TempoDeclaration::get_name() const noexcept{
    return name;
}

Datatype* TempoDeclaration::get_type() const noexcept{
    return new TempoDatatype();
}

int TempoDeclaration::get_bpm() const noexcept{
    return bpm;
}

KeyDeclaration::KeyDeclaration(
    const std::string& _name,
    const std::string& _pitch,
    const std::string& _mode
) noexcept
    : name(_name), pitch(_pitch), mode(_mode)
{
}

void KeyDeclaration::destroy() noexcept
{
    
}

ASTNodeInterface* KeyDeclaration::copy() const noexcept
{
    return new KeyDeclaration(name, pitch, mode);
}

bool KeyDeclaration::equal(ASTNodeInterface* other) const noexcept{
    auto other_key = dynamic_cast<KeyDeclaration*>(other);
    if (other_key == nullptr)
    {
        return false;
    }

    return name == other_key->name && 
           pitch == other_key->pitch && 
           mode == other_key->mode;
}

std::pair<bool, Datatype*> KeyDeclaration::type_check() const noexcept
{
    // Verificar que pitch (Do, Re, etc.) y mode(M, m) sean válidos
    return std::make_pair(true, new KeyDatatype());
}

bool KeyDeclaration::resolve_name(SymbolTable& symbol_table) noexcept
{
    auto symbol = Symbol::build(new KeyDatatype(), name);
    return symbol_table.bind(name, symbol);
}

std::string KeyDeclaration::get_name() const noexcept
{
    return name;
}

Datatype* KeyDeclaration::get_type() const noexcept
{
    return new KeyDatatype();
}

const std::string& KeyDeclaration::get_pitch() const noexcept
{
    return pitch;
}

const std::string& KeyDeclaration::get_mode() const noexcept
{
    return mode;
}

TimeSignatureDeclaration::TimeSignatureDeclaration(
    const std::string& _name,
    int _numerator,
    int _denominator
) noexcept
    : name(_name), numerator(_numerator), denominator(_denominator)
{
}

void TimeSignatureDeclaration::destroy() noexcept
{

}

ASTNodeInterface* TimeSignatureDeclaration::copy() const noexcept
{
    return new TimeSignatureDeclaration(name, numerator, denominator);
}

bool TimeSignatureDeclaration::equal(ASTNodeInterface* other) const noexcept{
    auto other_time = dynamic_cast<TimeSignatureDeclaration*>(other);
    if (other_time == nullptr)
    {
        return false;
    }

    return name == other_time->name && 
           numerator == other_time->numerator && 
           denominator == other_time->denominator;
}

std::pair<bool, Datatype*> TimeSignatureDeclaration::type_check() const noexcept{
    // Validar que el compás tenga valores positivos
    if (numerator <= 0 || denominator <= 0)
    {
        return std::make_pair(false, nullptr);
    }

    return std::make_pair(true, new TimeSignatureDatatype());
}

bool TimeSignatureDeclaration::resolve_name(SymbolTable& symbol_table) noexcept
{
    auto symbol = Symbol::build(new TimeSignatureDatatype(), name);
    return symbol_table.bind(name, symbol);
}

std::string TimeSignatureDeclaration::get_name() const noexcept
{
    return name;
}

Datatype* TimeSignatureDeclaration::get_type() const noexcept
{
    return new TimeSignatureDatatype();
}

int TimeSignatureDeclaration::get_numerator() const noexcept
{
    return numerator;
}

int TimeSignatureDeclaration::get_denominator() const noexcept
{
    return denominator;
}

NoteDeclaration::NoteDeclaration(
    const std::string& _name,
    char _pitch,
    int _octave,
    const std::string& _duration
) noexcept
    : name(_name), pitch(_pitch), octave(_octave), duration(_duration)
{
}

void NoteDeclaration::destroy() noexcept
{

}

ASTNodeInterface* NoteDeclaration::copy() const noexcept
{
    return new NoteDeclaration(name, pitch, octave, duration);
}

bool NoteDeclaration::equal(ASTNodeInterface* other) const noexcept{
    auto other_note = dynamic_cast<NoteDeclaration*>(other);
    if (other_note == nullptr)
    {
        return false;
    }

    return name == other_note->name && 
           pitch == other_note->pitch && 
           octave == other_note->octave &&
           duration == other_note->duration;
}

std::pair<bool, Datatype*> NoteDeclaration::type_check() const noexcept{
 // Verificar que el pitch esté entre A-G, la octava en un rango válido (0-8)
    // y la duración sea una de las permitidas
    if (pitch < 'A' || pitch > 'G' || octave < 0 || octave > 8)
    {
        return std::make_pair(false, nullptr);
    }

    // Verificar duración válida
    if (duration != "Blanca" && duration != "Negra" && 
        duration != "Corchea" && duration != "Semicorchea")
    {
        return std::make_pair(false, nullptr);
    }

    return std::make_pair(true, new NoteDatatype());
}

bool NoteDeclaration::resolve_name(SymbolTable& symbol_table) noexcept
{
    auto symbol = Symbol::build(new NoteDatatype(), name);
    return symbol_table.bind(name, symbol);
}

std::string NoteDeclaration::get_name() const noexcept
{
    return name;
}

Datatype* NoteDeclaration::get_type() const noexcept
{
    return new NoteDatatype();
}

char NoteDeclaration::get_pitch() const noexcept
{
    return pitch;
}

int NoteDeclaration::get_octave() const noexcept
{
    return octave;
}

const std::string& NoteDeclaration::get_duration() const noexcept
{
    return duration;
} 