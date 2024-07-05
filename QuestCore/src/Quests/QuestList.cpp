#include "Quests/QuestList.hpp"

using namespace QuestCore;

QuestList::QuestList(const std::vector<IQuest*>& quests):
	_currentId(-1),
	_quests(quests),
	_current(nullptr)
{
}

void QuestList::SetCurrent(unsigned int currentId)
{
	_currentId = currentId;
	_current = _quests[_currentId];
}

void QuestList::Up()
{
	unsigned int newCurrentId = (_currentId + 1) % _quests.size();
	SetCurrent(newCurrentId);
}

void QuestList::Down()
{
	unsigned int newCurrentId = (_currentId - 1) % _quests.size();
	SetCurrent(newCurrentId);
}

void QuestList::Init()
{
	Quest::Init();
	_current->Init();
}
