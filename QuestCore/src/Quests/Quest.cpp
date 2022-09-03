#include "Quests/Quest.hpp"

using namespace QuestCore;

void Quest::AddInitCallback(const Callback& callback)
{
	_initCallbacks.push_back(callback);
}

void Quest::Init()
{
	for (auto& callback : _initCallbacks) {
		callback();
	}
}
