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
    _textView->Write(_currentRoom->GetName() + ":\n" + paragraph->GetQuest() + GetCases());
}

void PlayerController::Answer(int caseID)
{
    auto& actions = _currentRoom->GetCurrentParagraph()->GetActionContainer().GetActions();
    assert(caseID < static_cast<int>(actions.size()));

    actions[caseID]->Do();
}

std::string PlayerController::GetCases()
{
    std::string caseString;
    int id = 1;
    auto& actions = _currentRoom->GetCurrentParagraph()->GetActionContainer().GetActions();
    for (auto& action : actions) {
        caseString += std::to_string(id) + " - " + action->GetName() + "\n";
        id++;
    }
    return caseString;
}

std::string PlayerController::GetNullableItemsContains()
{
    auto nullableItems = _inventory->GetNullableItems();

    std::string nullableItemsContains;
    for (auto itemIt = nullableItems.begin(); itemIt != nullableItems.end(); itemIt++) {
        if (itemIt != nullableItems.begin()) {
            nullableItemsContains += ", ";
        }
        nullableItemsContains += std::to_string(itemIt->second) + " " + itemIt->first->GetContainsFor(itemIt->second);
    }

    if (!nullableItems.empty()) {
        return "У вас " + nullableItemsContains + ".\n";
    }

    return std::string();
}

std::string PlayerController::GetItemsContains()
{
    auto items = _inventory->GetItems();

    auto itemCount = items.size();
    std::string prefix;
    if (itemCount == 1)
        prefix = "В сумке лежит ";
    else if (itemCount > 1) {
        prefix = "В сумке лежат ";
    }

    std::string nullableItemsContains;
    for (auto itemIt = items.begin(); itemIt != items.end(); itemIt++) {
        if (itemIt != items.begin()) {
            nullableItemsContains += ", ";
        }
        if (itemIt->second == 1) {
            nullableItemsContains += itemIt->first->GetContainsFor(itemIt->second);
        }
        else if (itemIt->second > 0) {
            nullableItemsContains += std::to_string(itemIt->second) + " " + itemIt->first->GetContainsFor(itemIt->second);
        }
    }

    if (!nullableItemsContains.empty()) {
        return prefix + nullableItemsContains + ".\n";
    }

    return std::string();
}
