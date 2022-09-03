#pragma once
#include <memory>

namespace QuestCore
{
	class Quest;

	class QuestInitable
	{
	protected:
		using QuestPtr = std::shared_ptr<Quest>;
	public:
		QuestInitable(const QuestPtr& quest);

		virtual ~QuestInitable() = default;
		virtual void Init() = 0;

	private:
		QuestPtr _quest;
	};
}
