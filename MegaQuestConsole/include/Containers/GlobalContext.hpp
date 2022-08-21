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

#define DECLARE_CONTAINER(Type) template <> static const std::shared_ptr<IContainer<Type>>& GlobalContext::GetContainer<Type>();

#define DECLARE_FACTORY(Type) template <> static const std::shared_ptr<IFactory<Type>>& GlobalContext::GetFactory<Type>();
