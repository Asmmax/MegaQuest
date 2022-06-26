#pragma once
#include "json.hpp"
#include <tuple>
#include <utility>

template<typename Type, typename... Initializers>
class ContainerInitializer
{
	using TypePtr = std::shared_ptr<Type>;
public:

	ContainerInitializer(const Initializers&... initializers) :
		_initializers(initializers...)
	{
	}

	void operator()(const TypePtr& element, const nlohmann::json& node)
	{
		Init(element, node, _initializers, std::index_sequence_for<Initializers...>());
	}

private:
	template<std::size_t... Is>
	void Init(const TypePtr& element, const nlohmann::json& node, std::tuple<Initializers...>& tuple, std::index_sequence<Is...>) {
		Init(element, node, std::get<Is>(tuple)...);
	}

	template<typename Current, typename... Other>
	void Init(const TypePtr& element, const nlohmann::json& node, Current& initializer, Other&... initializers)
	{
		initializer(element, node);
		Init(element, node, initializers...);
	}

	void Init(const TypePtr& element, const nlohmann::json& node)
	{
	}

private:
	std::tuple<Initializers...> _initializers;
};
