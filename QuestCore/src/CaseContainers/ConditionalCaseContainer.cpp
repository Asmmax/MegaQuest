#include "CaseContainers/ConditionalCaseContainer.hpp"
#include "ICondition.hpp"

using namespace QuestCore;

const std::vector<Case>& ConditionalCaseContainer::GetCases(const std::string& key) const
{
    static std::vector<Case> defaultCases;

    if (IsAllowed()) {
        if (!_thenContainer) {
            return defaultCases;
        }
        return _thenContainer->GetCases(key);
    }

    if (!_elseContainer) {
        return defaultCases;
    }
    return _elseContainer->GetCases(key);
}

size_t ConditionalCaseContainer::GetCaseCount() const
{
    if (IsAllowed()) {
        if (!_thenContainer) {
            return 0;
        }
        return _thenContainer->GetCaseCount();
    }

    if (!_elseContainer) {
        return 0;
    }
    return _elseContainer->GetCaseCount();
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