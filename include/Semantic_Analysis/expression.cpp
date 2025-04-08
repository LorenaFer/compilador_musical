#include "expression.hpp"
#include "datatype.hpp"
#include "symbol_table.hpp"

// Implementación de BoolExpression
BoolExpression::BoolExpression(bool _value) noexcept
    : value(_value)
{
}

void BoolExpression::destroy() noexcept
{
    
}

ASTNodeInterface* BoolExpression::copy() const noexcept
{
    return new BoolExpression(value);
}

bool BoolExpression::equal(ASTNodeInterface* other) const noexcept{
    auto other_bool = dynamic_cast<BoolExpression*>(other);
    if (other_bool == nullptr)
    {
        return false;
    }

    return value == other_bool->value;
}

std::pair<bool, Datatype*> BoolExpression::type_check() const noexcept
{
    return std::make_pair(true, new BooleanDatatype());
}

bool BoolExpression::resolve_name(SymbolTable& symbol_table) noexcept
{
    return true; 
}

bool BoolExpression::get_value() const noexcept
{
    return value;
}

IntExpression::IntExpression(int _value) noexcept
    : value(_value)
{
}

void IntExpression::destroy() noexcept
{
   
}

ASTNodeInterface* IntExpression::copy() const noexcept
{
    return new IntExpression(value);
}

bool IntExpression::equal(ASTNodeInterface* other) const noexcept
{
    auto other_int = dynamic_cast<IntExpression*>(other);
    if (other_int == nullptr)
    {
        return false;
    }

    return value == other_int->value;
}

std::pair<bool, Datatype*> IntExpression::type_check() const noexcept
{
    return std::make_pair(true, new IntegerDatatype());
}

bool IntExpression::resolve_name(SymbolTable& symbol_table) noexcept
{
    return true; 
}

int IntExpression::get_value() const noexcept
{
    return value;
}

StrExpression::StrExpression(const std::string& _value) noexcept
    : value(_value)
{
}

void StrExpression::destroy() noexcept
{

}

ASTNodeInterface* StrExpression::copy() const noexcept
{
    return new StrExpression(value);
}

bool StrExpression::equal(ASTNodeInterface* other) const noexcept
{
    auto other_str = dynamic_cast<StrExpression*>(other);
    if (other_str == nullptr)
    {
        return false;
    }

    return value == other_str->value;
}

std::pair<bool, Datatype*> StrExpression::type_check() const noexcept
{
    return std::make_pair(true, new StringDatatype());
}

bool StrExpression::resolve_name(SymbolTable& symbol_table) noexcept
{
    return true; 
}

const std::string& StrExpression::get_value() const noexcept
{
    return value;
}

// Implementación de expresiones musicales específicas
NoteExpression::NoteExpression(const std::string& _pitch, int _octave, int _duration) noexcept
    : pitch(_pitch), octave(_octave), duration(_duration)
{
}

void NoteExpression::destroy() noexcept
{

}

ASTNodeInterface* NoteExpression::copy() const noexcept
{
    return new NoteExpression(pitch, octave, duration);
}

bool NoteExpression::equal(ASTNodeInterface* other) const noexcept
{
    auto other_note = dynamic_cast<NoteExpression*>(other);
    if (other_note == nullptr)
    {
        return false;
    }

    return pitch == other_note->pitch && 
           octave == other_note->octave && 
           duration == other_note->duration;
}

std::pair<bool, Datatype*> NoteExpression::type_check() const noexcept
{
    // Validación básica de pitch: debe ser una nota válida (C, D, E, F, G, A, B, posiblemente con # o b)
    std::string valid_pitches = "CDEFGAB";
    if (pitch.empty() || valid_pitches.find(pitch[0]) == std::string::npos){
        return std::make_pair(false, nullptr);
    }

    // Validación de alteraciones (si existen)
    if (pitch.length() > 1){
        char alt = pitch[1];
        if (alt != '#' && alt != 'b')
        {
            return std::make_pair(false, nullptr);
        }
    }

    // Validación de octava: entre 0 y 8
    if (octave < 0 || octave > 8){
        return std::make_pair(false, nullptr);
    }

    // Validación de duración: debe ser positiva
    if (duration <= 0){
        return std::make_pair(false, nullptr);
    }

    return std::make_pair(true, new NoteDatatype());
}

