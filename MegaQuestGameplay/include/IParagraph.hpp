#pragma once
#include "TextString.hpp"
#include <memory>

namespace QuestCore
{
	class ActionContainer;

	class IParagraph
	{
	public:
		virtual ~IParagraph() = default;

		virtual TextString GetQuest() const = 0;
		virtual ActionContainer& GetActionContainer() = 0;
	};
}
