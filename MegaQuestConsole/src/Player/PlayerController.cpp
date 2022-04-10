#include "Player/PlayerController.hpp"
#include "IRoom.hpp"
#include "IParagraph.hpp"
#include "Player/ITextView.hpp"
#include "Player/PlayerInventory.hpp"

using namespace Player;

PlayerController::PlayerController(const std::shared_ptr<QuestCore::IRoom>& currentRoom, const std::shared_ptr<PlayerInventory>& inventory):
    _currentRoom(currentRoom),
    _inventory(inventory)
{
}

void PlayerController::DoCommand(int answerID)
{
    int caseID = answerID - 1;
    auto paragraph = _currentRoom->GetCurrentParagraph();

    
    if (caseID < 0 || caseID >= paragraph->GetCaseCount()) {
        throw AnswerNotExsistExeption();
    }

    paragraph->Answer(caseID);
    ViewParagraph();
}

void PlayerController::OpenInventory()
{
    _textView->Write(_inventory->GetContains());
}

void PlayerController::SetCurrentRoom(const std::shared_ptr<QuestCore::IRoom>& currentRoom)
{
    _currentRoom = currentRoom;
}

void PlayerController::SetTextView(const std::shared_ptr<ITextView>& textView)
{
    _textView = textView;
    ViewParagraph();
}

void PlayerController::ViewParagraph()
{
    auto paragraph = _currentRoom->GetCurrentParagraph();
    _textView->Write(_currentRoom->GetName() + ":\n" + paragraph->GetQuest() + paragraph->GetCases());
}
