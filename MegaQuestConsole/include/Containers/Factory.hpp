#pragma once
#include "IFactory.hpp"
#include "Utils/Reader.hpp"
#include "ReaderImplRecord.hpp"
#include <tuple>
#include <utility>

template<typename Type, typename... Impls>
class Factory : public IFactory<Type>
{
	using Inheritors = std::tuple<ReaderImplRecord<Impls>...>;

public:
	void SetInheritors(const ReaderImplRecord<Impls>&... inheritors)
	{
		_inheritors = std::make_tuple(inheritors...);
	}

	Type Get(const nlohmann::json& node) override
	{
		auto typeId = Utils::Read<std::string>(node, "type", std::string());
		return GetImpl(typeId, node, _inheritors, std::index_sequence_for<Impls...>());
	}

	void InitDependencies(const nlohmann::json& node) override
	{
		auto typeId = Utils::Read<std::string>(node, "type", std::string());
		InitDependenciesImpl(typeId, node, _inheritors, std::index_sequence_for<Impls...>());
	}

private:
	template<std::size_t... Is>
	Type GetImpl(const std::string& typeId, const nlohmann::json& node,
		Inheritors& inheritors, std::index_sequence<Is...>)
	{
		return GetImpl(typeId, node, std::get<Is>(inheritors)...);
	}

	template<typename Current, typename... Other>
	Type GetImpl(const std::string& typeId, const nlohmann::json& node, Current& inheritor, Other&... inheritors)
	{
		if (inheritor.type == typeId) {
			return inheritor.impl->Get(node);
		}

		return GetImpl(typeId, node, inheritors...);
	}

	Type GetImpl(const std::string& typeId, const nlohmann::json& node)
	{
		return Type();
	}



	template<std::size_t... Is>
	void InitDependenciesImpl(const std::string& typeId, const nlohmann::json& node,
		Inheritors& inheritors, std::index_sequence<Is...>)
	{
		return InitDependenciesImpl(typeId, node, std::get<Is>(inheritors)...);
	}

	template<typename Current, typename... Other>
	void InitDependenciesImpl(const std::string& typeId, const nlohmann::json& node, Current& inheritor, Other&... inheritors)
	{
		if (inheritor.type == typeId) {
			return inheritor.impl->InitDependencies(node);
		}

		return InitDependenciesImpl(typeId, node, inheritors...);
	}

	void InitDependenciesImpl(const std::string& typeId, const nlohmann::json& node)
	{
	}

private:
	Inheritors _inheritors;
};
