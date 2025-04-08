#include "datatype.hpp"
#include "symbol_table.hpp"

std::pair<bool, Datatype*> Datatype::type_check() const noexcept{
    return std::make_pair(true, nullptr);
}

void BasicDatatype::destroy() noexcept{
    
}

bool BasicDatatype::resolve_name(SymbolTable& symbol_table) noexcept{
    return true; // Los tipos básicos no tienen nombres que resolver
}

ASTNodeInterface* VoidDatatype::copy() const noexcept{
    return new VoidDatatype();
}

bool VoidDatatype::equal(ASTNodeInterface* other) const noexcept{
    return dynamic_cast<VoidDatatype*>(other) != nullptr;
}

ASTNodeInterface* BooleanDatatype::copy() const noexcept{
    return new BooleanDatatype();
}

bool BooleanDatatype::equal(ASTNodeInterface* other) const noexcept{
    return dynamic_cast<BooleanDatatype*>(other) != nullptr;
}

ASTNodeInterface* CharacterDatatype::copy() const noexcept{
    return new CharacterDatatype();
}

bool CharacterDatatype::equal(ASTNodeInterface* other) const noexcept{
    return dynamic_cast<CharacterDatatype*>(other) != nullptr;
}

ASTNodeInterface* IntegerDatatype::copy() const noexcept{
    return new IntegerDatatype();
}

bool IntegerDatatype::equal(ASTNodeInterface* other) const noexcept{
    return dynamic_cast<IntegerDatatype*>(other) != nullptr;
}

ASTNodeInterface* StringDatatype::copy() const noexcept{
    return new StringDatatype();
}

bool StringDatatype::equal(ASTNodeInterface* other) const noexcept{
    return dynamic_cast<StringDatatype*>(other) != nullptr;
}

// Implementación de tipos musicales
ASTNodeInterface* NoteDatatype::copy() const noexcept{
    return new NoteDatatype();
}

bool NoteDatatype::equal(ASTNodeInterface* other) const noexcept{
    return dynamic_cast<NoteDatatype*>(other) != nullptr;
}

ASTNodeInterface* TempoDatatype::copy() const noexcept{
    return new TempoDatatype();
}

bool TempoDatatype::equal(ASTNodeInterface* other) const noexcept{
    return dynamic_cast<TempoDatatype*>(other) != nullptr;
}

ASTNodeInterface* KeyDatatype::copy() const noexcept{
    return new KeyDatatype();
}

bool KeyDatatype::equal(ASTNodeInterface* other) const noexcept{
    return dynamic_cast<KeyDatatype*>(other) != nullptr;
}

ASTNodeInterface* TimeSignatureDatatype::copy() const noexcept{
    return new TimeSignatureDatatype();
}

bool TimeSignatureDatatype::equal(ASTNodeInterface* other) const noexcept{
    return dynamic_cast<TimeSignatureDatatype*>(other) != nullptr;
}

ArrayDatatype::ArrayDatatype(Datatype* _inner_datatype) noexcept
    : inner_datatype(_inner_datatype)
{
}

void ArrayDatatype::destroy() noexcept{
    if (inner_datatype != nullptr)
    {
        inner_datatype->destroy();
        delete inner_datatype;
        inner_datatype = nullptr;
    }
}

ASTNodeInterface* ArrayDatatype::copy() const noexcept{
    return new ArrayDatatype(dynamic_cast<Datatype*>(inner_datatype->copy()));
}

bool ArrayDatatype::equal(ASTNodeInterface* other) const noexcept{
    auto other_array = dynamic_cast<ArrayDatatype*>(other);
    if (other_array == nullptr)
    {
        return false;
    }
    
    return inner_datatype->equal(other_array->inner_datatype);
}

bool ArrayDatatype::resolve_name(SymbolTable& symbol_table) noexcept{
    return inner_datatype->resolve_name(symbol_table);
}

Datatype* ArrayDatatype::get_inner_datatype() const noexcept{
    return inner_datatype;
}

FunctionDatatype::FunctionDatatype(Datatype* ret_type, const ParamList& params) noexcept
    : return_type(ret_type), parameters(params){
}

void FunctionDatatype::destroy() noexcept
{
    if (return_type != nullptr)
    {
        return_type->destroy();
        delete return_type;
        return_type = nullptr;
    }
    
    destroy_param_list(parameters);
}

ASTNodeInterface* FunctionDatatype::copy() const noexcept{
    return new FunctionDatatype(
        dynamic_cast<Datatype*>(return_type->copy()),
        copy_param_list(parameters)
    );
}

bool FunctionDatatype::equal(ASTNodeInterface* other) const noexcept{
    auto other_function = dynamic_cast<FunctionDatatype*>(other);
    if (other_function == nullptr)
    {
        return false;
    }
    
    return return_type->equal(other_function->return_type) &&
           equal_param_list(parameters, other_function->parameters);
}

bool FunctionDatatype::resolve_name(SymbolTable& symbol_table) noexcept{
    if (!return_type->resolve_name(symbol_table))
    {
        return false;
    }
    //procesamiento de los parametros en funcion ->resolve_name_param_list -> ast_node_interface.cpp
    return true;
}

Datatype* FunctionDatatype::get_return_type() const noexcept{
    return return_type;
}

const ParamList& FunctionDatatype::get_parameters() const noexcept{
    return parameters;
} 