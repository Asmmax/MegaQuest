#pragma once
#include "PropertyReader.hpp"
#include "json.hpp"
#include <functional>

template<typename ElementType, typename ResultType, template<typename> typename ReaderStrategy>
class MethodInitializer : public PropertyReader<ResultType, ReaderStrategy>
{
	using ElementPtr = std::shared_ptr<ElementType>;
	using Callback = std::function<void(const ElementPtr&, const ResultType&)>;
public:
	MethodInitializer(const std::string& property, 
		const ReaderStrategy<ResultType>& reader,
		const ResultType& defValue, 
		const Callback& method) :

		PropertyReader<ResultType, ReaderStrategy>(property, reader, defValue),
		_callback(method)
	{
	}

	void operator()(const ElementPtr& element, const nlohmann::json& node)
	{
		auto result = Create(node);
		Init(node);
		_callback(element, result);
	}

private:
	Callback _callback;
};

// vector specialization
template<typename ElementType, typename Type, template<typename> typename ReaderStrategy>
class MethodInitializer<ElementType, std::vector<Type>, ReaderStrategy> : public PropertyReader<std::vector<Type>, ReaderStrategy>
{
	using ElementPtr = std::shared_ptr<ElementType>;
	using Callback = std::function<void(const ElementPtr&, const std::vector<Type>&)>;
public:
	MethodInitializer(const std::string& property,
		const ReaderStrategy<Type>& reader,
		const std::vector<Type>& defValue,
		const Callback& method) :

		PropertyReader<std::vector<Type>, ReaderStrategy>(property, reader, defValue),
		_callback(method)
	{
	}

	void operator()(const ElementPtr& element, const nlohmann::json& node)
	{
		auto result = Create(node);
		Init(node);
		_callback(element, result);
	}

private:
	Callback _callback;
};