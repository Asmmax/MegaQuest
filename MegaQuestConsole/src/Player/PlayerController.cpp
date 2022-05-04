#include "Player/PlayerController.hpp"
#include "IParagraph.hpp"
#include "Player/ITextView.hpp"
#include "CaseContainer.hpp"
#include "IAction.hpp"
#include "IQuest.hpp"

#include <assert.h>

using namespace Player;
using namespace QuestCore;

PlayerController::PlayerController(const std::shared_ptr<QuestCore::IQuest>& quest):
    _quest(quest)
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

void PlayerController::SetTextView(const std::shared_ptr<ITextView>& textView)
{
    _textView = textView;
    ViewParagraph();
}

void PlayerController::OpenInventory()
{
    auto& hotKeys = _quest->GetHotKeys();
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
    auto& roots = _quest->GetRoots();
    auto foundIt = roots.find("root");
    if (foundIt == roots.end()) {
        std::shared_ptr<IParagraph>();
    }
    return foundIt->second;
}
