#pragma once
#include "Utils/Reader.hpp"
#include <tuple>
#include <utility>

template<typename... Readers>
class FactoryImplBase
{
public:

	FactoryImplBase(const Readers&... readers) :
		_readers(readers...)
	{
	}

	void InitDependencies(const nlohmann::json& node)
	{
		InitDependencies(node, _readers, std::index_sequence_for<Readers...>());
	}

private:

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

protected:
	std::tuple<Readers...> _readers;
};


template<typename Type, typename... Readers>
class FactoryImpl : public FactoryImplBase<Readers...>
{
public:

	FactoryImpl(const Readers&... readers) :
		FactoryImplBase<Readers...>(readers...)
	{
	}

	Type Get(const nlohmann::json& node)
	{
		return CreateElement(node, _readers, std::index_sequence_for<Readers...>());
	}

private:

	template<std::size_t... Is>
	Type CreateElement(const nlohmann::json& node, std::tuple<Readers...>& tuple, std::index_sequence<Is...>) {
		return Type{ std::get<Is>(tuple).Create(node)... };
	}
};


template<typename Type, typename... Readers>
class FactoryImpl<std::shared_ptr<Type>, Readers...> : public FactoryImplBase<Readers...>
{
	using TypePtr = std::shared_ptr<Type>;
public:

	FactoryImpl(const Readers&... readers) :
		FactoryImplBase<Readers...>(readers...)
	{
	}

	TypePtr Get(const nlohmann::json& node)
	{
		return CreateElement(node, _readers, std::index_sequence_for<Readers...>());
	}

private:

	template<std::size_t... Is>
	TypePtr CreateElement(const nlohmann::json& node, std::tuple<Readers...>& tuple, std::index_sequence<Is...>) {
		return std::make_shared<Type>( std::get<Is>(tuple).Create(node)... );
	}
};
