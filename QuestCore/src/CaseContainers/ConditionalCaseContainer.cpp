#include "CaseContainers/ConditionalCaseContainer.hpp"
#include "ICondition.hpp"

using namespace QuestCore;

ConditionalCaseContainer::ConditionalCaseContainer(
	ICaseContainer* thenContainer,
	ICaseContainer* elseContainer, 
	const std::vector<ICondition*>& conditions):

	_thenContainer(thenContainer),
	_elseContainer(elseContainer),
	_conditions(conditions)
{
}

void ConditionalCaseContainer::Print(IButtonGroup& buttons)
{
    if (IsAllowed()) {
        if (_thenContainer) {
			_thenContainer->Print(buttons);
        }
	}
	else {

		if (_elseContainer) {
			_elseContainer->Print(buttons);
		}
	}
}

void ConditionalCaseContainer::ClearConditions()
{
	_conditions.clear();
}

void ConditionalCaseContainer::AddCondition(ICondition* condition)
{
	_conditions.push_back(condition);
}

bool ConditionalCaseContainer::IsAllowed() const
{
	for (auto& condition : _conditions) {
		if (!condition->IsAllowed()) {
			return false;
		}
	}
	return true;
}
