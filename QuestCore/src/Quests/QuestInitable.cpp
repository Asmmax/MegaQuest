#include "Quests/QuestInitable.hpp"
#include "Quests/QuestHeader.hpp"

using namespace QuestCore;

QuestInitable::QuestInitable(const QuestHeaderPtr& quest):
	_quest(quest)
{
	_quest->AddInitCallback([this]() {
		Init();
		});
}
