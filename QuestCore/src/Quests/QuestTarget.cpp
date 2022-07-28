#include "Quests/QuestTarget.hpp"

using namespace QuestCore;

QuestTarget::QuestTarget(const std::vector<SlotPtr>& slots) :
	QuestHeader(slots)
{
}

void QuestTarget::SetCurrent(const IQuest::Ptr& current)
{
	_current = current;
}

void QuestTarget::Init()
{
	QuestHeader::Init();
	_current->Init();
}
