#pragma once
#include "IParagraph.hpp"
#include "TextString.hpp"
#include <vector>

namespace QuestCore 
{
	/// @serializable
	class ParagraphGroup : public IParagraph
	{
	public:
		ParagraphGroup(const std::vector<std::shared_ptr<IParagraph>>& children, const TextString& gap);
		void Clear();
		void AddParagraph(const IParagraph::Ptr& paragraph);

		virtual void Print(ITextView& view) override;
	private:
		TextString _gap;
		std::vector<IParagraph::Ptr> _paragraphs;
	};
}
