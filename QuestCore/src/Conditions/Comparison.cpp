#include "Conditions/Comparison.hpp"
#include "Value.hpp"

using namespace QuestCore;

Comparison::Comparison(Value* left, Value* right, Operation op):
	_left(left),
	_right(right),
	_op(op)
{
}

bool Comparison::IsAllowed()
{
	if (!_left || !_right) {
		return false;
	}

	switch (_op)
	{
	case QuestCore::Operation::Less:
		return _left->Get() < _right->Get();
	case QuestCore::Operation::Greater:
		return _left->Get() > _right->Get();
	case QuestCore::Operation::Equal:
		return _left->Get() == _right->Get();
	case QuestCore::Operation::NotLess:
		return _left->Get() >= _right->Get();
	case QuestCore::Operation::NotGreater:
		return _left->Get() <= _right->Get();
	case QuestCore::Operation::NotEqual:
		return _left->Get() != _right->Get();
	case QuestCore::Operation::None:
		return true;
	default:
		break;
	}
	return false;
}
