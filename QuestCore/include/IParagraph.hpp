#pragma once
#include <memory>

namespace QuestCore
{
	class ITextView;
	class TextString;

	class IParagraph
	{
	public:
		using Ptr = std::shared_ptr<IParagraph>;

		virtual ~IParagraph() = default;

		virtual void Print(ITextView& view) = 0;
	};
}
