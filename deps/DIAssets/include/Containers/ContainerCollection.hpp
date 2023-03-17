#pragma once
#include "ContainerFactory.hpp"
#include <memory>
#include <string>
#include <map>

template <template <typename> typename ContainerType, typename Type>
class ContainerCollection
{
	using ContainerPtr = std::shared_ptr<ContainerType<Type>>;
public:
	ContainerPtr GetContainer(const std::string & id)
	{
		if (_containers.find(id) == _containers.end()) {
			auto newContainer = ContainerFactory<ContainerType>::Create<Type>();
			_containers.emplace(id, newContainer);
		}
		return _containers[id];
	}
private:
	std::map<std::string, ContainerPtr> _containers;
};
