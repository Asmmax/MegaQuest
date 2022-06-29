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

	template<typename T>
	void SetInheritor(const ReaderImplRecord<T>& inheritor)
	{
		SetInheritorImpl(inheritor, _inheritors, std::index_sequence_for<Impls...>());
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
	template<typename T, std::size_t... Is>
	void SetInheritorImpl(const ReaderImplRecord<T>& inheritor, Inheritors& inheritors, std::index_sequence<Is...>)
	{
		SetInheritorImpl(inheritor, std::get<Is>(inheritors)...);
	}

	template<typename T, typename Current, typename... Other>
	void SetInheritorImpl(const ReaderImplRecord<T>& inheritor, ReaderImplRecord<Current>& currentInheritor, ReaderImplRecord<Other>&... inheritors)
	{
		SetInheritorImpl(inheritor, inheritors...);
	}

	template<typename T, typename... Other>
	void SetInheritorImpl(const ReaderImplRecord<T>& inheritor, ReaderImplRecord<T>& currentInheritor, ReaderImplRecord<Other>&... inheritors)
	{
		currentInheritor = inheritor;
	}

	template<typename T>
	void SetInheritorImpl(const ReaderImplRecord<T>& inheritor)
	{
		static_assert(false);
	}


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
