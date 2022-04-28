#include "ActionGroup.hpp"

using namespace QuestCore;

ActionGroup::ActionGroup(const TextString& prefix, const TextString& gap):
	_prefix(prefix),
	_gap(gap)
{
}

TextString ActionGroup::GetName() const
{
	TextString name = _prefix;

	auto& actions = GetActions();
	for (auto actionIt = actions.begin(); actionIt != actions.end(); actionIt++) {
		if (actionIt != actions.begin()) {
			name += _gap;
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
