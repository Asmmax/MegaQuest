#include "Player/PlayerController.hpp"
#include "IRoom.hpp"
#include "IParagraph.hpp"
#include "Player/ITextView.hpp"
#include "Inventory.hpp"
#include "ItemInfo.hpp"
#include "ActionContainer.hpp"
#include "IAction.hpp"

#include <assert.h>

using namespace Player;
using namespace QuestCore;

PlayerController::PlayerController(const std::shared_ptr<QuestCore::IRoom>& currentRoom, const std::shared_ptr<QuestCore::Inventory>& inventory):
    _currentRoom(currentRoom),
    _inventory(inventory)
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

void PlayerController::OpenInventory()
{
    _textView->Write(GetNullableItemsContains() + GetItemsContains());
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
    _textView->Write(_currentRoom->GetName() + TextString::FromUtf8(u8":\n") + paragraph->GetQuest() + TextString::FromUtf8(u8"\n") + GetCases());
}

void PlayerController::Answer(int caseID)
{
    auto& actions = _currentRoom->GetCurrentParagraph()->GetActionContainer().GetActions();
    assert(caseID < static_cast<int>(actions.size()));

    actions[caseID]->Do();
}

TextString PlayerController::GetCases()
{
    TextString caseString;
    int id = 1;
    auto& actions = _currentRoom->GetCurrentParagraph()->GetActionContainer().GetActions();
    for (auto& action : actions) {
        caseString += TextString(id) + TextString::FromUtf8(u8" - ") + action->GetName() + TextString::FromUtf8(u8"\n");
        id++;
    }
    return caseString;
}

TextString PlayerController::GetNullableItemsContains()
{
    auto nullableItems = _inventory->GetNullableItems();

    TextString nullableItemsContains;
    for (auto itemIt = nullableItems.begin(); itemIt != nullableItems.end(); itemIt++) {
        if (itemIt != nullableItems.begin()) {
            nullableItemsContains += TextString::FromUtf8(u8", ");
        }
        nullableItemsContains += TextString(itemIt->second) + TextString::FromUtf8(u8" ") + itemIt->first->GetContainsFor(itemIt->second);
    }

    if (!nullableItems.empty()) {
        return TextString::FromUtf8(u8"У вас ") + nullableItemsContains + TextString::FromUtf8(u8".\n");
    }

    return TextString();
}

TextString PlayerController::GetItemsContains()
{
    auto items = _inventory->GetItems();

    auto itemCount = items.size();
    TextString prefix;
    if (itemCount == 1)
        prefix = TextString::FromUtf8(u8"В сумке лежит ");
    else if (itemCount > 1) {
        prefix = TextString::FromUtf8(u8"В сумке лежат ");
    }

    TextString nullableItemsContains;
    for (auto itemIt = items.begin(); itemIt != items.end(); itemIt++) {
        if (itemIt != items.begin()) {
            nullableItemsContains += TextString::FromUtf8(u8", ");
        }
        if (itemIt->second == 1) {
            nullableItemsContains += itemIt->first->GetContainsFor(itemIt->second);
        }
        else if (itemIt->second > 0) {
            nullableItemsContains += TextString(itemIt->second) + TextString::FromUtf8(u8" ") + itemIt->first->GetContainsFor(itemIt->second);
        }
    }

    if (!nullableItemsContains.IsEmpty()) {
        return prefix + nullableItemsContains + TextString::FromUtf8(u8".\n");
    }

    return TextString();
}
