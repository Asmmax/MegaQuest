#pragma once
#include "IParagraph.hpp"
#include "ActionMap.hpp"
#include <vector>
#include <memory>

namespace QuestCore {
	class ParagraphGroup : public IParagraph
	{
	public:
		ParagraphGroup(const TextString& gap);
		void ClearParagraphs();
		void AddParagraph(const std::shared_ptr<IParagraph>& paragraph);
		void UpdateActions();

		virtual TextString GetQuest() const override;
		virtual ActionMap& GetActionContainer() override;
	private:
		ActionMap _actions;
		TextString _gap;
		std::vector<std::shared_ptr<IParagraph>> _paragraphs;
	};
}