#pragma once
#include "ICondition.hpp"
#include <memory>

namespace QuestCore
{
	class Value;

	/// @serializable
	enum class Operation {None, Less, Greater, Equal, NotLess, NotGreater, NotEqual};

	/// @serializable
	class Comparison : public ICondition
	{
	public:
		Comparison(std::shared_ptr<Value> left, std::shared_ptr<Value> right, Operation op);

		virtual bool IsAllowed() override;

	private:
		std::shared_ptr<Value> _left;
		std::shared_ptr<Value> _right;
		Operation _op;
	};
}
