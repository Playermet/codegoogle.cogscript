#ifndef _VM_VALUE_H_INCLUDED_
#define _VM_VALUE_H_INCLUDED_

#include "gen_vector.h"
#include "vm_type.h"

namespace Cog
{
	namespace VirtualMachine
	{
		class Value
		{
		private:
			Type::Enum Type;

			union
			{
				int Integer;
				float Floating;
				bool Boolean;
				const char* String;
				struct
				{
					float X, Y, Z;
				} Vector;
			} Data;

		public:
			Value();

			Value(const Value&);
			const Value& operator=(const Value&);

			Value(int);
			int operator=(int);
			operator int() const;

			Value(float);
			float operator=(float);
			operator float() const;

			Value(bool);
			bool operator=(bool);
			operator bool() const;

			Value(const char*);
			const char* operator=(const char*);
			operator const char*() const;

			Value(const Generics::Vector<float>&);
			const Generics::Vector<float>& operator=(const Generics::Vector<float>&);
			operator Generics::Vector<float>() const;

			inline bool IsNumeric() const
			{
				return Type == Type::Integer || Type == Type::Float;
			}

			inline Type::Enum GetType() const
			{
				return Type;
			}

			inline Value operator+(const Value& v2) const
			{
				if(Type == Type::Float || v2.Type == Type::Float)
				{
					return Value(static_cast<float>(*this) + static_cast<float>(v2));
				}
				else
				{
					return Value(static_cast<int>(*this) + static_cast<int>(v2));
				}
			}

			inline Value operator-(const Value& v2) const
			{
				if(Type == Type::Float || v2.Type == Type::Float)
				{
					return Value(static_cast<float>(*this) - static_cast<float>(v2));
				}
				else
				{
					return Value(static_cast<int>(*this) - static_cast<int>(v2));
				}
			}

			inline Value operator*(const Value& v2) const
			{
				if(Type == Type::Float || v2.Type == Type::Float)
				{
					return Value(static_cast<float>(*this) * static_cast<float>(v2));
				}
				else
				{
					return Value(static_cast<int>(*this) * static_cast<int>(v2));
				}
			}

			inline Value operator/(const Value& v2) const
			{
				if(Type == Type::Float || v2.Type == Type::Float)
				{
					return Value(static_cast<float>(*this) / static_cast<float>(v2));
				}
				else
				{
					return Value(static_cast<int>(*this) / static_cast<int>(v2));
				}
			}

			inline Value operator%(const Value& v2) const
			{
				return Value(static_cast<int>(*this) % static_cast<int>(v2));
			}

			inline Value operator&(const Value& v2) const
			{
				return Value(static_cast<int>(*this) & static_cast<int>(v2));
			}

			inline Value operator|(const Value& v2) const
			{
				return Value(static_cast<int>(*this) | static_cast<int>(v2));
			}

			inline Value operator^(const Value& v2) const
			{
				return Value(static_cast<int>(*this) ^ static_cast<int>(v2));
			}

			inline Value operator>(const Value& v2) const
			{
				if(Type == Type::Float || v2.Type == Type::Float)
				{
					return Value(static_cast<float>(*this) > static_cast<float>(v2));
				}
				else
				{
					return Value(static_cast<int>(*this) > static_cast<int>(v2));
				}
			}

			inline Value operator>=(const Value& v2) const
			{
				if(Type == Type::Float || v2.Type == Type::Float)
				{
					return Value(static_cast<float>(*this) >= static_cast<float>(v2));
				}
				else
				{
					return Value(static_cast<int>(*this) >= static_cast<int>(v2));
				}
			}

			inline Value operator<(const Value& v2) const
			{
				if(Type == Type::Float || v2.Type == Type::Float)
				{
					return Value(static_cast<float>(*this) < static_cast<float>(v2));
				}
				else
				{
					return Value(static_cast<int>(*this) < static_cast<int>(v2));
				}
			}

			inline Value operator<=(const Value& v2) const
			{
				if(Type == Type::Float || v2.Type == Type::Float)
				{
					return Value(static_cast<float>(*this) <= static_cast<float>(v2));
				}
				else
				{
					return Value(static_cast<int>(*this) <= static_cast<int>(v2));
				}
			}

			inline Value operator==(const Value& v2) const
			{
				if(Type == Type::Float || v2.Type == Type::Float)
				{
					return Value(static_cast<float>(*this) == static_cast<float>(v2));
				}
				else if(Type == Type::Integer || v2.Type == Type::Integer)
				{
					return Value(static_cast<int>(*this) == static_cast<int>(v2));
				}
				else if(Type == Type::Boolean || v2.Type == Type::Boolean)
				{
					return Value(static_cast<bool>(*this) == static_cast<bool>(v2));
				}
				else
				{
					return Value(false);
				}
			}

			inline Value operator!=(const Value& v2) const
			{
				if(Type == Type::Float || v2.Type == Type::Float)
				{
					return Value(static_cast<float>(*this) != static_cast<float>(v2));
				}
				else if(Type == Type::Integer || v2.Type == Type::Integer)
				{
					return Value(static_cast<int>(*this) != static_cast<int>(v2));
				}
				else if(Type == Type::Boolean || v2.Type == Type::Boolean)
				{
					return Value(static_cast<bool>(*this) != static_cast<bool>(v2));
				}
				else
				{
					return Value(false);
				}
			}

			inline Value operator&&(const Value& v2) const
			{
				return Value(static_cast<bool>(*this) && static_cast<bool>(v2));
			}

			inline Value operator||(const Value& v2) const
			{
				return Value(static_cast<bool>(*this) || static_cast<bool>(v2));
			}

			inline Value operator+() const
			{
				return *this;
			}

			inline Value operator-() const
			{
				if(Type == Type::Float)
				{
					return Value(-static_cast<float>(*this));
				}
				else
				{
					return Value(-static_cast<int>(*this));
				}
			}

			inline Value operator!() const
			{
				return Value(!static_cast<bool>(*this));
			}
		};
	}
}

#endif // _VM_VALUE_H_INCLUDED_
