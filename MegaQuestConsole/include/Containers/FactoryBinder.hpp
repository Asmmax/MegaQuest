#pragma once
#include "Context.hpp"

template<typename Type>
class IFactoryImpl;

template<typename Type>
class FactoryBinder
{
	using FactoryImplPtr = std::shared_ptr<IFactoryImpl<Type>>;
public:
	FactoryBinder()
		: _factory(Context::Global().GetFactory<Type>())
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

#define DECLARE_FACTORY_BIND_IMPL(Type) template<> void FactoryBinder<Type>::BindImpl(const FactoryBinder::FactoryImplPtr& impl);
