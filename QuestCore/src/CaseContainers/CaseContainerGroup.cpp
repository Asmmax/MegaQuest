#include "CaseContainers/CaseContainerGroup.hpp"

using namespace QuestCore;

void CaseContainerGroup::SetChildren(const std::vector<std::shared_ptr<ICaseContainer>>& children)
{
	_containers = children;
}

void CaseContainerGroup::Clear()
{
	_containers.clear();
}

void CaseContainerGroup::AddCaseContainer(const ICaseContainer::Ptr& container)
{
	_containers.emplace_back(container);
}

void CaseContainerGroup::Print(IButtonGroup& buttons)
{
	for (auto& container : _containers) {
		container->Print(buttons);
	}
}
