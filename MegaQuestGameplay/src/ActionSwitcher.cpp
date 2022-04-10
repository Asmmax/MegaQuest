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

void QuestCore::ActionSwitcher::Switch(int actionID)
{
	auto& actions = GetActions();
	assert(actionID < static_cast<int>(actions.size()));

	_target = actions[actionID];
}
