#include "Quests/Slots/CaseContainerInput.hpp"
#include "Quests/Slots/CaseContainerSlot.hpp"

using namespace QuestCore;

CaseContainerInput::CaseContainerInput(const CaseContainerPtr& container, const CaseContainerSlotPtr& slot) :
	_container(container),
	_slot(slot)
{
}

void CaseContainerInput::Update()
{
	_slot->SetInput(this);
}

CaseContainerInput::CaseContainerPtr CaseContainerInput::GetCaseContainer() const
{
	return _container;
}
