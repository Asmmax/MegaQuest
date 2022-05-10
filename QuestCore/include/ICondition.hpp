#pragma once
#include <memory>

namespace QuestCore
{
	class ICondition
	{
	public:
		using Ptr = std::shared_ptr<ICondition>;

		virtual ~ICondition() = default;

		virtual bool IsAllowed() = 0;
	};
}