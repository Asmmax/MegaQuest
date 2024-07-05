#include "Quests/QuestInitable.hpp"
#include "Quests/Quest.hpp"

using namespace QuestCore;

QuestInitable::QuestInitable(Quest* quest):
	_quest(quest)
{
	_quest->AddInitCallback([this]() {
		Init();
		});
}
