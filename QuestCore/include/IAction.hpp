#pragma once

namespace QuestCore
{
	class IAction
	{
	public:
		virtual ~IAction() = default;

		virtual void Do() = 0;
	};
}
