#pragma once
#include <memory>

namespace QuestCore
{
	class IQuest
	{
	public:
		virtual ~IQuest() = default;

		virtual void Init() = 0;
	};
}
