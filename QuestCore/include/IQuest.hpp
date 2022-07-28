#pragma once
#include <memory>

namespace QuestCore
{
	/// @serializable @shared quests @abstract
	class IQuest
	{
	public:
		using Ptr = std::shared_ptr<IQuest>;
		virtual ~IQuest() = default;

		virtual void Init() = 0;
	};
}
