#pragma once
#include "IParagraph.hpp"
#include "TextString.hpp"
#include <vector>

namespace QuestCore 
{
	class ParagraphGroup : public IParagraph
	{
	public:
		ParagraphGroup(const std::vector<IParagraph*>& children, const TextString& gap);
		void Clear();
		void AddParagraph(IParagraph* paragraph);

		virtual void Print(ITextView& view) override;
	private:
		TextString _gap;
		std::vector<IParagraph*> _paragraphs;
	};
}
