#pragma once
#include <memory>

namespace QuestCore
{
	class ITextView;
	class TextString;

	class IParagraph
	{
	public:
		virtual ~IParagraph() = default;

		virtual void Print(ITextView& view) = 0;
	};
}
