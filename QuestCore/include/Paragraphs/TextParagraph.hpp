#pragma once
#include "IParagraph.hpp"
#include "TextString.hpp"

namespace QuestCore
{
	class TextParagraph : public IParagraph
	{
	public:
		TextParagraph(const TextString& text);
		virtual TextString GetText() const override;

	private:
		TextString _text;
	};
}
