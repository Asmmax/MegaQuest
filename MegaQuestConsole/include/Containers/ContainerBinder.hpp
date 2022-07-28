#pragma once
#include "GlobalContext.hpp"

template<typename Type>
class ContainerBinder
{
public:
	ContainerBinder()
		: _container(GlobalContext::GetContainer<Type>())
	{
	}

	template<typename TypeImpl>
	void BindImpl(const std::shared_ptr<TypeImpl>& impl);

private:
	template<typename ContainerType, typename TypeImpl>
	void BindImplWithCast(const std::shared_ptr<TypeImpl>& impl)
	{
		if (auto container = std::dynamic_pointer_cast<ContainerType>(_container)) {
			container->SetInheritor(impl);
		}
	}
private:
	std::shared_ptr<IContainer<Type>> _container;
};
