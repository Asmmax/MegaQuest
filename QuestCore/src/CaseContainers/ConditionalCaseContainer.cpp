#include "CaseContainers/ConditionalCaseContainer.hpp"
#include "ICondition.hpp"

using namespace QuestCore;

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

void ConditionalCaseContainer::SetThenContainer(const ICaseContainer::Ptr& thenContainer)
{
    _thenContainer = thenContainer;
}

void ConditionalCaseContainer::SetElseContainer(const ICaseContainer::Ptr& elseContainer)
{
	_elseContainer = elseContainer;
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
