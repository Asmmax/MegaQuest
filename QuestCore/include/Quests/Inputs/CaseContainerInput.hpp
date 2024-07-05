#pragma once
#include "Quests/Input.hpp"

namespace QuestCore
{
	class CaseContainerSlot;
	class ICaseContainer;

	class CaseContainerInput : public Input<ICaseContainer>
	{
		using Base = Input<ICaseContainer>;
	public:
		CaseContainerInput(ICaseContainer* container,
			CaseContainerSlot* slot,
			Quest* quest);
	};
}
