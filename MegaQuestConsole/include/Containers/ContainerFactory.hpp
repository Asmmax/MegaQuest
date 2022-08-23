#pragma once
#include <memory>

template < template <typename> typename ContainerType>
class ContainerFactory
{
public:
	template <typename Type>
	static std::shared_ptr<ContainerType<Type>> Create();
};

template <typename> class IContainer;
#define DECLARE_CONTAINER(Type) template <> template <> static std::shared_ptr<IContainer<Type>> ContainerFactory<IContainer>::Create<Type>();

template <typename> class IFactory;
#define DECLARE_FACTORY(Type) template <> template <> static std::shared_ptr<IFactory<Type>> ContainerFactory<IFactory>::Create<Type>();
