#pragma once
#include "IParagraph.hpp"
#include "CaseContainer.hpp"

namespace QuestCore
{
	class TextParagraph : public IParagraph
	{
	public:
		TextParagraph(const TextString& text);
		virtual TextString GetQuest() const override;
		virtual CaseContainer& GetCaseContainer() override;

	private:
		TextString _text;
		CaseContainer _cases;
	};
}
