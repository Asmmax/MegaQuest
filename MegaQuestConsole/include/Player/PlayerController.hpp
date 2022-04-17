#pragma once
#include <memory>
#include <exception>
#include <string>

namespace QuestCore
{
	class IRoom;
	class Inventory;
}

namespace Player 
{
	class ITextView;

	struct AnswerNotExsistExeption : public std::exception {};

	class PlayerController
	{
	public:
        PlayerController(const std::shared_ptr<QuestCore::IRoom>& currentRoom, const std::shared_ptr<QuestCore::Inventory>& inventory);

        void DoCommand(int answerID);
        void OpenInventory();
        void SetCurrentRoom(const std::shared_ptr<QuestCore::IRoom>& currentRoom);
        void SetTextView(const std::shared_ptr<ITextView>& textView);

    private:
		void ViewParagraph();
		void Answer(int caseID);
		std::string GetCases();
		std::string GetNullableItemsContains();
		std::string GetItemsContains();

	private:
		std::shared_ptr<QuestCore::IRoom> _currentRoom;
		std::shared_ptr<ITextView> _textView;
		std::shared_ptr<QuestCore::Inventory> _inventory;
	};
}
