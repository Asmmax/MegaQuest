#pragma once
#include "Quests/Slot.hpp"
#include "ICaseContainerFactory.hpp"

namespace QuestCore
{
	/// @serializable @shared slots
	class CaseContainerSlot : public ICaseContainerFactory, public Slot<ICaseContainer>
	{
		using Base = Slot<ICaseContainer>;
	public:
		CaseContainerSlot(const QuestPtr& quest);
		CaseContainerPtr GetCaseContainer() const;
	};
}
