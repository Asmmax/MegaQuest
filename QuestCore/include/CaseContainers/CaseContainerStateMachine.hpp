#pragma once
#include "ICaseContainer.hpp"

namespace QuestCore
{
	class CaseContainerStateMachine : public ICaseContainer
	{
	public:
		/// @inject
		void SetState(const ICaseContainer::WeakPtr& newState);

		virtual void Print(IButtonGroup& buttons) override;

	private:
		ICaseContainer::WeakPtr _state;
	};
}
