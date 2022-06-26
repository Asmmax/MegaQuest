#pragma once
#include "ContainerBase.hpp"
#include "ReaderImplRecord.hpp"
#include <tuple>
#include <utility>

template<typename Type, typename... Impls>
class Container : public ContainerBase<Type>
{
	using TypePtr = std::shared_ptr<Type>;
	using Inheritors = std::tuple<ReaderImplRecord<Impls>...>;

public:
	Container(const std::string& groupName) :
		ContainerBase<Type>(groupName)
	{
	}

	void SetInheritors(const ReaderImplRecord<Impls>&... inheritors)
	{
		_inheritors = std::make_tuple(inheritors...);
	}

	void Create(const nlohmann::json& node) override
	{
		auto id = Utils::Read<std::string>(node, "id", std::string());
		auto typeId = Utils::Read<std::string>(node, "type", std::string());
		CreateImpl(typeId, node, _inheritors, std::index_sequence_for<Impls...>());
	}

	void Init(const nlohmann::json& node) override
	{
		auto typeId = Utils::Read<std::string>(node, "type", std::string());
		InitImpl(typeId, node, _inheritors, std::index_sequence_for<Impls...>());
	}

	TypePtr Get(const std::string& id) override
	{
		return GetImpl(id, _inheritors, std::index_sequence_for<Impls...>());
	}

private:

	template<std::size_t... Is>
	void CreateImpl(const std::string& typeId, const nlohmann::json& node, 
		Inheritors& inheritors, std::index_sequence<Is...>)
	{
		CreateImpl(typeId, node, std::get<Is>(inheritors)...);
	}

	template<typename Current, typename... Other>
	void CreateImpl(const std::string& typeId, const nlohmann::json& node, Current& inheritor, Other&... inheritors)
	{
		if (inheritor.type == typeId) {
			inheritor.impl->Create(node);
			return;
		}

		CreateImpl(typeId, node, inheritors...);
	}

	void CreateImpl(const std::string& typeId, const nlohmann::json& node)
	{
	}




	template<std::size_t... Is>
	void InitImpl(const std::string& typeId, const nlohmann::json& node,
		Inheritors& inheritors, std::index_sequence<Is...>)
	{
		InitImpl(typeId, node, std::get<Is>(inheritors)...);
	}

	template<typename Current, typename... Other>
	void InitImpl(const std::string& typeId, const nlohmann::json& node, Current& inheritor, Other&... inheritors)
	{
		if (inheritor.type == typeId) {
			inheritor.impl->Init(node);
			return;
		}

		InitImpl(typeId, node, inheritors...);
	}

	void InitImpl(const std::string& typeId, const nlohmann::json& node)
	{
	}




	template<std::size_t... Is>
	TypePtr GetImpl(const std::string& id,
		Inheritors& inheritors, std::index_sequence<Is...>)
	{
		return GetImpl(id, std::get<Is>(inheritors)...);
	}

	template<typename Current, typename... Other>
	TypePtr GetImpl(const std::string& id, Current& inheritor, Other&... inheritors)
	{
		if (inheritor.impl->Contains(id)) {
			return inheritor.impl->Get(id);
		}

		return GetImpl(id, inheritors...);
	}

	TypePtr GetImpl(const std::string& id)
	{
		return nullptr;
	}

private:
	Inheritors _inheritors;
};
