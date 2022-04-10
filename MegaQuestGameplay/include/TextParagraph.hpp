#pragma once
#include "CaseContainer.hpp"

namespace QuestCore
{
	class TextParagraph : public CaseContainer
	{
	public:
		TextParagraph(const std::string& text);
		virtual std::string GetQuest() const override;

	private:
		std::string _text;
	};
}
