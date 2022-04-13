#pragma once
#include "ActionContainer.hpp"
#include "IParagraph.hpp"

namespace QuestCore
{
	class TextParagraph : public IParagraph
	{
	public:
		TextParagraph(const std::string& text);
		virtual std::string GetQuest() const override;
		virtual ActionContainer& GetActionContainer() override;

	private:
		std::string _text;
		ActionContainer _container;
	};
}
