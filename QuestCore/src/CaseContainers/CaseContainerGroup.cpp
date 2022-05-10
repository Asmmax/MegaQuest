#include "CaseContainers/CaseContainerGroup.hpp"

using namespace QuestCore;

void CaseContainerGroup::Clear()
{
	_containers.clear();
}

void CaseContainerGroup::AddCaseContainer(const ICaseContainer::Ptr& container)
{
	_containers.emplace_back(container);
}

const std::vector<Case>& CaseContainerGroup::GetCases(const std::string& key) const
{
	_cases.clear();
	for (auto& container : _containers) {
		for (auto _case : container->GetCases(key))
		{
			_cases.emplace_back(_case);
		}
	}
	return _cases;
}

size_t CaseContainerGroup::GetCaseCount() const
{
	size_t sumCaseCount = 0;
	for (auto& container : _containers) {
		sumCaseCount += container->GetCaseCount();
	}
	return sumCaseCount;
}
