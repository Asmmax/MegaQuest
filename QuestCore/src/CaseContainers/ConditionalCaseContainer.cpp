#include "CaseContainers/ConditionalCaseContainer.hpp"
#include "ICondition.hpp"

using namespace QuestCore;

ConditionalCaseContainer::ConditionalCaseContainer(
	const std::shared_ptr<ICaseContainer>& thenContainer,
	const std::shared_ptr<ICaseContainer>& elseContainer, 
	const std::vector<std::shared_ptr<ICondition>>& conditions):

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

void ConditionalCaseContainer::AddCondition(const ICondition::Ptr& condition)
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
