#pragma once
#include "Utils/Reader.hpp"
#include <tuple>
#include <utility>

template<typename Type, typename... Readers>
class FactoryImpl
{
public:

	FactoryImpl(const Readers&... readers) :
		_readers(readers...)
	{
	}

	Type Get(const nlohmann::json& node)
	{
		auto result = CreateElement(node, _readers, std::index_sequence_for<Readers...>());
		InitDependencies(node, _readers, std::index_sequence_for<Readers...>());
		return result;
	}

private:

	template<std::size_t... Is>
	Type CreateElement(const nlohmann::json& node, std::tuple<Readers...>& tuple, std::index_sequence<Is...>) {
		return Type{ std::get<Is>(tuple).Create(node)... };
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
	std::tuple<Readers...> _readers;
};


template<typename Type, typename... Readers>
class FactoryImpl<std::shared_ptr<Type>, Readers...>
{
	using TypePtr = std::shared_ptr<Type>;
public:

	FactoryImpl(const Readers&... readers) :
		_readers(readers...)
	{
	}

	TypePtr Get(const nlohmann::json& node)
	{
		auto result = CreateElement(node, _readers, std::index_sequence_for<Readers...>());
		InitDependencies(node, _readers, std::index_sequence_for<Readers...>());
		return result;
	}

private:

	template<std::size_t... Is>
	TypePtr CreateElement(const nlohmann::json& node, std::tuple<Readers...>& tuple, std::index_sequence<Is...>) {
		return std::make_shared<Type>( std::get<Is>(tuple).Create(node)... );
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
	std::tuple<Readers...> _readers;
};
