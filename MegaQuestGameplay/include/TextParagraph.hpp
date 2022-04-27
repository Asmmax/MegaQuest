#pragma once
#include "ActionMap.hpp"
#include "IParagraph.hpp"

namespace QuestCore
{
	class TextParagraph : public IParagraph
	{
	public:
		TextParagraph(const TextString& text);
		virtual TextString GetQuest() const override;
		virtual ActionMap& GetActionContainer() override;

	private:
		TextString _text;
		ActionMap _container;
	};
}
