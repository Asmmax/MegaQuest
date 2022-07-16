#pragma once
#include "ICaseContainer.hpp"

namespace QuestCore
{
	/// @serializable
	class CaseContainerStateMachine : public ICaseContainer
	{
	public:
		/// @inject
		void SetState(const ICaseContainer::WeakPtr& state);

		virtual void Print(IButtonGroup& buttons) override;

	private:
		ICaseContainer::WeakPtr _state;
	};
}
