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

void CaseContainerGroup::Print(IButtonPanel& buttonPanel)
{
	for (auto& container : _containers) {
		container->Print(buttonPanel);
	}
}
