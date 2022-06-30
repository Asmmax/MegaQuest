#pragma once
#include "Containers/ContainerBase.hpp"
#include "json.hpp"
#include <memory>
#include <assert.h>

template<typename Type>
class ContainerReader;

template<typename Type>
class ContainerReader<std::shared_ptr<Type>>
{
	using TypePtr = std::shared_ptr<Type>;
	using ContainerPtr = std::weak_ptr<ContainerBase<Type>>;

public:
	ContainerReader(const ContainerPtr& container) :
		_container(container)
	{
	}

	TypePtr Create(const nlohmann::json& node)
	{
		auto containerPtr = _container.lock();
		assert(containerPtr);
		auto id = node.get<std::string>();
		containerPtr->CreateById(id);
		return containerPtr->Get(id);
	}

	void Init(const nlohmann::json& node)
	{
		auto containerPtr = _container.lock();
		assert(containerPtr);
		auto id = node.get<std::string>();
		containerPtr->InitById(id);
	}

private:
	ContainerPtr _container;
};
