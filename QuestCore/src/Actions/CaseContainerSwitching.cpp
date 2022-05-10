#include "Actions/CaseContainerSwitching.hpp"
#include "CaseContainers/CaseContainerStateMachine.hpp"

using namespace QuestCore;

CaseContainerSwitching::CaseContainerSwitching(const std::shared_ptr<CaseContainerStateMachine>& stateMachine, const std::shared_ptr<ICaseContainer>& nextContainer) :
	_stateMachine(stateMachine),
	_nextContainer(nextContainer)
{
}

void CaseContainerSwitching::Do()
{
	_stateMachine->SetState(_nextContainer);
}