bool NoteExpression::resolve_name(SymbolTable& symbol_table) noexcept
{
    return true; 
}

const std::string& NoteExpression::get_pitch() const noexcept
{
    return pitch;
}

int NoteExpression::get_octave() const noexcept
{
    return octave;
}

int NoteExpression::get_duration() const noexcept
{
    return duration;
}

KeyExpression::KeyExpression(const std::string& _key) noexcept
    : key(_key)
{
}

void KeyExpression::destroy() noexcept
{
    
}

ASTNodeInterface* KeyExpression::copy() const noexcept
{
    return new KeyExpression(key);
}

bool KeyExpression::equal(ASTNodeInterface* other) const noexcept
{
    auto other_key = dynamic_cast<KeyExpression*>(other);
    if (other_key == nullptr){
        return false;
    }

    return key == other_key->key;
}

std::pair<bool, Datatype*> KeyExpression::type_check() const noexcept
{
    // Validación básica de tonalidad
    std::string valid_roots = "CDEFGAB";
    
    if (key.empty() || valid_roots.find(key[0]) == std::string::npos){
        return std::make_pair(false, nullptr);
    }

    // Si hay más caracteres, validar el segundo (puede ser #, b, m para menor)
    if (key.length() > 1){
        char modifier = key[1];
        if (modifier != '#' && modifier != 'b' && modifier != 'm')
        {
            return std::make_pair(false, nullptr);
        }
    }

    return std::make_pair(true, new KeyDatatype());
}

bool KeyExpression::resolve_name(SymbolTable& symbol_table) noexcept
{
    return true; 
}

const std::string& KeyExpression::get_key() const noexcept
{
    return key;
}

TempoExpression::TempoExpression(int _bpm) noexcept
    : bpm(_bpm)
{
}

void TempoExpression::destroy() noexcept
{
   
}

ASTNodeInterface* TempoExpression::copy() const noexcept
{
    return new TempoExpression(bpm);
}

bool TempoExpression::equal(ASTNodeInterface* other) const noexcept
{
    auto other_tempo = dynamic_cast<TempoExpression*>(other);
    if (other_tempo == nullptr){
        return false;
    }

    return bpm == other_tempo->bpm;
}

std::pair<bool, Datatype*> TempoExpression::type_check() const noexcept
{
    // Validación de tempo: entre 20 y 400 BPM
    if (bpm < 20 || bpm > 400){
        return std::make_pair(false, nullptr);
    }

    return std::make_pair(true, new TempoDatatype());
}

bool TempoExpression::resolve_name(SymbolTable& symbol_table) noexcept
{
    return true; 
}

int TempoExpression::get_bpm() const noexcept
{
    return bpm;
}

TimeSignatureExpression::TimeSignatureExpression(int _numerator, int _denominator) noexcept
    : numerator(_numerator), denominator(_denominator)
{
}

void TimeSignatureExpression::destroy() noexcept
{

}

ASTNodeInterface* TimeSignatureExpression::copy() const noexcept
{
    return new TimeSignatureExpression(numerator, denominator);
}

bool TimeSignatureExpression::equal(ASTNodeInterface* other) const noexcept
{
    auto other_ts = dynamic_cast<TimeSignatureExpression*>(other);
    if (other_ts == nullptr){
        return false;
    }

    return numerator == other_ts->numerator && denominator == other_ts->denominator;
}

std::pair<bool, Datatype*> TimeSignatureExpression::type_check() const noexcept
{
    // Validación básica de compás
    // Numerador: entre 1 y 16
    if (numerator < 1 || numerator > 16){
        return std::make_pair(false, nullptr);
    }

    // Denominador: típicamente potencias de 2 (2, 4, 8, 16, etc.)
    if (denominator != 2 && denominator != 4 && denominator != 8 && denominator != 16){
        return std::make_pair(false, nullptr);
    }

    return std::make_pair(true, new TimeSignatureDatatype());
}

bool TimeSignatureExpression::resolve_name(SymbolTable& symbol_table) noexcept
{
    return true; 
}

int TimeSignatureExpression::get_numerator() const noexcept
{
    return numerator;
}

