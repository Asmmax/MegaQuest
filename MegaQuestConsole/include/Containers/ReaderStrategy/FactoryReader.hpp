#pragma once
#include "Containers/IReaderStrategy.hpp"
#include "Containers/Factory.hpp"
#include "json.hpp"
#include <memory>
#include <assert.h>

template<typename Type>
class FactoryReader : public IReaderStrategy<Type>
{
	using FactoryPtr = std::weak_ptr<Factory<Type>>;

public:
	FactoryReader(const FactoryPtr& factory) :
		_factory(factory)
	{
	}

	Type Create(const nlohmann::json& node) override
	{
		auto factoryPtr = _factory.lock();
		assert(factoryPtr);
		return factoryPtr->Get(node);
	}

	void Init(const nlohmann::json& node) override
	{
		auto factoryPtr = _factory.lock();
		assert(factoryPtr);
		factoryPtr->InitDependencies(node);
	}

private:
	FactoryPtr _factory;
};
