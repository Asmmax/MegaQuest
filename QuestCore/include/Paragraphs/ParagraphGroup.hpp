#pragma once
#include "IParagraph.hpp"
#include "TextString.hpp"
#include <vector>

namespace QuestCore {
	class ParagraphGroup : public IParagraph
	{
	public:
		ParagraphGroup(const TextString& gap);
		/// @inject
		void SetChildren(const std::vector<std::shared_ptr<IParagraph>>& children);
		void Clear();
		void AddParagraph(const IParagraph::Ptr& paragraph);

		virtual void Print(ITextView& view) override;
	private:
		TextString _gap;
		std::vector<IParagraph::Ptr> _paragraphs;
	};
}
