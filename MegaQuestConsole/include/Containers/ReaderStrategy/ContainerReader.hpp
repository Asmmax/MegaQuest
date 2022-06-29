#pragma once
#include "Containers/ContainerBase.hpp"
#include "json.hpp"
#include <memory>
#include <assert.h>

template<typename Type, typename ResultType = Type>
class ContainerReader;

template<typename Type, typename ResultType>
class ContainerReader<std::shared_ptr<Type>, std::shared_ptr<ResultType>>
{
	using ContainerPtr = std::weak_ptr<ContainerBase<Type>>;
	using ResultTypePtr = std::shared_ptr<ResultType>;
public:
	ContainerReader(const ContainerPtr& container) :
		_container(container)
	{
	}

	ResultTypePtr Create(const nlohmann::json& node)
	{
		auto containerPtr = _container.lock();
		assert(containerPtr);
		auto id = node.get<std::string>();
		containerPtr->CreateById(id);
		return std::dynamic_pointer_cast<ResultType>(containerPtr->Get(id));
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
