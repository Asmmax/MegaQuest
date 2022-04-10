#pragma once
#include <memory>
#include <exception>

namespace QuestCore
{
	class IRoom;
}

namespace Player 
{
	class ITextView;
	class PlayerInventory;

	struct AnswerNotExsistExeption : public std::exception {};

	class PlayerController
	{
	public:
        PlayerController(const std::shared_ptr<QuestCore::IRoom>& currentRoom, const std::shared_ptr<PlayerInventory>& inventory);

        void DoCommand(int answerID);
        void OpenInventory();
        void SetCurrentRoom(const std::shared_ptr<QuestCore::IRoom>& currentRoom);
        void SetTextView(const std::shared_ptr<ITextView>& textView);

    private:
		void ViewParagraph();

	private:
		std::shared_ptr<QuestCore::IRoom> _currentRoom;
		std::shared_ptr<ITextView> _textView;
		std::shared_ptr<PlayerInventory> _inventory;
	};
}
