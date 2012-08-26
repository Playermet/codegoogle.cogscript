#include "vm_value.h"
#include "cog_constants.h"

using namespace Cog::VirtualMachine;

Value::Value()
	: Type(Type::Void)
{
	return;
}

Value::Value(const Value& v)
{
	*this = v;
}

const Value& Value::operator=(const Value& v)
{
	Type = v.Type;
	Data = v.Data;

	return v;
}

Value::Value(int v)
{
	*this = v;
}

int Value::operator=(int v)
{
	Type = Type::Integer;
	Data.Integer = v;

	return v;
}

Value::operator int() const
{
	switch(Type)
	{
	case Type::Void:
		return Constants::DefaultInt;

	case Type::Integer:
		return Data.Integer;

	case Type::Float:
		return static_cast<int>(Data.Floating);

	case Type::Boolean:
		return (Data.Boolean) ? 1 : 0;

	case Type::String:
		return Constants::DefaultInt;

	case Type::Vector:
		return Constants::DefaultInt;

	default:
		return Constants::DefaultInt;
	}
}

Value::Value(float v)
{
	*this = v;
}

float Value::operator=(float v)
{
	Type = Type::Float;
	Data.Floating = v;

	return v;
}

Value::operator float() const
{
	switch(Type)
	{
	case Type::Void:
		return Constants::DefaultFloat;

	case Type::Integer:
		return static_cast<float>(Data.Integer);

	case Type::Float:
		return Data.Floating;

	case Type::Boolean:
		return (Data.Boolean) ? 1.0f : 0.0f;

	case Type::String:
		return Constants::DefaultFloat;

	case Type::Vector:
		return Constants::DefaultFloat;

	default:
		return Constants::DefaultFloat;
	}
}

Value::Value(bool v)
{
	*this = v;
}

bool Value::operator=(bool v)
{
	Type = Type::Boolean;
	Data.Boolean = v;

	return v;
}

Value::operator bool() const
{
	switch(Type)
	{
	case Type::Void:
		return false;

	case Type::Integer:
		return Data.Integer != 0;

	case Type::Float:
		return Data.Floating != 0.0f;

	case Type::Boolean:
		return Data.Boolean;

	case Type::String:
		return true;

	case Type::Vector:
		return true;

	default:
		return false;
	}
}

Value::Value(const char* v)
{
	*this = v;
}

const char* Value::operator=(const char* v)
{
	Type = Type::String;
	Data.String = v;

	return v;
}

Value::operator const char*() const
{
	switch(Type)
	{
	case Type::Void:
		return Constants::DefaultString;

	case Type::Integer:
		return Constants::DefaultString;

	case Type::Float:
		return Constants::DefaultString;

	case Type::Boolean:
		return Constants::DefaultString;

	case Type::String:
		return Data.String;

	case Type::Vector:
		return Constants::DefaultString;

	default:
		return Constants::DefaultString;
	}
}

Value::Value(const Cog::Generics::Vector<float>& v)
{
	*this = v;
}

const Cog::Generics::Vector<float>& Value::operator=(const Cog::Generics::Vector<float>& v)
{
	Type = Type::Vector;
	Data.Vector.X = v.X;
	Data.Vector.Y = v.Y;
	Data.Vector.Z = v.Z;
	
	return v;
}

Value::operator Cog::Generics::Vector<float>() const
{
	switch(Type)
	{
	case Type::Void:
		return Generics::Vector<float>();

	case Type::Integer:
		return Generics::Vector<float>();

	case Type::Float:
		return Generics::Vector<float>();

	case Type::Boolean:
		return Generics::Vector<float>();

	case Type::String:
		return Generics::Vector<float>();

	case Type::Vector:
		return Generics::Vector<float>(Data.Vector.X, Data.Vector.Y, Data.Vector.Z);

	default:
		return Generics::Vector<float>();
	}
}
