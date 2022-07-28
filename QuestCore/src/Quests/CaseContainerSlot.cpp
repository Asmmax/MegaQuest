#include "Quests/CaseContainerSlot.hpp"
#include "Quests/CaseContainerInput.hpp"

using namespace QuestCore;

void CaseContainerSlot::Update()
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
