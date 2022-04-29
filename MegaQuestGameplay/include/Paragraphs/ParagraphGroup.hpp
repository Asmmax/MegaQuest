#pragma once
#include "IParagraph.hpp"
#include "CaseContainer.hpp"
#include <vector>
#include <memory>

namespace QuestCore {
	class ParagraphGroup : public IParagraph
	{
	public:
		ParagraphGroup(const TextString& gap);
		void ClearParagraphs();
		void AddParagraph(const std::shared_ptr<IParagraph>& paragraph);
		void UpdateCases();

		virtual TextString GetQuest() const override;
		virtual CaseContainer& GetCaseContainer() override;
	private:
		CaseContainer _cases;
		TextString _gap;
		std::vector<std::shared_ptr<IParagraph>> _paragraphs;
	};
}