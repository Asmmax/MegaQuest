#include "Quests/QuestHeader.hpp"

using namespace QuestCore;

void QuestHeader::AddInitCallback(const Callback& callback)
{
	_initCallbacks.push_back(callback);
}

void QuestHeader::Init()
{
	for (auto& callback : _initCallbacks) {
		callback();
	}
}