int TimeSignatureExpression::get_denominator() const noexcept
{
    return denominator;
}

NameExpression::NameExpression(const std::string& _name) noexcept
    : name(_name)
{
}

void NameExpression::destroy() noexcept
{

}

ASTNodeInterface* NameExpression::copy() const noexcept
{
    return new NameExpression(name);
}

bool NameExpression::equal(ASTNodeInterface* other) const noexcept
{
    auto other_name = dynamic_cast<NameExpression*>(other);
    if (other_name == nullptr){
        return false;
    }

    return name == other_name->name;
}

std::pair<bool, Datatype*> NameExpression::type_check() const noexcept
{
    // La comprobación de tipos para un nombre depende del símbolo al que se refiere
    return std::make_pair(true, nullptr);
}

bool NameExpression::resolve_name(SymbolTable& symbol_table) noexcept
{
    auto symbol = symbol_table.lookup(name);
    return symbol != nullptr;
}

const std::string& NameExpression::get_name() const noexcept
{
    return name;
}

ArrayAccessExpression::ArrayAccessExpression(Expression* _array, Expression* _index) noexcept
    : array(_array), index(_index)
{
}

void ArrayAccessExpression::destroy() noexcept
{
    if (array != nullptr){
        array->destroy();
        delete array;
        array = nullptr;
    }

    if (index != nullptr){
        index->destroy();
        delete index;
        index = nullptr;
    }
}

ASTNodeInterface* ArrayAccessExpression::copy() const noexcept
{
    return new ArrayAccessExpression(
        dynamic_cast<Expression*>(array->copy()),
        dynamic_cast<Expression*>(index->copy())
    );
}

bool ArrayAccessExpression::equal(ASTNodeInterface* other) const noexcept
{
    auto other_array_access = dynamic_cast<ArrayAccessExpression*>(other);
    if (other_array_access == nullptr){
        return false;
    }

    return array->equal(other_array_access->array) &&
           index->equal(other_array_access->index);
}

std::pair<bool, Datatype*> ArrayAccessExpression::type_check() const noexcept
{
    // Verificar que array sea de tipo array
    auto array_type = array->type_check();
    if (!array_type.first || array_type.second == nullptr){
        return std::make_pair(false, nullptr);
    }

    auto* array_datatype = dynamic_cast<ArrayDatatype*>(array_type.second);
    if (array_datatype == nullptr){
        delete array_type.second;
        return std::make_pair(false, nullptr);
    }

    // Verificar que el índice sea de tipo entero
    auto index_type = index->type_check();
    if (!index_type.first || index_type.second == nullptr){
        delete array_type.second;
        return std::make_pair(false, nullptr);
    }

    bool is_int = index_type.second->is<IntegerDatatype>();
    delete index_type.second;

    if (!is_int){
        delete array_type.second;
        return std::make_pair(false, nullptr);
    }

    // El tipo del resultado es el tipo interno del array
    return std::make_pair(true, dynamic_cast<Datatype*>(array_datatype->get_inner_datatype()->copy()));
}

bool ArrayAccessExpression::resolve_name(SymbolTable& symbol_table) noexcept
{
    return array->resolve_name(symbol_table) && index->resolve_name(symbol_table);
}

Expression* ArrayAccessExpression::get_array() const noexcept
{
    return array;
}

Expression* ArrayAccessExpression::get_index() const noexcept
{
    return index;
}

AssignmentExpression::AssignmentExpression(Expression* _target, Expression* _value) noexcept
    : target(_target), value(_value)
{
}

void AssignmentExpression::destroy() noexcept
{
    if (target != nullptr){
        target->destroy();
        delete target;
        target = nullptr;
    }

    if (value != nullptr){
        value->destroy();
        delete value;
        value = nullptr;
    }
}

ASTNodeInterface* AssignmentExpression::copy() const noexcept
{
    return new AssignmentExpression(
        dynamic_cast<Expression*>(target->copy()),
        dynamic_cast<Expression*>(value->copy())
    );
}

bool AssignmentExpression::equal(ASTNodeInterface* other) const noexcept
{
    auto other_assign = dynamic_cast<AssignmentExpression*>(other);
    if (other_assign == nullptr){
        return false;
    }

    return target->equal(other_assign->target) && value->equal(other_assign->value);
}

