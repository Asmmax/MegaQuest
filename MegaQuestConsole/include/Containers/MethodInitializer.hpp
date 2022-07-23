#pragma once
#include "PropertyReader.hpp"
#include "json.hpp"
#include <functional>

template<typename ElementType, typename ResultType>
class MethodInitializer
{
	using ElementPtr = std::shared_ptr<ElementType>;
	using Callback = std::function<void(const ElementPtr&, const ResultType&)>;
public:
	MethodInitializer(const PropertyReader<ResultType>& propertyReader,
		const Callback& method) :

		_propertyReader(propertyReader),
		_callback(method)
	{
	}

	void operator()(const ElementPtr& element, const nlohmann::json& node)
	{
		auto result = _propertyReader.Create(node);
		_propertyReader.Init(node);
		_callback(element, result);
	}

private:
	PropertyReader<ResultType> _propertyReader;
	Callback _callback;
};
