#pragma once

namespace QuestCore
{
	class ICondition
	{
	public:
		virtual ~ICondition() = default;

		virtual bool IsAllowed() = 0;
	};
}