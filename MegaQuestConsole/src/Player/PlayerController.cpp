#include "Player/PlayerController.hpp"
#include "IRoom.hpp"
#include "IParagraph.hpp"
#include "Player/ITextView.hpp"
#include "CaseContainer.hpp"
#include "IAction.hpp"

#include <assert.h>

using namespace Player;
using namespace QuestCore;

PlayerController::PlayerController(const std::shared_ptr<QuestCore::IRoom>& currentRoom):
    _currentRoom(currentRoom)
{
}

void PlayerController::DoCommand(int answerID)
{
    int caseID = answerID - 1;
    auto paragraph = GetCurrentParagraph();

    
    if (caseID < 0 || caseID >= paragraph->GetCaseContainer().GetCaseCount()) {
        throw AnswerNotExsistExeption();
    }

    Answer(caseID);
    ViewParagraph();
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

void PlayerController::OpenInventory()
{
    auto& hotKeys = _currentRoom->GetHotKeys();
    auto hotKeyIt = std::find(hotKeys.begin(), hotKeys.end(), "inventory");
    if (hotKeyIt == hotKeys.end()) {
        return;
    }

    auto inventoryCases = GetCurrentParagraph()->GetCaseContainer().GetCases(*hotKeyIt);
    if (inventoryCases.empty()) {
        return;
    }

    if (auto inventoryAction = inventoryCases.front().action) {
        inventoryAction->Do();
    }

    ViewParagraph();
}

void PlayerController::ViewParagraph()
{
    auto paragraph = GetCurrentParagraph();
    _textView->Write(paragraph->GetQuest() + TextString::FromUtf8(u8"\n") + GetCasesContain());
}

void PlayerController::Answer(int caseID)
{
    auto cases = GetCases();
    assert(caseID < static_cast<int>(cases.size()));

    cases[caseID].action->Do();
}

std::vector<QuestCore::Case> PlayerController::GetCases() const
{
    return GetCurrentParagraph()->GetCaseContainer().GetCases();
}

TextString PlayerController::GetCasesContain() const
{
    TextString caseString;
    int id = 1;
    auto cases = GetCases();
    for (auto& _case : cases) {
        caseString += TextString(id) + TextString::FromUtf8(u8" - ") + _case.name + TextString::FromUtf8(u8"\n");
        id++;
    }
    return caseString;
}

std::shared_ptr<IParagraph> PlayerController::GetCurrentParagraph() const
{
    return _currentRoom->GetParagraph("root");
}
