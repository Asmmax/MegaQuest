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
		Comparison(const std::shared_ptr<Value>& left, const std::shared_ptr<Value>& right, Operation op);
		virtual bool IsAllowed() override;

	private:
		std::shared_ptr<Value> _left;
		std::shared_ptr<Value> _right;
		Operation _op;
	};
}