#pragma once
#include "IContainerImpl.hpp"
#include <vector>

template<typename Type>
class Container
{
	using TypePtr = std::shared_ptr<Type>;
	using ContainerImplPtr = std::shared_ptr<IContainerImpl<Type>>;
public:

	void AddInheritor(const ContainerImplPtr& inheritor)
	{
		_inheritors.push_back(inheritor);
	}

	void CreateById(const std::string& id)
	{
		for (auto& inheritor : _inheritors) {
			inheritor->CreateById(id);
		}
	}

	void InitById(const std::string& id)
	{
		for (auto& inheritor : _inheritors) {
			inheritor->InitById(id);
		}
	}

	TypePtr Get(const std::string& id)
	{
		for (auto& inheritor : _inheritors) {
			if (inheritor->Contains(id)) {
				return inheritor->GetBase(id);
			}
		}
		return nullptr;
	}

	TypePtr Get()
	{
		for (auto& inheritor : _inheritors) {
			if (!inheritor->Empty()) {
				return inheritor->GetBase();
			}
		}
		return nullptr;
	}

private:
	std::vector<ContainerImplPtr> _inheritors;
};
