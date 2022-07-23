#pragma once
#include "ContainerBase.hpp"
#include "IFactory.hpp"
#include <memory>

class GlobalContext
{
public:
	template <typename Type>
	static const std::shared_ptr<ContainerBase<Type>>& GetContainer();

	template <typename Type>
	static const std::shared_ptr<IFactory<Type>>& GetFactory();
};
