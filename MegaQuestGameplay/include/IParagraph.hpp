#pragma once
#include "TextString.hpp"

namespace QuestCore
{
	class CaseContainer;

	class IParagraph
	{
	public:
		virtual ~IParagraph() = default;

		virtual TextString GetQuest() const = 0;
		virtual CaseContainer& GetCaseContainer() = 0;
	};
}
