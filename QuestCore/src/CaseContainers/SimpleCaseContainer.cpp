#include "CaseContainers/SimpleCaseContainer.hpp"
#include "IButtonGroup.hpp"

using namespace QuestCore;

void SimpleCaseContainer::Print(IButtonGroup& buttons)
{
	for (auto& _case : _cases) {
		buttons.AddButton(_case.name, [_case = _case]() mutable {
			_case.Do(); });
	}
}

void SimpleCaseContainer::Clear()
{
	_cases.clear();
}

void SimpleCaseContainer::AddCase(const Case& _case)
{
	_cases.push_back(_case);
}
