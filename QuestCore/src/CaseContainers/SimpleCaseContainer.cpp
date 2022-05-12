#include "CaseContainers/SimpleCaseContainer.hpp"
#include "IButtonPanel.hpp"

using namespace QuestCore;

void SimpleCaseContainer::Print(IButtonPanel& buttonPanel)
{
	for (auto& caseList : _cases) {
		auto& buttonContainer = buttonPanel.GetButtonGroup(caseList.first);
		for (auto& _case : caseList.second) {
			buttonContainer.AddButton(_case.name, [_case = _case]() mutable { 
				_case.Do(); });
		}
	}
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
