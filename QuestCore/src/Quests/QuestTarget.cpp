#include "Quests/QuestTarget.hpp"

using namespace QuestCore;

void QuestTarget::SetCurrent(const IQuest::Ptr& current)
{
	_current = current;
}

void QuestTarget::Init()
{
	QuestHeader::Init();
	_current->Init();
}
