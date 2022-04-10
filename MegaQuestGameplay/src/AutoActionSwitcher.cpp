#include "AutoActionSwitcher.hpp"

using namespace QuestCore;

QuestCore::AutoActionSwitcher::AutoActionSwitcher():
	_isInited(false),
	_finalActionId(0)
{
}

void AutoActionSwitcher::Do()
{
	ActionSwitcher::Do();
	if (_isInited) {
		Switch(_finalActionId);
	}
}

void AutoActionSwitcher::SetFinalAction(int actionID)
{
	_finalActionId = actionID;
	_isInited = true;
}
