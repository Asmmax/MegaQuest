#pragma once
#include "Containers/IFactory.hpp"
#include "json.hpp"
#include <memory>
#include <assert.h>

template<typename Type>
class FactoryReader
{
	using FactoryPtr = std::weak_ptr<IFactory<Type>>;

public:
	FactoryReader(const FactoryPtr& factory) :
		_factory(factory)
	{
	}

	Type Create(const nlohmann::json& node)
	{
		auto factoryPtr = _factory.lock();
		assert(factoryPtr);
		return factoryPtr->Get(node);
	}

	void Init(const nlohmann::json& /*node*/)
	{
	}

private:
	FactoryPtr _factory;
};
