#pragma once
#include "TextString.hpp"
#include <memory>

namespace QuestCore
{
	class CaseContainer;

	class IParagraph
	{
	public:
		using Ptr = std::shared_ptr<IParagraph>;

		virtual ~IParagraph() = default;

		virtual TextString GetQuest() const = 0;
		virtual CaseContainer& GetCaseContainer() = 0;
	};
}
