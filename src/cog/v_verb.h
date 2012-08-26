#ifndef _V_VERB_H_INCLUDED_
#define _V_VERB_H_INCLUDED_

#include "vm_type.h"
#include "vm_value.h"
#include "v_verbbinder.h"
#include <stack>
#include <functional>
#include <boost/function_types/result_type.hpp>
#include <boost/function_types/function_arity.hpp>

namespace Cog
{
	namespace Verbs
	{
		class BaseVerb
		{
		private:
			const size_t parameterCount;
			const VirtualMachine::Type::Enum returnType;

		public:
			BaseVerb(VirtualMachine::Type::Enum returnType, size_t parameterCount);
			virtual ~BaseVerb();

			inline VirtualMachine::Type::Enum ReturnType() const
			{
				return returnType;
			}

			inline size_t ParameterCount() const
			{
				return parameterCount;
			}

			virtual VirtualMachine::Value Invoke(std::stack<VirtualMachine::Value>& stack) const = 0;
		};

		template <typename ResultType, int Arity, typename F> class Verb : public BaseVerb
		{
		private:
			template <typename T> static VirtualMachine::Type::Enum helper_get_vm_type()
			{
				static_assert(false, "helper_get_vm_type is not defined for this type.");
			}

			template <> static VirtualMachine::Type::Enum helper_get_vm_type<void>()
			{
				return VirtualMachine::Type::Void;
			}

			template <> static VirtualMachine::Type::Enum helper_get_vm_type<int>()
			{
				return VirtualMachine::Type::Integer;
			}

			template <> static VirtualMachine::Type::Enum helper_get_vm_type<float>()
			{
				return VirtualMachine::Type::Float;
			}

			template <> static VirtualMachine::Type::Enum helper_get_vm_type<bool>()
			{
				return VirtualMachine::Type::Boolean;
			}

			template <> static VirtualMachine::Type::Enum helper_get_vm_type<Generics::Vector<float>>()
			{
				return VirtualMachine::Type::Vector;
			}

			F functor;

		public:
			Verb(F functor) : BaseVerb(helper_get_vm_type<ResultType>(), Arity), functor(functor)
			{
				return;
			}

			VirtualMachine::Value Invoke(std::stack<VirtualMachine::Value>& stack) const
			{
				VerbBinder<ResultType, Arity> binder;
				return binder.Invoke(stack, functor);
			}
		};
	}
}

#endif // _V_VERB_H_INCLUDED_
