#pragma once
#include "ICondition.hpp"
#include <memory>

namespace QuestCore
{
	class Value;

	enum class Operation {None, Less, Greater, Equal, NotLess, NotGreater, NotEqual};

	class Comparison : public ICondition
	{
	public:
		Comparison(Value* left, Value* right, Operation op);

		virtual bool IsAllowed() override;

	private:
		Value* _left;
		Value* _right;
		Operation _op;
	};
}
