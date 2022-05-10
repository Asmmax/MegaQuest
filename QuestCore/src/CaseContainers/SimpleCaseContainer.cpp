#include "CaseContainers/SimpleCaseContainer.hpp"

using namespace QuestCore;

const std::vector<Case>& SimpleCaseContainer::GetCases(const std::string& key) const
{
	return _cases[key];
}

size_t SimpleCaseContainer::GetCaseCount() const
{
	return _cases[""].size();
}

void SimpleCaseContainer::Clear()
{
	_cases.clear();
}

void SimpleCaseContainer::AddCase(const Case& _case)
{
	_cases[""].push_back(_case);
}

void SimpleCaseContainer::AddCase(const std::string& key, const Case& _case)
{
	_cases[key].push_back(_case);
}
