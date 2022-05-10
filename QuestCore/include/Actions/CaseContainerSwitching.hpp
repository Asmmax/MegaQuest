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
		CaseContainerSwitching(const std::shared_ptr<CaseContainerStateMachine>& stateMachine, const std::shared_ptr<ICaseContainer>& nextContainer);
		virtual void Do() override;
	private:
		std::shared_ptr<CaseContainerStateMachine> _stateMachine;
		std::shared_ptr<ICaseContainer> _nextContainer;
	};
}
