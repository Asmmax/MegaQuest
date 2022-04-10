#include "ActionGroup.hpp"

using namespace QuestCore;

std::string ActionGroup::GetName() const
{
	std::string name;

	auto& actions = GetActions();
	for (auto actionIt = actions.begin(); actionIt != actions.end(); actionIt++) {
		if (actionIt != actions.begin()) {
			name += " è ";
		}
		auto& action = *actionIt;
		name += action->GetName();
	}

	return name;
}

void ActionGroup::Do()
{
	auto& actions = GetActions();
	for (auto& action : actions) {
		action->Do();
	}
}
