#include "Quests/QuestInitable.hpp"
#include "Quests/Quest.hpp"

using namespace QuestCore;

QuestInitable::QuestInitable(const QuestPtr& quest):
	_quest(quest)
{
	_quest->AddInitCallback([this]() {
		Init();
		});
}
