#include "Game/Replay/ReplayManager.hpp"

using namespace Game;

void ReplayManager::PushAction(const ReplayAction& action)
{
	_actions.push_back(action);
}

void ReplayManager::Store()
{
	Save();
}

void ReplayManager::Restore()
{
	_actions.clear();
	
	Load();

	for (auto& action : _actions) {
		action();
	}
}
