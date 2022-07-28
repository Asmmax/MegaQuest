#pragma once
#include "IContainer.hpp"
#include "IFactory.hpp"
#include <memory>

class GlobalContext
{
public:
	template <typename Type>
	static const std::shared_ptr<IContainer<Type>>& GetContainer();

	template <typename Type>
	static const std::shared_ptr<IFactory<Type>>& GetFactory();
};
