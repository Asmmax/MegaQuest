#include "Quests/Slots/CaseContainerSlot.hpp"
#include "Quests/Slots/CaseContainerInput.hpp"

using namespace QuestCore;

CaseContainerSlot::CaseContainerSlot(const QuestHeaderPtr& quest):
	QuestInitable(quest)
{
}

void CaseContainerSlot::Init()
{
	_input = nullptr;
}

void CaseContainerSlot::SetInput(CaseContainerInput* input)
{
	_input = input;
}

CaseContainerSlot::CaseContainerPtr CaseContainerSlot::GetCaseContainer() const
{
	if (!_input) {
		return nullptr;
	}
	return _input->GetCaseContainer();
}
