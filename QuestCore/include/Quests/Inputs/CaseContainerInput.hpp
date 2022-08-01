#pragma once
#include "Quests/Input.hpp"

namespace QuestCore
{
	class CaseContainerSlot;
	class ICaseContainer;

	/// @serializable @shared inputs
	class CaseContainerInput : public Input<ICaseContainer>
	{
		using Base = Input<ICaseContainer>;
		using CaseContainerSlotPtr = std::shared_ptr<CaseContainerSlot>;
		using CaseContainerPtr = std::shared_ptr<ICaseContainer>;
	public:
		CaseContainerInput(const CaseContainerPtr& container,
			const CaseContainerSlotPtr& slot,
			const QuestHeaderPtr& quest);
	};
}
