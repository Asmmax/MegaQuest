bind "Quests/Quest.hpp";
bind "Quests/QuestList.hpp";
bind "Quests/QuestTarget.hpp";

shared QuestCore::Quest : QuestCore::IQuest
{
};

shared QuestCore::QuestList : QuestCore::Quest
{
	QuestList(vector<QuestCore::IQuest> quests);
	SetCurrent(unsigned int currentId);
};

shared QuestCore::QuestTarget : QuestCore::Quest
{
	SetCurrent(QuestCore::IQuest current);
};
