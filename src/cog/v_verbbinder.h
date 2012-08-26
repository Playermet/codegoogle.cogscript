#ifndef _V_VERBBINDER_H_INCLUDED_
#define _V_VERBBINDER_H_INCLUDED_

#include "vm_value.h"
#include <stack>

namespace Cog
{
	namespace Verbs
	{
		template <typename T, int n> class VerbBinder;

#define COG_CV_BINDER_ARG(n) VirtualMachine::Value v##n = stack.top(); stack.pop();

#define COG_CV_BINDER_ARGS_0
#define COG_CV_BINDER_ARGS_1 COG_CV_BINDER_ARG(1); COG_CV_BINDER_ARGS_0
#define COG_CV_BINDER_ARGS_2 COG_CV_BINDER_ARG(2); COG_CV_BINDER_ARGS_1
#define COG_CV_BINDER_ARGS_3 COG_CV_BINDER_ARG(3); COG_CV_BINDER_ARGS_2
#define COG_CV_BINDER_ARGS_4 COG_CV_BINDER_ARG(4); COG_CV_BINDER_ARGS_3
#define COG_CV_BINDER_ARGS_5 COG_CV_BINDER_ARG(5); COG_CV_BINDER_ARGS_4
#define COG_CV_BINDER_ARGS_6 COG_CV_BINDER_ARG(6); COG_CV_BINDER_ARGS_5
#define COG_CV_BINDER_ARGS_7 COG_CV_BINDER_ARG(7); COG_CV_BINDER_ARGS_6
#define COG_CV_BINDER_ARGS_8 COG_CV_BINDER_ARG(8); COG_CV_BINDER_ARGS_7
#define COG_CV_BINDER_ARGS_9 COG_CV_BINDER_ARG(9); COG_CV_BINDER_ARGS_8
#define COG_CV_BINDER_ARGS_10 COG_CV_BINDER_ARG(10); COG_CV_BINDER_ARGS_9

#define COG_CV_BINDER_ARG_PASS_0
#define COG_CV_BINDER_ARG_PASS_1 v1
#define COG_CV_BINDER_ARG_PASS_2 COG_CV_BINDER_ARG_PASS_1, v2
#define COG_CV_BINDER_ARG_PASS_3 COG_CV_BINDER_ARG_PASS_2, v3
#define COG_CV_BINDER_ARG_PASS_4 COG_CV_BINDER_ARG_PASS_3, v4
#define COG_CV_BINDER_ARG_PASS_5 COG_CV_BINDER_ARG_PASS_4, v5
#define COG_CV_BINDER_ARG_PASS_6 COG_CV_BINDER_ARG_PASS_5, v6
#define COG_CV_BINDER_ARG_PASS_7 COG_CV_BINDER_ARG_PASS_6, v7
#define COG_CV_BINDER_ARG_PASS_8 COG_CV_BINDER_ARG_PASS_7, v8
#define COG_CV_BINDER_ARG_PASS_9 COG_CV_BINDER_ARG_PASS_8, v9
#define COG_CV_BINDER_ARG_PASS_10 COG_CV_BINDER_ARG_PASS_9, v10

#define COG_CV_BINDER(n)																									\
	template <typename T> class VerbBinder<T, n>																	\
		{																												\
		public:																											\
		template <typename U> VirtualMachine::Value Invoke(std::stack<VirtualMachine::Value>& stack, U fn)			\
		{																											\
		COG_CV_BINDER_ARGS_##n;																				\
		return VirtualMachine::Value(fn(COG_CV_BINDER_ARG_PASS_##n));											\
		}																											\
		};																												\
		\
		template <> class VerbBinder<void, n>																			\
		{																												\
		public:																											\
		template <typename U> VirtualMachine::Value Invoke(std::stack<VirtualMachine::Value>& stack, U fn)			\
		{																											\
		COG_CV_BINDER_ARGS_##n;																				\
		fn(COG_CV_BINDER_ARG_PASS_##n);																		\
		return VirtualMachine::Value();																			\
		}																											\
		};

		COG_CV_BINDER(0);
		COG_CV_BINDER(1);
		COG_CV_BINDER(2);
		COG_CV_BINDER(3);
		COG_CV_BINDER(4);
		COG_CV_BINDER(5);
		COG_CV_BINDER(6);
		COG_CV_BINDER(7);
		COG_CV_BINDER(8);
		COG_CV_BINDER(9);
		COG_CV_BINDER(10);
	}
}

#endif // _V_VERBBINDER_H_INCLUDED_
