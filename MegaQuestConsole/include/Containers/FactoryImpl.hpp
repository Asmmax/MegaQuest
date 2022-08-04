#pragma once
#include "Containers/PropertyReader.hpp"
#include "Utils/Reader.hpp"
#include <tuple>
#include <utility>

template<typename Base, typename... Dependencies>
class BaseFactoryImpl : public Base
{
public:

	BaseFactoryImpl(const std::string& typeName, const PropertyReader<Dependencies>&... properties) :
		_typeName(typeName),
		_properties(properties...)
	{
	}

	void InitDependencies(const nlohmann::json& node) override
	{
		InitDependencies(node, _properties, std::index_sequence_for<Dependencies...>());
	}

	bool IsSuitType(const std::string& typeName) override
	{
		return _typeName == typeName;
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
	std::string _typeName;
	std::tuple<PropertyReader<Dependencies>...> _properties;
};


template<typename Type, typename Base, typename... Dependencies>
class FactoryImpl : public BaseFactoryImpl<Base, Dependencies...>
{
public:

	FactoryImpl(const std::string& typeName, const PropertyReader<Dependencies>&... properties) :
		BaseFactoryImpl<Base, Dependencies...>(typeName, properties...)
	{
	}

	Type Get(const nlohmann::json& node) override
	{
		return CreateElement(node, _properties, std::index_sequence_for<Dependencies...>());
	}

private:

	template<std::size_t... Is>
	Type CreateElement(const nlohmann::json& node, std::tuple<PropertyReader<Dependencies>...>& tuple, std::index_sequence<Is...>) {
		return Type{ std::get<Is>(tuple).Create(node)... };
	}
};


template<typename Type, typename Base, typename... Dependencies>
class FactoryImpl<std::shared_ptr<Type>, Base, Dependencies...> : public BaseFactoryImpl<Base, Dependencies...>
{
	using TypePtr = std::shared_ptr<Type>;
public:

	FactoryImpl(const std::string& typeName, const PropertyReader<Dependencies>&... properties) :
		BaseFactoryImpl<Base, Dependencies...>(typeName, properties...)
	{
	}

	TypePtr Get(const nlohmann::json& node) override
	{
		return CreateElement(node, _properties, std::index_sequence_for<Dependencies...>());
	}

private:

	template<std::size_t... Is>
	TypePtr CreateElement(const nlohmann::json& node, std::tuple<PropertyReader<Dependencies>...>& tuple, std::index_sequence<Is...>) {
		return std::make_shared<Type>( std::get<Is>(tuple).Create(node)... );
	}
};
