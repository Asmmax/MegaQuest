#pragma once
#include "TextString.hpp"
#include <memory>
#include <exception>
#include <vector>

namespace QuestCore
{
	class IRoom;
	class IAction;
	struct Case;
}

namespace Player 
{
	class ITextView;

	struct AnswerNotExsistExeption : public std::exception {};

	class PlayerController
	{
	public:
        PlayerController(const std::shared_ptr<QuestCore::IRoom>& currentRoom);

        void DoCommand(int answerID);
        void SetCurrentRoom(const std::shared_ptr<QuestCore::IRoom>& currentRoom);
        void SetTextView(const std::shared_ptr<ITextView>& textView);
		void OpenInventory();

    private:
		void ViewParagraph();
		void Answer(int caseID);
		std::vector<QuestCore::Case> GetCases();
		QuestCore::TextString GetCasesContain();

	private:
		std::shared_ptr<QuestCore::IRoom> _currentRoom;
		std::shared_ptr<ITextView> _textView;
	};
}
