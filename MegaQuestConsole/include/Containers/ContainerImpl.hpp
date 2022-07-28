#pragma once
#include "Containers/IContainerReader.hpp"
#include "Containers/PropertyReader.hpp"
#include "Utils/Reader.hpp"

#include <tuple>
#include <utility>
#include <assert.h>

template<typename Type, typename Initializer, typename... Dependencies>
class ContainerImpl : public IContainerReader
{
	using TypePtr = std::shared_ptr<Type>;
public:

	ContainerImpl(const std::string& groupName, const std::string& typeName, const Initializer& initializer, const PropertyReader<Dependencies>&... properties):
		_groupName(groupName),
		_typeName(typeName),
		_initializer(initializer),
		_properties(properties...)
	{
	}

	void AddRoot(const nlohmann::json& root) override
	{
		auto foundIt = root.find(_groupName);
		if (foundIt == root.end()) {
			return;
		}

		for (auto& node : *foundIt) {
			auto typeId = Utils::Read<std::string>(node, "type", std::string());
			if (typeId == _typeName) {
				_nodes.push_back(node);
			}
		}
	}

	void CreateAll() override
	{
		for (auto& node : _nodes) {
			Create(node);
		}
	}

	void InitAll() override
	{
		for (auto& node : _nodes) {
			Init(node);
		}
	}

	void CreateById(const std::string& id)
	{
		for (auto& child : _nodes) {
			auto childId = Utils::Read(child, "id", std::string());
			if (!childId.empty() && childId == id) {
				Create(child);
			}
		}
	}

	void InitById(const std::string& id)
	{
		for (auto& child : _nodes) {
			auto childId = Utils::Read(child, "id", std::string());
			if (!childId.empty() && childId == id) {
				Init(child);
			}
		}
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

	TypePtr Get()
	{
		auto beg_iter = _elements.begin();
		assert(beg_iter != _elements.end());
		return beg_iter->second;
	}

	bool Contains(const std::string& id)
	{
		return _elements.find(id) != _elements.end();
	}

	bool Empty()
	{
		return _elements.empty();
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
	std::string _groupName;
	std::string _typeName;
	std::map<std::string, TypePtr> _elements;
	std::vector<std::string> _isInited; //оптимизация, исключаем повторное создание структур и unique сущностей
	Initializer _initializer;
	std::tuple<PropertyReader<Dependencies>...> _properties;
	std::vector<nlohmann::json> _nodes;
};
