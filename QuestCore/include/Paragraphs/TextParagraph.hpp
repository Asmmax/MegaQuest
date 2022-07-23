#pragma once
#include "IParagraph.hpp"
#include "TextString.hpp"

namespace QuestCore
{
	/// @serializable
	class TextParagraph : public IParagraph
	{
	public:
		TextParagraph(const TextString& text);
		virtual void Print(ITextView& view) override;

	private:
		TextString _text;
	};
}
