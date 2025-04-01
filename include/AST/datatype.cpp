#include "datatype.hpp"

// Implementación de los métodos de BasicDatatype
void BasicDatatype::destroy() noexcept {}

// Implementación de los métodos para tipos de datos específicos
std::string VoidDatatype::to_string() const { return "void"; }
std::string BooleanDatatype::to_string() const { return "boolean"; }
std::string CharacterDatatype::to_string() const { return "char"; }
std::string IntegerDatatype::to_string() const { return "integer"; }
std::string StringDatatype::to_string() const { return "string"; }
std::string NoteDatatype::to_string() const { return "note"; }
std::string TempoDatatype::to_string() const { return "tempo"; }
std::string KeyDatatype::to_string() const { return "key"; }
std::string TimeSignatureDatatype::to_string() const { return "time_signature"; }

// Implementación de los métodos de ArrayDatatype
ArrayDatatype::ArrayDatatype(Datatype* _inner_datatype) noexcept
    : inner_datatype{_inner_datatype} {}

void ArrayDatatype::destroy() noexcept
{
    this->inner_datatype->destroy();
    delete this->inner_datatype;
}

std::string ArrayDatatype::to_string() const
{
    return "array<" + this->inner_datatype->to_string() + ">";
}

// Implementación de los métodos de FunctionDatatype
FunctionDatatype::FunctionDatatype(Datatype* ret_type, const ParamList& params) noexcept
    : return_type{ret_type}, parameters{params} {}

void FunctionDatatype::destroy() noexcept
{
    this->return_type->destroy();
    delete this->return_type;

    while (!this->parameters.empty())
    {
        Param param = this->parameters.front();
        this->parameters.pop_front();
        param.second->destroy();
        delete param.second;
    }
}

std::string FunctionDatatype::to_string() const
{
    std::stringstream ss;
    ss << "function(";
    
    bool first = true;
    for (const auto& param : this->parameters)
    {
        if (!first)
            ss << ", ";
        first = false;
        ss << param.first << ": " << param.second->to_string();
    }
    
    ss << ") -> " << this->return_type->to_string();
    return ss.str();
} 