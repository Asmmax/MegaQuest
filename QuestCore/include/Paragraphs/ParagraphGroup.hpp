#pragma once
#include "IParagraph.hpp"
#include "TextString.hpp"
#include <vector>

namespace QuestCore {
	class ParagraphGroup : public IParagraph
	{
	public:
		ParagraphGroup(const TextString& gap);
		void Clear();
		void AddParagraph(const IParagraph::Ptr& paragraph);

		virtual TextString GetText() const override;
	private:
		TextString _gap;
		std::vector<IParagraph::Ptr> _paragraphs;
	};
}