#pragma once
#include "IContainer.hpp"
#include <tuple>
#include <utility>

template<typename Type, typename... Impls>
class Container : public IContainer<Type>
{
	using TypePtr = std::shared_ptr<Type>;
	using Inheritors = std::tuple<std::shared_ptr<Impls>...>;

public:
	void SetInheritors(const std::shared_ptr<Impls>&... inheritors)
	{
		_inheritors = std::make_tuple(inheritors...);
	}

	template<typename T>
	void SetInheritor(const std::shared_ptr<T>& inheritor)
	{
		SetInheritorImpl(inheritor, _inheritors, std::index_sequence_for<Impls...>());
	}

	void CreateById(const std::string& id) override
	{
		CreateByIdImpl(id, _inheritors, std::index_sequence_for<Impls...>());
	}

	void InitById(const std::string& id) override
	{
		InitByIdImpl(id, _inheritors, std::index_sequence_for<Impls...>());
	}

	TypePtr Get(const std::string& id) override
	{
		return GetImpl(id, _inheritors, std::index_sequence_for<Impls...>());
	}

	TypePtr Get() override
	{
		return GetImpl(_inheritors, std::index_sequence_for<Impls...>());
	}

private:

	template<typename T, std::size_t... Is>
	void SetInheritorImpl(const std::shared_ptr<T>& inheritor,	Inheritors& inheritors, std::index_sequence<Is...>)
	{
		SetInheritorImpl(inheritor, std::get<Is>(inheritors)...);
	}

	template<typename T, typename Current, typename... Other>
	void SetInheritorImpl(const std::shared_ptr<T>& inheritor, std::shared_ptr<Current>& currentInheritor, std::shared_ptr<Other>&... inheritors)
	{
		SetInheritorImpl(inheritor, inheritors...);
	}

	template<typename T, typename... Other>
	void SetInheritorImpl(const std::shared_ptr<T>& inheritor, std::shared_ptr<T>& currentInheritor, std::shared_ptr<Other>&... inheritors)
	{
		currentInheritor = inheritor;
	}

	template<typename T>
	void SetInheritorImpl(const std::shared_ptr<T>& inheritor)
	{
		static_assert(false);
	}





	template<std::size_t... Is>
	void CreateByIdImpl(const std::string& id,
		Inheritors& inheritors, std::index_sequence<Is...>)
	{
		CreateByIdImpl(id, std::get<Is>(inheritors)...);
	}

	template<typename Current, typename... Other>
	void CreateByIdImpl(const std::string& id, Current& inheritor, Other&... inheritors)
	{
		inheritor->CreateById(id);
		CreateByIdImpl(id, inheritors...);
	}

	void CreateByIdImpl(const std::string& id)
	{
	}





	template<std::size_t... Is>
	void InitByIdImpl(const std::string& id,
		Inheritors& inheritors, std::index_sequence<Is...>)
	{
		InitByIdImpl(id, std::get<Is>(inheritors)...);
	}

	template<typename Current, typename... Other>
	void InitByIdImpl(const std::string& id, Current& inheritor, Other&... inheritors)
	{
		inheritor->InitById(id);
		InitByIdImpl(id, inheritors...);
	}

	void InitByIdImpl(const std::string& id)
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
		if (inheritor->Contains(id)) {
			return inheritor->Get(id);
		}

		return GetImpl(id, inheritors...);
	}

	TypePtr GetImpl(const std::string& id)
	{
		return nullptr;
	}




	template<std::size_t... Is>
	TypePtr GetImpl(Inheritors& inheritors, std::index_sequence<Is...>)
	{
		return GetImpl(std::get<Is>(inheritors)...);
	}

	template<typename Current, typename... Other>
	TypePtr GetImpl(Current& inheritor, Other&... inheritors)
	{
		if (!inheritor->Empty()) {
			return inheritor->Get();
		}

		return GetImpl(inheritors...);
	}

	TypePtr GetImpl()
	{
		return nullptr;
	}

private:
	Inheritors _inheritors;
};
