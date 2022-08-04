#pragma once
#include "IContainerImpl.hpp"
#include "IContainer.hpp"
#include <vector>

template<typename Type>
class Container : public IContainer<Type>
{
	using TypePtr = std::shared_ptr<Type>;
	using ContainerImplPtr = std::shared_ptr<IContainerImpl<Type>>;
public:

	void AddInheritor(const ContainerImplPtr& inheritor)
	{
		_inheritors.push_back(inheritor);
	}

	void CreateById(const std::string& id) override
	{
		for (auto& inheritor : _inheritors) {
			inheritor->CreateById(id);
		}
	}

	void InitById(const std::string& id) override
	{
		for (auto& inheritor : _inheritors) {
			inheritor->InitById(id);
		}
	}

	TypePtr Get(const std::string& id) override
	{
		for (auto& inheritor : _inheritors) {
			if (inheritor->Contains(id)) {
				return inheritor->GetBase(id);
			}
		}
		return nullptr;
	}

	TypePtr Get() override
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
