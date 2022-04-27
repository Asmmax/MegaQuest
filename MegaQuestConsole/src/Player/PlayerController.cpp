#include "Player/PlayerController.hpp"
#include "IRoom.hpp"
#include "IParagraph.hpp"
#include "Player/ITextView.hpp"
#include "ActionMap.hpp"
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
    auto paragraph = _currentRoom->GetCurrentParagraph();

    
    if (caseID < 0 || caseID >= paragraph->GetActionContainer().GetActionCount()) {
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

    if (auto inventoryAction = _currentRoom->GetCurrentParagraph()->GetActionContainer().GetAction(*hotKeyIt)) {
        inventoryAction->Do();
    }

    ViewParagraph();
}

void PlayerController::ViewParagraph()
{
    auto paragraph = _currentRoom->GetCurrentParagraph();
    _textView->Write(_currentRoom->GetName() + TextString::FromUtf8(u8":\n") + paragraph->GetQuest() + TextString::FromUtf8(u8"\n") + GetCases());
}

void PlayerController::Answer(int caseID)
{
    auto actions = GetActions();
    assert(caseID < static_cast<int>(actions.size()));

    actions[caseID]->Do();
}

std::vector<std::shared_ptr<QuestCore::IAction>> PlayerController::GetActions()
{
    auto& actions = _currentRoom->GetCurrentParagraph()->GetActionContainer().GetActions();
    auto& hotKeys = _currentRoom->GetHotKeys();

    std::vector<std::shared_ptr<QuestCore::IAction>> hotActions;
    for (auto& hotKey : hotKeys) {
        if (auto hotAction = _currentRoom->GetCurrentParagraph()->GetActionContainer().GetAction(hotKey)) {
            hotActions.push_back(hotAction);
        }
    }

    std::vector<std::shared_ptr<QuestCore::IAction>> result;


    for (auto& action : actions) {

        bool ignore = false;
        for (auto& hotAction : hotActions) {
            if (hotAction == action) {
                ignore = true;
            }
        }
        if (ignore) {
            continue;
        }

        result.push_back(action);
    }

    return result;
}

TextString PlayerController::GetCases()
{
    TextString caseString;
    int id = 1;
    auto actions = GetActions();
    for (auto& action : actions) {
        caseString += TextString(id) + TextString::FromUtf8(u8" - ") + action->GetName() + TextString::FromUtf8(u8"\n");
        id++;
    }
    return caseString;
}
