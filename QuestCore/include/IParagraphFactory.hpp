#pragma once
#include <memory>

namespace QuestCore
{
	class IParagraph;

	/// @serializable @abstract @shared
	class IParagraphFactory
	{
	protected:
		using ParagraphPtr = std::shared_ptr<IParagraph>;
	public:
		virtual ~IParagraphFactory() = default;
		virtual ParagraphPtr GetParagraph() const = 0;
	};
}
