#pragma once
#include <memory>

namespace QuestCore
{
	class IQuest;

	class IQuestFactory
	{
	public:
		virtual ~IQuestFactory() = default;
		virtual std::shared_ptr<IQuest> GetQuest() = 0;
	};
}
