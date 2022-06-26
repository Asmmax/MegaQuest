#pragma once
#include "Utils/Reader.hpp"
#include <tuple>
#include <utility>

template<typename Type, typename Initializer, typename... Readers>
class ContainerImpl
{
	using TypePtr = std::shared_ptr<Type>;
public:

	ContainerImpl(const Initializer& initializer, const Readers&... readers):
		_initializer(initializer),
		_readers(readers...)
	{
	}

	void Create(const nlohmann::json& node)
	{
		auto id = Utils::Read<std::string>(node, "id", std::string());
		if (Contains(id)) {
			return;
		}

		auto result = CreateElement(node, _readers, std::index_sequence_for<Readers...>());
		Register(id, result);
	}

	void Init(const nlohmann::json& node)
	{
		InitDependencies(node, _readers, std::index_sequence_for<Readers...>());
		auto id = Utils::Read<std::string>(node, "id", std::string());
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
	TypePtr CreateElement(const nlohmann::json& node, std::tuple<Readers...>& tuple, std::index_sequence<Is...>) {
		return std::make_shared<Type>(std::get<Is>(tuple).Create(node)...);
	}

	template<std::size_t... Is>
	void InitDependencies(const nlohmann::json& node, std::tuple<Readers...>& tuple, std::index_sequence<Is...>) {
		InitChildren(node, std::get<Is>(tuple)...);
	}

	template<typename Current, typename... Other>
	void InitChildren(const nlohmann::json& node, Current& reader, Other&... readers)
	{
		reader.Init(node);
		InitChildren(node, readers...);
	}

	void InitChildren(const nlohmann::json& node)
	{
	}

private:
	std::map<std::string, TypePtr> _elements;
	Initializer _initializer;
	std::tuple<Readers...> _readers;
};
