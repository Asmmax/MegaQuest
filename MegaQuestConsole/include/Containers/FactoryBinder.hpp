#pragma once
#include "GlobalContext.hpp"

template<typename Type>
class IFactoryImpl;

template<typename Type>
class FactoryBinder
{
	using FactoryImplPtr = std::shared_ptr<IFactoryImpl<Type>>;
public:
	FactoryBinder()
		: _factory(GlobalContext::GetFactory<Type>())
	{
	}

	void BindImpl(const FactoryImplPtr& impl);

private:
	template<typename FactoryType>
	void BindImplWithCast(const FactoryImplPtr& impl)
	{
		if (auto factory = std::dynamic_pointer_cast<FactoryType>(_factory)) {
			factory->AddInheritor(impl);
		}
	}
private:
	std::shared_ptr<IFactory<Type>> _factory;
};