std::pair<bool, Datatype*> AssignmentExpression::type_check() const noexcept
{
    auto target_type = target->type_check();
    if (!target_type.first){
        if (target_type.second != nullptr)
        {
            delete target_type.second;
            target_type.second = nullptr;
        }
        return std::make_pair(false, nullptr);
    }

    auto value_type = value->type_check();
    if (!value_type.first){
        if (target_type.second != nullptr)
        {
            delete target_type.second;
            target_type.second = nullptr;
        }
        if (value_type.second != nullptr)
        {
            delete value_type.second;
            value_type.second = nullptr;
        }
        return std::make_pair(false, nullptr);
    }

    // Verificar que los tipos sean compatibles
    bool compatible = false;
    if (target_type.second != nullptr && value_type.second != nullptr){
        compatible = target_type.second->equal(value_type.second);
    }

    if (target_type.second != nullptr){
        delete target_type.second;
        target_type.second = nullptr;
    }

    if (!compatible){
        if (value_type.second != nullptr)
        {
            delete value_type.second;
            value_type.second = nullptr;
        }
        return std::make_pair(false, nullptr);
    }

    return std::make_pair(true, value_type.second);
}

bool AssignmentExpression::resolve_name(SymbolTable& symbol_table) noexcept
{
    return target->resolve_name(symbol_table) && value->resolve_name(symbol_table);
}

Expression* AssignmentExpression::get_target() const noexcept
{
    return target;
}

Expression* AssignmentExpression::get_value() const noexcept
{
    return value;
}

// Implementación de expresiones unarias
UnaryExpression::UnaryExpression(Expression* _operand) noexcept
    : operand(_operand)
{
}

void UnaryExpression::destroy() noexcept
{
    if (operand != nullptr){
        operand->destroy();
        delete operand;
        operand = nullptr;
    }
}

CallExpression::CallExpression(Expression* _function, Expression* _arguments) noexcept
    : function(_function), arguments(_arguments)
{
}

void CallExpression::destroy() noexcept
{
    if (function != nullptr){
        function->destroy();
        delete function;
        function = nullptr;
    }

    if (arguments != nullptr){
        arguments->destroy();
        delete arguments;
        arguments = nullptr;
    }
}

ASTNodeInterface* CallExpression::copy() const noexcept
{
    return new CallExpression(
        dynamic_cast<Expression*>(function->copy()),
        arguments ? dynamic_cast<Expression*>(arguments->copy()) : nullptr
    );
}

bool CallExpression::equal(ASTNodeInterface* other) const noexcept{
    auto other_call = dynamic_cast<CallExpression*>(other);
    if (other_call == nullptr){
        return false;
    }

    if (!function->equal(other_call->function)){
        return false;
    }

    if ((arguments == nullptr) != (other_call->arguments == nullptr)){
        return false;
    }

    if (arguments == nullptr){
        return true;
    }

    return arguments->equal(other_call->arguments);
}

std::pair<bool, Datatype*> CallExpression::type_check() const noexcept{
    // Verificar que function sea una función
    auto func_type = function->type_check();
    if (!func_type.first || func_type.second == nullptr){
        return std::make_pair(false, nullptr);
    }
    
    // Comprobar que el tipo obtenido sea un FunctionDatatype
    auto* function_type = dynamic_cast<FunctionDatatype*>(func_type.second);
    if (function_type == nullptr){
        delete func_type.second;
        return std::make_pair(false, nullptr);
    }
    
    // Verificar los argumentos
    const ParamList& params = function_type->get_parameters();
    Expression* current_arg = arguments;
    bool args_valid = true;
    
    // Verificar que el número y tipos de argumentos coincidan con los parámetros
    for (const auto& param : params){
        // Si no hay más argumentos pero quedan parámetros
        if (current_arg == nullptr){
            args_valid = false;
            break;
        }
        
        // Obtener el argumento actual
        ArgExpression* arg_expr = dynamic_cast<ArgExpression*>(current_arg);
        if (arg_expr == nullptr){
            args_valid = false;
            break;
        }
        
        // Verificar que el tipo del argumento sea compatible con el tipo del parámetro
        auto arg_type = arg_expr->get_value()->type_check();
        if (!arg_type.first || arg_type.second == nullptr){
            args_valid = false;
            break;
        }
        
        bool compatible = arg_type.second->equal(param.second);
        delete arg_type.second;
        
        if (!compatible){
            args_valid = false;
            break;
        }
        
        // Avanzar al siguiente argumento
        current_arg = arg_expr->get_next();
    }
    
    // Verificar que no sobren argumentos
    if (current_arg != nullptr){
        args_valid = false;
    }
    
    if (!args_valid){
        delete func_type.second;
        return std::make_pair(false, nullptr);
    }
    
    // retornar el tipo return de la función
    return std::make_pair(true, dynamic_cast<Datatype*>(function_type->get_return_type()->copy()));
}

