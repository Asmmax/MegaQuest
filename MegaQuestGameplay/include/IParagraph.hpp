#pragma once
#include "TextString.hpp"

namespace QuestCore
{
	class ActionMap;

	class IParagraph
	{
	public:
		virtual ~IParagraph() = default;

		virtual TextString GetQuest() const = 0;
		virtual ActionMap& GetActionContainer() = 0;
	};
}
