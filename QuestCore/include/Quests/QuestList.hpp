#pragma once
#include "Quests/Quest.hpp"

namespace QuestCore
{
	class QuestList : public Quest
	{
	public:
		QuestList(const std::vector<IQuest*>& quests);
		void SetCurrent(unsigned int currentId);

		void Up();
		void Down();

		virtual void Init() override;

	private:
		unsigned int _currentId;
		IQuest* _current;
		std::vector<IQuest*> _quests;
	};
}
