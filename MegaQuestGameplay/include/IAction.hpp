#pragma once
#include <string>

namespace QuestCore
{
	class IAction
	{
	public:
		virtual ~IAction() = default;

		virtual std::string GetName() const = 0;
		virtual void Do() = 0;
	};
}
