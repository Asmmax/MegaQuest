#pragma once
#include "IAction.hpp"
#include <memory>

namespace QuestCore
{
	class CaseContainerStateMachine;
	class ICaseContainer;

	class CaseContainerSwitching : public IAction
	{
	public:
		void SetStateMachine(CaseContainerStateMachine* stateMachine);
		void SetNextContainer(ICaseContainer* nextContainer);

		virtual void Do() override;
	private:
		CaseContainerStateMachine* _stateMachine;
		ICaseContainer* _nextContainer;
	};
}
