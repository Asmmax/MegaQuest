#pragma once
#include "Containers/IReaderStrategy.hpp"
#include "Containers/Container.hpp"
#include <memory>
#include <assert.h>

template<typename Type>
class ContainerReader;

template<typename Type>
class ContainerReader<std::shared_ptr<Type>> : public IReaderStrategy<std::shared_ptr<Type>>
{
	using TypePtr = std::shared_ptr<Type>;
	using ContainerPtr = std::weak_ptr<Container<Type>>;

public:
	ContainerReader(const ContainerPtr& container) :
		_container(container)
	{
	}

	TypePtr Create(const nlohmann::json& node) override
	{
		auto containerPtr = _container.lock();
		assert(containerPtr);
		auto id = node.get<std::string>();
		containerPtr->CreateById(id);
		return containerPtr->Get(id);
	}

	void Init(const nlohmann::json& node) override
	{
		auto containerPtr = _container.lock();
		assert(containerPtr);
		auto id = node.get<std::string>();
		containerPtr->InitById(id);
	}

private:
	ContainerPtr _container;
};
