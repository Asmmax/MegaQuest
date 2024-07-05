#include "CaseContainers/CaseContainerGroup.hpp"

using namespace QuestCore;

CaseContainerGroup::CaseContainerGroup(const std::vector<ICaseContainer*>& children):
	_containers(children)
{
}

void CaseContainerGroup::Clear()
{
	_containers.clear();
}

void CaseContainerGroup::AddCaseContainer(ICaseContainer* container)
{
	_containers.emplace_back(container);
}

void CaseContainerGroup::Print(IButtonGroup& buttons)
{
	for (auto container : _containers) {
		container->Print(buttons);
	}
}
