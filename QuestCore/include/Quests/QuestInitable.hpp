#pragma once
#include <memory>

namespace QuestCore
{
	class Quest;

	class QuestInitable
	{
	public:
		QuestInitable(Quest* quest);

		virtual ~QuestInitable() = default;
		virtual void Init() = 0;

	private:
		Quest* _quest;
	};
}
