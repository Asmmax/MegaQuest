#pragma once
#include "ICondition.hpp"
#include <memory>

namespace QuestCore
{
	class Value;

	/// @serializable
	enum class Operation {None, Less, Greater, Equal, NotLess, NotGreater, NotEqual};

	class Comparison : public ICondition
	{
	public:
		Comparison(std::unique_ptr<Value> left, std::unique_ptr<Value> right, Operation op);
		virtual bool IsAllowed() override;

	private:
		std::unique_ptr<Value> _left;
		std::unique_ptr<Value> _right;
		Operation _op;
	};
}
