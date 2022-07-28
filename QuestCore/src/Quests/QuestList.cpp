#include "Quests/QuestList.hpp"

using namespace QuestCore;

QuestList::QuestList(const std::vector<IQuest::Ptr>& quests):
	_currentId(-1),
	_quests(quests)
{
}

void QuestList::SetCurrent(size_t currentId)
{
	_currentId = currentId;
	_current = _quests[_currentId];
}

void QuestList::Up()
{
	size_t newCurrentId = (_currentId + 1) % _quests.size();
	SetCurrent(newCurrentId);
}

void QuestList::Down()
{
	size_t newCurrentId = (_currentId - 1) % _quests.size();
	SetCurrent(newCurrentId);
}

void QuestList::Init()
{
	QuestHeader::Init();
	_current->Init();
}
