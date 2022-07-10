#pragma once
#include "Containers/PropertyReader.hpp"
#include "Utils/Reader.hpp"
#include <tuple>
#include <utility>

template<typename... Dependencies>
class FactoryImplBase
{
public:

	FactoryImplBase(const PropertyReader<Dependencies>&... properties) :
		_properties(properties...)
	{
	}

	void InitDependencies(const nlohmann::json& node)
	{
		InitDependencies(node, _properties, std::index_sequence_for<Dependencies...>());
	}

private:

	template<std::size_t... Is>
	void InitDependencies(const nlohmann::json& node, std::tuple<PropertyReader<Dependencies>...>& tuple, std::index_sequence<Is...>) {
		InitChildren(node, std::get<Is>(tuple)...);
	}

	template<typename Current, typename... Other>
	void InitChildren(const nlohmann::json& node, PropertyReader<Current>& property, PropertyReader<Other>&... properties)
	{
		property.Init(node);
		InitChildren(node, properties...);
	}

	void InitChildren(const nlohmann::json& node)
	{
	}

protected:
	std::tuple<PropertyReader<Dependencies>...> _properties;
};


template<typename Type, typename... Dependencies>
class FactoryImpl : public FactoryImplBase<Dependencies...>
{
public:

	FactoryImpl(const PropertyReader<Dependencies>&... properties) :
		FactoryImplBase<Dependencies...>(properties...)
	{
	}

	Type Get(const nlohmann::json& node)
	{
		return CreateElement(node, _properties, std::index_sequence_for<Dependencies...>());
	}

private:

	template<std::size_t... Is>
	Type CreateElement(const nlohmann::json& node, std::tuple<PropertyReader<Dependencies>...>& tuple, std::index_sequence<Is...>) {
		return Type{ std::get<Is>(tuple).Create(node)... };
	}
};


template<typename Type, typename... Dependencies>
class FactoryImpl<std::shared_ptr<Type>, Dependencies...> : public FactoryImplBase<Dependencies...>
{
	using TypePtr = std::shared_ptr<Type>;
public:

	FactoryImpl(const PropertyReader<Dependencies>&... properties) :
		FactoryImplBase<Dependencies...>(properties...)
	{
	}

	TypePtr Get(const nlohmann::json& node)
	{
		return CreateElement(node, _properties, std::index_sequence_for<Dependencies...>());
	}

private:

	template<std::size_t... Is>
	TypePtr CreateElement(const nlohmann::json& node, std::tuple<PropertyReader<Dependencies>...>& tuple, std::index_sequence<Is...>) {
		return std::make_shared<Type>( std::get<Is>(tuple).Create(node)... );
	}
};
