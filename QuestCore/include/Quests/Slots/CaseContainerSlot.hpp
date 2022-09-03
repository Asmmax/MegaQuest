#pragma once
#include "Quests/Slot.hpp"

namespace QuestCore
{
	class ICaseContainer;

	/// @serializable @shared slots
	class CaseContainerSlot : public Slot<ICaseContainer>
	{
		using Base = Slot<ICaseContainer>;
		using CaseContainerPtr = std::shared_ptr<ICaseContainer>;
	public:
		CaseContainerSlot(const QuestPtr& quest);
		CaseContainerPtr GetCaseContainer() const;
	};
}
