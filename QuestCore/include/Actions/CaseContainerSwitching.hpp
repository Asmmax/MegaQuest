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
		/// @inject
		void SetStateMachine(const std::weak_ptr<CaseContainerStateMachine>& stateMachine);
		/// @inject
		void SetNextContainer(const std::weak_ptr<ICaseContainer>& nextContainer);

		virtual void Do() override;
	private:
		std::weak_ptr<CaseContainerStateMachine> _stateMachine;
		std::weak_ptr<ICaseContainer> _nextContainer;
	};
}
