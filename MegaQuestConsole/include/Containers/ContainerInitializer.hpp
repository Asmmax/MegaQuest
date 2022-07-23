#pragma once
#include "Containers/MethodInitializer.hpp"
#include "json.hpp"
#include <tuple>
#include <utility>

template<typename Type, typename... Dependencies>
class ContainerInitializer
{
	using TypePtr = std::shared_ptr<Type>;
public:

	ContainerInitializer(const MethodInitializer<Type, Dependencies>&... methods) :
		_methods(methods...)
	{
	}

	void operator()(const TypePtr& element, const nlohmann::json& node)
	{
		Init(element, node, _methods, std::index_sequence_for<Dependencies...>());
	}

private:
	template<std::size_t... Is>
	void Init(const TypePtr& element, const nlohmann::json& node, std::tuple<MethodInitializer<Type, Dependencies>...>& tuple, std::index_sequence<Is...>) {
		Init(element, node, std::get<Is>(tuple)...);
	}

	template<typename Current, typename... Other>
	void Init(const TypePtr& element, const nlohmann::json& node, MethodInitializer<Type, Current>& method, MethodInitializer<Type,Other>&... methods)
	{
		method(element, node);
		Init(element, node, methods...);
	}

	void Init(const TypePtr& element, const nlohmann::json& node)
	{
	}

private:
	std::tuple<MethodInitializer<Type, Dependencies>...> _methods;
};
