#pragma once
#include <memory>

namespace QuestCore
{
	class IParagraph;

	class IParagraphFactory
	{
	public:
		virtual ~IParagraphFactory() = default;
		virtual IParagraph* GetParagraph() const = 0;
	};
}
