#pragma once
#include "ActionContainer.hpp"
#include "IParagraph.hpp"

namespace QuestCore
{
	class TextParagraph : public IParagraph
	{
	public:
		TextParagraph(const TextString& text);
		virtual TextString GetQuest() const override;
		virtual ActionContainer& GetActionContainer() override;

	private:
		TextString _text;
		ActionContainer _container;
	};
}
