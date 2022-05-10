#pragma once
#include "TextString.hpp"
#include <memory>
#include <exception>
#include <vector>

namespace QuestCore
{
	class IQuest;
	class IParagraph;
	struct Case;
	struct Node;
}

namespace Player 
{
	class ITextView;

	struct AnswerNotExsistExeption : public std::exception {};

	class PlayerController
	{
	public:
        PlayerController(const std::shared_ptr<QuestCore::IQuest>& quest);

        void DoCommand(int answerID);
        void SetTextView(const std::shared_ptr<ITextView>& textView);
		void OpenInventory();

    private:
		void ViewParagraph();
		void Answer(int caseID);
		std::vector<QuestCore::Case> GetCases() const;
		QuestCore::TextString GetCasesContain() const;
		QuestCore::Node GetCurrentNode() const;

	private:
		std::shared_ptr<QuestCore::IQuest> _quest;
		std::shared_ptr<ITextView> _textView;
	};
}
