#include "AutoActionSwitcher.hpp"

using namespace QuestCore;

QuestCore::AutoActionSwitcher::AutoActionSwitcher():
	_finalActionId(0)
{
}

void AutoActionSwitcher::Do()
{
	ActionSwitcher::Do();
	if (_finalActionId) {
		Switch(_finalActionId);
	}
}

void AutoActionSwitcher::SetFinalAction(const std::shared_ptr<IAction>& action)
{
	_finalActionId = action;
}