bool CallExpression::resolve_name(SymbolTable& symbol_table) noexcept{
    if (!function->resolve_name(symbol_table)){
        return false;
    }

    if (arguments != nullptr && !arguments->resolve_name(symbol_table)){
        return false;
    }

    return true;
}

Expression* CallExpression::get_function() const noexcept
{
    return function;
}

Expression* CallExpression::get_arguments() const noexcept
{
    return arguments;
}

ArgExpression::ArgExpression(Expression* _value, Expression* _next) noexcept
    : value(_value), next(_next)
{
}

void ArgExpression::destroy() noexcept{
    if (value != nullptr){
        value->destroy();
        delete value;
        value = nullptr;
    }

    if (next != nullptr){
        next->destroy();
        delete next;
        next = nullptr;
    }
}

ASTNodeInterface* ArgExpression::copy() const noexcept{
    return new ArgExpression(
        dynamic_cast<Expression*>(value->copy()),
        next ? dynamic_cast<Expression*>(next->copy()) : nullptr
    );
}

bool ArgExpression::equal(ASTNodeInterface* other) const noexcept{
    auto other_arg = dynamic_cast<ArgExpression*>(other);
    if (other_arg == nullptr){
        return false;
    }

    if (!value->equal(other_arg->value)){
        return false;
    }

    if ((next == nullptr) != (other_arg->next == nullptr)){
        return false;
    }

    if (next == nullptr){
        return true;
    }

    return next->equal(other_arg->next);
}

std::pair<bool, Datatype*> ArgExpression::type_check() const noexcept
{
    auto value_type = value->type_check();
    if (!value_type.first){
        return std::make_pair(false, nullptr);
    }

    if (next != nullptr){
        auto next_type = next->type_check();
        if (!next_type.first)
        {
            if (value_type.second != nullptr)
            {
                delete value_type.second;
            }
            return std::make_pair(false, nullptr);
        }
    }

    return value_type;
}

bool ArgExpression::resolve_name(SymbolTable& symbol_table) noexcept{
    if (!value->resolve_name(symbol_table)){
        return false;
    }

    if (next != nullptr && !next->resolve_name(symbol_table)){
        return false;
    }

    return true;
}

Expression* ArgExpression::get_value() const noexcept{
    return value;
}

Expression* ArgExpression::get_next() const noexcept{
    return next;
}

// implementacion operador sostenido
ASTNodeInterface* SharpExpression::copy() const noexcept{
    return new SharpExpression(dynamic_cast<Expression*>(operand->copy()));
}

bool SharpExpression::equal(ASTNodeInterface* other) const noexcept{
    auto other_sharp = dynamic_cast<SharpExpression*>(other);
    if (other_sharp == nullptr){
        return false;
    }

    return operand->equal(other_sharp->operand);
}

std::pair<bool, Datatype*> SharpExpression::type_check() const noexcept{
    auto operand_type = operand->type_check();
    if (!operand_type.first){
        return std::make_pair(false, nullptr);
    }

    // Verificar que el operando sea una nota musical
    if (operand_type.second && !operand_type.second->is<NoteDatatype>()){
        delete operand_type.second;
        return std::make_pair(false, nullptr);
    }

    return operand_type;
}

bool SharpExpression::resolve_name(SymbolTable& symbol_table) noexcept
{
    return operand->resolve_name(symbol_table);
}

