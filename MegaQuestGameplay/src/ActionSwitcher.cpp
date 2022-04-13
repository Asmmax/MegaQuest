#include "ActionSwitcher.hpp"

#include <assert.h>

using namespace QuestCore;

std::string ActionSwitcher::GetName() const
{
	if (!_target) {
		return std::string();
	}

	return _target->GetName();
}

void ActionSwitcher::Do()
{
	if (!_target) {
		return ;
	}

	_target->Do();
}

void QuestCore::ActionSwitcher::Switch(const std::shared_ptr<IAction>& action)
{
	auto& actions = GetActions();
	auto foundActionIt = std::find(actions.begin(), actions.end(), action);

	bool actionValid = foundActionIt != actions.end();
	assert(actionValid);
	if (actionValid) {
		_target = action;
	}
}
