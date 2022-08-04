#pragma once
#include "GlobalContext.hpp"

template<typename Type>
class IContainerImpl;

template<typename Type>
class ContainerBinder
{
	using ContainerImplPtr = std::shared_ptr<IContainerImpl<Type>>;
public:
	ContainerBinder()
		: _container(GlobalContext::GetContainer<Type>())
	{
	}

	void BindImpl(const ContainerImplPtr& impl);

private:
	template<typename ContainerType>
	void BindImplWithCast(const ContainerImplPtr& impl)
	{
		if (auto container = std::dynamic_pointer_cast<ContainerType>(_container)) {
			container->AddInheritor(impl);
		}
	}
private:
	std::shared_ptr<IContainer<Type>> _container;
};
