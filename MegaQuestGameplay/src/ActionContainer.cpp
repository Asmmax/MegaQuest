#include "ActionContainer.hpp"

using namespace QuestCore;

void ActionContainer::Clear()
{
	_actions.clear();
}

int ActionContainer::GetActionCount() const
{
	return static_cast<int>(_actions.size());
}

void ActionContainer::AddAction(const std::shared_ptr<IAction>& action)
{
	_actions.emplace_back(action);
}

void ActionContainer::RemoveAction(const std::shared_ptr<IAction>& action)
{
	auto foundAction = std::find(_actions.begin(), _actions.end(), action);
	if (foundAction != _actions.end()) {
		_actions.erase(foundAction);
	}
}

const ActionContainer::ActionList& ActionContainer::GetActions() const
{
	return _actions;
}

ActionContainer& ActionContainer::operator+=(const ActionContainer& other)
{
	for (auto& action : other._actions) {
		_actions.push_back(action);
	}
	return *this;
}

