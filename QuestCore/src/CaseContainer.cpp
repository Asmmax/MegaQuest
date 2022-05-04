#include "CaseContainer.hpp"

using namespace QuestCore;

void CaseContainer::Clear()
{
	_cases.clear();
}

size_t CaseContainer::GetCaseCount() const
{
	size_t count = 0;
	for (auto& caseList : _cases) {
		count += caseList.second.size();
	}
	return count;
}

void CaseContainer::AddCase(const Case& _case)
{
	_cases[""].push_back(_case);
}

void CaseContainer::AddCase(const std::string& key, const Case& _case)
{
	_cases[key].push_back(_case);
}

const std::vector<Case>& CaseContainer::GetCases(const std::string& key) const
{
	return _cases[key];
}

CaseContainer& CaseContainer::operator+=(const CaseContainer& other)
{
	for (auto& caseList : other._cases) {
		for (auto& _case : caseList.second) {
			_cases[caseList.first].push_back(_case);
		}
	}
	return *this;
}

