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
	void BindImpl(const std::string& implName, const std::shared_ptr<TypeImpl>& impl);

private:
	template<typename ContainerType, typename TypeImpl>
	void BindImplWithCast(const std::string& implName, const std::shared_ptr<TypeImpl>& impl)
	{
		if (auto container = std::dynamic_pointer_cast<ContainerType>(_container)) {
			container->SetInheritor(ReaderImplRecord<TypeImpl>{ implName, impl });
		}
	}
private:
	std::shared_ptr<ContainerBase<Type>> _container;
};
