#pragma once
#include "GlobalContext.hpp"

template<typename Type>
class FactoryBinder
{
public:
	FactoryBinder()
		: _factory(GlobalContext::GetFactory<Type>())
	{
	}

	template<typename TypeImpl>
	void BindImpl(const std::shared_ptr<TypeImpl>& impl);

private:
	template<typename FactoryType, typename TypeImpl>
	void BindImplWithCast(const std::shared_ptr<TypeImpl>& impl)
	{
		if (auto factory = std::dynamic_pointer_cast<FactoryType>(_factory)) {
			factory->SetInheritor(impl);
		}
	}
private:
	std::shared_ptr<IFactory<Type>> _factory;
};
