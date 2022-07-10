#pragma once
#include "Containers/PropertyReader.hpp"
#include "Utils/Reader.hpp"
#include <tuple>
#include <utility>

template<typename Type, typename Initializer, typename... Dependencies>
class ContainerImpl
{
	using TypePtr = std::shared_ptr<Type>;
public:

	ContainerImpl(const Initializer& initializer, const PropertyReader<Dependencies>&... properties):
		_initializer(initializer),
		_properties(properties...)
	{
	}

	void Create(const nlohmann::json& node)
	{
		auto id = Utils::Read<std::string>(node, "id", std::string());
		if (Contains(id)) {
			return;
		}

		auto result = CreateElement(node, _properties, std::index_sequence_for<Dependencies...>());
		Register(id, result);
	}

	void Init(const nlohmann::json& node)
	{
		auto id = Utils::Read<std::string>(node, "id", std::string());
		if (std::find(_isInited.begin(), _isInited.end(), id) != _isInited.end()) {
			return;
		}
		_isInited.emplace_back(id);

		InitDependencies(node, _properties, std::index_sequence_for<Dependencies...>());
		auto element = Get(id);
		_initializer(element, node);
	}

	TypePtr Get(const std::string& id)
	{
		return _elements[id];
	}

	bool Contains(const std::string& id)
	{
		return _elements.find(id) != _elements.end();
	}

private:
	void Register(const std::string& id, const TypePtr& element) 
	{
		_elements.emplace(id, element);
	}

	template<std::size_t... Is>
	TypePtr CreateElement(const nlohmann::json& node, std::tuple<PropertyReader<Dependencies>...>& tuple, std::index_sequence<Is...>) {
		return std::make_shared<Type>(std::get<Is>(tuple).Create(node)...);
	}

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

private:
	std::map<std::string, TypePtr> _elements;
	std::vector<std::string> _isInited; //оптимизация, исключаем повторное создание структур и unique сущностей
	Initializer _initializer;
	std::tuple<PropertyReader<Dependencies>...> _properties;
};
