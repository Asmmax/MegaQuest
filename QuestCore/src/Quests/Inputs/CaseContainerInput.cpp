#include "Quests/Inputs/CaseContainerInput.hpp"
#include "Quests/Slots/CaseContainerSlot.hpp"

using namespace QuestCore;

CaseContainerInput::CaseContainerInput(const CaseContainerPtr& container, 
	const CaseContainerSlotPtr& slot,
	const QuestHeaderPtr& quest) :

	Base(container, slot, quest)
{
}
