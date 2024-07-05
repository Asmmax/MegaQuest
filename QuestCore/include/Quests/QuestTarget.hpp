#pragma once
#include "Quests/Quest.hpp"

namespace QuestCore
{
	class QuestTarget : public Quest
	{
	public:
		void SetCurrent(IQuest* current);

		virtual void Init() override;

	private:
		IQuest* _current;
	};
}
