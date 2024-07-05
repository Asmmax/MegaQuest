#include "Quests/Inputs/CaseContainerInput.hpp"
#include "Quests/Slots/CaseContainerSlot.hpp"

using namespace QuestCore;

CaseContainerInput::CaseContainerInput(ICaseContainer* container, 
	CaseContainerSlot* slot,
	Quest* quest) :

	Base(container, slot, quest)
{
}
