#pragma once
#include "Quests/Slot.hpp"
#include "ICaseContainerFactory.hpp"

namespace QuestCore
{
	class CaseContainerSlot : public ICaseContainerFactory, public Slot<ICaseContainer>
	{
		using Base = Slot<ICaseContainer>;
	public:
		CaseContainerSlot(Quest* quest);
		ICaseContainer* GetCaseContainer() const;
	};
}
