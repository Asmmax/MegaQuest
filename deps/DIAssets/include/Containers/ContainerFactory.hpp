#pragma once
#include <memory>

template < template <typename> typename ContainerType>
class ContainerFactory
{
public:
	template <typename Type>
	static std::shared_ptr<ContainerType<Type>> Create()
	{
		return std::make_shared<ContainerType<Type>> ();
	}
};
