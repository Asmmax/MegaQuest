#include "Actions/ActionGroup.hpp"

using namespace QuestCore;

void ActionGroup::Clear()
{
	_actions.clear();
}

void ActionGroup::AddAction(const std::shared_ptr<IAction>& action)
{
	_actions.push_back(action);
}

void ActionGroup::Do()
{
	for (auto& action : _actions) {
		action->Do();
	}
}
