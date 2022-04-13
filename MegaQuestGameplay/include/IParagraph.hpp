#pragma once
#include <string>
#include <memory>

namespace QuestCore
{
	class ActionContainer;

	class IParagraph
	{
	public:
		virtual ~IParagraph() = default;

		virtual std::string GetQuest() const = 0;
		virtual ActionContainer& GetActionContainer() = 0;
	};
}
