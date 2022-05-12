#pragma once
#include "ICaseContainer.hpp"

namespace QuestCore
{
	class CaseContainerStateMachine : public ICaseContainer
	{
	public:
		virtual void Print(IButtonPanel& buttonPanel) override;

		inline void SetState(const ICaseContainer::Ptr& newState) { _state = newState; }

	private:
		ICaseContainer::Ptr _state;
	};
}
