#pragma once
#include <memory>

namespace QuestCore
{
	class ITextView;
	class TextString;

	/// @serializable @shared paragraphs @abstract
	class IParagraph
	{
	public:
		using Ptr = std::shared_ptr<IParagraph>;
		using WeakPtr = std::weak_ptr<IParagraph>;

		virtual ~IParagraph() = default;

		virtual void Print(ITextView& view) = 0;
	};
}
